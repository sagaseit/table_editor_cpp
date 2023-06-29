/**
* @author Sagadat Seitzhan <seitzsag@cvut.cz>
* @date 12.05.2023
*/

#ifndef CString_h
#define CString_h

#include "CCell.h"
#include <string>
#include <vector>
#include <map>

using std::pair;
using std::string;
using std::vector;
using std::map;

/**
 *Child class contains methods and function for working with string
 */
class CString : public CCell{
public:
    CString() = default;
    /**
     * @brief Construct a new CString object
     * @param str cell's value in string
     */
    explicit CString(const string & str);
    /**
     * Method that splits string depending on delimiter
     * @param str string to be split.
     * @param delimiter depending on delimiter strings will be split
     * @returns vector of strings where split strings will be located
     */
    static vector<string>stringDelimiter(const string & str, char delimiter);
    /**
     * Method that works with string: joining two or more strings, repeating string
     * @param str string that will be joined or repeated
     * @returns edited string
     */
    static string stringOperations(const string & str);
    /**
     * Method removes quotes from string
     * @param str string with quotes
     * @returns string without quotes
     */
    static string removeQuotes(const string & str);
    /**
     * Method that removes odd whitespaces from string
     * @param str string with odd whitespaces
     */
    static void editedString(string & str);
    /**
     * Method that repeats string particular amount of times
     * @param str string that will be repeated
     * @return repeated string
     */
    static string multiplyString(const string & str);
    /**
     * Boolean method for export class that finds out if user wants to export table in binary or text format
     * @param str future file's name with particular suffix
     * @param to_find suffix that can be .txt or .bin
     * @return true if suffix found successfully
     * @return false if suffix's length is longer than file's name, false if suffix was not found
     */
    static bool endsWith(const string & str, const string & to_find);
    /**
     * Override method used for export/input depending on cell's value
     * @returns cell's value in string
     */
    string get_value() const override;
    /**
     * Override method that prints cell's value in string if string was assigned to the cell previously
     */
    void print() override;

};

#endif