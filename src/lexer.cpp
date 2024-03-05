#include "lexer.hpp"

Lexer::Lexer(const char* file) {
    fin.open(file, std::fstream::in);
}

std::vector<Token*> Lexer::tokenize() {
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
            Token* integer_token = generate_number(cur);
            tokens.push_back(integer_token);
            print_token(integer_token);
        } else if(isalpha(cur)) {
            Token* keyword_token = generate_keyword(cur);
            tokens.push_back(keyword_token);
            print_token(keyword_token);
        }
    }

    return tokens;
}

Token* Lexer::generate_number(char firstDigit) {
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

Token* Lexer::generate_keyword(char firstChar) {
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

void Lexer::print_token(Token* token) {
    std::cout << "Found token " << token->value << ". ";
    if(token->type == TokenType::INT) {
        std::cout << "Type: INT.\n";
    } else if(token->type == TokenType::KEYWORD) {
        std::cout << "Type: KEYWORD.\n";
    } else if(token->type == TokenType::SEPARATOR) {
        std::cout << "Type: SEPARATOR.\n";
    }
}
