/**
* @author Sagadat Seitzhan <seitzsag@cvut.cz>
* @date 12.05.2023
*/

#ifndef CImport_h
#define CImport_h

#include "CCell.h"
#include <string>
#include <memory>
#include <map>
using std::string;
using std::pair;
using std::shared_ptr;
using std::map;

/**
 * @brief Import class that handles import from particular file
 */
class CImport {
public:
    /**
     * Method handles import from particular file and adds value with formulas to each cell
     * @param str file's name that will be imported from
     * @param m_table map of cells that will be inserted with values and formulas from file
     */
    static void importFile(const string & str, map<pair<int, int>, shared_ptr<CCell>>& m_table);
};

#endif
