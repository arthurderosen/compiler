#include <stdio.h>
#include <iostream>
#include "lexer.h"

using namespace std;

Token token;
void r_id();
void r_bloco();
void r_tipo();
void r_atrib();
void r_expr();
void r_var();
void r_relacao();
void r_letra();
void r_digit();


//PROGRAMA E BLOCO
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

//DECLARACOES
void r_tipo() {
  token = proximo_token();
  if ((token.nome_token != INT) && (token.nome_token != BOOLEAN)) {
    cout<<"ERRO. Esperado token INT ou BOOLEAN";
  }
}

//COMANDOS
void r_atrib() {
  r_var();
  token = proximo_token();
  if (token.nome_token == ASSOP) {
    r_expr();
  }
  else {
    cout<<"ERRO. Esperado token ASSOP";
  }
}



void r_id(){ 
}

void r_bloco(){ 
}

//EXPRESSOES
void r_expr() {
  
}

void r_var() {
  
}

void r_relacao() {
  token = proximo_token();
  if (token.nome_token != RELOP)
    cout<<"ERRO. Esperado token RELOP";
}

//NUMEROS E IDENFICADORES
void r_digit() {
  token = proximo_token();
  if (!isdigit(token.nome_token))
    cout<<"ERRO. Esperado token digito";
}

void r_letra() {
  token = proximo_token();
  if (!isalphabetic(token.nome_token))
    cout<<"ERRO. Esperado token letra";
}
  

int main()
{
  r_programa();
  /*  
    while (token.nome_token != EOF) {
        token = proximo_token();
        if (token.nome_token == '.' )
          return 0;
    }
  */
}