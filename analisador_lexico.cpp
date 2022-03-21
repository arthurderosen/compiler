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
				if((c == ' ')||(c == '\n')||(c == NULL))
				{
					estado = 0;
					cont_sim_lido++;
				}
                else if(c == 'a') estado = 1;
                else if(c == 'p') estado = 24;
                else if(c == 't') estado = 37;
                else if(c == 'v') estado = 41;
                else if(c == 'w') estado = 44;
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

            case 24:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'r') estado = 25;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 25:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'o') estado = 26;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 26:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'g') estado = 27;
                else if (c == 'c') estado = 31;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 27:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'r') estado = 28;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 28:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'a') estado = 29;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 29:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'm') estado = 30;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 30:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n')) {
                    printf("<program, >\n");
                    estado = 0;
                }
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 31:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'e') estado = 32;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 32:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'd') estado = 33;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 33:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'u') estado = 34;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 34:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'r') estado = 35;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 35:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'e') estado = 36;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 36:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n')) {
                    printf("<procedure, >\n");
                    estado = 0;
                }
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 37:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'h') estado = 38;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 38:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'e') estado = 39;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 39:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'n') estado = 40;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 40:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n')) {
                    printf("<then, >\n");
                    estado = 0;
                }
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 41:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'a') estado = 42;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 42:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'r') estado = 43;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 43:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n')) {
                    printf("<var, >\n");
                    estado = 0;
                }
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 44:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'h') estado = 45;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 45:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'i') estado = 46;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 46:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'l') estado = 47;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 47:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if(c == 'e') estado = 48;
                else if(isalnum(c)) estado = 99;
                else estado = falhar();
                break;

            case 48:
                cont_sim_lido++;
                c = code[cont_sim_lido];
                if((c == ' ')||(c == '\n')) {
                    printf("<while, >\n");
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
    while(token.nome_token != EOF){
            token = proximo_token();
    }
    //...


}

