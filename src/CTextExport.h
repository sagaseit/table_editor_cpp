#ifndef CTextExport_h
#define CTextExport_h

#include "CExport.h"

/*Child class that exports whole table with values and formulas in text mode*/
class CTextExport : public CExport {
public:
    /**
     * @brief Method that exports table to particular file in text mode
     * Table will be exported in a user-friendly form
     * @param filename future name of the file that user wants to create
     * @param m_table map of cells that contains each cell's value and formula
     */
    void ExportToFile(const string& filename, const map<pair<int, int>, shared_ptr<CCell>>& m_table) override;
};

#endif
