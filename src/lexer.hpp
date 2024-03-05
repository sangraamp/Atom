#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>

typedef enum {
    INT,
    KEYWORD,
    SEPARATOR,
} TokenType;

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const char* file);
    std::vector<Token*> tokenize();
private:
    Token* generate_number(char firstDigit);
    Token* generate_keyword(char firstChar);
    void print_token(Token* token);
    
    std::fstream fin;
};

#endif
