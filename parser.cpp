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
void r_lista_id();
void r_lista_idl();
void r_p_decl_subr();
void r_decl_proc();
void r_decl_procl();
void r_param_form();
void r_param_forml();
void r_sec_param_form();
void r_tipo();

//COMANDOS
void r_comand_comp();
void r_comand_compl();
void r_comand();
void r_atrib();
void r_chama_proc();
void r_chama_procl();
void r_comand_cond();
void r_cond_else();
void r_comand_rep();

//EXPRESSOES

void r_list_expr();
void r_list_exprl();
void r_expr();
void r_exprl();
void r_expr_simp();
void r_e();
void r_el();
void r_ell();
void r_termo();
void r_termol();
void r_fator();
void r_var();
void r_relacao();

//NUMEROS E IDENTIFICADORES
void r_num();
void r_id();
void r_idl();
void r_digit();
void r_letra();

struct First {
  vector<int> id {ID};
  vector<int> num {NUM};
  vector<int> tipo {INT, BOOLEAN};
  vector<int> relacao {RELOP};
  vector<int> programa, bloco, blocol, blocoll, p_decl_var, decl, decll, decl_var, listaid, listaidl, p_decl_subr, decl_proc, decl_procl, param_form, param_forml, sec_param_form, comand_comp,comand_compl,comand_compll,comand,atrib,chama_proc,chama_procl,comand_cond,cond_else,comand_rep,expr,expr_simp,e,el,ell,termo,termol,fator,var,list_expr,list_exprl;
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
  cout << "ERRO. Esperado token "<< output << endl;
}



//PROGRAMA E BLOCO
void r_programa(){
  if (token.nome == PROGRAM ){
    cout<<"<parser, program"<<endl;
    token = proximo_token();
    r_id();
    if(token.nome == ';'){
      cout<<"<parser, ;"<<endl;
      token = proximo_token();
      r_bloco();
    }
    print_parser(";");
  }
  else
    print_parser("program");
}

void r_bloco() {
  r_blocol();
  r_comand_comp();  
}

void r_blocol(){
  cout<<"blocol";
  if (vector_contains(first.p_decl_var, token.nome)) {
    cout<<"if";
    r_p_decl_var();
    r_blocoll();
  }
}

void r_blocoll(){
  if (vector_contains(first.p_decl_subr, token.nome))
    r_p_decl_subr();
}

//DECLARACOES

void r_p_decl_var(){
    r_decl_var();
    r_decl();
}

void r_decl(){
  if (token.nome == ';') {
    cout<<"<parser, ;"<<endl;
    token = proximo_token();
    r_decll();
  }
  else
    print_parser(";");
}

void r_decll() {
  if (vector_contains(first.p_decl_var, token.nome)) {
    token = proximo_token();
    cout<<"<parser, first(p_decl_var)"<<endl;
    r_p_decl_var();
  }
}


void r_decl_var(){
    r_tipo();
    r_lista_id();
}

void r_lista_id(){
    r_id();
    r_lista_idl();
  }

void r_lista_idl(){
  if (token.nome == ','){
    token = proximo_token();
    cout<<"<parser, ,"<<endl;
    r_lista_idl();   
  }
}

void r_p_decl_subr(){
  if (vector_contains(first.decl_proc, token.nome)){
    //token = proximo_token();
    r_decl_proc();
    if (token.nome == ';'){
      cout<<"<parser, ;"<<endl;
      token = proximo_token();
      r_p_decl_subr();
    }
    else
      print_parser(";");
  } 
}

void r_decl_proc(){
  if (token.nome == PROCEDURE){
    cout<<"<parser, PROCEDURE"<<endl;
    token = proximo_token();
    r_id();
    r_decl_procl();
    if (token.nome == ';'){
      
    }
  }
}

void r_decl_procl(){
  if (vector_contains(first.param_form, token.nome)){
    r_param_form();
  } 
}

void r_param_form(){
  if (token.nome == '('){
    cout<<"<parser, ("<<endl;
    token = proximo_token();
    r_sec_param_form();
    r_param_forml();
    if (token.nome == ')'){
      cout<<"<parser, )"<<endl;
      token = proximo_token();
    }
    else
      print_parser(")");
  }
}

void r_param_forml(){
  if (token.nome == ';'){
    cout<<"<parser, ;"<<endl;
    token = proximo_token();
    r_sec_param_form();
    r_param_forml();   
  }
  else
    print_parser(";");
  
}


void r_sec_param_form(){
  if (vector_contains(first.listaid, token.nome)){
    r_lista_id();
    if (token.nome == ':'){
      cout<<"<parser, :"<<endl;
      token = proximo_token();
      r_id();
    }
    else
      print_parser(":");
  }
  if (vector_contains(first.var, token.nome)){
    r_var();
    r_lista_id();
    if (token.nome == ':'){
      cout<<"<parser, :"<<endl;
      token = proximo_token();
      r_id();
    }
    else
      print_parser(":");
  }
}


//COMANDOS

void r_comand_comp(){
  if (token.nome ==  BEGIN) {
    cout<<"<parser, begin>"<<endl;
    token = proximo_token();
    r_comand();
    r_comand_compl();
    if (token.nome ==  END){
      cout<<"<parser, end>"<<endl;
      token = proximo_token();
    }
    else
      print_parser("END");
  }
  else
     print_parser("BEGIN");
}

