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
{int}              {yylval.type_int=atoi(yytext);printf("(%s, CONST_INT)\n",yytext);return INT;}
{float}            {yylval.type_float=atof(yytext);printf("(%s, CONST_FLOAT)\n",yytext);return FLOAT;}
{double}           {yylval.type_double=atof(yytext);printf("(%s, CONST_DOUBLE)\n",yytext);return DOUBLE;}
{char1}		       {yylval.type_char=yytext[1];printf("(%c, CONST_CHAR)\n",yylval.type_char);return CHAR;}
{char2}		       {switch(yytext[2]){case 'n':yylval.type_char=10;break;case 'r':yylval.type_char=13;break;case 't':yylval.type_char=13;break;case 'b':yylval.type_char=8;break;case 'f':yylval.type_char=12;break;case '\\':yylval.type_char=92;break;case '\'':yylval.type_char=39;break;case '\"':yylval.type_char=34;break;}printf("(%c, CONST_CHAR)\n",yylval.type_char);return CHAR;}
{string}           {strcpy(yylval.type_string,yytext);printf("(%s, CONST_STRING)\n",yytext);return STRING;}
{CommentLine}      {}
{CommentBlock}     {}

"int"              {strcpy(yylval.type_id,  yytext);printf("(%s, INT)\n",yytext);return TYPE;}
"float"            {strcpy(yylval.type_id,  yytext);printf("(%s, FLOAT)\n",yytext);return TYPE;}
"double"           {strcpy(yylval.type_id,  yytext);printf("(%s, DOUBLE)\n",yytext);return TYPE;}
"char"		       {strcpy(yylval.type_id,  yytext);printf("(%s, CHAR)\n",yytext);return TYPE;}
"string"           {strcpy(yylval.type_id,  yytext);printf("(%s, STRING)\n",yytext);return TYPE;}
"void"             {strcpy(yylval.type_id,  yytext);printf("(%s, VOID)\n",yytext);return TYPE;}
"struct"           {strcpy(yylval.type_id,  yytext);printf("(%s, STRUCT)\n",yytext);return STRUCT;}

"return"           {printf("(%s, RETURN)\n",yytext);return RETURN;}
"if"               {printf("(%s, IF)\n",yytext);return IF;}
"else"             {printf("(%s, ELSE)\n",yytext);return ELSE;}
"while"            {printf("(%s, WHILE)\n",yytext);return WHILE;}
"for"		       {printf("(%s, FOR)\n",yytext);return FOR;}
"break"		       {printf("(%s, BREAK)\n",yytext);return BREAK;}
"continue"	       {printf("(%s, CONTINUE)\n",yytext);return CONTINUE;}

{id}       	       {strcpy(yylval.type_id,  yytext);printf("(%s, ID)\n",yytext);return ID;/*由于关键字的形式也符合表示符的规则，所以把关键字的处理全部放在标识符的前面，优先识别*/}
";"			       {printf("(%s, SEMI)\n",yytext);return SEMI;}
","			       {printf("(%s, COMMA)\n",yytext);return COMMA;}
">"|"<"            {strcpy(yylval.type_id, yytext);printf("(%s, RELOP)\n",yytext);return RELOP;}
">="|"<="          {strcpy(yylval.type_id, yytext);printf("(%s, RELOP)\n",yytext);return RELOP;}
"=="|"!="          {strcpy(yylval.type_id, yytext);printf("(%s, RELOP)\n",yytext);return RELOP;}
"="			       {printf("(%s, ASSIGNOP)\n",yytext);return ASSIGNOP;}
"++"               {printf("(%s, PLUS_SELF)\n",yytext);return PLUS_SELF;}
"--"               {printf("(%s, MINUS_SELF)\n",yytext);return MINUS_SELF;}
"+"			       {printf("(%s, PLUS)\n",yytext);return PLUS;}
"-"			       {printf("(%s, MINUS)\n",yytext);return MINUS;}
"*"			       {printf("(%s, STAR)\n",yytext);return STAR;}
"/"			       {printf("(%s, DIV)\n",yytext);return DIV;}
"&&"               {printf("(%s, AND)\n",yytext);return AND;}
"||"               {printf("(%s, OR)\n",yytext);return OR;}
"!"			       {printf("(%s, NOT)\n",yytext);return NOT;}
"("			       {printf("(%s, LP)\n",yytext);return LP;}
")"			       {printf("(%s, RP)\n",yytext);return RP;}
"["                {printf("(%s, LB)\n",yytext);return LB;}
"]"                {printf("(%s, RB)\n",yytext);return RB;}
"{"			       {printf("(%s, LC)\n",yytext);return LC;}
"}"			       {printf("(%s, RC)\n",yytext);return RC;}
"."                {printf("(%s, DOT)\n",yytext);return DOT;}
[\n]               {yycolumn=1;}
[ \r\t]            {}
.			       {printf("Error type A :Mysterious character \"%s\"\n\t at Line %d\n",yytext,yylineno);}


%%

int yywrap()
{
return 1;
}

