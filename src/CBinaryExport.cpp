#include "CBinaryExport.h"
#include <fstream>
#include <iostream>

using std::ofstream;
using std::logic_error;

void CBinaryExport::ExportToFile(const string& toPath, const map<pair<int, int>, shared_ptr<CCell>>& m_table) {
    /*Opens file in binary mode*/
    ofstream file(toPath, std::ios::binary);

    /*Checking if file can be opened*/
    if (!file.is_open()) {
        throw logic_error("File cannot be opened!");
    }

    /*mapSize is used for file writing to determine number of entries*/
    size_t mapSize = m_table.size();
    file.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));

    /*for loop that takes each cell's coordinates and value to write it to file*/
    for (const auto& entry : m_table) {
        const auto& coordinates = entry.first;
        const auto& cell = entry.second;

        int row = coordinates.first;
        int col = coordinates.second;

        file.write(reinterpret_cast<const char*>(&row), sizeof(row));
        file.write(reinterpret_cast<const char*>(&col), sizeof(col));

        double value = cell->get_num();
        file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    /*if error during export occured*/
    if (file.bad()) {
        throw logic_error("Error in exporting!");
    }

    /*table was successfully exported to file*/
    std::cout << "Export completed" << std::endl;
    file.close();
}