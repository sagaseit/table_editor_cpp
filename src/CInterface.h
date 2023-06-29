#ifndef CInterface_h
#define CInterface_h

#include "CCell.h"
#include <string>
#include <memory>
#include <map>
#include "../libs/tabulate.hpp"

using std::string;
using std::map;
using std::shared_ptr;
using std::pair;

/**
 * Class that contains text made for the user like welcoming message, help command
 */
class CInterface {
public:
    CInterface() = default;
    /**
     * Welcome message
     */
    static void welcome_msg();
    /**
     * Help message that contains instruction to help user
     */
    static void print_help();
    /**
     * @brief Method prints particular cell's value
     * @param str particular cell's coordinates
     * @param m_table map of CCells where each cell's value locates
     * @param printFormula boolean variable, if true table with each cells formula will be printed
     * @param printValue boolean variable, if true table with each cells value will be printed
     */
    static void cell_print(const string &str, const map<pair<int, int>, shared_ptr<CCell>>& m_table, bool printFormula, bool printValue);
    /**
     * Method that prints table depending on which what user wants to have in table. Method uses tabulate library
     * that helps with each cell's width and length depending on size of value/formula
     * @param x1 beginning of left range
     * @param y1 beginning of right range
     * @param x2 end of left range
     * @param y2 end of right range
     * @param m_table map of CCells where each cell's value/formula locates
     * @param printFormula boolean variable, if true table with each cell's formula will be printed
     * @param printValue boolean variable, if true table with each cell's value will be printed
     * @returns whole table with numbered columns and rows and each cell's value/formula
     */
    static tabulate::Table print_table(int x1, int y1, int x2, int y2,
                                       const map<pair<int, int>, shared_ptr<CCell>>& m_table, bool printFormula, bool printValue);
    /**
     * Main method that works with coordinates for printing whole table depending on user's input's range
     * @param os reference to an output stream object
     * @param coordinates user's input that contains tables range, will be divided into tokens in method
     * @param m_table map of CCells where each cell's value/formula locates
     * @param printFormula boolean variable, if true table with each cell's formula will be printed
     * @param printValue boolean variable, if true table with each cell's value will be printed
     */
    static void print_formula(ostream& os, string & coordinates, const map<pair<int, int>,
            shared_ptr<CCell>>& m_table, bool printFormula, bool printValue);
};


#endif
