#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

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
char* code;
string temp_id;
string temp_num;
vector<string> tabela_simb;

char* readFile(char* fileName)
{
    FILE* file = fopen(fileName, "r");
    char* code;
    int n = 0;
    int c;

    if (file == NULL)
        return NULL;

    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    code = new char(f_size);

    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
    }
    code[n] = '\0';
    return code;
}

int falhar()
{
    switch (estado) {
    case 0:
        partida = 9;
        break;

    case 9:
        partida = 12;
        break;

    case 12:
        partida = 20;
        break;

    case 20:
        partida = 25;
        break;

    case 25:
        //retornar msg de erro
        printf("Erro encontrado no código\n");
        break;

    default:
        printf("Erro do compilador");
    }
    return (partida);
}

bool isspecialsymbol(char c)
{
    string cstring(1,c);
    regex re(R"([(){}[\]*+-/><=.,;:])");
    return regex_match(cstring, re);
}

bool iswhitespace(char c)
{
    return c == ' ' || c == '\n' || c == '\t';
}

bool isalphabetic(char c)
{
    return isalpha(c) || c == '_';
}

bool isalphanum(char c)
{
    return isalphanum(c) || c == '_';
}

bool isallowedsymbol(char c)
{
    return isalphanum(c) || iswhitespace(c) || isspecialsymbol(c);
}

Token proximo_token()
{
    Token token;
    char c;
    while (code[cont_simb_lido] != EOF) {
        switch (estado) {
        case 0:
            c = code[cont_simb_lido];
            cont_simb_lido++;

            temp_id.clear();
            temp_id.push_back(c);
            temp_num.clear();
            temp_num.push_back(c);

            if (iswhitespace(c)) {
                estado = 0;
            } else if (c == 'a')
                estado = 1;
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
            else {
                printf("chama falha");
                estado = falhar();
            }
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

        case 99:
            c = code[cont_simb_lido];
            while (isalphanum(c)) {
                cont_simb_lido++;
                temp_id += c;
                c = code[cont_simb_lido];
            }
            cout << temp_id;
            break;

            vector<string>::iterator it = find(tabela_simb.begin(), tabela_simb.end(), temp_id);
            int indice_id = distance(tabela_simb.begin(), it);
            bool achou_id = it != tabela_simb.end(); 

            if(!achou_id) {
                tabela_simb.push_back(temp_id);
                indice_id++;
            }

            printf("<id, %d>\n", indice_id);
            token.nome_token = ID;
            token.atributo = indice_id;
            estado = 0;
            return (token);
        }
    }
    token.nome_token = EOF;
    token.atributo = -1;
    return (token);
}

int main()
{
    Token token;
    code = readFile((char*)"programa.txt");

    while (token.nome_token != EOF) {
        token = proximo_token();
    }
    //...
}
