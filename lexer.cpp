#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <fstream>
#include <streambuf>
#include "lexer.h"

using namespace std;

int estado = 0;
int partida = 0;
int cont_simb_lido = 0;
vector<string> tabela_simb;

ifstream file("programa.txt");
string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

bool isspecialsymbol(char c)
{
    string cstring(1,c);
    regex re(R"([(){}[\]*+-/><=.,;:])");
    return regex_match(cstring, re);
}

bool iswhitespace(char c) { return (c == ' ') || (c == '\n') || (c == '\t'); }

bool isalphabetic(char c) { return (c == '_') || isalpha(c); }

bool isalphanum(char c) { return (c == '_') || isalnum(c); }

bool isallowedsymbol(char c) { return isalphanum(c) || iswhitespace(c) || isspecialsymbol(c); }

bool isresto(char c) {
    string cstring(1,c);
    regex re(R"([abdeinoptvw])");

    return isalphabetic(c) && !regex_match(cstring, re);
}


int falhar()
{
    return 404;
}

Token proximo_token()
{
    Token token;
    char c;
    string temp_id;
    string temp_num;

    while (code[cont_simb_lido] != EOF) {
        switch (estado) {
        case 0:
            c = code[cont_simb_lido];
            cont_simb_lido++;

            temp_id.clear();
            temp_id.push_back(c);
            temp_num.clear();
            temp_num.push_back(c);

            if (iswhitespace(c))
                estado = 0;
            else if (c == 'a')
                estado = 1;
            else if (c == 'b')
                estado = 4;
            else if (c == 'd')
                estado = 9;
            else if (c == 'e')
                estado = 11;
            else if (c == 'i')
                estado = 17;
            else if (c == 'n')
                estado = 19;
            else if (c == 'o')
                estado = 22;
            else if (c == 'p')
                estado = 24;
            else if (c == 't')
                estado = 37;
            else if (c == 'v')
                estado = 41;
            else if (c == 'w')
                estado = 44;
            else if (isresto(c))
                estado = 49;
            else if (isdigit(c))
                estado = 50;
            else if (c == '+')
                estado = 51;
            else if (c == '-')
                estado = 52;
            else if (c == '*')
                estado = 53;
            else if (c == '<')
                estado = 54;
            else if(c == '>')
                estado = 57;
            else if(c == '=')
                estado = 59;
            else if(c == ',')
                estado = 60;
            else if(c == ';')
                estado = 61;
            else if(c == ':')
                estado = 62;
            else if(c == '(' )
                estado = 64;
            else if(c == ')' )
                estado = 65;
            else if(c == '[' )
                estado = 66;
            else if(c == ']' )
                estado = 67;
            else if(c == '{' )
                estado = 68;
            else if(c == '}' )
                estado = 69;
            else if(c == '/' )
                estado = 70;
            else if(c == '.' )
                estado = 72;
            else
                estado = falhar();
            break;

        case 1:
            c = code[cont_simb_lido];
            if (c == 'n') {
                cont_simb_lido++;
                temp_id += c;
                estado = 2;
            }
            else
                estado = 99;
            break;

        case 2:
            c = code[cont_simb_lido];
            if (c == 'd') {
                cont_simb_lido++;
                temp_id += c;
                estado = 3;
            }
            else
                estado = 99;
            break;

        case 3:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<logop, AND>\n");
                token.nome_token = LOGOP;
                token.atributo = AND;
                estado = 0;
                return(token);
            }
            else
                estado = 99;
            break;

        case 4:
            c = code[cont_simb_lido];
            if (c == 'e'){
                cont_simb_lido++;
                temp_id += c;
                estado = 5;
            }
            else if(c == 'o') {
                cont_simb_lido++;
                temp_id += c;
                estado = 78;
            }
            else
                estado = 99;
            break;

        case 5:
            c = code[cont_simb_lido];
            if (c == 'g'){
                cont_simb_lido++;
                temp_id += c;
                estado = 6;
            }
            else
                estado = 99;
            break;

        case 6:
            c = code[cont_simb_lido];
            if (c == 'i'){
                cont_simb_lido++;
                temp_id += c;
                estado = 7;
            }
            else
                estado = 99;
            break;

        case 7:
            c = code[cont_simb_lido];
            if (c == 'n'){
                cont_simb_lido++;
                temp_id += c;
                estado = 8;
            }
            else
                estado = 99;
            break;

        case 8:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<begin, >\n");
                token.nome_token = BEGIN;
                token.atributo = -1;
                estado = 0;
                return(token);
            }
            else
                estado = 99;
            break;

        case 9:
            c = code[cont_simb_lido];
            if (c == 'o'){
                cont_simb_lido++;
                temp_id += c;
                estado = 10;
            }
            else if (c == 'i'){
                cont_simb_lido++;
                temp_id += c;
                estado = 74;
            }
            else
                estado = 99;
            break;

        case 10:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<do, >\n");
                token.nome_token = DO;
                token.atributo = -1;
                estado = 0;
                return(token);
            } else
                estado = 99;
            break;

        case 11:
            c = code[cont_simb_lido];
            if (c == 'n'){
                cont_simb_lido++;
                temp_id += c;
                estado = 12;
            }
            else if (c == 'l'){
                cont_simb_lido++;
                temp_id += c;
                estado = 14;
            }
            else
                estado = 99;
            break;

        case 12:
            c = code[cont_simb_lido];
            if (c == 'd'){
                cont_simb_lido++;
                temp_id += c;
                estado = 13;
            }
            else
                estado = 99;
            break;

        case 13:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<end, >\n");
                token.nome_token = END;
                token.atributo = -1;
                estado = 0;
                return(token);
            }
            else if(c == '.'){
                printf("<end, >\n");
                token.nome_token = END;
                token.atributo = -1;
                estado = 72;
                return(token);
            }
            else
                estado = 99;
            break;

        case 14:
            c = code[cont_simb_lido];
            if (c == 's'){
                cont_simb_lido++;
                temp_id += c;
                estado = 15;
            }
            else
                estado = 99;
            break;

        case 15:
            c = code[cont_simb_lido];
            if (c == 'e'){
                cont_simb_lido++;
                temp_id += c;
                estado = 16;
            }
            else
                estado = 99;
            break;

        case 16:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<else, >\n");
                token.nome_token = ELSE;
                token.atributo = -1;
                estado = 0;
                return(token);
            }
            else
                estado = 99;
            break;

        case 17:
            c = code[cont_simb_lido];
            if (c == 'f'){
                cont_simb_lido++;
                temp_id += c;
                estado = 18;
            }
            else if(c == 'n') {
                cont_simb_lido++;
                 temp_id += c;
                 estado = 76;
            }
            else
                estado = 99;
            break;

        case 18:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<if, >\n");
                token.nome_token = IF;
                token.atributo = -1;
                estado = 0;
                return(token);
            }
            else
                estado = 99;
            break;

        case 19:
            c = code[cont_simb_lido];
            if (c == 'o'){
                cont_simb_lido++;
                temp_id += c;
                estado = 20;
            }
            else
                estado = 99;
            break;

        case 20:
            c = code[cont_simb_lido];
            if (c == 't'){
                cont_simb_lido++;
                temp_id += c;
                estado = 21;
            }
            else
                estado = 99;
            break;

        case 21:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<logop, NOT>\n");
                token.nome_token = LOGOP;
                token.atributo = NOT;
                estado = 0;
                return(token);
            }
            else
                estado = 99;
            break;

        case 22:
            c = code[cont_simb_lido];
            if (c == 'r'){
                cont_simb_lido++;
                temp_id += c;
                estado = 23;
            }
            else
                estado = 99;
            break;

        case 23:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<logop, OR>\n");
                token.nome_token = LOGOP;
                token.atributo = OR;
                estado = 0;
                return(token);
            }
            else
                estado = 99;
            break;

        case 24:
            c = code[cont_simb_lido];
            if (c == 'r'){
                cont_simb_lido++;
                temp_id += c;
                estado = 25;
            }
            else
                estado = 99;
            break;

        case 25:
            c = code[cont_simb_lido];
            if (c == 'o'){
                cont_simb_lido++;
                temp_id += c;
                estado = 26;
            }
            else
                estado = 99;
            break;

        case 26:
            c = code[cont_simb_lido];
            if (c == 'g'){
                cont_simb_lido++;
                temp_id += c;
                estado = 27;
            }
            else if (c == 'c'){
                cont_simb_lido++;
                temp_id += c;
                estado = 31;
            }
            else
                estado = 99;
            break;

        case 27:
            c = code[cont_simb_lido];
            if (c == 'r'){
                cont_simb_lido++;
                temp_id += c;
                estado = 28;
            }
            else
                estado = 99;
            break;

        case 28:
            c = code[cont_simb_lido];
            if (c == 'a'){
                cont_simb_lido++;
                temp_id += c;
                estado = 29;
            }
            else
                estado = 99;
            break;

        case 29:
            c = code[cont_simb_lido];
            if (c == 'm'){
                cont_simb_lido++;
                temp_id += c;
                estado = 30;
            }
            else
                estado = 99;
            break;

        case 30:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (iswhitespace(c)) {
                printf("<program, >\n");
                token.nome_token = PROGRAM;
                token.atributo = -1;
                estado = 0;
                return(token);
            }
            else
                estado = 99;
            break;

        case 31:
            c = code[cont_simb_lido];
            if (c == 'e'){
                cont_simb_lido++;
                temp_id += c;
                estado = 32;
            }
            else
                estado = 99;
            break;

        case 32:
            c = code[cont_simb_lido];
            if (c == 'd'){
                cont_simb_lido++;
                temp_id += c;
                estado = 33;
            }
            else
                estado = 99;
            break;

        case 33:
            c = code[cont_simb_lido];
            if (c == 'u'){
                cont_simb_lido++;
                temp_id += c;
                estado = 34;
            }
            else
                estado = 99;
            break;

        case 34:
            c = code[cont_simb_lido];
            if (c == 'r'){
                cont_simb_lido++;
                temp_id += c;
                estado = 35;
            }
            else
                estado = 99;
            break;

        case 35:
            c = code[cont_simb_lido];
            if (c == 'e'){
                cont_simb_lido++;
                temp_id += c;
                estado = 36;
            }
            else
                estado = 99;
            break;

        case 36:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (iswhitespace(c)) {
                printf("<procedure, >\n");
                token.nome_token = PROCEDURE;
                token.atributo = -1;
                estado = 0;
                return(token);
            }
            else
                estado = 99;
            break;

        case 37:
            c = code[cont_simb_lido];
            if (c == 'h'){
                cont_simb_lido++;
                temp_id += c;
                estado = 38;
            }
            else
                estado = 99;
            break;

        case 38:
            c = code[cont_simb_lido];
            if (c == 'e'){
                cont_simb_lido++;
                temp_id += c;
                estado = 39;
            }
            else
                estado = 99;
            break;

        case 39:
            c = code[cont_simb_lido];
            if (c == 'n'){
                cont_simb_lido++;
                temp_id += c;
                estado = 40;
            }
            else
                estado = 99;
            break;

        case 40:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (iswhitespace(c)) {
                printf("<then, >\n");
                token.nome_token = THEN;
                token.atributo = -1;
                estado = 0;
                return(token);
            }
            else
                estado = 99;
            break;

        case 41:
            c = code[cont_simb_lido];
            if (c == 'a'){
                cont_simb_lido++;
                temp_id += c;
                estado = 42;
            }
            else
                estado = 99;
            break;

        case 42:
            c = code[cont_simb_lido];
            if (c == 'r'){
                cont_simb_lido++;
                temp_id += c;
                estado = 43;
            }
            else
                estado = 99;
            break;

        case 43:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (iswhitespace(c)) {
                printf("<var, >\n");
                token.nome_token = VAR;
                token.atributo = -1;
                estado = 0;
                return(token);
            }
            else
                estado = 99;
            break;

        case 44:
            c = code[cont_simb_lido];
            if (c == 'h'){
                cont_simb_lido++;
                temp_id += c;
                estado = 45;
            }
            else
                estado = 99;
            break;

        case 45:
            c = code[cont_simb_lido];
            if (c == 'i'){
                cont_simb_lido++;
                temp_id += c;
                estado = 46;
            }
            else
                estado = 99;
            break;

        case 46:
            c = code[cont_simb_lido];
            if (c == 'l'){
                cont_simb_lido++;
                temp_id += c;
                estado = 47;
            }
            else
                estado = 99;
            break;

        case 47:
            c = code[cont_simb_lido];
            if (c == 'e'){
                cont_simb_lido++;
                temp_id += c;
                estado = 48;
            }
            else
                estado = 99;
            break;

        case 48:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (iswhitespace(c)) {
                printf("<while, >\n");
                token.nome_token = WHILE;
                token.atributo = -1;
                estado = 0;
                return(token);
            }
            else
                estado = 99;
            break;

        case 49:
            //estado redundante
            //porem necessario para controle
            estado = 99;
            break;

        case 50:
            c = code[cont_simb_lido];
            if(isdigit(c)) {
                cont_simb_lido++;
                temp_num += c;
                estado = 50;
            }
            else {
                printf("<num, %s>\n",temp_num.c_str());
                token.nome_token = NUM;
                token.atributo = atoi(temp_num.c_str());
                estado = 0;
                return (token);
            }
            break;

        case 51:
            printf("<ariop, PLUS>\n");
            token.nome_token = ARIOP;
            token.atributo = PLUS;
            estado = 0;
            return (token);
            break;

        case 52:
            printf("<ariop, MINUS>\n");
            token.nome_token = ARIOP;
            token.atributo = MINUS;
            estado = 0;
            return (token);
            break;

        case 53:
            printf("<ariop, MULTI>\n");
            token.nome_token = ARIOP;
            token.atributo = MULTI;
            estado = 0;
            return (token);
            break;

        case 54:
            c = code[cont_simb_lido];
            if (c == '=') {
                cont_simb_lido++;
                estado = 55;
            }
            else if (c == '>') {
                cont_simb_lido++;
                estado = 56;
            }
            else {
                printf("<relop, LT>\n");
                token.nome_token = RELOP;
                token.atributo = LT;
                estado = 0;
                return (token);
            }
            break;

        case 55:
            printf("<relop, LE>\n");
            token.nome_token = RELOP;
            token.atributo = LE;
            estado = 0;
            return (token);
            break;

        case 56:
            printf("<relop, NE>\n");
            token.nome_token = RELOP;
            token.atributo = NE;
            estado = 0;
            return (token);
            break;

        case 57:
            c = code[cont_simb_lido];
            if(c == '=') {
                cont_simb_lido++;
                estado = 58;
            }
            else {
                printf("<relop, GT>\n");
                token.nome_token = RELOP;
                token.atributo = GT;
                estado = 0;
                return(token);
            }
            break;

        case 58:
            printf("<relop, GE>\n");
            token.nome_token = RELOP;
            token.atributo = GE;
            estado = 0;
            return(token);
            break;

        case 59:
            printf("<relop, EQ>\n");
            token.nome_token = RELOP;
            token.atributo = EQ;
            estado = 0;
            return(token);
            break;

        case 60:
            printf("<,, >\n");
            token.nome_token = c;
            token.atributo = -1;
            estado = 0;
            return(token);
            break;

        case 61:
            printf("<;, >\n");
            token.nome_token = c;
            token.atributo = -1;
            estado = 0;
            return(token);
            break;

        case 62:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if(c == '=') estado = 63;
            else estado = falhar();
            break;

        case 63:
            printf("<assop, >\n");
            token.nome_token = ASSOP;
            token.atributo = -1;
            estado = 0;
            return(token);
            break;

        case 64:
            printf("<(, >\n");
            token.nome_token = c;
            token.atributo = -1;
            estado = 0;
            return(token);
            break;

        case 65:
            printf("<), >\n");
            token.nome_token = c;
            token.atributo = -1;
            estado = 0;
            return(token);
            break;

        case 66:
            printf("<[, >\n");
            token.nome_token = c;
            token.atributo = -1;
            estado = 0;
            return(token);
            break;

        case 67:
            printf("<], >\n");
            token.nome_token = c;
            token.atributo = -1;
            estado = 0;
            return(token);
            break;

        case 68:
            printf("<{, >\n");
            token.nome_token = c;
            token.atributo = -1;
            estado = 0;
            return(token);
            break;

        case 69:
            printf("<}, >\n");
            token.nome_token = c;
            token.atributo = -1;
            estado = 0;
            return(token);
            break;

        case 70:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if(c == '/') estado = 71;
            else estado = falhar();
            break;

        case 71:
            printf("<lcomm, >\n");
            token.nome_token = LCOMM;
            token.atributo = -1;
            estado = 0;
            return(token);
            break;

        case 72:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if(!isallowedsymbol(c)) estado = 73;
            else estado = falhar();
            break;

        case 73:
            printf("<., >\n");
            token.nome_token = '.';
            token.atributo = -1;
            estado = 0;
            return(token);
            break;

        case 74:
            c = code[cont_simb_lido];
            if (c == 'v'){
                cont_simb_lido++;
                temp_id += c;
                estado = 75;
            }
            else
                estado = 99;
            break;

        case 75:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<ariop, DIV>\n");
                token.nome_token = ARIOP;
                token.atributo = DIV;
                estado = 0;
                return (token);
                break;
            }
            else
                estado = 99;
            break;

         case 76:
            c = code[cont_simb_lido];
            if (c == 't'){
                cont_simb_lido++;
                temp_id += c;
                estado = 77;
            }
            else
                estado = 99;
            break;

        case 77:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<int, >\n");
                token.nome_token = INT;
                token.atributo = -1;
                estado = 0;
            }
            else
                estado = 99;
            break;

        case 78:
            c = code[cont_simb_lido];
            if (c == 'o'){
                cont_simb_lido++;
                temp_id += c;
                estado = 79;
            }
            else
                estado = 99;
            break;

        case 79:
            c = code[cont_simb_lido];
            if (c == 'l'){
                cont_simb_lido++;
                temp_id += c;
                estado = 80;
            }
            else
                estado = 99;
            break;

        case 80:
            c = code[cont_simb_lido];
            if (c == 'e'){
                cont_simb_lido++;
                temp_id += c;
                estado = 81;
            }
            else
                estado = 99;
            break;

        case 81:
            c = code[cont_simb_lido];
            if (c == 'a'){
                cont_simb_lido++;
                temp_id += c;
                estado = 82;
            }
            else
                estado = 99;
            break;

         case 82:
            c = code[cont_simb_lido];
            if (c == 'n'){
                cont_simb_lido++;
                temp_id += c;
                estado = 83;
            }
            else
                estado = 99;
            break;

         case 83:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<boolean, >\n");
                token.nome_token = BOOLEAN;
                token.atributo = -1;
                estado = 0;
            }
            else
                estado = 99;
            break;


        case 99:
            c = code[cont_simb_lido];
            cont_simb_lido++;

            if (!isallowedsymbol(c))
            {
                estado = falhar();
            }
            else if (isalphanum(c))
            {
                temp_id += c;
                estado = 99;
            }
            else
            {
                vector<string>::iterator it = find(tabela_simb.begin(), tabela_simb.end(), temp_id);
                int indice_id = distance(tabela_simb.begin(), it);

                bool achou_id = (it != tabela_simb.end());
                if(!achou_id) tabela_simb.push_back(temp_id);

                //cout<<endl<<temp_id<<endl;
                printf("<id, %d>\n", indice_id+1);
                token.nome_token = ID;
                token.atributo = indice_id;
                cont_simb_lido--;
                estado = 0;
                return (token);
            }
            break;

        case 404:
            printf("Erro de compilacao");
            //cout<<endl<<temp_id<<endl;
            token.nome_token = EOF;
            token.atributo = -1;
            return (token);
            break;
        }
    }
    token.nome_token = EOF;
    token.atributo = -1;
    return (token);
}