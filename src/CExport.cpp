#include "CExport.h"
#include "CInterface.h"
#include <ostream>
#include <fstream>
#include <iostream>
#include <climits>
#include "../libs/tabulate.hpp"

using std::ofstream;
using std::logic_error;
using std::cout;
using std::endl;

/**
 * Overloaded operator for << that allows to specify how a CCell object should be formatted
 * @param os represents the output stream where the data will be written
 * @param m_cell reference to CCell object that will be serialized to the output stream
 * @returns output stream with the data
 */
ostream &operator<<(ostream &os, const CCell &m_cell) {
    os << m_cell.get_value();
    return os;
}

tabulate::Table CExport::table(const map<pair<int, int>, shared_ptr<CCell>> &m_table) {
    int minX = INT_MAX;
    int minY = INT_MAX;
    int maxX = INT_MIN;
    int maxY = INT_MIN;

    for (const auto& entry : m_table) {
        const auto& key = entry.first;
        minX = std::min(minX, key.first);
        minY = std::min(minY, key.second);
        maxX = std::max(maxX, key.first);
        maxY = std::max(maxY, key.second);
    }

    tabulate::Table out_table;
    vector<string> start_row{""};

    for (int i = minX; i < maxX + 1; i++){
        start_row.push_back(std::to_string(i));
    }
    out_table.add_row(tabulate::Table::Row_t{start_row.begin(), start_row.end()});
    start_row.clear();

    for (int j = minY; j < maxY + 1; j++) {
        start_row.push_back(std::to_string(j));
        for (int i = minX; i < maxX + 1; i++) {
            try {
                if (m_table.at(std::make_pair(i, j)) == nullptr) {
                    start_row.emplace_back("");
                    continue;
                }
            } catch ( const std::exception & e) {
                start_row.emplace_back("");
                continue;
            }
            auto it = m_table.find(std::make_pair(i, j));
            if(isdigit(it->second->get_value()[0])){
                start_row.push_back(it->second->get_value() + " = " + it->second->get_formula());
            } else {
                start_row.push_back( '"' + it->second->get_value() + '"' + " = " + it->second->get_formula());
            }
        }
        out_table.add_row(tabulate::Table::Row_t{start_row.begin(), start_row.end()});
        start_row.clear();
    }
    out_table[0].format().font_align(tabulate::FontAlign::center);

    return out_table;
}

void CExport::ExportToFile(const string &str, const map<pair<int, int>, shared_ptr<CCell>>& m_table) {
    ofstream writer(str);

    /**If file cannot be opened*/
    if(!writer.is_open()){
        writer.close();
        throw logic_error("File cannot be opened!");
    }
    tabulate::Table out_table = table(m_table);
    writer << out_table << endl;

    if(writer.bad()){
        writer.close();
        throw logic_error("Error in exporting!");
    }
    cout << "Export completed" << endl;
    writer.close();
}