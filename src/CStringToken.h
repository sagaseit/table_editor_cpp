#ifndef CStringToken_h
#define CStringToken_h

#include "CCell.h"
#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <cmath>
#include <cstring>
#include <map>
#include <memory>

using std::deque;
using std::string;

/**
 * Class that works with operations with string like repeat string, stitch two strings
 * Uses Shunting Yard Algorithm [https://en.wikipedia.org/wiki/Shunting_yard_algorithm]
 * Idea from: Shunting-yard Algorithm in C++ [https://gist.github.com/t-mat/b9f681b7591cdae712f6]
 */
class CStringToken {
public:
    /**
     * Enum class that helps with finding out what kind of token method dealing with
     */
    enum class Type {
        Unknown,
        Operand,
        Operator,
        LeftParen,
        RightParen,
    };
    /**
     * @brief Construct a new CToken object
     * Constructor used for shunting yard algorithm with precedences and types of each variables
     * @param type type of the token
     * @param s string representation of token
     * @param precedence precedence of the token
     * @param rightAssociative specifies if the token is right associative
     */
    CStringToken(Type type, string s, int precedence = -1, bool rightAssociative = false);

    /**
     * @brief Method that divides given string into a tokens that are
     * stored in deque that contains both operators and operands
     * @param str string that will be divided into tokens
     * @param cellMap map of cells
     * @return operations and operands divided into tokens 
     */
    static deque<CStringToken> exprToCStringTokens(const string & str, const std::map<std::pair<int, int>, std::shared_ptr<CCell>>& cellMap);
    /**
     * A method that distributes operators and operands across
     * stacks and queues depending on their precedence and task
     * @param tokens deque that contains divided operators and operands
     * @returns deque that is stored in order by operators precedence
     */
    static deque<CStringToken> shuntingYard(const deque<CStringToken>& tokens);
    /**
     * @brief Method that takes user's input and works with strings by operators precedences
     * @param expr string with mathematical operators
     * @param cellMap map of cells
     * @return edited string depending on input 
     */
    static string compute(const string& expr, const std::map<std::pair<int, int>, std::shared_ptr<CCell>>& cellMap);
private:
    /**
     * @brief type of token
     */
    Type type;
    /**
     * @brief string representation of token
     */
    string str;
    /**
     * @brief  precedence that helps to add tokens into a deque in correct order
     */
    int precedence;
};


#endif
