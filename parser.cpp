#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include "lexer.h"

using namespace std;

//PROGRAMA E BLOCO
void r_programa();
void r_bloco();
void r_blocol();
void r_blocoll();

//DECLARAÇÕES
void r_p_decl_var();
void r_decl();
void r_decll();
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

struct First {
  vector<int> letra {'_','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', 'A', 'B', 'C', 'D', 'E', 'F', 'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  vector<int> digito {0,1,2,3,4,5,6,7,8,9};
  vector<int> tipo {INT, BOOLEAN};
  vector<int> programa, bloco, blocol, blocoll, p_decl_var, decl, decll, decl_var, listaid, listaidl, pdecl_subr, decl_proc, decl_procl, param_form, param_forml, sec_param_form, comand_comp,comand_compl,comand_compll,comand,atrib,chama_proc,chama_procl,comand_cond,cond_else,comand_rep,expr,expr_simp,e,el,ell,termo,termol,fator,var,list_expr,list_exprl,relacao,num,id,idl;
};

First first;
Token token;

const int empty_str = 0;

//HELPERS
bool vector_contains(vector<int>& vector, int value) {
  return find(vector.begin(), vector.end(), value) != vector.end(); 
}

void push_back_vector(vector<int>& dest, vector<int>& source) {
  for(int i: source) dest.push_back(i);
}

void push_back_empty(vector<int>& dest) {
  dest.push_back(empty_str);
}

void print_parser(string output) {
  cout << output << endl;
}

//PROGRAMA E BLOCO
void r_programa(){
  token = proximo_token();
  cout << token.nome;
  if (token.nome == PROGRAM ){
    r_id();
    token = proximo_token();
    if(token.nome == ';'){
      r_bloco();
    } 
  }
}

void r_bloco(){
  r_blocol();
  r_comand_comp();  
}

void r_blocol(){
  r_p_decl_var();
  r_blocoll();
}

void r_blocoll(){
  r_pdecl_subr(); 
}

//DECLARACOES

void r_p_decl_var(){
  if(vector_contains(first.p_decl_var, token.nome)) {
    r_decl_var();
    r_decl();
  }
}

void r_decl(){
  if (token.nome == ';') {
    r_decll();
  }
}

void r_decll() {
  token = proximo_token();
  if (vector_contains(first.decll, token.nome)) {
    r_p_decl_var();
  }
  return;
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
  if ((token.nome != INT) && (token.nome != BOOLEAN)) {
    print_parser("ERRO. Esperado token INT ou BOOLEAN");
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
  if (token.nome == ASSOP) {
    r_expr();
  }
  else {
    print_parser("ERRO. Esperado token ASSOP");
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
  if (token.nome != RELOP)
    print_parser("ERRO. Esperado token RELOP");
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
  if (!isdigit(token.nome))
    print_parser("ERRO. Esperado token digito");
}

void r_letra() {
  token = proximo_token();
  if (!isalphabetic(token.nome))
    print_parser("ERRO. Esperado token letra");
}


int main()
{
  push_back_vector(first.id, first.letra);

  push_back_vector(first.idl, first.letra);
  push_back_vector(first.idl, first.digito);
  push_back_empty(first.idl);

  push_back_vector(first.num, first.digito);
  push_back_empty(first.num);

  //return 1;  
  //r_programa();
  while (token.nome != EOF) {
      token = proximo_token();
      if (token.nome == '.' )
        return 0;
  }
}
