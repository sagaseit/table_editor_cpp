#include "CImport.h"
#include "CString.h"
#include "CNum.h"
#include "CString.h"
#include <fstream>
#include <iostream>
#include <cstring>

using std::system_error;
using std::logic_error;
using std::shared_ptr;
using std::ifstream;
using std::make_shared;
using std::make_pair;
using std::getline;
using std::strncpy;
using std::strtok;
using std::endl;
using std::cout;
using std::cin;

void CImport::importFile(const string& str, map<pair<int, int>, shared_ptr<CCell>>& m_table) {
    ifstream file(str);
    if (!file.is_open()) {
        throw logic_error("File cannot be opened!");
    }

    string table_char;
    int x_coor = -1, y_coor = -1;
    bool is_empty;

    while (getline(file, table_char)) {
        if (table_char[0] == '+') {
            x_coor++;
        } else if (table_char[0] == '|') {
            y_coor = -1;
            char* new_line = new char[table_char.size() + 1];
            strncpy(new_line, table_char.c_str(), table_char.size() + 1);
            const char* token = "|";

            char* cell_token = strtok(new_line, token);
            y_coor++;
            if (x_coor == 0) {
                while (cell_token) {
                    cell_token = strtok(nullptr, token);
                    y_coor++;
                }
            } else {
                while (cell_token) {
                    if (y_coor == 0) {
                        cell_token = strtok(nullptr, token);
                        y_coor++;
                    }
                    if (y_coor != 0) {
                        is_empty = true;
                        while (*cell_token != '=') {
                            if (isblank(*cell_token)) {
                                // Do nothing
                            } else if (isdigit(*cell_token) || *cell_token == '-') {
                                string num;
                                while (isdigit(*cell_token) || *cell_token == '.' || *cell_token == '-') {
                                    num += *cell_token;
                                    cell_token++;
                                }
                                double number = std::stod(num);
                                m_table.emplace(make_pair(y_coor, x_coor), make_shared<CNum>(number));

                                is_empty = false;
                                cell_token--;
                            } else if (*cell_token == '"') {
                                char* str_tmp = cell_token++;
                                while (*cell_token != '"') {
                                    cell_token++;
                                }
                                string m_str(str_tmp, cell_token++);
                                m_table.emplace(make_pair(y_coor, x_coor), make_shared<CString>(m_str));
                                is_empty = false;
                                cell_token--;
                            } else if (*cell_token == 0) {
                                break;
                            } else {
                                throw logic_error("Error occurred here");
                            }
                            cell_token++;
                        }
                        if (is_empty) {
                            m_table.emplace(make_pair(y_coor, x_coor), make_shared<CNum>());
                        } else {
                            cell_token++;
                            string m_formula(cell_token, table_char.size() - (cell_token - new_line));
                            m_table[make_pair(y_coor, x_coor)]->set_formula(m_formula);
                        }
                    }
                    cell_token = strtok(nullptr, token);
                    y_coor++;
                }
            }
            delete[] new_line;
        } else {
            throw logic_error("Error");
        }
    }
    file.close();
    cout << "Table was successfully imported!" << endl;
}

