/**
* @author Sagadat Seitzhan <seitzsag@cvut.cz>
* @date 12.05.2023
*/

#ifndef CExport_h
#define CExport_h

#include "CParser.h"
#include "CCell.h"
#include "../libs/tabulate.hpp"
#include <string>
#include <memory>
#include <map>

using std::string;
using std::map;
using std::shared_ptr;
using std::pair;

/**
 * Abstract class that exports tables values/formulas to particular file
 */
class CExport {
public:
    virtual ~CExport() {}
    /**
     * Virtual method that exports table to file in text or binary mode
     * @param str future name of the file that user entered
     * @param m_table map of cells that contains each cell's value
     */
    virtual void ExportToFile(const string & str, const map<pair<int, int>, shared_ptr<CCell>>& m_table) = 0;
    /**
     * Method that creates table with all cells values
     * @param m_table map of CCells where each cell's value locates
     * @returns table with values that can be exported to certain file
     */
    static tabulate::Table table(const map<pair<int, int>, shared_ptr<CCell>>& m_table);
};

#endif
