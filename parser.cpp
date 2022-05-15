#include "lexer.h"
#include <iostream>
#include <stdio.h>
using namespace std;

Token token;
//PROGRAMA E BLOCO
void r_programa();
void r_bloco();
void r_bloco_l();
void r_bloco_ll();

//DECLARAÇÕES
void r_pdecl_var();
void r_decl();
void r_decl_var();
void r_listaid();
void r_listaidl();
void r_pdecl_subr();
void r_decl_proc();
void r_decl_procl();
void r_param_form();
void r_param_forml();
void r_sec_param_form();
void r_tipo();

//COMANDOS
void r_comand_comp();
void r_comand_compl();
void r_comand_compll();
void r_comand();
void r_atrib();
void r_chama_proc();
void r_chama_procl();
void r_comand_cond();
void r_cond_else();
void r_comand_rep();

//EXPRESSOES

void r_expr();
void r_expr_simp();
void r_e();
void r_el();
void r_ell();
void r_termo();
void r_termol();
void r_fator();
void r_var();
void r_list_expr();
void r_list_exprl();
void r_relacao();

//NUMEROS E IDENTIFICADORES
void r_num();
void r_id();
void r_idl();
void r_digit();
void r_letra();



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

void r_bloco(){
  r_bloco_l();
  r_comand_comp();  
}

void r_bloco_l(){
  r_pdecl_var();
  r_bloco_ll();
}

void r_bloco_ll(){
  r_pdecl_subr(); 
}

//DECLARACOES

void r_pdecl_var(){
  
}

void r_decl(){
  
}

void r_decl_var(){
  
}

void r_listaid(){
  
}

void r_listaidl(){
  
}

void r_pdecl_subr(){
  
}

void r_decl_proc(){
  
}

void r_decl_procl(){
  
}

void r_param_form(){
  
}

void r_param_forml(){
  
}

void r_sec_param_form(){
  
}

void r_tipo() {
  token = proximo_token();
  if ((token.nome_token != INT) && (token.nome_token != BOOLEAN)) {
    cout<<"ERRO. Esperado token INT ou BOOLEAN";
  }
}


//COMANDOS

void r_comand_comp(){
  
}

void r_comand_compl(){
  
}

void r_comand_compll(){
  
}

void r_comand(){
  
}

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

void r_chama_proc(){
  
}

void r_chama_procl(){
  
}

void r_comand_cond(){
  
}

void r_cond_else(){
  
}

void r_comand_rep(){
  
}


//EXPRESSOES
void r_expr() {
  
}

void r_expr_simp() {
  
}

void r_e() {
  
}

void r_el() {
  
}

void r_ell() {
  
}

void r_termo() {
  
}

void r_termol() {
  
}

void r_fator() {
  
}

void r_var() {
  
}

void r_list_expr() {
  
}

void r_list_exprl() {
  
}

void r_relacao() {
  token = proximo_token();
  if (token.nome_token != RELOP)
    cout<<"ERRO. Esperado token RELOP";
}

//NUMEROS E IDENFICADORES

void r_num(){
  
}

void r_id(){ 
  
}

void r_idl(){
  
}


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
    while (token.nome_token != EOF) {
        token = proximo_token();
        if (token.nome_token == '.' )
          return 0;
    }

}
