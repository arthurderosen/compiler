#include "lexer.h"
#include <iostream>
#include <stdio.h>

Token token;
void r_id();
void r_bloco();

void r_programa(){
  token = proximo_token();
  if (token.nome_token == PROGRAM ){
    r_id();
    token = proximo_token();
    if(token.nome_token == ';'){
      r_bloco();
    } 
  }
}

void r_id(){ 
}

void r_bloco(){ 
}

int main()
{
    while (token.nome_token != EOF) {
        token = proximo_token();
        if (token.nome_token == '.' )
          return 0;
    }

}
