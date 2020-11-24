%error-verbose
%locations
%{
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
void display(struct node *,int);
%}

%union {
	int    array_len;
	int    type_int;
	float  type_float;
	double type_double;
    char   type_char;
    char   type_string[32];
	char   type_void[5];
	char   type_id[32];
	char   type_struct[32];
	struct node *ptr;
};

//  %type 定义非终结符的语义值类型
%type  <ptr> program ExtDefList ExtDef  Specifier ExtDecList FuncDec CompSt VarList VarDec ParamDec Stmt StmList DefList Def DecList Dec Exp Args
// 结构体、for循环的非终结符定义
%type  <ptr> ForDec

//% token 定义终结符的语义值类型
%token <type_id> ID RELOP TYPE     //指定ID RELOP TYPE的语义值是type_id，有词法分析得到的标识符字符串
%token <type_int> INT              //指定INT的语义值是type_int，有词法分析得到的数值
%token <type_float> FLOAT          //指定FLOAT的语义值是type_float，有词法分析得到的数值
%token <type_double> DOUBLE        //指定DOUBLE的语义值是type_double，有词法分析得到的数值   
%token <type_char> CHAR            //指定CHAR的语义值是type_char，有词法分析得到的字符
%token <type_string> STRING        //指定STRING的语义值是type_string，有词法分析得到的字符串
%token <type_void> VOID            //指定VOID的语义值是type_void，有词法分析得到的字符串


//用bison对该文件编译时，带参数-d，生成的exp.tab.h中给这些单词进行编码，可在lex.l中包含parser.tab.h使用这些单词种类码
//左右括号、左右花括号、左右方括号、小数点、分号、逗号
%token LP RP LC RC LB RB DOT SEMI COMMA
//自增、自减、加、减、乘、除、赋值、加等、减等、乘等、除等、与、或、非
%token PRE_PLUS_SELF NEXT_PLUS_SELF PRE_MINUS_SELF NEXT_MINUS_SELF PLUS MINUS STAR DIV ASSIGNOP ASSIGNOP_PLUS ASSIGNOP_MINUS ASSIGNOP_STAR ASSIGNOP_DIV AND OR NOT VARDEC
//、if、else、while、return、for
%token IF ELSE WHILE RETURN FOR
//结构体类型
%token <type_struct> STRUCT
//控制语句
%token BREAK CONTINUE

//赋值类语句具有右结合性，解决shift-reduce冲突
%right ASSIGNOP ASSIGNOP_MINUS ASSIGNOP_PLUS ASSIGNOP_DIV ASSIGNOP_STAR
//运算类语句具有左结合性，解决shift-reduce冲突
%left PLUS_SELF MINUS_SELF
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right UMINUS NOT
//定义方括号结合性，解决多维数组的shift-reduce冲突
%right LB
%left RB
//定义小数点的结合性，解决结构体访问的shift-reduce冲突
%left DOT

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%%
//程序入口
program: ExtDefList          { semantic_Analysis0($1);/*语义分析*/ }
         ; 
ExtDefList:                   {$$=NULL;}
          | ExtDef ExtDefList  {$$=mknode(EXT_DEF_LIST,$1,$2,NULL,yylineno);}//每一个EXTDEFLIST的结点，其第1棵子树对应一个外部变量声明或函数
          ;  
ExtDef: Specifier ExtDecList SEMI     {$$=mknode(EXT_VAR_DEF,$1,$2,NULL,yylineno);}   //该结点对应一个外部变量声明
	  | Specifier VarDec ASSIGNOP Exp SEMI {$$=mknode(EXT_VAR_DEF_ASSIGN,$1,$2,$4,yylineno);}//对应一个外部变量的声明赋值
      | Specifier FuncDec CompSt      {$$=mknode(FUNC_DEF,$1,$2,$3,yylineno);}         //该结点对应一个函数定义
      | error SEMI                    {$$=NULL; }
      ;
ExtDecList: VarDec                  {$$=$1;}       /*每一个EXT_DECLIST的结点，其第一棵子树对应一个变量名(ID类型的结点),第二棵子树对应剩下的外部变量名*/
          | VarDec COMMA ExtDecList {$$=mknode(EXT_DEC_LIST,$1,$3,NULL,yylineno);}
          ;  
