#ifndef CNum_h
#define CNum_h
#include "CCell.h"

/**
 * Child class contains methods and functions for working with number
 */
class CNum : public CCell{
public:
    /**
     * @brief Construct a new CNum object
     */
    CNum() = default;
    /**
     * @brief Construct a new CNum object
     * @param num cell's value in double
     */
    explicit CNum(const double & num);
    /**
     * Method that finds out if assigning value is number or string
     * @param str value
     * @return true if value is number, false if value is string
     */
    static bool isNum(const string &str);
    /**
     * Override method used for export/input depending on cell's value
     * @returns cell's value in numbers converted to string
     */
    string get_value() const override;
    /**
     * Override method that prints cell's value in double if number was assigned to the cell previously
     */
    void print() override;
};

#endif
