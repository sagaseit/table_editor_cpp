#include "CToken.h"
#include <iostream>
#include <deque>
#include <queue>
#include <cmath>
#include <cstring>
#include <map>
#include <memory>

using std::shared_ptr;
using std::string;
using std::vector;
using std::deque;
using std::map;
using std::isblank;
using std::isdigit;
using std::endl;
using std::pow;
using std::cout;
using std::logic_error;
using std::to_string;
using std::make_pair;

CToken::CToken(CToken::Type type, string s, int precedence, bool rightAssociative, bool unary)
        : type{type}, str(std::move(s)), precedence{precedence},
          rightAssociative{rightAssociative}, unary{unary} {}

deque<CToken> CToken::exprToCTokens(const string &str, const map<pair<int, int>, shared_ptr<CCell>> &cellMap) {
    deque<CToken> tokens;
    string currentToken;
    for (const auto *p = str.c_str(); *p; ++p) {
        if (isblank(*p)) {
            // Do nothing for whitespace
        } else if (*p == '[') {
            string cellCoordinates;
            ++p;
            while (*p && *p != ']') {
                cellCoordinates += *p;
                ++p;
            }
            if (*p == ']') {
                size_t commaPos = cellCoordinates.find(',');
                if (commaPos != string::npos) {
                    try {
                        int row = stoi(cellCoordinates.substr(0, commaPos));
                        int col = stoi(cellCoordinates.substr(commaPos + 1));

                        auto cellIterator = cellMap.find(make_pair(row, col));
                        if (cellIterator != cellMap.end()) {
                            shared_ptr<CCell> cell = cellIterator->second;

                            tokens.emplace_back(CToken::Type::Number, to_string(cell->get_num()));
                        } else {
                            throw logic_error("Cell not found");
                        }
                    } catch (const std::invalid_argument& e) {
                        throw logic_error("Invalid input");
                    }
                } else {
                    throw logic_error("Invalid cell input!");
                }
            } else {
                throw logic_error("Invalid cell reference format!");
            }
        } else if (isdigit(*p) || *p == '.') {
            const auto *b = p;
            bool hasComma = false;
            while (isdigit(*p) || *p == '.') {
                if (*p == ',') {
                    hasComma = true;
                    break;
                }
                ++p;
            }
            const auto s = string(b, p);
            if (!hasComma) {
                tokens.emplace_back(CToken::Type::Number, s);
            } else {
                //Do nothing
            }
            --p;
        } else {
            CToken::Type t = CToken::Type::Unknown;
            int precedence = -1;
            bool rightAssociative = false;
            bool unary = false;
            char c = *p;

            switch (c) {
                case '(':
                    t = CToken::Type::LeftParen;
                    break;
                case ')':
                    t = CToken::Type::RightParen;
                    break;
                case '^':
                    t = CToken::Type::Operator;
                    precedence = 5;
                    rightAssociative = true;
                    break;
                case '*':
                    t = CToken::Type::Operator;
                    precedence = 4;
                    break;
                case '/':
                    t = CToken::Type::Operator;
                    precedence = 4;
                    break;
                case '+':
                    t = CToken::Type::Operator;
                    precedence = 3;
                    break;
                case '-':
                    if (tokens.empty() || tokens.back().type == CToken::Type::Operator ||
                        tokens.back().type == CToken::Type::LeftParen) {
                        unary = true;
                        c = 'm';
                        t = CToken::Type::Operator;
                        precedence = 5;
                    } else {
                        t = CToken::Type::Operator;
                        precedence = 3;
                    }
                    break;
                case 's':
                    if (strncmp(p, "sin", 3) == 0) {
                        t = CToken::Type::Operator;
                        precedence = 5;
                        p += 2;
                    }
                    break;
                case 'c':
                    if (strncmp(p, "cos", 3) == 0) {
                        t = CToken::Type::Operator;
                        precedence = 5;
                        p += 2;
                    }
                    break;
                case 't':
                    if (strncmp(p, "tan", 3) == 0) {
                        t = CToken::Type::Operator;
                        precedence = 5;
                        p += 2;
                    }
                    break;
                case 'a':
                    if (strncmp(p, "abs", 3) == 0) {
                        t = CToken::Type::Operator;
                        precedence = 5;
                        p += 2;
                    }
                    break;
                case 'e':
                    if (strncmp(p, "exp", 3) == 0) {
                        t = CToken::Type::Operator;
                        precedence = 5;
                        p += 2;
                    }
                    break;
                case 'l':
                    if (strncmp(p, "log", 3) == 0) {
                        t = CToken::Type::Operator;
                        precedence = 5;
                        p += 2;
                    }
                    break;
                default:
                    break;
            }
            const auto s = string(1, c);
            tokens.emplace_back(t, s, precedence, rightAssociative, unary);
        }
    }

    return tokens;
}

