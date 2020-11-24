#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdarg.h"
#include "parser.tab.h"
enum node_kind  
{ 
    EXT_DEF_LIST,
    EXT_VAR_DEF,
	EXT_VAR_DEF_ASSIGN,
    FUNC_DEF,
    FUNC_DEC,
	STRUCT_COMP_STM,
	STRUCT_TYPE,
    STRUCT_DEF,
    STRUCT_DEC,
    STRUCT_ID,
    EXP_ELE,
    EXP_ARRAY,
    ARRAY_DEC,
	ARRAY_ID,
	ARRAY_DEP,
    EXT_DEC_LIST,
    PARAM_LIST,
    PARAM_DEC,
    VAR_DEF,
    DEC_LIST,
    DEF_LIST,
	DEC_ASSIGNOP,
    COMP_STM,
    STM_LIST,
    EXP_STMT,
    FOR_DEC,
    IF_THEN,
    IF_THEN_ELSE,
    FUNC_CALL,
    ARGS,
    FUNCTION,
    PARAM,
    ARG,
    CALL,
    LABEL,
    GOTO,
	EJLT,
	EJGT,
	EJLE,
	EJGE,
	EEQ,
	ENEQ,
    JLT,
    JGT,
    JLE,
    JGE,
    EQ,
    NEQ
};
#define MAXLENGTH   1000    //定义符号表的大小
#define DX 3*sizeof(int)          //活动记录控制信息需要的单元数
#define MAX_BLOCK_NUM 100     //基本块最大数量
struct opn
{
    int kind; //标识操作的类型
    int type; //标识操作数的类型
    union {
        int const_int;     //整常数值，立即数
        float const_float; //浮点常数值，立即数
        double const_double; //浮点常数值，立即数
        char const_char;   //字符常数值，立即数
        char const_string[32];   //字符串常数值，立即数
        char id[32];       //变量或临时变量的别名或标号字符串
    };
    int level;  //变量的层号，0表示是全局变量，数据保存在静态数据区
    int offset; //变量单元偏移量，或函数在符号表的定义位置序号，目标代码生成时用
};

struct codenode
{                                  //三地址TAC代码结点,采用双向循环链表存放中间语言代码
    int op;                        //TAC代码的运算符种类
    struct opn opn1, opn2, result; //2个操作数和运算结果
    struct codenode *next, *prior;
};

union Value {
    char type_id[32]; //由标识符生成的叶结点
    int type_int;     //由整常数生成的叶结点
    float type_float; //由浮点常数生成的叶结点
    double type_double; //由双精度浮点常数生成的叶结点
    char type_char;
    char type_string[32];
};

// 使用链表存储多个变量
struct Array
{
    int arrary_size;//数组维数
    int offset;//数组首地址
    int array_par[32];//每一维的大小。最多支持32维数组
};

// 使用链表存储多个变量
struct Struct
{
    int kind;
    char id[32]; // 字段名字
    union Value value;
    struct Struct *next;
};

struct node
{                        //以下对结点属性定义没有考虑存储效率，只是简单地列出要用到的一些属性
    enum node_kind kind; //结点类型
    char struct_name[32];
    union {
        char type_id[32]; //由标识符生成的叶结点
        int type_int;     //由整常数生成的叶结点
        float type_float; //由浮点常数生成的叶结点
        double type_double; //由浮点常数生成的叶结点
        char type_char;
        char type_string[32];
        struct Array type_array;
        struct Struct *type_struct;
    };
    struct node *ptr[3];        //子树指针，由kind确定有多少棵子树
    int level;                  //层号
    int place;                  //表示结点对应的变量或运算结果符号表的位置序号
    char Etrue[15], Efalse[15]; //对布尔表达式的翻译时，真假转移目标的标号
    char Snext[15];             //该结点对应语句执行后的下一条语句位置标号
    struct codenode *code;      //该结点中间代码链表头指针
    char op[10];
    int type;   //结点对应值的类型
    int pos;    //语法单位所在位置行号
    int offset; //偏移量
    int width;  //占数据字节数
	int array_par[30];//数组每一维大小
	int array_size;//数组维数
	int num;//参数数量
	char isWhile;//是否为循环体节点
	char Ebreak[15], Econtinue[15];//对循环语句翻译时，break语句、continue语句转义目标的标号
};

struct symbol
{                   //这里只列出了一个符号表项的部分属性，没考虑属性间的互斥
    char name[32];  //变量或函数名
    int level;      //层号，外部变量名或函数名层号为0，形参名为1，每到1个复合语句层号加1，退出减1
    int type;       //变量类型或函数返回值类型
    int paramnum;   //形式参数个数
    char alias[10]; //别名，为解决嵌套层次使用，使得每一个数据名称唯一
    char flag;      //符号标记，函数：'F'  变量：'V'   参数：'P'  临时变量：'T'
    int offset;    //外部变量和局部变量在其静态数据区或活动记录中的偏移量
                    //或函数活动记录大小，目标代码生成时使用
    struct Array type_array;
};
//符号表，是一个顺序栈，index初值为0
struct symboltable
{
    struct symbol symbols[MAXLENGTH];
    int index;
} symbolTable;

struct symbol_scope_begin
{ /*当前作用域的符号在符号表的起始位置序号,这是一个栈结构，/每到达一个复合语句，将符号表的index值进栈，离开复合语句时，取其退栈值修改符号表的index值，完成删除该复合语句中的所有变量和临时变量*/
    int TX[30];
    int top;
} symbol_scope_TX;

//基本块信息节点，保存基本块的label和下标，在基本块节点中表示其next流
struct block_node
{
    char label[32];//标签
    int pos;//在基本块数组中的下标
};

//基本块节点
struct block
{
    char name[10];//基本块名字，形如：BLOCK1、BLOCK2...
    struct codenode *begin;//基本块代码链表头指针
    struct codenode *end;//基本块代码链表尾指针
	struct block_node next[2];//其next流节点信息，用于代码优化
	int num;//next节点个数
	char label[32];//记录基本块中的label
	int hasLabel;//标记label是否存在
	int isSearched;//搜索标记，用于遍历基本块时判断是否已搜索
    int isFunction;//函数基本块标记，若基本块内有FUNCTION则置1，用于代码优化
};

struct block_list
{
    int valid;//有效位，若基本块无有效语句，则valid = 0
    struct block *BLOCK;
};

struct additional_sign
{
    char name[32];//附加标记名
    struct additional_sign *next;//下一个附加标记指针
};

struct DAG
{
    int type;//节点类型
    int num;//节点标号
    union 
    {
        int const_int;//整形常量
        float const_float;//单精度浮点常量
        double const_double;//双精度浮点常量
        char const_char;//字符常量
        char id[10];//标识符字符串
        char op[10];//操作类型
    };
    struct DAG *ptr[3];//后继节点指针
    struct codenode code;//节点代码
    struct additional_sign *additional_sign_head;//附加标记链表头指针
};


struct node *mknode(int kind,struct node *first,struct node *second, struct node *third,int pos );
void semantic_Analysis0(struct node *T);
void semantic_Analysis(struct node *T);
void Exp(struct node *T);
void boolExp(struct node *T);
void prnIR(struct codenode *head, struct codenode *tail);