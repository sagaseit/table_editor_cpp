#ifndef CCell_h
#define CCell_h
#include <string>
#include <ostream>
using std::string;
using std::ostream;

/**
 *Abstract class that represents one cell, stores cell's value in string or double depending on
 * value that was assigned, stores formula in which formula Cell was assigned
 */
class CCell {
public:
    CCell() = default;
    virtual ~CCell() = default;
    /**
     * @brief Construct a new CCell object in strings
     * @param str cell's value in strings
     */
    explicit CCell(string str);
    /**
     * @brief Construct a new CCell object in doubles
     * @param num cell's value in doubles
     */
    explicit CCell(const double & num);
    /**
     * Virtual method prints cell's value depending which value was assigned before
     */
    virtual void print() = 0;
    /**
     * Sets cell's formula
     * @param str cell's formula 
     */
    void set_formula(const string & str);
    /**
     * @brief Get the value object
     * @returns string/double depending on which one is initialized
     */
    virtual string get_value() const = 0;
    /**
     * @brief Get the string object
     * @return cell's value in string 
     */
    string get_str() const;
    /**
     * @brief Get the number object
     * @return cell's value in double
     */
    double get_num() const;
    /**
     * Getter that gets particular cell's formula
     * @return cell's formula
     */
    string get_formula() const ;

protected:
    /**
     * @brief Cell is assigned with double values
     */
    double m_num{};
    /**
     * @brief Cell is assigned with string values
     */
    string m_str;
    /**
     * @brief In which formula cell was made
     * 
     */
    string m_formula;
};

#endif
