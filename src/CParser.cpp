#include "CParser.h"
#include "CToken.h"
#include "CString.h"
#include "CInterface.h"
#include "CStringToken.h"
#include "CImport.h"
#include "CNum.h"
#include "CExport.h"
#include "CBinaryExport.h"
#include "CTextExport.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

using std::stringstream;
using std::istringstream;
using std::ifstream;
using std::logic_error;
using std::string;
using std::stack;
using std::cin;
using std::cout;
using std::make_shared;
using std::make_pair;
using std::getline;
using std::endl;

void CParser::input() {

    CInterface::welcome_msg();

    while (true) {
        string command;
        cout << "/<Enter command/>: ";
        getline(cin, command);
        if (cin.eof()) {
            break;
        }

        CString::editedString(command);

        if (command.at(0) == '/') {
            command = command.substr(1);
            if (!commands_only(command)) {
                break;
            }
        } else {
            assigning(command);
        }

    }
}

void CParser::assigning(const string &str) {
    string work_str = str, name;
    size_t check = work_str.find_first_of('=');

    if(check == string::npos){
        throw logic_error("Invalid input");
    }
    if (check != string::npos) {
        name = work_str.substr(0, check);
        CString::editedString(name);
        work_str = work_str.substr(check + 1);
        CString::editedString(work_str);
    }

    CToken token(CToken::Type::Unknown, "");
    auto key = CString::stringDelimiter(name, ',');
    int pair1 = stoi(key.at(0));
    int pair2 = stoi(key.at(1));

    if (CNum::isNum(work_str)) {
        double value = CToken::compute(work_str, m_table);
        auto it = m_table.find(make_pair(pair1, pair2));
        if (it != m_table.end()) {
            it->second = make_shared<CNum>(value);
        } else {
            m_table.emplace(make_pair(pair1, pair2), make_shared<CNum>(value));
            m_table[make_pair(pair1, pair2)]->set_formula(work_str);
        }
    } else if (!CNum::isNum(work_str)) {
        if(work_str.find('"') == string::npos){
            throw logic_error("Invalid input for string!");
        }
        string formula = work_str;
        work_str = CStringToken::compute(work_str, m_table);
        auto it = m_table.find(make_pair(pair1, pair2));
        if (it != m_table.end()) {
            it->second = make_shared<CString>(work_str);
        } else {
            m_table.emplace(make_pair(pair1, pair2), make_shared<CString>(work_str));
            m_table[make_pair(pair1, pair2)]->set_formula(formula);
        }
    }
}

bool CParser::commands_only(const string &str) {
    auto token = CString::stringDelimiter(str, ' ');
    string command = token.at(0);

    if (token.at(0) == "EXIT") {
        cout << "Thanks for using my table!" << endl;
        return false;
    } else if (token.at(0) == "HELP") {
        CInterface::print_help();
    } else if (token.at(0) == "FORMULA") {
        if (token.size() != 2) {
            throw logic_error("Invalid number of parameters!");
        }
        string formulaPart = token.at(1);
        if (formulaPart.front() == '[' && formulaPart.back() == ']') {
            printFormula = true;
            printValue = false;
            std::ostringstream os;
            CInterface::print_formula(os, formulaPart, m_table, printFormula, printValue);
            cout << os.str() << endl;
        } else if(formulaPart.find(',') != string::npos && formulaPart.size() == 3) {
            printFormula = true;
            printValue = false;
            CInterface::cell_print(formulaPart, m_table, printFormula, printValue);
        } else {
            throw logic_error("Invalid input for printing!");
        }
    } else if (token.at(0) == "PRINT") {
        string printPart = token.at(1);
        if (printPart.front() == '[' && printPart.back() == ']') {
            printValue = true;
            printFormula = false;
            std::ostringstream os;
            CInterface::print_formula(os, printPart, m_table, printFormula, printValue);
            cout << os.str() << endl;
        } else if(printPart.find(',') != string::npos && printPart.size() == 3) {
            printFormula = false;
            printValue = true;
            CInterface::cell_print(printPart, m_table, printFormula, printValue);
        } else {
            throw logic_error("Invalid input for printing!");
        }
    } else if (token.at(0) == "IMPORT") {
        string fromPath = token.at(1);
        CImport::importFile(fromPath, m_table);
    } else if (token.at(0) == "EXPORT") {
        string toPath = token.at(1);
        CTextExport textExport;
        CBinaryExport binaryExport;
        if(CString::endsWith(toPath, ".txt")){
            textExport.ExportToFile(toPath, m_table);
        } else if(CString::endsWith(toPath, ".bin")){
            binaryExport.ExportToFile(toPath, m_table);
        } else {
            throw logic_error("Invalid extension for file");
        }
    } else {
        cout << "Command doesn't exist!" << endl;
    }
    return true;
}