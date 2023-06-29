#include "CStringToken.h"
#include "CCell.h"
#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <memory>
#include <algorithm>

using std::map;
using std::string;
using std::pair;
using std::deque;
using std::vector;
using std::shared_ptr;
using std::logic_error;
using std::cout;
using std::make_pair;
using std::to_string;
using std::strncmp;
using std::isblank;

CStringToken::CStringToken(CStringToken::Type type, string s, int precedence, bool rightAssociative)
        : type(type), str(std::move(s)), precedence(precedence) {}

deque<CStringToken> CStringToken::exprToCStringTokens(const string& str, const map<pair<int, int>, shared_ptr<CCell>>& cellMap) {
    deque<CStringToken> tokens;
    string currentToken;
    bool insideString = false;

    for (const auto* p = str.c_str(); *p; ++p) {
        if (isblank(*p)) {
            if (insideString) {
                currentToken += *p;
            }
        } else if (*p == '"') {
            if (insideString) {
                if (!currentToken.empty()) {
                    tokens.emplace_back(CStringToken::Type::Operand, currentToken);
                    currentToken.clear();
                }
                insideString = false;
            } else {
                insideString = true;
            }
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
                    int row = stoi(cellCoordinates.substr(0, commaPos));
                    int col = stoi(cellCoordinates.substr(commaPos + 1));

                    auto cellIterator = cellMap.find(make_pair(row, col));
                    if (cellIterator != cellMap.end()) {
                        shared_ptr<CCell> cell = cellIterator->second;

                        if (cell->get_num() < 1) {
                            throw logic_error("Cell value less than 1");
                        }

                        tokens.emplace_back(CStringToken::Type::Operand, to_string(cell->get_num()));
                    } else {
                            throw logic_error("Cell not found");
                    }
                } else {
                    throw logic_error("Invalid input");
                }
            } else {
                throw logic_error("Invalid input");
            }
        } else {
            if (insideString) {
                currentToken += *p;
            } else {
                CStringToken::Type t = CStringToken::Type::Unknown;
                int precedence = -1;
                bool rightAssociative = false;
                char c = *p;
                switch (c) {
                    case '(':
                        t = CStringToken::Type::LeftParen;
                        break;
                    case ')':
                        t = CStringToken::Type::RightParen;
                        break;
                    case '*':
                        t = CStringToken::Type::Operator;
                        precedence = 3;
                        break;
                    case '.':
                        t = CStringToken::Type::Operator;
                        precedence = 2;
                        break;
                    default:
                        break;
                }
                if (t != CStringToken::Type::Unknown) {
                    if (!currentToken.empty()) {
                        tokens.emplace_back(CStringToken::Type::Operand, currentToken);
                        currentToken.clear();
                    }
                    const auto s = string(1, c);
                    tokens.emplace_back(t, s, precedence, rightAssociative);
                } else {
                    currentToken += *p;
                }
            }
        }
    }

    if (insideString) {
        cout << "Error: Unterminated string literal\n";
        return {};
    }

    if (!currentToken.empty()) {
        tokens.emplace_back(CStringToken::Type::Operand, currentToken);
    }
    return tokens;
}


deque<CStringToken> CStringToken::shuntingYard(const deque<CStringToken>& tokens) {
    deque<CStringToken> queue;
    vector<CStringToken> stack;

    for (const auto& token : tokens) {
        switch (token.type) {
            case CStringToken::Type::Operand:
                queue.push_back(token);
                break;

            case CStringToken::Type::Operator: {
                const auto o1 = token;
                while (!stack.empty()) {
                    const auto o2 = stack.back();
                    if (o1.precedence <= o2.precedence) {
                        stack.pop_back();
                        queue.push_back(o2);
                        continue;
                    }
                    break;
                }
                stack.push_back(o1);
            } break;

            case CStringToken::Type::LeftParen:
                stack.push_back(token);
                break;

            case CStringToken::Type::RightParen: {
                bool match = false;
                while (!stack.empty() && stack.back().type != CStringToken::Type::LeftParen) {
                    queue.push_back(stack.back());
                    stack.pop_back();
                    match = true;
                }
                if (!match && stack.empty()) {
                    cout << "RightParen error (" << token.str << ")\n";
                    return {};
                }
                stack.pop_back();
            } break;

            default:
                cout << "Error: Invalid token type! Try again.\n";
                return {};
        }
    }

    while (!stack.empty()) {
        if (stack.back().type == CStringToken::Type::LeftParen) {
            cout << "Mismatched parentheses error\n";
            return {};
        }
        queue.push_back(std::move(stack.back()));
        stack.pop_back();
    }

    return queue;
}

string CStringToken::compute(const string& expr, const map<pair<int, int>, shared_ptr<CCell>>& cellMap) {
    const auto tokens = exprToCStringTokens(expr, cellMap);
    auto queue = shuntingYard(tokens);
    vector<string> stack;

    while (!queue.empty()) {
        string op;

        const auto token = queue.front();
        queue.pop_front();
        switch (token.type) {
            case CStringToken::Type::Operand:
                stack.push_back(token.str);
                break;

            case CStringToken::Type::Operator: {
                if (token.str == "*") {
                    if (stack.size() < 2) {
                        cout << "Error: Insufficient operands for multiplication\n";
                        return "";
                    }
                    const auto rhs = stack.back();
                    stack.pop_back();
                    const auto lhs = stack.back();
                    stack.pop_back();

                    string result;
                    double num = stod(rhs);
                    while (num != 0) {
                        result += lhs;
                        num--;
                    }

                    stack.push_back(result);
                } else if (token.str == ".") {
                    if (stack.size() < 2) {
                        cout << "Error: Insufficient operands for dot operation\n";
                        return "";
                    }
                    const auto rhs = stack.back();
                    stack.pop_back();
                    const auto lhs = stack.back();
                    stack.pop_back();
                    stack.push_back(lhs + rhs);
                } else {
                    cout << "Operator error [" << token.str << "]\n";
                    exit(0);
                }
            } break;

            default:
                cout << "CStringToken error\n";
                exit(1);
        }
    }

    if (stack.size() != 1) {
        cout << "Error: Invalid expression\n";
        return "";
    }

    return stack.back();
}

