#include "CNum.h"
#include <iostream>

using std::cout;
using std::endl;
using std::to_string;

CNum::CNum(const double &num): CCell(num) {}

bool CNum::isNum(const string &str) {
    if (str[0] == '"' && str.back() == '"'){
        return false;
    }

    if(str.find_first_of('"') == string::npos) {
        for (char c: str) {
            if (isdigit(c) || c == '.' || c == '-' || c == '+' || c == '*' || c == '/')
                return true;
        }
    }

    return false;
}

string CNum::get_value() const {
    return to_string(m_num);
}

void CNum::print() {
    cout << this->m_num << endl;
}

