#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>

/*
Token name           Explanation                                            Sample token values
identifier           Names assigned by the programmer.                       x, color, UP
keyword              Reserved words of the language.                         if, while, return
separator/punctuator Punctuation characters and paired delimiters.            }, (, ;
operator             Symbols that operate on arguments and produce results.   +, <, =
literal              Numeric, logical, textual, and reference literals.       true, 6.02e23, "music"
comment              Line or block comments. Usually discarded.               // must be negative
whitespace           Groups of non-printable characters. Usually discarded.   –
*/

typedef enum {
    INT,
    KEYWORD,
    SEPARATOR,
} TokenType;

struct Token {
    TokenType type;
    std::string value;
};

void print_token(Token* token) {
    std::cout << "Found token " << token->value << ". ";
    if(token->type == TokenType::INT) {
        std::cout << "Type: INT.\n";
    } else if(token->type == TokenType::KEYWORD) {
        std::cout << "Type: KEYWORD.\n";
    } else if(token->type == TokenType::SEPARATOR) {
        std::cout << "Type: SEPARATOR.\n";
    }
}

Token* generate_number(char firstDigit, std::fstream& fin) {
    Token *token = new Token();
    token->type = TokenType::INT;
    std::string value = "";
    value += firstDigit;
    char cur;
    while(fin >> std::noskipws >> cur && isdigit(cur)) {
        value += cur;
    }
    // At this point, cur will hold the character after the last digit of the number
    // Get the current position in the file stream
    std::streampos currentPos = fin.tellg();
    // Move the file stream pointer back one character
    fin.seekg(currentPos - std::streamoff(1));

    token->value = value;
    return token;
}

Token* generate_keyword(char firstChar, std::fstream& fin) {
    Token *token = new Token();
    std::string keyword = "";
    keyword += firstChar;
    char cur;
    while(fin >> std::noskipws >> cur && isalpha(cur)) {
        keyword += cur;
    }
    // At this point, cur will hold the character after the last digit of the number
    // Get the current position in the file stream
    std::streampos currentPos = fin.tellg();
    // Move the file stream pointer back one character
    fin.seekg(currentPos - std::streamoff(1));
    
    if(keyword == "exit") {
        token->type = TokenType::KEYWORD;
        token->value = "EXIT";
    }
    return token;
}

std::vector<Token*> lexer(const char* file) {
    std::fstream fin(file, std::fstream::in);
    std::vector<Token*> tokens; 
    char cur;
    // noskipws ensures whitespaces and \n chars aren't skipped
    while(fin >> std::noskipws >> cur) {
        if(cur == ';') {
            Token* semicolon_token = new Token();
            semicolon_token->value = cur;
            semicolon_token->type = TokenType::SEPARATOR;
            tokens.push_back(semicolon_token);
            print_token(semicolon_token);
        } else if(cur == '(') {
            Token* open_paren_token = new Token();
            open_paren_token->value = cur;
            open_paren_token->type = TokenType::SEPARATOR;
            tokens.push_back(open_paren_token);
            print_token(open_paren_token);
        } else if(cur == ')') {
            Token* closed_paren_token = new Token();
            closed_paren_token->value = cur;
            closed_paren_token->type = TokenType::SEPARATOR;
            tokens.push_back(closed_paren_token);
            print_token(closed_paren_token);
        } else if(isdigit(cur)) {
            Token* integer_token = generate_number(cur, fin);
            tokens.push_back(integer_token);
            print_token(integer_token);
        } else if(isalpha(cur)) {
            Token* keyword_token = generate_keyword(cur, fin);
            tokens.push_back(keyword_token);
            print_token(keyword_token);
        } else {
            printf("Unrecognized char: %c\n", cur);
        }
    }

    return tokens;
}

int main() {
    lexer("test.atom");
}