void r_comand_compl(){
  if (token.nome ==  ';') {
    cout<<"<parser, ;>"<<endl;
    token = proximo_token();
    r_comand();
    r_comand_compl();
  }
}

void r_comand(){
  if (vector_contains(first.atrib, token.nome))
    r_atrib();
  else if (vector_contains(first.chama_proc, token.nome))
    r_chama_proc();
  else if (vector_contains(first.comand_comp, token.nome))
    r_comand_comp();
  else if (vector_contains(first.comand_cond, token.nome))
    r_comand_cond();
  else if (vector_contains(first.comand_rep, token.nome))
    r_comand_rep();
    
}

void r_atrib() {  
  r_var();
  if (token.nome == ASSOP) {
    cout<<"<parser, assop>"<<endl;
    token = proximo_token();
    r_expr();
  }
  else {
    print_parser("ASSOP");
  }
}

void r_chama_proc(){
  r_id();
  r_chama_procl();
}

void r_chama_procl(){
  if (token.nome == '(') {
    cout<<"<parser, (>"<<endl;
    token = proximo_token();
    r_list_expr();
    if (token.nome == ')'){
      cout<<"<parser, )>"<<endl;
      token = proximo_token();
    }
    else
      print_parser(")");
  }
}

void r_comand_cond(){
  if (token.nome == IF) {
    cout<<"<parser, if>"<<endl;
    token = proximo_token();
    r_expr();
    if (token.nome == THEN) {
      cout<<"<parser, then>"<<endl;
      token = proximo_token();
      r_comand();
      r_cond_else();
    }
    else
      print_parser("then");
  }
  else
    print_parser("if");
}

void r_cond_else(){
  if (token.nome == ELSE) {
    cout<<"<parser, else>"<<endl;
    token = proximo_token();
    r_comand();  
  }
}

void r_comand_rep(){
  if (token.nome == WHILE) {
    cout<<"<parser, while>"<<endl;
    token = proximo_token();
    r_expr();
    if (token.nome == DO) {
      cout<<"<parser, do>"<<endl;
      token = proximo_token();
      r_comand();
    }
    else
      print_parser("do");
  }
  else
    print_parser("while");
}


//EXPRESSOES
void r_list_expr() {
  if (vector_contains(first.expr, token.nome)) {
    r_expr();

    token = proximo_token();
    if(vector_contains(first.list_exprl, token.nome)) {
      r_list_exprl();
    }
  }
}

void r_list_exprl() {
  if(token.nome == ',') {
    cout<<"<parser, ,>"<<endl;
    token = proximo_token();
    r_list_expr();
  }
  return;
}

void r_expr() {
  if(vector_contains(first.expr_simp, token.nome)) {
    r_expr_simp();

    token = proximo_token();
    r_exprl();
  }
}

void r_exprl() {
  if(token.nome == RELOP) {
    cout<<"<parser, relop>"<<endl;
    r_relacao();

    token = proximo_token();
    r_expr_simp();
  }
  return;
}

void r_expr_simp() {
  if(token.atributo == PLUS || token.atributo == MINUS) {
    cout<<"<parser, + ->"<<endl;
    token = proximo_token();
  }
  r_el();
}

void r_el() {
  if (vector_contains(first.termo, token.nome)) {
    r_termo();
    
    token = proximo_token();
    r_ell();

    token = proximo_token();
    r_el();
  }
}

void r_ell() {
  if(token.atributo == PLUS || token.atributo == MINUS || token.atributo == OR) {
    token = proximo_token();
    r_termo();
  }
  
}

void r_termo() {
  if (vector_contains(first.fator, token.nome)) {
    r_fator();

    token = proximo_token();
    r_termol();
  }
  else
    print_parser("first(TERMO)");
}

void r_termol() {
  if(token.atributo == MULTI || token.atributo == DIV || token.atributo == AND) {
    token = proximo_token();
    r_termo();
  }
}

void r_fator() {
  if (token.atributo == NOT) {
    token = proximo_token();
    r_fator();
  }
  else if (token.nome == '(') {
    cout<<"<parser, (>"<<endl;
    token = proximo_token();
    r_expr();

    if(token.nome == ')'){
      cout<<"<parser, )>"<<endl;
      return;
    }
    else
      print_parser(")");
  }
  else if (vector_contains(first.var, token.nome)) {
    r_var();
  }
  else if (vector_contains(first.num, token.nome)) {
    r_num();
  }
  else print_parser("first(FATOR)");
}

void r_var() {
  if (token.nome == ID) {
    token = proximo_token();
    r_expr();
  }
  else
    print_parser("ID");
}

void r_tipo() {
  if (!vector_contains(first.tipo, token.nome)) {
    print_parser("INT ou BOOLEAN");
  }
  cout<<"<parser, int boolean>"<<endl;
  
}

void r_relacao() {
  if (token.nome == RELOP)
    token = proximo_token();
  else
    print_parser("RELOP");
}

void r_num(){
  if (token.nome == NUM)
    token = proximo_token();
  else
    print_parser("NUM");
}

void r_id(){ 
    if (token.nome == ID){
      cout<<"<parser, id>"<<endl;
      token = proximo_token();
    }
    else
      print_parser("ID");
}


int main()
{
  //TODO: declaracao dos firsts

  token = proximo_token();
  r_programa();
}
