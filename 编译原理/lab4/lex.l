%{
#include "parser.tab.h"
#include "string.h"
#include "def.h"
int yycolumn=1;
#define YY_USER_ACTION    	yylloc.first_line=yylloc.last_line=yylineno; \
	yylloc.first_column=yycolumn;	yylloc.last_column=yycolumn+yyleng-1; yycolumn+=yyleng;
typedef union {
	int type_int;
	float type_float;
	double type_double;
	char type_char;
	char type_string[32];
	char type_void [5];
	char type_id[32];
	struct node *ptr;
} YYLVAL;
#define YYSTYPE YYLVAL

%}
%option yylineno

id     [A-Za-z_][A-Za-z0-9]*
int    ([0-9]+)|(0[xX][a-fA-f0-9]+)|([oO][0-7]+)
float  ([0-9]+\.[0-9]+)|([0-9]+)
double ([0-9]+\.[0-9]+)|([0-9]+)
char1   (\'[\x20-\x7F]\')
char2   (\'\\[ntfrb\\\'\"]\')
string (\"[A-Za-z0-9]*\")
CommentLine   ("//"[^\n]*)
CommentBlock  ("/*"([^\*]|(\*)*[^\*/])*(\*)*"*/")

%%
{int}              {yylval.type_int=atoi(yytext);return INT;}
{float}            {yylval.type_float=atof(yytext);return FLOAT;}
{double}           {yylval.type_double=atof(yytext);return DOUBLE;}
{char1}		       {yylval.type_char=yytext[1];return CHAR;}
{char2}		       {switch(yytext[2]){case 'n':yylval.type_char=10;break;case 'r':yylval.type_char=13;break;case 't':yylval.type_char=13;break;case 'b':yylval.type_char=8;break;case 'f':yylval.type_char=12;break;case '\\':yylval.type_char=92;break;case '\'':yylval.type_char=39;break;case '\"':yylval.type_char=34;break;}printf("(%c, CONST_CHAR)\n",yylval.type_char);return CHAR;}
{string}           {strcpy(yylval.type_string,yytext);return STRING;}
{CommentLine}      {}
{CommentBlock}     {}

"int"              {strcpy(yylval.type_id,  yytext);return TYPE;}
"float"            {strcpy(yylval.type_id,  yytext);return TYPE;}
"double"           {strcpy(yylval.type_id,  yytext);return TYPE;}
"char"		       {strcpy(yylval.type_id,  yytext);return TYPE;}
"string"           {strcpy(yylval.type_id,  yytext);return TYPE;}
"void"             {strcpy(yylval.type_id,  yytext);return TYPE;}
"struct"           {strcpy(yylval.type_id,  yytext);return STRUCT;}

"return"           {return RETURN;}
"if"               {return IF;}
"else"             {return ELSE;}
"while"            {return WHILE;}
"for"		       {return FOR;}
"break"		       {return BREAK;}
"continue"	       {return CONTINUE;}

{id}       	       {strcpy(yylval.type_id,  yytext);return ID;/*由于关键字的形式也符合表示符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}
";"			       {return SEMI;}
","			       {return COMMA;}
">"|"<"            {strcpy(yylval.type_id, yytext);return RELOP;}
">="|"<="          {strcpy(yylval.type_id, yytext);return RELOP;}
"=="|"!="          {strcpy(yylval.type_id, yytext);return RELOP;}
"="			       {return ASSIGNOP;}
"++"               {return PLUS_SELF;}
"--"               {return MINUS_SELF;}
"+"			       {return PLUS;}
"-"			       {return MINUS;}
"*"			       {return STAR;}
"/"			       {return DIV;}
"&&"               {return AND;}
"||"               {return OR;}
"!"			       {return NOT;}
"("			       {return LP;}
")"			       {return RP;}
"["                {return LB;}
"]"                {return RB;}
"{"			       {return LC;}
"}"			       {return RC;}
"."                {return DOT;}
[\n]               {yycolumn=1;}
[ \r\t]            {}
.			       {printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}


%%

int yywrap()
{
return 1;
}

