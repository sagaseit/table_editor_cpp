/**
* @author Sagadat Seitzhan <seitzsag@cvut.cz>
* @date 12.05.2023
*/

#ifndef CBinaryExport_h
#define CBinaryExport_h

#include "CExport.h"

/*Child class that exports table with data in binary type*/
class CBinaryExport : public CExport {
public:
    /**
     * Method exports table with data in binary file
     * @param toPath future file's name with suffix .bin    
     * @param m_table map of CCells that contains each cell's value
     */
    void ExportToFile(const string& toPath, const map<pair<int, int>, shared_ptr<CCell>>& m_table) override;
};

#endif