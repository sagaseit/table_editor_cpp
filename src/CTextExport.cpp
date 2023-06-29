#include "CTextExport.h"
#include <fstream>
#include <iostream>

using std::ofstream;
using std::logic_error;
using std::cout;
using std::endl;

void CTextExport::ExportToFile(const string &str, const map<pair<int, int>, shared_ptr<CCell>>& m_table) {
    ofstream writer(str);

    /*if file cannot be opened*/
    if(!writer.is_open()){
        writer.close();
        throw logic_error("File cannot be opened!");
    }
    /*tabulate method in CExport that makes table in user-friendly form*/
    tabulate::Table out_table = table(m_table);
    writer << out_table << endl;

    /*if error during export occured*/
    if(writer.bad()){
        writer.close();
        throw logic_error("Error in exporting!");
    }
    /*table exported to the file successfully*/
    cout << "Export completed" << endl;
    writer.close();
}