#include "src/lexer.hpp"

int main() {
    Lexer lexer("test.atom");
    std::vector<Token*> tokens = lexer.tokenize();
}
