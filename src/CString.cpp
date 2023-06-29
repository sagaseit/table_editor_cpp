#include "CString.h"
#include "CCell.h"
#include <iostream>
#include <sstream>

using std::istringstream;
using std::cout;
using std::endl;

CString::CString(const string & str) : CCell(str) {}

vector<string> CString::stringDelimiter(const string &str, char delimiter) {
    vector<string> tokens;
    istringstream iss(str);
    string token;
    while (getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string CString::removeQuotes(const string& str) {
    string result;
    for (char c : str) {
        if (c != '"') {
            result += c;
        }
    }
    return result;
}

string CString::multiplyString(const string &str) {
    string res;
    auto it = stringDelimiter(str, '*');
    string tmp = it.at(0);
    double num = std::stod(it.at(1));
    while(num != 0) {
        res += tmp;
        num--;
    }
    return res;
}

void CString::editedString(string &str) {
    string result;
    bool inSpace = true;
    for (char c: str) {
        if (isspace(c)) {
            if (!inSpace) {
                result += ' ';
                inSpace = true;
            }
        } else {
            result += c;
            inSpace = false;
        }
    }
    if (inSpace && !result.empty()) {
        result.pop_back();
    }
    str = result;
}

string CString::stringOperations(const string &str) {
    string res;
    if(str.find_first_of('+') != string::npos){
        auto it = stringDelimiter(str, '+');
        for (const auto& s : it) {
            res += removeQuotes(s);
        }
    } else if(str.find_first_of('*') != string::npos){
        res = multiplyString(str);
    } else {
        res = str;
    }
    res = removeQuotes(res);
    return res;
}

bool CString::endsWith(const string & str, const string & to_find){
    if (to_find.length() > str.length()) {
        return false;
    }
    return str.substr(str.length() - to_find.length()) == to_find;
}

string CString::get_value() const  {
    return m_str;
}

void CString::print(){
    cout << this->m_str << endl;
}
