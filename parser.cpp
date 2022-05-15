#include <stdio.h>
#include <iostream>
#include <vector>
#include "lexer.h"

using namespace std;

//PROGRAMA E BLOCO
void r_programa();
void r_bloco();
void r_bloco_l();
void r_bloco_ll();

//DECLARAÇÕES
void r_pdecl_var();
void r_decl();
void r_decl_l();
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
  vector<int> digit{'_','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', 'A', 'B', 'C', 'D', 'E', 'F', 'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  vector<int> letra{0,1,2,3,4,5,6,7,8,9};
  vector<int> tipo{INT, BOOLEAN};
  vector<int> programa;
  vector<int> bloco;
  vector<int> bloco_l;
  vector<int> bloco_ll;
  vector<int> pdecl_var;
  vector<int> decl;
  vector<int> decl_l;
  vector<int> decl_var;
  vector<int> listaid;
  vector<int> listaidl;
  vector<int> pdecl_subr;
  vector<int> decl_proc;
  vector<int> decl_procl;
  vector<int> param_form;
  vector<int> param_forml;
  vector<int> sec_param_form;
  vector<int> tipo;
  vector<int> comand_comp;
  vector<int> comand_compl;
  vector<int> comand_compll;
  vector<int> comand;
  vector<int> atrib;
  vector<int> chama_proc;
  vector<int> chama_procl;
  vector<int> comand_cond;
  vector<int> cond_else;
  vector<int> comand_rep;
  vector<int> expr;
  vector<int> expr_simp;
  vector<int> e;
  vector<int> el;
  vector<int> ell;
  vector<int> termo;
  vector<int> termol;
  vector<int> fator;
  vector<int> var;
  vector<int> list_expr;
  vector<int> list_exprl;
  vector<int> relacao;
  vector<int> num;
  vector<int> id;
  vector<int> idl;
};

First first;
Token token;

const int empty = 0;


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
  r_decl_var();
  r_decl();
}

void r_decl(){
  if (token.nome == ';') {

  }
}

void r_decl_l() {

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
  if (token.nome == ASSOP) {
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
  if (token.nome != RELOP)
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
  if (!isdigit(token.nome))
    cout<<"ERRO. Esperado token digito";
}

void r_letra() {
  token = proximo_token();
  if (!isalphabetic(token.nome))
    cout<<"ERRO. Esperado token letra";
}
  

int main()
{
  //r_programa();

  while (token.nome != EOF) {
      token = proximo_token();
      if (token.nome == '.' )
        return 0;
  }
}
