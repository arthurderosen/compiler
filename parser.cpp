#include "lexer.h"
#include <iostream>
#include <stdio.h>

int main()
{
    Token token;

    while (token.nome_token != EOF) {
        token = proximo_token();
        if (token.nome_token == '.' )
          return 0;
    }

}