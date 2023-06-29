#ifndef CParser_h
#define CParser_h

#include "CCell.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

using std::map;
using std::pair;
using std::string;
using std::vector;
using std::shared_ptr;

/**
 * @brief Parser class that handles user's input and parses it into a tokens and sends data to other classes
depending on user's input
 * 
 */
class CParser{
public:
    CParser() = default;
    ~CParser() = default;
    /**
     * @brief Method that accepts commands starting with '/'
     * @param str string that contains command
     * @return true if user continues using code
     * @return false if user wants to end session
     */
    bool commands_only(const string & str);
    /**
     * Method that works with assigning values to particular cell
     * @param str string that contains cell coordinates and value that will be assigned
     */
    void assigning(const string & str);
    /**
     * @brief main input
     */
    void input();

private:
    /**
     * @brief main map that represents each cell, 
     * where key of the map is in which coordinates cell is located
     */
    map<pair<int,int>, shared_ptr<CCell>> m_table;
    /**
     * @brief boolean variable, if true table with each cell's formulas will be printed
     */
    bool printFormula = true;
    /**
     * @brief boolean variable, if true table with each cell's values will be printed
     */
    bool printValue = true;
};

#endif