deque<CToken> CToken::shuntingYard(const deque<CToken> &tokens) {
    deque<CToken> queue;
    vector<CToken> stack;

    for (const auto &token: tokens) {
        switch (token.type) {
            case CToken::Type::Number:
                queue.push_back(token);
                break;

            case CToken::Type::Operator: {
                if (token.str == "s" || token.str == "c" || token.str == "t"
                    || token.str == "l" || token.str == "e" || token.str == "a") {
                    stack.push_back(token);
                } else {
                    const auto o1 = token;
                    while (!stack.empty()) {
                        const auto o2 = stack.back();
                        if (((!o1.rightAssociative && o1.precedence <= o2.precedence) ||
                             (o1.rightAssociative && o1.precedence < o2.precedence)) &&
                            (o2.str != "sin" && o2.str != "cos" && o2.str != "tan"
                             && o2.str != "log" && o2.str != "abs" && o2.str != "exp")) {
                            stack.pop_back();
                            queue.push_back(o2);
                            continue;
                        }
                        break;
                    }
                    stack.push_back(o1);
                }
            }
                break;

            case CToken::Type::LeftParen:
                stack.push_back(token);
                break;

            case CToken::Type::RightParen: {
                bool match = false;
                while (!stack.empty() && stack.back().type != CToken::Type::LeftParen) {
                    queue.push_back(stack.back());
                    stack.pop_back();
                    match = true;
                }
                if (!match && stack.empty()) {
                    printf("RightParen error (%s)\n", token.str.c_str());
                    return {};
                }
                stack.pop_back();
            }
                break;
            default:
                throw logic_error("Error: Invalid token type! Try Again");
        }
    }

    while (!stack.empty()) {
        if (stack.back().type == CToken::Type::LeftParen) {
            cout << "Mismatched parentheses error" << endl;
            exit(1);
        }
        queue.push_back(std::move(stack.back()));
        stack.pop_back();
    }
    return queue;
}

void CToken::mathFunctions(const string &token, vector<double> &m_stack) {
    if(m_stack.empty()){
        cout << "Error: Insufficient operands for sin" << endl;
        exit(1);
    }
    if (token == "s") {
        const auto operand = m_stack.back();
        m_stack.pop_back();
        m_stack.push_back(sin(operand));
    } else if (token == "c") {
        const auto operand = m_stack.back();
        m_stack.pop_back();
        m_stack.push_back(cos(operand));
    } else if (token == "t") {
        const auto operand = m_stack.back();
        m_stack.pop_back();
        m_stack.push_back(tan(operand));
    } else if (token == "e") {
        const auto operand = m_stack.back();
        m_stack.pop_back();
        m_stack.push_back(exp(operand));
    } else if (token == "a") {
        const auto operand = m_stack.back();
        m_stack.pop_back();
        m_stack.push_back(std::abs(operand));
    } else if (token == "l") {
        const auto operand = m_stack.back();
        if(operand <= 0){
            throw logic_error("Invalid input for logarithmic equation!");
        }
        m_stack.pop_back();
        m_stack.push_back(log10(operand));
    }
}

double CToken::compute(const string &expr, const map<pair<int, int>, shared_ptr<CCell>> &cellMap) {

    const auto tokens = exprToCTokens(expr, cellMap);
    auto queue = shuntingYard(tokens);
    vector<double> stack;

    while (!queue.empty()) {
        string op;
        const auto token = queue.front();
        queue.pop_front();
        switch (token.type) {
            case CToken::Type::Number:
                stack.push_back(stod(token.str));
                break;
            case CToken::Type::Operator: {
                if(token.str == "s" || token.str == "c" ||token.str == "l" ||token.str == "e" ||token.str == "a" || token.str == "t"){
                    mathFunctions(token.str, stack);
                } else if (token.unary) {
                    const auto rhs = stack.back();
                    stack.pop_back();
                    switch (token.str[0]) {
                        default:
                            printf("Operator error [%s]\n", token.str.c_str());
                            exit(0);
                        case 'm':
                            stack.push_back(-rhs);
                            break;
                    }
                } else {
                    if(stack.size() < 2){
                        throw logic_error("Invalid input!");
                    }
                    const auto rhs = stack.back();
                    stack.pop_back();
                    const auto lhs = stack.back();
                    stack.pop_back();
                    switch (token.str[0]) {
                        default:
                            printf("Operator error [%s]\n", token.str.c_str());
                            exit(0);
                        case '^':
                            stack.push_back(pow(lhs, rhs));
                            break;
                        case '*':
                            stack.push_back(lhs * rhs);
                            break;
                        case '/':
                            stack.push_back(lhs / rhs);
                            break;
                        case '+':
                            stack.push_back(lhs + rhs);
                            break;
                        case '-':
                            stack.push_back(lhs - rhs);
                            break;
                    }
                }
            }
                break;
            default:
                cout << "CToken error" << endl;
                exit(1);
        }
    }
    return stack.back();
}