Specifier: TYPE          {$$=mknode(TYPE,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);if(!strcmp($1,"void"))$$->type=VOID;if(!strcmp($1,"int"))$$->type=INT;if(!strcmp($1,"float"))$$->type=FLOAT;if(!strcmp($1,"double"))$$->type=DOUBLE;if(!strcmp($1,"char"))$$->type=CHAR;if(!strcmp($1,"string"))$$->type=STRING;}
		  ;      
VarDec: ID          {$$=mknode(ID,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}   //ID结点，标识符符号串存放结点的type_id
      | VarDec LB Exp RB   {$$=mknode(ARRAY_DEC,$1,$3,NULL,yylineno);}
      ;
FuncDec: ID LP VarList RP   {$$=mknode(FUNC_DEC,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
	   | ID LP  RP   {$$=mknode(FUNC_DEC,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}//函数名存放在$$->type_id
       ;  

VarList: ParamDec  {$$=mknode(PARAM_LIST,$1,NULL,NULL,yylineno);}
       | ParamDec COMMA  VarList  {$$=mknode(PARAM_LIST,$1,$3,NULL,yylineno);}
       ;
ParamDec: Specifier VarDec         {$$=mknode(PARAM_DEC,$1,$2,NULL,yylineno);}
        ;

CompSt: LC DefList StmList RC    {$$=mknode(COMP_STM,$2,$3,NULL,yylineno);}
      ;
StmList: {$$=NULL; }  
       | Stmt StmList  {$$=mknode(STM_LIST,$1,$2,NULL,yylineno);}
       ;
Stmt: Exp SEMI    {$$=mknode(EXP_STMT,$1,NULL,NULL,yylineno);}
    | CompSt      {$$=$1;}      //复合语句结点直接作为语句结点，不再生成新的结点
    | RETURN Exp SEMI   {$$=mknode(RETURN,$2,NULL,NULL,yylineno);}
	| RETURN SEMI       {$$=mknode(RETURN,NULL,NULL,NULL,yylineno);}
    | IF LP Exp RP Stmt %prec LOWER_THEN_ELSE   {$$=mknode(IF_THEN,$3,$5,NULL,yylineno);}
    | IF LP Exp RP Stmt ELSE Stmt   {$$=mknode(IF_THEN_ELSE,$3,$5,$7,yylineno);}
    | WHILE LP Exp RP Stmt {$$=mknode(WHILE,$3,$5,NULL,yylineno);}
    | FOR LP ForDec RP Stmt {$$=mknode(FOR,$3,$5,NULL,yylineno);}
	| BREAK SEMI {$$=mknode(BREAK,NULL,NULL,NULL,yylineno);}
	| CONTINUE SEMI {$$=mknode(CONTINUE,NULL,NULL,NULL,yylineno);}
    ;
ForDec: Exp SEMI Exp SEMI Exp {$$=mknode(FOR_DEC,$1,$3,$5,yylineno);}
      | SEMI Exp SEMI {$$=mknode(FOR_DEC,$2,NULL,NULL,yylineno);}
      ;
           ;
DefList: {$$=NULL; }
       | Def DefList {$$=mknode(DEF_LIST,$1,$2,NULL,yylineno);}
       ;
Def: Specifier DecList SEMI {$$=mknode(VAR_DEF,$1,$2,NULL,yylineno);}
   ;
DecList: Dec  {$$=mknode(DEC_LIST,$1,NULL,NULL,yylineno);}
       | Dec COMMA DecList  {$$=mknode(DEC_LIST,$1,$3,NULL,yylineno);}
	   ;
Dec: VarDec  {$$=$1;}
   | VarDec ASSIGNOP Exp  {$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno);strcpy($$->type_id,"=");}
   ;
Exp:    Exp ASSIGNOP Exp {$$=mknode(ASSIGNOP,$1,$3,NULL,yylineno);strcpy($$->type_id,"=");}//$$结点type_id空置未用，正好存放运算符
      | Exp AND Exp   {$$=mknode(AND,$1,$3,NULL,yylineno);strcpy($$->type_id,"AND");}
      | Exp OR Exp    {$$=mknode(OR,$1,$3,NULL,yylineno);strcpy($$->type_id,"OR");}
      | Exp RELOP Exp {$$=mknode(RELOP,$1,$3,NULL,yylineno);strcpy($$->type_id,$2);}  //词法分析关系运算符号自身值保存在$2中
      | Exp PLUS Exp  {$$=mknode(PLUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"PLUS");}
      | Exp PLUS ASSIGNOP Exp {$$=mknode(ASSIGNOP_PLUS,$1,$4,NULL,yylineno);strcpy($$->type_id,"+=");}
      | Exp PLUS_SELF  {$$=mknode(NEXT_PLUS_SELF,$1,NULL,NULL,yylineno);strcpy($$->type_id,"++");}
      | PLUS_SELF Exp  {$$=mknode(PRE_PLUS_SELF,$2,NULL,NULL,yylineno);strcpy($$->type_id,"++");}
      | Exp MINUS Exp {$$=mknode(MINUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"MINUS");}
      | Exp MINUS ASSIGNOP Exp {$$=mknode(ASSIGNOP_MINUS,$1,$4,NULL,yylineno);strcpy($$->type_id,"-=");}
      | Exp MINUS_SELF  {$$=mknode(NEXT_MINUS_SELF,$1,NULL,NULL,yylineno);strcpy($$->type_id,"--");}
      | MINUS_SELF Exp  {$$=mknode(PRE_MINUS_SELF,$2,NULL,NULL,yylineno);strcpy($$->type_id,"--");}
      | Exp STAR Exp  {$$=mknode(STAR,$1,$3,NULL,yylineno);strcpy($$->type_id,"STAR");}
      | Exp STAR ASSIGNOP Exp {$$=mknode(ASSIGNOP_STAR,$1,$4,NULL,yylineno);strcpy($$->type_id,"*=");}
      | Exp DIV Exp   {$$=mknode(DIV,$1,$3,NULL,yylineno);strcpy($$->type_id,"DIV");}
      | Exp DIV ASSIGNOP Exp {$$=mknode(ASSIGNOP_DIV,$1,$4,NULL,yylineno);strcpy($$->type_id,"\\=");}
      | LP Exp RP     {$$=$2;}
      | MINUS Exp %prec UMINUS   {$$=mknode(UMINUS,$2,NULL,NULL,yylineno);strcpy($$->type_id,"UMINUS");}
      | NOT Exp       {$$=mknode(NOT,$2,NULL,NULL,yylineno);strcpy($$->type_id,"!");}
      | ID LP Args RP {$$=mknode(FUNC_CALL,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
      | ID LP RP      {$$=mknode(FUNC_CALL,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
      | Exp LB Exp RB {$$=mknode(EXP_ARRAY,$1,$3,NULL,yylineno)}
      | Exp DOT ID {$$=mknode(EXP_ELE,NULL,NULL,NULL,yylineno);}
      | ID            {$$=mknode(ID,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
      | INT           {$$=mknode(INT,NULL,NULL,NULL,yylineno);$$->type_int=$1;$$->type=INT;}
      | FLOAT         {$$=mknode(FLOAT,NULL,NULL,NULL,yylineno);$$->type_float=$1;$$->type=FLOAT;}
      | DOUBLE         {$$=mknode(DOUBLE,NULL,NULL,NULL,yylineno);$$->type_double=$1;$$->type=DOUBLE;}
      | CHAR           {$$=mknode(CHAR,NULL,NULL,NULL,yylineno);$$->type_char=$1;$$->type=CHAR;}
      | STRING         {$$=mknode(STRING,NULL,NULL,NULL,yylineno);strcpy($$->type_string,$1);$$->type=STRING;}
	  ;
Args:   Exp COMMA Args    {$$=mknode(ARGS,$1,$3,NULL,yylineno);}
    |   Exp               {$$=mknode(ARGS,$1,NULL,NULL,yylineno);}
    ;
%%

int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return 0;
                yylineno=1;
                yyparse();
                return 0;
	}

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}