#ifndef LEXER_H  
#define LEXER_H 

//NOME TOKENS
#define IF 256
#define THEN 257
#define ELSE 258
#define BEGIN 259
#define END 260
#define DO 261
#define WHILE 262
#define PROCEDURE 263
#define PROGRAM 264
#define VAR 265
#define RELOP 266
#define ARIOP 267
#define LOGOP 268
#define ASSOP 269
#define LCOMM 270
#define ID 271
#define NUM 272
#define INT 273
#define BOOLEAN 274

//ATRIBUTOS
//relop
#define LT 300
#define LE 301
#define EQ 302
#define NE 303
#define GT 304
#define GE 305
//ariop
#define DIV 306
#define PLUS 307
#define MINUS 308
#define MULTI 309
//logop;
#define AND 310
#define OR 311
#define NOT 312

struct Token {
    int nome_token;
    int atributo;
};

Token proximo_token();
bool isalphabetic(char c);

#endif