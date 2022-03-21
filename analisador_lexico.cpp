/*
 * ESTE CÓDIGO IMPLEMENTA UM ANALIZADOR LÉXICO PARA O EXEMPLO DE FRAGMENTO DE LINGUAGEM APRESENTADO EM SALA DE AULA (VEJA OS SLIDES DA AULA 4: ANÁLISE LÉXICA: PARTE 2)
 * E PODERÁ SER UTILIZADO COMO PONTO DE PARTIDA PARA IMPLEMENTAÇÃO DO ANALISADOR LÉXICO PARA LINGUAGEM ADOTADA NO TRABALHO PROPOSTO.
 * */

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

//NOME TOKENS
#define IF  256;
#define THEN  257;
#define ELSE  258;
#define RELOP  259;
#define LOGOP 260;
#define ARIOP 261;
#define ID  262;
#define NUM  263;


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




struct Token{
 int nome_token;
 int atributo;
};



int estado = 0;
int partida = 0;
int cont_sim_lido = 0;
char *code;
string temp_id;
string temp_num;

char *readFile(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	char *code;
	int n = 0;
	int c;

	if(file == NULL) return NULL;

	fseek(file, 0, SEEK_END);
	long f_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	code = new char (f_size);

	while ((c = fgetc(file))!= EOF)
	{
		code[n++] = (char) c;
	}
	code[n] = '\0';
	return code;
}




int falhar()
{
	switch(estado)
	{
	case 0: partida = 9; break;

	case 9: partida = 12; break;

	case 12: partida = 20; break;

	case 20: partida = 25; break;

	case 25:
		//retornar msg de erro
		printf("Erro encontrado no código\n");
		cont_sim_lido++;
		break;

	default: printf("Erro do compilador");
	}
	return(partida);
}

Token proximo_token()
{
	Token token;
	char c;
	while(code[cont_sim_lido] != EOF)
	{
		switch(estado)
		{
		    case 0:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
                else if(c == 'a') estado = 1;
                else if(c == '+') estado = 51;
                else if(c == '-') estado = 52;
                else if(c == '*') estado = 53;
                else if(c == '<') estado = 54;
				else
					{
                     printf("chama falha");
					 estado = falhar();
					}
				break;

            case 1:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'n') estado = 2;
                else if (isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 2:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'd') estado = 3;
                else if (isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 3:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n')) {
                    printf("<logop, AND>\n");
                    estado = 0;
                }
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 51:
                cont_sim_lido++;
                printf("<ariop, PLUS>\n");
                token.nome_token = ARIOP;
				token.atributo = PLUS;
                estado = 0;
                return(token);
                break;

             case 52:
                cont_sim_lido++;
                printf("<ariop, MINUS>\n");
                token.nome_token = ARIOP;
				token.atributo = MINUS;
                estado = 0;
                return(token);
                break;

            case 53:
                cont_sim_lido++;
                printf("<ariop, MULTI>\n");
                token.nome_token = ARIOP;
                token.atributo = MULTI;
                estado = 0;
                return(token);
                break;

            case 54:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == '=') estado = 55;
                else if(c == '>') estado = 56;
                else {
                    cont_sim_lido++;
                    printf("<relop, LT>\n");
                    token.nome_token = LOGOP;
                    token.atributo = LT;
                    estado = 0;
                    return(token);
                }
                break;

            case 55:
                cont_sim_lido++;
                printf("<relop, LE>\n");
                token.nome_token = LOGOP;
                token.atributo = LE;
                estado = 0;
                return(token);
                break;

            case 56:
                cont_sim_lido++;
                printf("<relop, NE>\n");
                token.nome_token = LOGOP;
                token.atributo = NE;
                estado = 0;
                return(token);
                break;
        }
	}
	token.nome_token = EOF;
	token.atributo = -1;
	return(token);
}




int main ()
{
	Token token;
    code = readFile("programa.txt");
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    //...


}
