#include "CInterface.h"
#include "CString.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::stringstream;
using std::istringstream;

using std::cout;
using std::string;
using std::vector;
using std::ifstream;
using std::endl;
using std::make_pair;
using std::getline;

void CInterface::welcome_msg() {
    ifstream inputFile("build/welcome.txt");
    string line;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }
    inputFile.close();
}

void CInterface::print_help() {
    ifstream inputFile("build/help.txt");
    string line;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }
    inputFile.close();
}

void CInterface::cell_print(const string &str, const map<pair<int, int>, shared_ptr<CCell>> &m_table, bool printFormula,
                            bool printValue) {
    auto coordinates = CString::stringDelimiter(str, ',');
    int x = stoi(coordinates.at(0));
    int y = stoi(coordinates.at(1));

    auto it = m_table.find(make_pair(x, y));
    if (it != m_table.end()) {
        cout << "[" << x << "," << y << "] = ";
        if(printValue && !printFormula) {
            cout << it->second->get_value() << endl;
        } else if(!printValue && printFormula){
            cout << it->second->get_formula() << endl;
        }
    } else {
        cout << "Cell [" << x << "," << y << "] is not initialized yet!" << endl;
    }
}

tabulate::Table CInterface::print_table(int x1, int y1, int x2, int y2, const map<pair<int, int>,
        shared_ptr<CCell>> &m_table, bool printFormula, bool printValue) {

    tabulate::Table out_table;
    vector<string> start_row{""};

    for (int i = x1; i < x2 + 1; i++)
        start_row.push_back(std::to_string(i));
    out_table.add_row(tabulate::Table::Row_t{start_row.begin(), start_row.end()});
    start_row.clear();

    for (int j = y1; j < y2 + 1; j++) {
        start_row.push_back(std::to_string(j));
        for (int i = x1; i < x2 + 1; i++) {
            try {
                if (m_table.at(make_pair(i, j)) == nullptr) {
                    start_row.emplace_back("");
                    continue;
                }
            } catch (const std::exception &e) {
                start_row.emplace_back("");
                continue;
            }
            auto it = m_table.find(make_pair(i, j));
            if (printValue && !printFormula) {
                start_row.push_back(it->second->get_value());
            } else if (!printValue && printFormula) {
                start_row.push_back("=" + (it->second->get_formula()));
            }
        }
        out_table.add_row(tabulate::Table::Row_t{start_row.begin(), start_row.end()});
        start_row.clear();
    }

    out_table[0].format().font_align(tabulate::FontAlign::center);
    return out_table;
}

void CInterface::print_formula(ostream &os, string &coordinates, const map<pair<int, int>, shared_ptr<CCell>> &m_table,
                               bool printFormula, bool printValue) {

    coordinates = coordinates.substr(1, coordinates.size() - 2);
    auto coordinatesNum = CString::stringDelimiter(coordinates, ':');
    string left = coordinatesNum.at(0);
    string right = coordinatesNum.at(1);

    auto start = CString::stringDelimiter(left, ',');
    auto end = CString::stringDelimiter(right, ',');

    int x1 = stoi(start.at(0));
    int x2 = stoi(end.at(0));
    int y1 = stoi(start.at(1));
    int y2 = stoi(end.at(1));

    if (x1 < 1 || x2 < 1 || y1 < 1 || y2 < 1) {
        throw std::logic_error("Invalid input for table print!");
    }

    tabulate::Table out_table = print_table(x1, y1, x2, y2, m_table, printFormula, printValue);
    os << out_table << endl;
}

