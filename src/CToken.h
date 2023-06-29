#ifndef CToken_h
#define CToken_h

#include "CCell.h"
#include <string>
#include <deque>
#include <queue>
#include <memory>
#include <map>
#include <vector>

using std::string;
using std::deque;
using std::pair;
using std::map;
using std::vector;
using std::shared_ptr;

/**
 * CToken class is class that uses Shunting yard algorithm [https://en.wikipedia.org/wiki/Shunting_yard_algorithm]
 * Implementation notes for unary operators by Austin Taylor [https://stackoverflow.com/a/5240912]
 * Idea from: Shunting-yard Algorithm in C++ [https://gist.github.com/t-mat/b9f681b7591cdae712f6]
 */
class CToken {
public:
    /**
     * Enum class that helps with finding out what kind of token method dealing with
     */
    enum class Type {
        Unknown, Number, Operator, LeftParen, RightParen,
    };
    /**
     * @brief Construct a new CToken object
     * Constructor used for shunting yard algorithm with precedences and types of each variables
     * @param type type of the token
     * @param s string representation of token
     * @param precedence precedence of the token
     * @param rightAssociative specifies if the token is right associative
     * @param unary specifies if the token is a unary operator
     */
    CToken(Type type, string s, int precedence = -1, bool rightAssociative = false, bool unary = false );

    /**
     * @brief method that takes user's input and calculates it by operators precedences
     * @param str is mathematical expression that will be calculated
     * @param cellMap map of cells that contains each cells values and formulas
     * @return calculated result in doubles
     */
    static double compute(const string &str, const map<pair<int, int>, shared_ptr<CCell>>& cellMap);
    /**
     * @brief Construct a new deque<C Token>expr To C Tokens object
     * @param str string that will be divided into tokens
     * @param cellMap map of cells that contains each cells values and formulas
     */
    static deque<CToken>exprToCTokens(const string &str, const map<pair<int, int>, shared_ptr<CCell>>& cellMap);
    /**
     * @brief method that distributes operators and operands across
     * @param tokens deque that contains divided operators and operands
     * @return deque<CToken> that is stored in order by operators precedence
     */
    static deque<CToken> shuntingYard(const deque<CToken>& tokens);
    /**
     * @brief Method that works with functions like sin, cos, tan, abs, exp and log depending on token
     * @param token function's token depending on calculation will be made
     * @param stack stack vector where number that will calculated
     */
    static void mathFunctions(const string & token, vector<double> & stack);

    /**
     * @brief type of token
     */
    const Type type;
    /**
     * @brief string representation of token
     */
    const string str;
    /**
     * @brief  precedence that helps to add tokens into a deque in correct order
     */
    const int precedence;
    /**
     * @brief specifies if the token is right associative
     */
    const bool rightAssociative;
    /**
     * @brief specifies if the token is a unary operator
     */
    const bool unary;
};

#endif
