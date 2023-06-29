#include "CCell.h"
#include <utility>

CCell::CCell (string str) : m_str(std::move(str)) {}
CCell::CCell (const double &num) : m_num(num) {}

string CCell::get_str() const { return this->m_str; }
double CCell::get_num() const { return this->m_num; }

void CCell::set_formula(const std::string &str) {
    this->m_formula = str;
}

string CCell::get_formula() const {
    return this->m_formula;
}