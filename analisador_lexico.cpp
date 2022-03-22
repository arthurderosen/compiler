#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <fstream>
#include <streambuf>

using namespace std;

//NOME TOKENS
#define IF 256;
#define THEN 257;
#define ELSE 258;
#define BEGIN 259;
#define END 260;
#define DO 261;
#define WHILE 262
#define PROCEDURE 263;
#define PROGRAM 264;
#define VAR 265;
#define RELOP 266;
#define ARIOP 267;
#define LOGOP 268;
#define ID 269;
#define NUM 270;

//ATRIBUTOS
//relop
#define LT 300;
#define LE 301;
#define EQ 302;
#define NE 303;
#define GT 304;
#define GE 305;
//ariop
#define DIV 306;
#define PLUS 307;
#define MINUS 308;
#define MULTI 309;
//logop;
#define AND 310;
#define OR 311;
#define NOT 312;

struct Token {
    int nome_token;
    int atributo;
};

int estado = 0;
int partida = 0;
int cont_simb_lido = 0;
vector<string> tabela_simb;

ifstream file("programa.txt");
string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

int falhar()
{
    return 404;
}

bool isspecialsymbol(char c)
{
    string cstring(1,c);
    regex re(R"([(){}[\]*+-/><=.,;:])");
    return regex_match(cstring, re);
}

bool iswhitespace(char c)
{
    return (c == ' ') || (c == '\n') || (c == '\t');
}

bool isalphabetic(char c)
{
    return (c == '_') || isalpha(c);
}

bool isalphanum(char c)
{
    return (c == '_') || isalnum(c);
}

bool isallowedsymbol(char c)
{
    return isalphanum(c) || iswhitespace(c) || isspecialsymbol(c);
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
            else
                estado = falhar();
            break;

        case 1:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'n')
                estado = 2;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 2:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'd')
                estado = 3;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 3:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<logop, AND>\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 4:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'e')
                estado = 5;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 5:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'g')
                estado = 6;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 6:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'i')
                estado = 7;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 7:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'n')
                estado = 8;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 8:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<begin, >\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 9:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'o')
                estado = 10;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 10:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<do, >\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 11:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'n')
                estado = 12;
            else if (c == 'l')
                estado = 14;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 12:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'd')
                estado = 13;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 13:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<end, >\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 14:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 's')
                estado = 15;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 15:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'e')
                estado = 16;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 16:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<else, >\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 17:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'f')
                estado = 18;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 18:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<if, >\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 19:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'o')
                estado = 20;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 20:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 't')
                estado = 21;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 21:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<logop, NOT>\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 22:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (c == 'r')
                estado = 23;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 23:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            temp_id += c;
            if (iswhitespace(c)) {
                printf("<logop, OR>\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 24:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'r')
                estado = 25;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 25:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'o')
                estado = 26;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 26:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'g')
                estado = 27;
            else if (c == 'c')
                estado = 31;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 27:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'r')
                estado = 28;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 28:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'a')
                estado = 29;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 29:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'm')
                estado = 30;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 30:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (iswhitespace(c)) {
                printf("<program, >\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 31:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'e')
                estado = 32;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 32:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'd')
                estado = 33;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 33:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'u')
                estado = 34;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 34:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'r')
                estado = 35;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 35:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'e')
                estado = 36;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 36:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (iswhitespace(c)) {
                printf("<procedure, >\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 37:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'h')
                estado = 38;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 38:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'e')
                estado = 39;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 39:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'n')
                estado = 40;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 40:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (iswhitespace(c)) {
                printf("<then, >\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 41:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'a')
                estado = 42;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 42:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'r')
                estado = 43;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 43:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (iswhitespace(c)) {
                printf("<var, >\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 44:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'h')
                estado = 45;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 45:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'i')
                estado = 46;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 46:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'l')
                estado = 47;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 47:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (c == 'e')
                estado = 48;
            else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
            break;

        case 48:
            c = code[cont_simb_lido];
            cont_simb_lido++;
            if (iswhitespace(c)) {
                printf("<while, >\n");
                estado = 0;
            } else if (isalphanum(c))
                estado = 99;
            else
                estado = falhar();
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
            cont_simb_lido++;
            if (c == '=')
                estado = 55;
            else if (c == '>')
                estado = 56;
            else {
                printf("<relop, LT>\n");
                token.nome_token = LOGOP;
                token.atributo = LT;
                estado = 0;
                return (token);
            }
            break;

        case 55:
            printf("<relop, LE>\n");
            token.nome_token = LOGOP;
            token.atributo = LE;
            estado = 0;
            return (token);
            break;

        case 56:
            printf("<relop, NE>\n");
            token.nome_token = LOGOP;
            token.atributo = NE;
            estado = 0;
            return (token);
            break;

        case 57:
                c = code[cont_simb_lido];
                cont_simb_lido++;
                if(c == '=') estado = 58;
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
                printf("<, >\n");
                token.nome_token = 44;
				        token.atributo = -1;
                estado = 0;
                return(token);
                break;

            case 61:
                printf("<;, >\n");
                token.nome_token = 59;
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
                printf("<:=, >\n");
                token.nome_token = 99;
                token.atributo = -1;
                estado = 0;
                return(token);
                break;

            case 64:
                printf("<(, >\n");
                token.nome_token = 40;
				token.atributo = -1;
                estado = 0;
                return(token);
                break;

            case 65:
                printf("<), >\n");
                token.nome_token = 41;
				token.atributo = -1;
                estado = 0;
                return(token);
                break;

            case 66:
                printf("<[, >\n");
                token.nome_token = 91;
				token.atributo = -1;
                estado = 0;
                return(token);
                break;

            case 67:
                printf("<], >\n");
                token.nome_token = 93;
				token.atributo = -1;
                estado = 0;
                return(token);
                break;

            case 68:
                printf("<{, >\n");
                token.nome_token = 123;
				token.atributo = -1;
                estado = 0;
                return(token);
                break;

            case 69:
                printf("<}, >\n");
                token.nome_token = 125;
				token.atributo = -1;
                estado = 0;
                return(token);
                break;

        case 99: {
            c = code[cont_simb_lido];

            while (isalphanum(c)) {
                temp_id += c;
                c = code[++cont_simb_lido];
            }

            vector<string>::iterator it = find(tabela_simb.begin(), tabela_simb.end(), temp_id);
            int indice_id = distance(tabela_simb.begin(), it);
            bool achou_id = (it != tabela_simb.end());

            if(!achou_id)
                tabela_simb.push_back(temp_id);

            printf("<id, %d>\n", indice_id);
            token.nome_token = ID;
            token.atributo = indice_id;
            estado = 0;
            }
            return (token);
            break;

        case 404:
            printf("Erro de compilacao");
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

int main()
{
    Token token;

    while (token.nome_token != EOF) {
        token = proximo_token();
    }

}
