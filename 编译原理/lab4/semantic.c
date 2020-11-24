#include "def.h"
/*
去除了结构;
*/

int LEV = 0;   //层号
int func_size; //1个函数的活动记录大小
char error_msg[256][128]; //错误信息缓冲区
char optimization[256][128];//优化信息缓冲区
int error_index = 0;
int optimization_index = 0;
int isReturn = 1;
int isFunc = 0;
int offset0 = 0;
struct block_list BLOCK_LIST[MAX_BLOCK_NUM];//基本块数组
int block_list_index = 0;//基本块数量


char *strcat0(char *s1, char *s2)
{
    static char result[10];
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *newAlias()
{
    static int no = 1;
    char s[10];
    snprintf(s, 10, "%d", no++);
    return strcat0("v", s);
}

char *newLabel()
{
    static int no = 1;
    char s[10];
    snprintf(s, 10, "%d", no++);
    return strcat0("label", s);
}

char *newTemp()
{
    static int no = 1;
    char s[10];
    snprintf(s, 10, "%d", no++);
    return strcat0("temp", s);
}

char *newBlockName()
{
    static int no = 1;
    char s[10];
    snprintf(s, 10, "%d", no++);
    return strcat0("BLOCK",s);
}

//生成一个基本块节点，指向该基本块代码链表的起始和结尾
struct block *genBlock(char *name, struct codenode *begin, struct codenode *end)
{
    struct block * BLOCK = (struct block *)malloc(sizeof(struct block));
    strcpy(BLOCK->name, name);
    BLOCK->begin = begin;
    BLOCK->end = end;
}

//生成一条TAC代码的结点组成的双向循环链表，返回头指针
struct codenode *genIR(int op, struct opn opn1, struct opn opn2, struct opn result)
{
    struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = op;
    h->opn1 = opn1;
    h->opn2 = opn2;
    h->result = result;
    h->next = h->prior = h;
    return h;
}

//生成一条标号语句，返回头指针
struct codenode *genLabel(char *label)
{
    struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = LABEL;
    strcpy(h->result.id, label);
    h->next = h->prior = h;
    return h;
}

//生成GOTO语句，返回头指针
struct codenode *genGoto(char *label)
{
    struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = GOTO;
    strcpy(h->result.id, label);
    h->next = h->prior = h;
    return h;
}

//合并多个中间代码的双向循环链表，首尾相连
struct codenode *merge(int num, ...)
{
    struct codenode *h1, *h2, *p, *t1, *t2;
    va_list ap;
    va_start(ap, num);
    h1 = va_arg(ap, struct codenode *);
    while (--num > 0)
    {
        h2 = va_arg(ap, struct codenode *);
        if (h1 == NULL)
            h1 = h2;
        else if (h2)
        {
            t1 = h1->prior;
            t2 = h2->prior;
            t1->next = h2;
            t2->next = h1;
            h1->prior = t2;
            h2->prior = t1;
        }
    }
    va_end(ap);
    return h1;
}

void dfsBlock(struct block *BLOCK)
{
    if (BLOCK->isSearched)//基本块已扫描过，返回
        return;
        BLOCK->isSearched = 1;
    if (BLOCK->num == 1)//有一个next流
    {
        if (BLOCK->name && BLOCK_LIST[BLOCK->next[0].pos].BLOCK->name){
            printf("%s----->%s\n",BLOCK->name, BLOCK_LIST[BLOCK->next[0].pos].BLOCK->name);
            dfsBlock(BLOCK_LIST[BLOCK->next[0].pos].BLOCK);}
    }
    else if(BLOCK->num == 2)//有两个next流
    {
        if (BLOCK->name && BLOCK_LIST[BLOCK->next[0].pos].BLOCK->name){
         printf("%s----->%s\n",BLOCK->name, BLOCK_LIST[BLOCK->next[0].pos].BLOCK->name);
        dfsBlock(BLOCK_LIST[BLOCK->next[0].pos].BLOCK);}
        if (BLOCK->name && BLOCK_LIST[BLOCK->next[1].pos].BLOCK->name){
            printf("%s----->%s\n",BLOCK->name, BLOCK_LIST[BLOCK->next[1].pos].BLOCK->name);
        dfsBlock(BLOCK_LIST[BLOCK->next[1].pos].BLOCK);}
    }
}

//扫描中间代码产生基本块，填充基本块列表
void fill_block_list(struct codenode *head)
{
    struct codenode *h = head,*begin,*end;
    int begin_flag,end_flag,branch_flag,return_goto_flag;
    begin_flag = end_flag = branch_flag = return_goto_flag =  0;
    do
    {
        // if ((h->op == LABEL && h->next->op !=FUNCTION || h->op == FUNCTION) && begin_flag == 0)
        // {
        //     begin = h;
        //     begin_flag = 1;
        // }
        // else if ((h->op == LABEL && h->next->op !=FUNCTION || h->op ==FUNCTION) && begin_flag == 1 && branch_flag == 0)
        // {
        //     end = h;
        //     end_flag = 1;
        // }
        // if (h->op >= JLT && h->op <= NEQ || h->op == RETURN || h->op == GOTO)
        // {
        //     end = h;
        //     end_flag = branch_flag = 1;
        // }
        // if (begin_flag && end_flag)
        // {
        //     BLOCK_LIST[block_list_index].BLOCK = genBlock(newBlockName(), begin, end);
        //     BLOCK_LIST[block_list_index].valid = 1;
        //     block_list_index++;
        //     begin_flag = end_flag = 0;
        // }
        // if (branch_flag)
        // {
        //     begin = end->next;
        //     begin_flag = 1;
        //     end_flag = 0;
        //     branch_flag = 0;
        // }
        // h=h->next;     
        if(return_goto_flag)
        {
            // printf("基本块以return或goto后的语句%d开始...\n",h->op);
            // prnIR(h,h->next);
            begin = h;
            begin_flag = 1;
            return_goto_flag = 0;
            if (h->op >= JLT && h->op <= NEQ || h->op == RETURN || h-> op == GOTO)//若该语句是特殊语句，则结束
            {
                end = h;
                end_flag = 1;
                // prnIR(h,h->next);
                // printf("基本块以return或goto后的特殊语句结束...\n");
                if (h->op >= JLT && h->op <= NEQ)
                {
                    branch_flag = 1;
                }
                else
                {
                    return_goto_flag = 1;
                }
                
            }
        }   
        else if (h->op == LABEL && begin_flag == 0)
        {
            // printf("基本块以label开始...\n");
            // prnIR(h,h->next);
            begin = h;
            begin_flag = 1;
        }
        else if (h->op == LABEL && begin_flag == 1)
        {
            end = h->prior;
            begin_flag = 1;
            end_flag = 1;
            // prnIR(end,end->next);
            // printf("基本块以label前一条语句结束...\n");
            BLOCK_LIST[block_list_index].BLOCK = genBlock(newBlockName(), begin, end);
            BLOCK_LIST[block_list_index].valid = 1;
            block_list_index++;
            begin_flag = end_flag = 0;
            // printf("基本块以label开始...\n");
            begin = h;
            // prnIR(begin,begin->next);
            begin_flag = 1;
            h = h->next;
            continue;
        }
        else if (h->op == FUNCTION)
        {
            // printf("基本块以function开始...\n");
            // prnIR(h,h->next);
            begin = h;
            begin_flag = 1;
        }
        else if (h->op >= JLT && h->op <= NEQ)
        {
            // prnIR(h,h->next);
            // printf("基本块以分支%d结束结束...\n",h->op);
            end = h;
            end_flag = branch_flag = 1;
        }
        else if(h->op == RETURN || h->op == GOTO)
        {
            // prnIR(h,h->next);
            // printf("基本块以return或goto%d结束结束...\n",h->op);            
            end = h;
            end_flag = 1;
            return_goto_flag = 1;
        }
        // else if (h->op == RETURN || h->op == GOTO)
        // {
        //     end = h;
        //     end_flag = 1;
        // }
        // else if (begin_flag == 0)
        // {
        //     begin = h;
        //     begin_flag = 1;
        // }
        if (begin_flag && end_flag)
        {
            BLOCK_LIST[block_list_index].BLOCK = genBlock(newBlockName(), begin, end);
            BLOCK_LIST[block_list_index].valid = 1;
            block_list_index++;
            begin_flag = end_flag = 0;
        }
        if (branch_flag)
        {
            // printf("基本块以分支语句紧接着的语句%d开始...\n",end->next->op);
            // prnIR(end->next,end->next->next);
            begin = end->next;
            begin_flag = 1;
            branch_flag = 0;
        }
        h=h->next;
    } while (h != head);
}

//输出中间代码
void prnIR(struct codenode *head, struct codenode *tail)
{
    char opnstr1[32], opnstr2[32], resultstr[32];
    struct codenode *h = head;
    //printf("---------------%s---------------\n",newBlockName());//起始语句是第一个基本块
    do
    {
        if (h->opn1.kind == INT)
            sprintf(opnstr1, "#%d", h->opn1.const_int);
        if (h->opn1.kind == FLOAT)
            sprintf(opnstr1, "#%f", h->opn1.const_float);
        if (h->opn1.kind == DOUBLE)
            sprintf(opnstr1, "#%lf", h->opn1.const_double);
        if (h->opn1.kind == CHAR)
            sprintf(opnstr1, "#%d", h->opn1.const_char);
        if (h->opn1.kind == ID)
            sprintf(opnstr1, "%s", h->opn1.id);
        if (h->opn2.kind == INT)
            sprintf(opnstr2, "#%d", h->opn2.const_int);
        if (h->opn2.kind == FLOAT)
            sprintf(opnstr2, "#%f", h->opn2.const_float);
        if (h->opn2.kind == DOUBLE)
            sprintf(opnstr2, "#%lf", h->opn2.const_double);
        if (h->opn2.kind == CHAR)
            sprintf(opnstr2, "#%d", h->opn2.const_char);
        if (h->opn2.kind == ID)
            sprintf(opnstr2, "%s", h->opn2.id);
        sprintf(resultstr, "%s", h->result.id);
        switch (h->op)
        {
            
            case NOT:
            case UMINUS:
                printf("    %s := %c %s\n",resultstr,(h->op==NOT?'!':'-'),opnstr1);
                break;  
            case ASSIGNOP:
                printf("    %s := %s\n", resultstr, opnstr1);
                break;
            case ASSIGNOP_ARRAY:
                printf("    %s := %s[%s]\n", resultstr, opnstr1,opnstr2);
                break;
            case ARRAY_ASSIGNOP:
                printf("    %s[%s] := %s\n", resultstr, opnstr2,opnstr1);
                break;
            case ASSIGNOP_PLUS:
            case ASSIGNOP_MINUS:
            case ASSIGNOP_STAR:
            case ASSIGNOP_DIV:
                printf("    %s := %s %c %s\n", resultstr, opnstr1,
                h->op==ASSIGNOP_PLUS?'+':h->op==ASSIGNOP_MINUS?'-':h->op==ASSIGNOP_STAR?'*':'/',opnstr2);
                printf("    %s := %s\n",opnstr1,resultstr);
                break;
            case PLUS:
            case MINUS:
            case STAR:
            case DIV:
                printf("    %s := %s %c %s\n", resultstr, opnstr1,
                    h->op == PLUS ? '+' : h->op == MINUS ? '-' : h->op == STAR ? '*' : '\\', opnstr2);
                break;
            case PRE_PLUS_SELF:
            case PRE_MINUS_SELF:
                printf("    %s := %s %c #1\n",opnstr1,opnstr1,h->op==PRE_PLUS_SELF?'+':'-');
                printf("    %s := %s\n",resultstr,opnstr1);
                break;
            case NEXT_PLUS_SELF:
            case NEXT_MINUS_SELF:
                printf("    %s := %s\n",resultstr,opnstr1);
                printf("    %s := %s %c #1\n",opnstr1,opnstr1,h->op==NEXT_PLUS_SELF?'+':'-');
                break;
            case FUNCTION:
                printf("  FUNCTION %s :\n", h->result.id);
                break;
            case PARAM:
                printf("  PARAM %s\n", h->result.id);
                break;
            case LABEL:
               // printf("---------------end------------------\n\n");//上一个基本块结束
               // printf("---------------%s---------------\n", newBlockName());//转移目标语句是基本块的起始语句
                printf("LABEL %s :\n", h->result.id);                
                break;
            case GOTO:
                printf("    GOTO %s\n", h->result.id);
                break;
            case JLE:
                printf("    IF %s <= %s GOTO %s\n", opnstr1, opnstr2, resultstr);
               // printf("---------------end------------------\n\n");//上一个基本块结束
                //printf("---------------%s---------------\n",newBlockName());//转移语句后的第一条语句是基本块的起始语句
                break;
            case JLT:
                printf("    IF %s < %s GOTO %s\n", opnstr1, opnstr2, resultstr);
               // printf("---------------end------------------\n\n");//上一个基本块结束
                //printf("---------------%s---------------\n",newBlockName());//转移语句后的第一条语句是基本块的起始语句
                break;
            case JGE:
                printf("    IF %s >= %s GOTO %s\n", opnstr1, opnstr2, resultstr);
                break;
            case JGT:
                printf("    IF %s > %s GOTO %s\n", opnstr1, opnstr2, resultstr);
                //printf("---------------end------------------\n\n");//上一个基本块结束
                //printf("---------------%s---------------\n",newBlockName());//转移语句后的第一条语句是基本块的起始语句
                break;
            case EQ:
                printf("    IF %s == %s GOTO %s\n", opnstr1, opnstr2, resultstr);
                //printf("---------------end------------------\n\n");//上一个基本块结束
                //printf("---------------%s---------------\n",newBlockName());//转移语句后的第一条语句是基本块的起始语句
                break;
            case NEQ:
                printf("    IF %s != %s GOTO %s\n", opnstr1, opnstr2, resultstr);
                //printf("---------------end------------------\n\n");//上一个基本块结束
                //printf("---------------%s---------------\n",newBlockName());//转移语句后的第一条语句是基本块的起始语句
                break;
            case EJLE:       
            case EJLT:       
            case EJGE:       
            case EJGT:       
            case EEQ:        
            case ENEQ:
                printf("    %s := %s %s %s\n",resultstr,opnstr1,h->op==EJLT ? "<":h->op==EJLE?"<=":h->op==EJGT?">":h->op==EJGE?">=":h->op==EEQ?"==":"!=",opnstr2);
                break;
            case ARG:
                printf("    ARG %s\n", h->result.id);
                break;
            case CALL:
                printf("    %s := CALL %s\n", resultstr, opnstr1);
                break;
            case RETURN:
                if (h->result.kind)
                    printf("    RETURN %s\n", resultstr);
                else
                    printf("    RETURN\n");
                break;
        }
        h = h->next;
    } while (h != tail);
    //printf("---------------end------------------\n\n");//上一个基本块结束
}

//记录优化信息
void optimization_msg(char *name, char *msg)
{
    sprintf(optimization[optimization_index++],"在基本块%s，%s\n",name, msg);
}

//窥孔优化，只对无效转移语句和空的语句块进行删除
// void peepholeOptimization(void)
// {
//     int i = 0,change = 1;
//     struct codenode *c1,*c2,*prior,*next,*temp,*del,*del0;
//     while (i < block_list_index)
//     {
//         change = 1;
//         while (change)//循环搜索直到不在改变
//         {
//             c1 = BLOCK_LIST[i].BLOCK->begin;
//             c2 = BLOCK_LIST[i].BLOCK->end;
//             change = 0;
//             if (c1 == c2 && c1->op == LABEL)//基本块只有一个代码节点，且为label节点，删除该基本块
//             {
//                 BLOCK_LIST[i].valid = 0;//置该基本块无效
//                 optimization_msg(i+1, "不包含中间代码，删除该基本块");
//                 break;
//             }
//             while(c1 != c2)
//             {
//                 if (c1->op == GOTO && c1->next->op == GOTO)//连续两个GOTO语句，仅第一个有效，后面直到LABEL节点均是无效代码，删除
//                 {
//                     BLOCK_LIST[i].BLOCK->end = c1;
//                     optimization_msg(i+1,"去掉GOTO语句后续的无用代码");
//                     change = 1;
//                     break;
//                 }
//                 else
//                     c1 = c1->next;
//             }
//         }
//         i++;
//     }
// }

//基本块优化
void blockOptimization(void)
{
    struct codenode *c;
    int i,j,branch_flag;
    struct block *BLOCK = NULL;
    //第一遍扫描基本块数组，初始化基本块的部分信息
    for ( i = 0; i < block_list_index; i++)
    {
        BLOCK = BLOCK_LIST[i].BLOCK;
        branch_flag = 0;//初始分支标记为0
        //初始化基本块信息
        BLOCK->num = 0;
        BLOCK->hasLabel = 0;
        BLOCK->isFunction = 0;
        BLOCK->isSearched = 0;
        BLOCK->next[0].pos = BLOCK->next[1].pos = -1;
        c = BLOCK->begin;
        do
        {
            if (c->op == FUNCTION)
                BLOCK->isFunction = 1;
            if (c->op == LABEL)
            {
                BLOCK->hasLabel = 1;
                strcpy(BLOCK->label, c->result.id);//基本块标记为其LABEL代码节点
            }
            if (c->op ==RETURN)
            {
               BLOCK->num = 0;//返回语句是基本块的结束语句，表示无next流
               branch_flag = 1;
               break;
            }
            if (c->op == GOTO)
            {
                BLOCK->num = 1;//GOTO语句是基本块的结束语句，有一个next流
                strcpy(BLOCK->next[0].label, c->result.id);//记录分支目标的LABEL
                branch_flag = 1;
                break;
            }
            if (c->op >= JLT && c->op <= NEQ)
            {
                BLOCK->num = 2;//条件转移语句是基本块的结束语句，有条件为真和条件为假的两个next流，此处仅记录数量和条件为真的转移LABEL
                //prnIR(c,c->next);
                strcpy(BLOCK->next[0].label, c->result.id);//记录分支目标的LABEL
                branch_flag = 1;
                break;
            }
            c = c->next;
        } while (c != BLOCK->begin);
        if (branch_flag == 0)//基本块无分支，若不是最后一个基本块，下一个基本块是其next流
        {
            if (i < block_list_index - 1)//不是最后一个基本块
            {
                BLOCK->num = 1;
                BLOCK->next[0].pos = i + 1;//记录next流的基本块标号
            }
        }
    }
    //第二遍扫描基本块数组，
    for ( i = 0; i < block_list_index; i++)
    {
        BLOCK = BLOCK_LIST[i].BLOCK;
        if (BLOCK->num == 1)//该基本块有一个next流
        {
            if (BLOCK->next[0].pos != -1)//已经记录了next流基本块的下标
            {
                if (BLOCK_LIST[BLOCK->next[0].pos].BLOCK->hasLabel)//如果next流基本块有标签 
                    strcpy(BLOCK->next[0].label,BLOCK_LIST[BLOCK->next[0].pos].BLOCK->label);//将next流的基本块标签传递到基本块信息节点
                continue;
            }
            for (j = 0; j < block_list_index; j++)//搜索next流基本块，并记录下标
            {
                if (!strcmp(BLOCK->next[0].label, BLOCK_LIST[j].BLOCK->label))//两个label相等，即找到目标基本块
                {
                    BLOCK->next[0].pos = j;//记录下标
                }
            }
        }
        else if (BLOCK->num == 2)//该基本块有两个next流，此处仅为条件分支语句的基本块
        {
            BLOCK->next[1].pos = i + 1;//条件分支语句的条件为假语句，在基本块数组中即下一个元素，下标为i+1
            if (i < block_list_index - 1)//如果不是最后一个基本块
                if (BLOCK_LIST[i + 1].BLOCK->hasLabel)//如果该基本块有label
                    strcpy(BLOCK->next[1].label, BLOCK_LIST[i + 1].BLOCK->label);//将next流中条件为假的分支地址的label传递到基本块信息节点
            for (j = 0; j < block_list_index; j++)//搜索next流基本块，并记录下标
            {
                if (!strcmp(BLOCK->next[0].label, BLOCK_LIST[j].BLOCK->label))//两个label相等，即找到目标基本块
                {
                    BLOCK->next[0].pos = j;//记录下标
                }
            }
        }
    }
    printf("\n流图的dfs遍历：\n");
    //第三遍扫描基本块数组，对其进行深度优先遍历，对遍历到的节点进行标记，注意起始节点一定是函数基本块节点
    for (i = 0; i < block_list_index; i++)
    {
        if (BLOCK_LIST[i].BLOCK->isFunction)
            dfsBlock(BLOCK_LIST[i].BLOCK);
    }
    printf("\n");
    //第四遍扫描基本块数组，将没遍历到的基本块的valid置为0
    for (i = 0; i < block_list_index; i++)
    {
        if (BLOCK_LIST[i].BLOCK->isSearched == 0)//若该基本块未被搜索
        {
            BLOCK_LIST[i].valid = 0;//置valid=0，逻辑删除该基本块
            optimization_msg(BLOCK_LIST[i].BLOCK->name, "基本块不可达，删除");
        }
    }
}

//输出基本块
void prnBlock(void)
{
    int i = 0;
    printf("未优化代码的基本块如下：\n");
    while (i < block_list_index)
    {
        if (BLOCK_LIST[i].valid)
        {
            printf("------------------%s------------------\n",BLOCK_LIST[i].BLOCK->name);
            prnIR(BLOCK_LIST[i].BLOCK->begin, BLOCK_LIST[i].BLOCK->end->next);
            printf("------------------end------------------------\n\n");
        }
        i++;
    }
    blockOptimization();
    //peepholeOptimization();
    printf("优化后的代码的基本块如下：\n");
    i = 0;
    while (i < block_list_index)
    {
        if (BLOCK_LIST[i].valid)
        {
            printf("------------------%s------------------\n",BLOCK_LIST[i].BLOCK->name);
            prnIR(BLOCK_LIST[i].BLOCK->begin, BLOCK_LIST[i].BLOCK->end->next);
            printf("------------------end------------------------\n\n");
        }
        i++;
    }
    printf("\n优化信息：\n");
    i = 0;
    while (i < optimization_index)
    {
        printf("%s",optimization[i]);
        i++;
    }
}

//打印错误信息
void semantic_error(int line, char *msg1, char *error_type)
{
    sprintf(error_msg[error_index++],"error: in line %d,%s %s\n", line, msg1, error_type);
}

//显示符号表
void display_symbol()
{ 
    int i = 0;
    char *symbolsType;
    printf("%-8s%-8s%-8s%-8s%-8s%-8s\n", "变量名", "别名", "层号", "类型", "标记", "偏移量");
    for (i = 0; i < symbolTable.index; i++)
    {
        if (symbolTable.symbols[i].type == INT)
        {
            symbolsType = "int";
        }
        if (symbolTable.symbols[i].type == FLOAT)
        {
            symbolsType = "float";
        }
        if (symbolTable.symbols[i].type == CHAR)
        {
            symbolsType = "char";
        }
        if (symbolTable.symbols[i].type == DOUBLE)
        {
            symbolsType = "double";
        }
        if (symbolTable.symbols[i].type == STRING)
        {
            symbolsType = "string";
        }
        if (symbolTable.symbols[i].type == VOID)
        {
            symbolsType = "void";
        }
        printf("%-8s%-8s%-8d%-8s%-8c%-8d\n", symbolTable.symbols[i].name,
               symbolTable.symbols[i].alias, symbolTable.symbols[i].level,
               symbolsType,
               symbolTable.symbols[i].flag, symbolTable.symbols[i].offset);
    }
}

//按名查找符号表
int searchSymbolTable(char *name)
{
    int i;
    for (i = symbolTable.index - 1; i >= 0; i--)
        if (!strcmp(symbolTable.symbols[i].name, name))
            return i;
    return -1;
}

//添加符号表函数
int add_symbolTable(char *name, char *alias, int level, int type, char flag, int offset)
{
    int i;
    //搜索符号表进行重复检测
    for (i = symbolTable.index - 1; symbolTable.symbols[i].level == level || (level == 0 && i >= 0); i--)
    {
		//外部变量和形参不比较
        if (level == 0 && symbolTable.symbols[i].level == 1)
            continue; 
		//命名重复，返回-1
        if (!strcmp(symbolTable.symbols[i].name, name))
            return -1;
    }
    //填写符号表内容
    strcpy(symbolTable.symbols[symbolTable.index].name, name);
    strcpy(symbolTable.symbols[symbolTable.index].alias, alias);
    symbolTable.symbols[symbolTable.index].level = level;
    symbolTable.symbols[symbolTable.index].type = type;
    symbolTable.symbols[symbolTable.index].flag = flag;
    symbolTable.symbols[symbolTable.index].offset = offset;
	//返回的是符号在符号表中的位置序号，中间代码生成时可用序号取到符号别名
    return symbolTable.index++;
}

//填写临时变量到符号表，返回临时变量在符号表中的位置
int fill_Temp(char *name, int level, int type, char flag, int offset)
{
    strcpy(symbolTable.symbols[symbolTable.index].name, "");
    strcpy(symbolTable.symbols[symbolTable.index].alias, name);
    symbolTable.symbols[symbolTable.index].level = level;
    symbolTable.symbols[symbolTable.index].type = type;
    symbolTable.symbols[symbolTable.index].flag = flag;
    symbolTable.symbols[symbolTable.index].offset = offset;
    return symbolTable.index++; //返回的是临时变量在符号表中的位置序号
}

// 匹配函数参数
int match_param(int i, struct node *T)
{ 
    int j, num = symbolTable.symbols[i].paramnum;
    int type1, type2;
    if (num == 0 && T == NULL)
		return 1;
	if(num == 1)
	{
        if (!T)
        {
            semantic_error(T->pos, "", "函数调用参数太少");
            return 0;
        }
		type1 = symbolTable.symbols[i + 1].type;
		type2 = T->ptr[0]->type;
        if (type1 != type2)
        {
                            printf("形参类型：%d 传入的参数类型：%d\n",type1,type2);
            semantic_error(T->pos, "", "参数类型不匹配");
            return 0;
        }
	}
	else
	{
		for (j = 1; j < num; j++)
		{
			if (!T)
			{
				semantic_error(T->pos, "", "函数调用参数太少");
				return 0;
			}
			type1 = symbolTable.symbols[i + j].type; //形参类型
			type2 = T->ptr[0]->type;
			if (type1 != type2)
			{
                printf("形参类型：%d 传入的参数类型：%d\n",type1,type2);
				semantic_error(T->pos, "", "参数类型不匹配");
				return 0;
			}
			T = T->ptr[1];
		}
	}
	if (T->ptr[1])
	{ //num个参数已经匹配完，还有实参表达式
		semantic_error(T->pos, "", "函数调用参数太多");
		return 0;
	}
    return 1;
    
}

//布尔表达式，参考文献[2]p84的思想
void boolExp(struct node *T)
{
    struct opn opn1,opn2,result;
    int op;
    int rtn;
    if (T)
    {
        switch (T->kind)
        {
            case INT:
                    if (T->type_int!=0)
                        T->code=genGoto(T->Etrue);
                    else
                        T->code=genGoto(T->Efalse);
                    T->width=0;
                    break;
            case FLOAT:
                    if (T->type_float!=0.0)
                        T->code=genGoto(T->Etrue);
                    else
                        T->code=genGoto(T->Efalse);
                    T->width=0;
                    break;
            case ID:    //查符号表，获得符号表中的位置，类型送type
                    rtn=searchSymbolTable(T->type_id);
                    if (rtn==-1)
                        semantic_error(T->pos,T->type_id, "变量未定义");
                    if (symbolTable.symbols[rtn].flag=='F')
                        semantic_error(T->pos,T->type_id, "是函数名，类型不匹配");
                    else
                    {
                        opn1.kind=ID;
                        strcpy(opn1.id,symbolTable.symbols[rtn].alias);
                        opn1.offset=symbolTable.symbols[rtn].offset;
                        opn2.kind=INT;
                        opn2.const_int=0;
                        result.kind=ID;
                        strcpy(result.id,T->Etrue);
                        T->code=genIR(NEQ,opn1,opn2,result);
                        T->code=merge(2,T->code,genGoto(T->Efalse));
                    }
                    T->width=0;
                    break;
            case RELOP: //处理关系运算表达式,2个操作数都按基本表达式处理
                        T->ptr[0]->offset=T->ptr[1]->offset=T->offset;
                        Exp(T->ptr[0]);
                        T->width=T->ptr[0]->width;
                        Exp(T->ptr[1]);
                        if (T->width<T->ptr[1]->width)
                            T->width=T->ptr[1]->width;
                        opn1.kind=ID;
                        strcpy(opn1.id,symbolTable.symbols[T->ptr[0]->place].alias);
                        opn1.offset=symbolTable.symbols[T->ptr[0]->place].offset;
                        opn2.kind=ID;
                        strcpy(opn2.id,symbolTable.symbols[T->ptr[1]->place].alias);
                        opn2.offset=symbolTable.symbols[T->ptr[1]->place].offset;
                        result.kind=ID;
                        strcpy(result.id,T->Etrue);
                        if (strcmp(T->type_id,"<")==0)
                                op=JLT;
                        else if (strcmp(T->type_id,"<=")==0)
                                op=JLE;
                        else if (strcmp(T->type_id,">")==0)
                                op=JGT;
                        else if (strcmp(T->type_id,">=")==0)
                                op=JGE;
                        else if (strcmp(T->type_id,"==")==0)
                                op=EQ;
                        else if (strcmp(T->type_id,"!=")==0)
                                op=NEQ;
                        T->code=genIR(op,opn1,opn2,result);
                        T->code=merge(4,T->ptr[0]->code,T->ptr[1]->code,T->code,genGoto(T->Efalse));
                        break;
            case AND:
            case OR:
                        if (T->kind==AND)
                        {
                            strcpy(T->ptr[0]->Etrue,newLabel());
                            strcpy(T->ptr[0]->Efalse,T->Efalse);
                        }
                        else
                        {
                            strcpy(T->ptr[0]->Etrue,T->Etrue);
                            strcpy(T->ptr[0]->Efalse,newLabel());
                        }
                        strcpy(T->ptr[1]->Etrue,T->Etrue);
                        strcpy(T->ptr[1]->Efalse,T->Efalse);
                        T->ptr[0]->offset=T->ptr[1]->offset=T->offset;
                        boolExp(T->ptr[0]);
                        T->width=T->ptr[0]->width;
                        boolExp(T->ptr[1]);
                        if (T->width<T->ptr[1]->width)
                            T->width=T->ptr[1]->width;
                        if (T->kind==AND)
                            T->code=merge(3,T->ptr[0]->code,genLabel(T->ptr[0]->Etrue),T->ptr[1]->code);
                        else
                            T->code=merge(3,T->ptr[0]->code,genLabel(T->ptr[0]->Efalse),T->ptr[1]->code);
                        break;
            case NOT:   strcpy(T->ptr[0]->Etrue,T->Efalse);
                        strcpy(T->ptr[0]->Efalse,T->Etrue);
                        boolExp(T->ptr[0]);
                        T->code=T->ptr[0]->code;
                        break;
        }
	}
}

//处理基本表达式，参考文献[2]p82的思想
void Exp(struct node *T)
{
	int index,num,width;
	struct node *T0,*T1;
    struct opn opn1,opn2,result;
    struct codenode *c;
	if (T)
	{
		//处理循环体内的节点
        if(T->isWhile==1)
        {
            if(T->ptr[0])
            {
                T->ptr[0]->isWhile=1;
                strcpy(T->ptr[0]->Ebreak,T->Ebreak);
                strcpy(T->ptr[0]->Econtinue,T->Econtinue);
            }
            if(T->ptr[1])
            {
                T->ptr[1]->isWhile=1;
                strcpy(T->ptr[1]->Ebreak,T->Ebreak);
                strcpy(T->ptr[1]->Econtinue,T->Econtinue);
            }
            if(T->ptr[2])
            {
                T->ptr[2]->isWhile=1;
                strcpy(T->ptr[2]->Ebreak,T->Ebreak);
                strcpy(T->ptr[2]->Econtinue,T->Econtinue);
            }
        }
		switch (T->kind)
		{
		case ID:    //查符号表，获得符号表中的位置，类型送type
					index=searchSymbolTable(T->type_id);
					if (index == -1)
						semantic_error(T->pos,T->type_id, "变量未定义");
					if (symbolTable.symbols[index].flag == 'F')
						semantic_error(T->pos,T->type_id, "是函数名，类型不匹配");
					else {
						T->place = index;       //结点保存变量在符号表中的位置
                        T->code = NULL;
						T->type = symbolTable.symbols[index].type;
						T->offset = symbolTable.symbols[index].offset;
						T->width = 0;   //此前已定义，无需占用字节
						}
					break;
		case INT:   
					T->type = INT;
                    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
                    opn1.kind = INT;
                    opn1.const_int = T->type_int;
                    opn1.level=result.level=1;
                    result.kind = ID;
                    strcpy(result.id, symbolTable.symbols[T->place].alias);
                    result.offset=symbolTable.symbols[T->place].offset;
                    T->code=genIR(ASSIGNOP,opn1,opn2,result);
					T->width = 4;
					break;
		case FLOAT: 
					T->type=FLOAT;
                    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
                    opn1.kind=FLOAT;
                    opn1.level=result.level=1;
                    opn1.const_float=T->type_float;
                    result.kind=ID;
                    strcpy(result.id,symbolTable.symbols[T->place].alias);
                    result.offset=symbolTable.symbols[T->place].offset;
                    T->code=genIR(ASSIGNOP,opn1,opn2,result);
                    T->width=4;
					break;
		case DOUBLE: 
					T->type=DOUBLE;
                    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
                    opn1.kind=DOUBLE;
                    opn1.level=result.level=1;
                    opn1.const_double=T->type_double;
                    result.kind=ID;
                    strcpy(result.id,symbolTable.symbols[T->place].alias);
                    result.offset=symbolTable.symbols[T->place].offset;
                    T->code=genIR(ASSIGNOP,opn1,opn2,result);
					T->width=8;
					break;
		case CHAR:  
					T->type=CHAR;
                    T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
                    opn1.kind=CHAR;
                    opn1.level=result.level=1;
                    opn1.const_char=T->type_char;
                    result.kind=ID;
                    strcpy(result.id,symbolTable.symbols[T->place].alias);
                    result.offset=symbolTable.symbols[T->place].offset;
                    T->code=genIR(ASSIGNOP,opn1,opn2,result);
					T->width=1;
					break;
		case ASSIGNOP:         
					if (T->ptr[0]->kind!=ID && T->ptr[0]->kind != EXP_ARRAY)
						semantic_error(T->pos,"", "赋值语句需要左值");
					else
                    {
						Exp(T->ptr[0]);   //处理左值，例中仅为变量
						T->ptr[1]->offset=T->offset;
						Exp(T->ptr[1]);
						T->type=T->ptr[0]->type;
						T->width=T->ptr[1]->width;
                        T->code=merge(2,T->ptr[0]->code,T->ptr[1]->code);
                        int flag = 0;
                        opn1.kind=ID;
                        if (T->ptr[1]->kind == EXP_ARRAY)
                        {
                            strcpy(opn1.id,symbolTable.symbols[T->ptr[1]->place].alias);
                            opn2.kind=ID;
                            strcpy(opn2.id,symbolTable.symbols[T->ptr[1]->ptr[1]->place].alias);
                            opn2.offset=symbolTable.symbols[T->ptr[1]->ptr[1]->place].offset;
                            flag = 1;
                        }
                            //sprintf(opn1.id,"%s[%s]",symbolTable.symbols[T->ptr[1]->place].alias, symbolTable.symbols[T->ptr[1]->ptr[1]->place].alias);
                        else
                            strcpy(opn1.id,symbolTable.symbols[T->ptr[1]->place].alias);
                        opn1.level=symbolTable.symbols[T->ptr[1]->place].level;
                        opn1.offset=symbolTable.symbols[T->ptr[1]->place].offset;
                        result.kind=ID;
                        if (T->ptr[0]->kind == EXP_ARRAY)
                        {
                            strcpy(result.id,symbolTable.symbols[T->ptr[0]->place].alias);
                            opn2.kind=ID;
                            strcpy(opn2.id,symbolTable.symbols[T->ptr[0]->ptr[1]->place].alias);
                            opn2.offset=symbolTable.symbols[T->ptr[0]->ptr[1]->place].offset;
                            flag = 2;
                        }
                            //sprintf(result.id,"%s[%s]",symbolTable.symbols[T->ptr[0]->place].alias, symbolTable.symbols[T->ptr[0]->ptr[1]->place].alias);
                        else
                            strcpy(result.id,symbolTable.symbols[T->ptr[0]->place].alias);
                        result.offset=symbolTable.symbols[T->ptr[0]->place].offset;
                        result.level=symbolTable.symbols[T->ptr[0]->place].level;
                        if (flag == 1)
                            T->code=merge(2,T->code,genIR(ASSIGNOP_ARRAY,opn1,opn2,result));
                        else if(flag == 2)
                            T->code=merge(2,T->code,genIR(ARRAY_ASSIGNOP,opn1,opn2,result));
                        else
                            T->code=merge(2,T->code,genIR(ASSIGNOP,opn1,opn2,result));
					}
					break;
		case AND:   
		case OR:    
					T->type=INT;
					T->ptr[0]->offset=T->ptr[1]->offset=T->offset;
					Exp(T->ptr[0]);
					Exp(T->ptr[1]);
					if (T->ptr[0]->type==FLOAT || T->ptr[1]->type==FLOAT || T->ptr[0]->type==DOUBLE || T->ptr[1]->type==DOUBLE || T->ptr[0]->type==CHAR || T->ptr[1]->type==CHAR)
					{
						if(T->ptr[0]->type==FLOAT || T->ptr[1]->type==FLOAT)
							semantic_error(T->pos,"", "逻辑运算不支持FLOAT类型");
						if(T->ptr[0]->type==DOUBLE || T->ptr[1]->type==DOUBLE)
							semantic_error(T->pos,"", "逻辑运算不支持DOUBLE类型");
						if(T->ptr[0]->type==CHAR || T->ptr[1]->type==CHAR)
							semantic_error(T->pos,"", "逻辑运算不支持CHAR类型");
					}               
					else
                    {
                        T->place=fill_Temp(newTemp(),LEV,T->type,'T',T->offset+T->ptr[0]->width+T->ptr[1]->width);
                        opn1.kind=ID;
                        if (T->ptr[0]->kind == EXP_ARRAY)
                            sprintf(opn1.id,"%s[%s]",symbolTable.symbols[T->ptr[0]->place].alias, symbolTable.symbols[T->ptr[0]->ptr[1]->place].alias);
                        else
                            strcpy(opn1.id,symbolTable.symbols[T->ptr[0]->place].alias);
                        opn2.kind=ID;
                        if (T->ptr[1]->kind == EXP_ARRAY)
                            sprintf(opn2.id,"%s[%s]",symbolTable.symbols[T->ptr[1]->place].alias, symbolTable.symbols[T->ptr[1]->ptr[1]->place].alias);
                        else
                            strcpy(opn2.id,symbolTable.symbols[T->ptr[1]->place].alias);
                        opn1.type=T->ptr[0]->type;
                        opn1.offset=symbolTable.symbols[T->ptr[0]->place].offset;
                        opn2.type=T->ptr[1]->type;
                        opn2.offset=symbolTable.symbols[T->ptr[1]->place].offset;
                        result.kind=ID;
                        strcpy(result.id,symbolTable.symbols[T->place].alias);
                        result.type=T->type;
                        result.offset=symbolTable.symbols[T->place].offset;
                        T->code=merge(3,T->ptr[0]->code,T->ptr[1]->code,genIR(T->kind,opn1,opn2,result));
						T->width=T->ptr[0]->width+T->ptr[1]->width+(T->type==CHAR?1:(T->type==DOUBLE?8:4));
                    }
					break;
		case RELOP: 
					T->type=INT;
					T->ptr[0]->offset=T->ptr[1]->offset=T->offset;
					Exp(T->ptr[0]);
					Exp(T->ptr[1]);
					if (T->ptr[0]->type==CHAR || T->ptr[1]->type==CHAR)
						semantic_error(T->pos,"", "比较运算不支持CHAR类型");
					else
					{
                        T->place=fill_Temp(newTemp(),LEV,T->type,'T',T->offset+T->ptr[0]->width+T->ptr[1]->width);
                        opn1.kind=ID;
                        if (T->ptr[0]->kind == EXP_ARRAY)
                            sprintf(opn1.id,"%s[%s]",symbolTable.symbols[T->ptr[0]->place].alias, symbolTable.symbols[T->ptr[0]->ptr[1]->place].alias);
                        else
                            strcpy(opn1.id,symbolTable.symbols[T->ptr[0]->place].alias);
                        opn2.kind=ID;
                        if (T->ptr[1]->kind == EXP_ARRAY)
                            sprintf(opn2.id,"%s[%s]",symbolTable.symbols[T->ptr[1]->place].alias, symbolTable.symbols[T->ptr[1]->ptr[1]->place].alias);
                        else
                            strcpy(opn2.id,symbolTable.symbols[T->ptr[1]->place].alias);
                        opn1.type=T->ptr[0]->type;
                        opn1.offset=symbolTable.symbols[T->ptr[0]->place].offset;
                        opn2.type=T->ptr[1]->type;
                        opn2.offset=symbolTable.symbols[T->ptr[1]->place].offset;
                        result.kind=ID;
                        strcpy(result.id,symbolTable.symbols[T->place].alias);
                        result.type=T->type;
                        result.offset=symbolTable.symbols[T->place].offset;
                        if (strcmp(T->type_id,"<")==0)
								T->kind=EJLT;
						else if (strcmp(T->type_id,"<=")==0)
								T->kind=EJLE;
						else if (strcmp(T->type_id,">")==0)
								T->kind=EJGT;
						else if (strcmp(T->type_id,">=")==0)
								T->kind=EJGE;
						else if (strcmp(T->type_id,"==")==0)
								T->kind=EEQ;
						else if (strcmp(T->type_id,"!=")==0)
								T->kind=ENEQ;
                        T->code=merge(3,T->ptr[0]->code,T->ptr[1]->code,genIR(T->kind,opn1,opn2,result));
						T->width=T->ptr[0]->width+T->ptr[1]->width+(T->type==CHAR?1:(T->type==DOUBLE?8:4));
					}     
					break;
		case PLUS:
		case MINUS:
		case STAR:
		case DIV:   
					T->ptr[0]->offset=T->offset;
					Exp(T->ptr[0]);
					T->ptr[1]->offset=T->offset+T->ptr[0]->width;
					Exp(T->ptr[1]);
					if (T->ptr[0]->type==CHAR || T->ptr[1]->type==CHAR)
						semantic_error(T->pos,"", "算术运算不支持CHAR类型");
					else
					{
						//判断T->ptr[0]，T->ptr[1]类型是否正确，可能根据运算符生成不同形式的代码，给T的type赋值
						//下面的类型属性计算，没有考虑错误处理情况
						if (T->ptr[0]->type==DOUBLE || T->ptr[1]->type==DOUBLE)
							 T->type=DOUBLE,T->width=T->ptr[0]->width+T->ptr[1]->width+8;
						else if (T->ptr[0]->type==FLOAT || T->ptr[1]->type==FLOAT)
							 T->type=FLOAT,T->width=T->ptr[0]->width+T->ptr[1]->width+4;
						else
                            T->type=INT,T->width=T->ptr[0]->width+T->ptr[1]->width+4;
                        T->place=fill_Temp(newTemp(),LEV,T->type,'T',T->offset+T->ptr[0]->width+T->ptr[1]->width);
                        opn1.kind=ID;
                        if (T->ptr[0]->kind == EXP_ARRAY)
                            sprintf(opn1.id,"%s[%s]",symbolTable.symbols[T->ptr[0]->place].alias, symbolTable.symbols[T->ptr[0]->ptr[1]->place].alias);
                        else
                            strcpy(opn1.id,symbolTable.symbols[T->ptr[0]->place].alias);
                        opn2.kind=ID;
                        if (T->ptr[1]->kind == EXP_ARRAY)
                            sprintf(opn2.id,"%s[%s]",symbolTable.symbols[T->ptr[1]->place].alias, symbolTable.symbols[T->ptr[1]->ptr[1]->place].alias);
                        else
                            strcpy(opn2.id,symbolTable.symbols[T->ptr[1]->place].alias);
                        opn1.type=T->ptr[0]->type;
                        opn1.offset=symbolTable.symbols[T->ptr[0]->place].offset;
                        opn1.level=symbolTable.symbols[T->ptr[0]->place].level;
                        opn2.type=T->ptr[1]->type;
                        opn2.offset=symbolTable.symbols[T->ptr[1]->place].offset;
                        opn2.level=symbolTable.symbols[T->ptr[1]->place].level;
                        result.kind=ID;
                        strcpy(result.id,symbolTable.symbols[T->place].alias);
                        result.type=T->type;
                        result.offset=symbolTable.symbols[T->place].offset;
                        result.level=symbolTable.symbols[T->place].level;
                        T->code=merge(3,T->ptr[0]->code,T->ptr[1]->code,genIR(T->kind,opn1,opn2,result));
						T->width=T->ptr[0]->width+T->ptr[1]->width+(T->type==CHAR?1:(T->type==DOUBLE?8:4));
					}
					break;
		case ASSIGNOP_PLUS:
		case ASSIGNOP_MINUS:
		case ASSIGNOP_STAR:
		case ASSIGNOP_DIV:
					if (T->ptr[0]->kind!=ID && T->ptr[0]->kind != EXP_ARRAY)
						semantic_error(T->pos,"", "复合赋值语句需要左值");
					else 
					{
						Exp(T->ptr[0]);   //处理左值，例中仅为变量
						T->ptr[1]->offset=T->offset;
						Exp(T->ptr[1]);
						if(T->ptr[0]->type==CHAR || T->ptr[1]->type==CHAR)
							semantic_error(T->pos,"", "复合运算不支持CHAR类型");
						else 
						{
							if (T->ptr[0]->type==FLOAT || T->ptr[1]->type==FLOAT)
								T->type=FLOAT,T->width=T->ptr[0]->width+T->ptr[1]->width+4;
							else if (T->ptr[0]->type==DOUBLE || T->ptr[1]->type==DOUBLE)
								T->type=DOUBLE,T->width=T->ptr[0]->width+T->ptr[1]->width+8;
							else 
								T->type=INT,T->width=T->ptr[0]->width+T->ptr[1]->width+4;
                            T->place=fill_Temp(newTemp(),LEV,T->type,'T',T->offset+T->ptr[0]->width+T->ptr[1]->width);
                            opn1.kind=ID;
                            if (T->ptr[0]->kind == EXP_ARRAY)
                                sprintf(opn1.id,"%s[%s]",symbolTable.symbols[T->ptr[0]->place].alias, symbolTable.symbols[T->ptr[0]->ptr[1]->place].alias);
                            else
                                strcpy(opn1.id,symbolTable.symbols[T->ptr[0]->place].alias);
                            opn2.kind=ID;
                            if (T->ptr[1]->kind == EXP_ARRAY)
                                sprintf(opn2.id,"%s[%s]",symbolTable.symbols[T->ptr[1]->place].alias, symbolTable.symbols[T->ptr[1]->ptr[1]->place].alias);
                            else
                                strcpy(opn2.id,symbolTable.symbols[T->ptr[1]->place].alias);
                            opn1.type=T->ptr[0]->type;
                            opn1.offset=symbolTable.symbols[T->ptr[0]->place].offset;
                            opn2.type=T->ptr[1]->type;
                            opn2.offset=symbolTable.symbols[T->ptr[1]->place].offset;
                            result.kind=ID;
                            strcpy(result.id,symbolTable.symbols[T->place].alias);
                            result.type=T->type;
                            result.offset=symbolTable.symbols[T->place].offset;
                            T->code=merge(3,T->ptr[0]->code,T->ptr[1]->code,genIR(T->kind,opn1,opn2,result));
						    T->width=T->ptr[0]->width+T->ptr[1]->width+(T->type==CHAR?1:T->type==DOUBLE?8:4);
                        }
					}
					break;
		case PRE_PLUS_SELF:
		case NEXT_PLUS_SELF:
		case PRE_MINUS_SELF:
		case NEXT_MINUS_SELF:
					if(T->ptr[0]->kind!=ID && T->ptr[0]->kind != EXP_ARRAY)
					{
						semantic_error(T->pos,"", "自增自减对象只能是int变量");
						break;
					}
					Exp(T->ptr[0]);   //处理左值，例中仅为变量
					if (T->ptr[0]->type==CHAR || T->ptr[0]->type==FLOAT || T->ptr[0]->type==DOUBLE)
					{
						semantic_error(T->pos,"", "自增自减只支持int类型");
						break;
					}
					else 
					{
						T->type=INT;
						T->width=T->ptr[0]->width+4;
                        T->place=fill_Temp(newTemp(),LEV,T->type,'T',T->offset+T->ptr[0]->width);
                        opn1.kind=ID;
                        if (T->ptr[0]->kind == EXP_ARRAY)
                            sprintf(opn1.id,"%s[%s]",symbolTable.symbols[T->ptr[0]->place].alias, symbolTable.symbols[T->ptr[0]->ptr[1]->place].alias);
                        else
                            strcpy(opn1.id,symbolTable.symbols[T->ptr[0]->place].alias);
                        strcpy(opn1.id,symbolTable.symbols[T->ptr[0]->place].alias);
                        opn1.type=T->ptr[0]->type;
                        opn1.offset=symbolTable.symbols[T->ptr[0]->place].offset;
                        result.kind=ID;
                        strcpy(result.id,symbolTable.symbols[T->place].alias);
                        result.type=T->type;
                        result.offset=symbolTable.symbols[T->place].offset;
                        T->width=T->ptr[0]->width+(T->type==CHAR?1:T->type==DOUBLE?8:4);
                        T->code=merge(2,T->ptr[0]->code,genIR(T->kind,opn1,opn2,result));
					}
					break;
		case NOT:   
		case UMINUS:
					T->type = INT;
					T->ptr[0]->offset=T->offset;
					Exp(T->ptr[0]);
					if (T->ptr[0]->type==FLOAT || T->ptr[0]->type==CHAR || T->ptr[0]->type==DOUBLE)
					{
						if (T->kind == NOT && T->ptr[0]->type==CHAR)
						{
							semantic_error(T->pos,"", "取非语句不允许char类型");
						}
						if (T->kind == NOT && T->ptr[0]->type==FLOAT)
						{
							semantic_error(T->pos,"", "取非语句不允许float类型");
						}
						if (T->kind == NOT && T->ptr[0]->type==DOUBLE)
						{
							semantic_error(T->pos,"", "取非语句不允许double类型");
						}
						if(T->kind == UMINUS && T->ptr[0]->type==CHAR)
						{
							semantic_error(T->pos,"", "取负语句不允许char类型");
						}
						if(T->kind == UMINUS && T->ptr[0]->type==FLOAT)
						{
							semantic_error(T->pos,"", "取负语句不允许float类型");
						}
						if(T->kind == UMINUS && T->ptr[0]->type==DOUBLE)
						{
							semantic_error(T->pos,"", "取负语句不允许duble类型");
						}
					} 
					else
                    {
                        T->place=fill_Temp(newTemp(),LEV,T->type,'T',T->offset+T->ptr[0]->width);
                        opn1.kind=ID;
                        if (T->ptr[0]->kind == EXP_ARRAY)
                            sprintf(opn1.id,"%s[%s]",symbolTable.symbols[T->ptr[0]->place].alias, symbolTable.symbols[T->ptr[0]->ptr[1]->place].alias);
                        else
                            strcpy(opn1.id,symbolTable.symbols[T->ptr[0]->place].alias);
                        opn1.type=T->ptr[0]->type;
                        opn1.offset=symbolTable.symbols[T->ptr[0]->place].offset;
                        result.kind=ID;
                        strcpy(result.id,symbolTable.symbols[T->place].alias);
                        result.type=T->type;
                        result.offset=symbolTable.symbols[T->place].offset;
                        T->code=merge(2,T->ptr[0]->code,genIR(T->kind,opn1,opn2,result));
						T->width=T->ptr[0]->width+(T->type==DOUBLE?8:4);
                    }
					break;
		case FUNC_CALL: //根据T->type_id查出函数的定义，如果语言中增加了实验教材的read，write需要单独处理一下
					index=searchSymbolTable(T->type_id);
					if (index==-1)
					{
						semantic_error(T->pos,T->type_id, "函数未定义");
						break;
					}
					if (symbolTable.symbols[index].flag!='F')
					{
						semantic_error(T->pos,T->type_id, "不是一个函数");
						 break;
					}
					T->type=symbolTable.symbols[index].type;
					width=T->type==CHAR?1:(T->type==DOUBLE?8:4);   //存放函数返回值的单数字节数
					if (T->ptr[0])//有参函数
					{
						T->ptr[0]->offset=T->offset;
						Exp(T->ptr[0]);       //处理所有实参表达式求值，及类型
						T->width=T->ptr[0]->width+width; //累加上计算实参使用临时变量的单元数
                        T->code=T->ptr[0]->code;
					}
					else
                    {
						T->width=width;
                        T->code=NULL;
                    }
					match_param(index,T->ptr[0]);   //处理所以参数的匹配
                    T0=T->ptr[0];
                    while (T0)//生成所有参数节点代码
                    {
                        result.kind=ID;
                        strcpy(result.id,symbolTable.symbols[T0->ptr[0]->place].alias);
                        result.offset=symbolTable.symbols[T0->ptr[0]->place].offset;
                        T->code=merge(2,T->code,genIR(ARG,opn1,opn2,result));
                        T0=T0->ptr[1];
                    }
                    T->place=fill_Temp(newTemp(),LEV,T->type,'T',T->offset+T->width-width);
                    opn1.kind=ID;
                    strcpy(opn1.id,T->type_id);  //保存函数名
                    opn1.offset=index;  //这里offset用以保存函数定义入口,在目标代码生成时，能获取相应信息
                    result.kind=ID;
                    strcpy(result.id,symbolTable.symbols[T->place].alias);
                    result.offset=symbolTable.symbols[T->place].offset;
                    T->code=merge(2,T->code,genIR(CALL,opn1,opn2,result)); //生成函数调用中间代码
					break;
		case ARGS:      //此处仅处理各实参表达式的求值的代码序列，不生成ARG的实参系列
					T->ptr[0]->offset=T->offset;
					Exp(T->ptr[0]);
					T->width=T->ptr[0]->width;
                    T->code=T->ptr[0]->code;
					if (T->ptr[1])
					{
						T->ptr[1]->offset=T->offset+T->ptr[0]->width;
						Exp(T->ptr[1]);
						T->width+=T->ptr[1]->width;
                        T->code=merge(2,T->code,T->ptr[1]->code);
					}
					break;
		case EXP_ARRAY:
                    opn1.level = opn2.level = result.level = 1;
					if(T->ptr[1]->type != INT)
					{
						semantic_error(T->pos, "","数组访问的下标只能是正整数");
						break;
					}
					T0 = T;
					num = 0;
					//搜索到数组ID节点
					while(T0)
					{
						if(T0->kind != ID)
						{
							T0 = T0->ptr[0];
							num++;
						}
						else break;
					}
                    index = searchSymbolTable(T0->type_id);
                    if (index == -1)
                    {
                        semantic_error(T->pos, "","数组不存在");
                        break;
                    }
					if(num != symbolTable.symbols[index].type_array.arrary_size)
					{
						semantic_error(T->pos, T0->type_id,"错误的数组访问");
                        break;
					}
                    //产生中间代码
                    T0 = T;
                    //处理第一层
                    T0->ptr[1]->place=fill_Temp(newTemp(), LEV, T->type, 'T', T0->offset);
                    T0->ptr[0]->offset = T0->offset + 4;
                    opn1.kind=INT;
                    opn1.const_int=T0->ptr[1]->type_int;//该层偏移量
                    result.kind=ID;
                    strcpy(result.id,symbolTable.symbols[T->ptr[1]->place].alias);
                    result.offset=symbolTable.symbols[T->ptr[1]->place].offset;
                    c=genIR(ASSIGNOP,opn1,opn2,result);
                    T1=T0->ptr[0];
                    num=1;
                    while(T1)
                    {
                        if(T1->kind !=ID)//非id节点，继续产生记录偏移量的中间代码
                        {
                            opn1.kind=INT;
                            opn1.const_int=T1->ptr[1]->type_int;
                            struct opn result1, result2;//
                            int index1,index2;//
                            result1.level=result2.level=1;
                            result1.kind=ID;//
                            index1=fill_Temp(newTemp(), LEV, T->type, 'T', T1->offset);//
                            result1.offset=T1->offset;
                            T1->offset+=4;
                            strcpy(result1.id,symbolTable.symbols[index1].alias);//
                            c=merge(2,c,genIR(ASSIGNOP,opn1,opn2,result1));
                            int i=1;
                            int offsets=1;
                            while(i <= num)//获取维数偏移
                            {
                                offsets*=symbolTable.symbols[index].type_array.array_par[num-i];
                                i++;
                            }
                            opn1.kind=INT;
                            opn1.const_int=offsets;
                            result2.kind=ID;
                            index2=fill_Temp(newTemp(), LEV, T->type, 'T', T1->offset);//
                            result2.offset=T1->offset;
                            T1->offset+=4;
                            strcpy(result2.id,symbolTable.symbols[index2].alias);//
                            c=merge(2,c,genIR(ASSIGNOP,opn1,opn2,result2));
                            result.kind=ID;
                            T1->ptr[1]->place=fill_Temp(newTemp(), LEV, T->type, 'T', T1->offset);
                            strcpy(result.id,symbolTable.symbols[T1->ptr[1]->place].alias);
                            result.offset=T1->offset;
                            T1->offset+=4;
                            c=merge(2,c,genIR(STAR,result1,result2,result));
                            T0=T1;
                            T1=T1->ptr[0];
                            num++;
                        }
                        else
                            break;
                    }
                    T->offset=symbolTable.symbols[index].offset;
                    T->place=index;
                    T0=T;
                    T1=T->ptr[0];
                    opn1.kind=ID;
                    strcpy(opn1.id, symbolTable.symbols[T->ptr[1]->place].alias);
                    opn1.offset=symbolTable.symbols[T->ptr[1]->place].offset;
                    result.kind=ID;
                    strcpy(result.id, symbolTable.symbols[T->ptr[1]->place].alias);
                    result.offset=symbolTable.symbols[T->ptr[1]->place].offset;
                    while(T1)
                    {
                        if (T1->kind != ID)
                        {
                            opn2.kind=ID;
                            strcpy(opn2.id,symbolTable.symbols[T1->ptr[1]->place].alias);
                            opn2.offset=symbolTable.symbols[T1->ptr[1]->place].offset;
                            c=merge(2,c,genIR(PLUS,opn1,opn2,result));
                            T0=T1;
                            T1=T1->ptr[0];
                        }
                        else
                            break;
                    }
                    T->code=c;
					break;
		case BREAK: 
					if(T->isWhile == 0)
						semantic_error(T->pos, "break语句前没有匹配的循环体","");
					else
                    {
                    	T->width=0;
                        T->code=merge(1,genGoto(T->Ebreak));
                    }  
					break;
		case CONTINUE: 
					if(T->isWhile == 0)
						semantic_error(T->pos, "continue语句前没有匹配的循环体","");
					else
                    {
						T->width=0;
                        T->code=merge(1,genGoto(T->Econtinue));
                    }
					break;
		}
    }
}

//外部定义列表处理函数
void ext_def_list(struct node *T)
{
	//分号
    if (!T->ptr[0])
        return;
    //设置偏移地址
    offset0=T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]);//对第一个外部定义进行语义分析
    T->code=T->ptr[0]->code;
    //若其后还有外部定义，则进行语义分析
    if (T->ptr[1])
    {
		//增加偏移地址为前一个外部定义的字节数
        T->ptr[1]->offset = T->ptr[0]->offset + T->ptr[0]->width;
        semantic_Analysis(T->ptr[1]); //语义分析
        T->code=merge(2,T->code,T->ptr[1]->code);
    }
}

//数组声明处理函数
void array_dec(struct node *T)
{
	//统计了每一维大小，中间代码生成用
	struct node *T0;
    int width, index;
	int size = 1;
	T0 = T;
	int array_pars[32];
	int array_size = 0;
	while(T0)
	{
		if(T0->kind != ID)
		{
			T->type_array.array_par[array_size] = array_pars[array_size] = T0->ptr[1]->type_int;//记录第i维数组大小
            array_size++;
			size *= T0->ptr[1]->type_int;
			T0->ptr[1]->offset = T0->ptr[0]->offset = T0->offset;
			T0 = T0->ptr[0];
		}
		else break;
	}
	//将数组维数记录到数组ID节点和内情向量中
	T->type_array.arrary_size = T0->array_size = array_size;
    if (T->type == INT)
        width = 4;
    if (T->type == FLOAT)
        width = 4;
    if (T->type == DOUBLE)
        width = 8;
    if (T->type == CHAR)
        width = 1;
    T->width = width * size;
    index = add_symbolTable(T0->type_id, newAlias(), LEV, T->type, 'V', T->offset);
    if (index == -1)
    {
		T->width = 0;
        semantic_error(T->pos, T0->type_id, "变量重复声明");
        return;
    }
    else
    {
        T->place = index;
        symbolTable.symbols[symbolTable.index-1].type_array.arrary_size = array_size;
        symbolTable.symbols[symbolTable.index-1].type_array.offset = T->offset;
        int i=0;
        while(i<array_size)
        {
            symbolTable.symbols[symbolTable.index-1].type_array.array_par[i] = array_pars[i];
            i++;
        }
    }
}

//变量声明处理函数
void var_dec(struct node *T)
{
	int index;
	switch(T->kind)
	{
		//变量声明处理
		case ID:
			index = add_symbolTable(T->type_id, newAlias(), LEV, T->type, 'V', T->offset);
			if (index == -1)
				semantic_error(T->pos, T->type_id, "变量重复声明");
			else
			{
				T->place = index;
				T->width = T->type==CHAR?1:(T->type==DOUBLE?8:4);
				T->num = 1;
			}
			break;
		//数组声明处理
		case ARRAY_DEC:
			array_dec(T);
			break;
	}
}

//外部变量声明列表处理函数
void ext_dec_list(struct node *T)
{
    switch (T->kind)
    {
		//外部变量声明列表，递归调用函数
		case EXT_DEC_LIST:
			//设置变量声明列表中第一个变量的类型和偏移量
			T->ptr[0]->type = T->type;
			T->ptr[0]->offset = T->offset;
			//设置后续列表的类型和偏移量
			T->ptr[1]->type = T->type;
			T->ptr[1]->offset = T->offset + T->width;
			T->ptr[1]->width = T->width;
			//递归分析第一个变量和后续变量列表
			var_dec(T->ptr[0]);
			ext_dec_list(T->ptr[1]);
			//计算变量个数
			T->num = T->ptr[1]->num + 1;
			T->width = T->ptr[0]->width + T->ptr[1]->width;
			break;
		//变量声明节点，对节点调用变量声明处理函数
		default:
			var_dec(T);
			break;
    }
}

//外部变量定义处理函数
void ext_var_def(struct node *T)
{
    if (!strcmp(T->ptr[0]->type_id, "int"))
    {
        T->type = T->ptr[1]->type = INT;
        T->ptr[1]->width = 4;
    }
    if (!strcmp(T->ptr[0]->type_id, "float"))
    {
        T->type = T->ptr[1]->type = FLOAT;
        T->ptr[1]->width = 4;
    }
    if (!strcmp(T->ptr[0]->type_id, "double"))
    {
        T->type = T->ptr[1]->type = DOUBLE;
        T->ptr[1]->width = 8;
    }
    if (!strcmp(T->ptr[0]->type_id, "char"))
    {
        T->type = T->ptr[1]->type = CHAR;
        T->ptr[1]->width = 1;
    }
    if (!strcmp(T->ptr[0]->type_id, "string"))
    {
        T->type = T->ptr[1]->type = STRING;
    }
	//前面的关键字不占偏移量
    T->ptr[1]->offset = T->offset;
    ext_dec_list(T->ptr[1]);//处理变量列表
    T->width = T->ptr[1]->width; //计算这个外部变量说明的宽度
    T->code = NULL;//外部变量定义未初始化，不产生中间代码
}

//外部变量定义赋值处理函数
void ext_var_def_assign(struct node *T)
{
    if(T->ptr[1]->kind != ID)
		semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "数组类型不支持初始化");
	else if(!strcmp(T->ptr[0]->type_id, "int") && T->ptr[2]->type != INT)
		semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "初始化类型不匹配");
	else if(!strcmp(T->ptr[0]->type_id, "float") && T->ptr[2]->type != FLOAT)
		semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "初始化类型不匹配");
	else if(!strcmp(T->ptr[0]->type_id, "double") && T->ptr[2]->type != DOUBLE)
		semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "初始化类型不匹配");
	else if(!strcmp(T->ptr[0]->type_id, "char") && T->ptr[2]->type != CHAR)
		semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "初始化类型不匹配");
	else if(!strcmp(T->ptr[0]->type_id, "string") && T->ptr[2]->type != STRING)
		semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "初始化类型不匹配");
	else
	{
		add_symbolTable(T->ptr[1]->type_id, newAlias(), LEV, T->ptr[0]->type, 'V', T->offset);
		T->width = T->ptr[0]->type == CHAR?1:(T->ptr[0]->type == DOUBLE?8:4);
	}
}

//参数声明处理函数
void param_dec(struct node *T)
{
    int index;
    struct opn opn1, opn2, result;
    index = add_symbolTable(T->ptr[1]->type_id, newAlias(), 1, T->ptr[0]->type, 'P', T->offset);
    if (index == -1)
        semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "参数名重复声明");
    else
        T->ptr[1]->place = index;
    T->num = 1;//参数个数计算的初始值
	if(T->ptr[0]->type == INT)
		T->width = 4;
	if(T->ptr[0]->type == FLOAT)
		T->width = 4;
	if(T->ptr[0]->type == DOUBLE)
		T->width = 8;
	if(T->ptr[0]->type == CHAR)
		T->width = 1;
    result.kind = ID;
    strcpy(result.id, symbolTable.symbols[index].alias);
    result.offset = T->offset;
    T->code = genIR(PARAM, opn1, opn2, result);
}

//参数列表处理函数
void param_list(struct node *T)
{
    T->ptr[0]->offset = T->offset + DX;
    semantic_Analysis(T->ptr[0]);
	//还有参数声明
    if (T->ptr[1])
    {
        T->ptr[1]->offset = T->offset + T->ptr[0]->width;
        semantic_Analysis(T->ptr[1]);
        T->num = T->ptr[0]->num + T->ptr[1]->num;             //统计参数个数
        T->width = T->ptr[0]->width + T->ptr[1]->width;       //累加参数单元宽度
        T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code); //连接参数代码
    }
	//最后一个参数声明
    else
    {
        T->num = T->ptr[0]->num;
        T->width = T->ptr[0]->width;
        T->code = T->ptr[0]->code;
    }
}

//函数声明处理函数
void func_dec(struct node *T)
{
    struct opn result,opn1,opn2;
    int index;
    index = add_symbolTable(T->type_id, newAlias(), LEV, T->type, 'F', 0); //函数声明不在数据区中分配单元，偏移量为0
    if (index == -1)
    {
        semantic_error(T->pos, T->type_id, "函数重复声明");
        return;
    }
	symbol_scope_TX.TX[symbol_scope_TX.top++] = index + 1;
	isFunc = 1;
    T->place = index;
    result.kind = ID;
    strcpy(result.id, T->type_id);
    result.offset = index;
    T->code = genIR(FUNCTION, opn1, opn2, result); //生成中间代码：FUNCTION 函数名
    //T->offset = DX;                                //设置形式参数在活动记录中的偏移量初值
    if (T->ptr[0])
    { //判断是否有参数
        T->ptr[0]->offset = T->offset;
        semantic_Analysis(T->ptr[0]); //处理函数参数列表
        T->width = T->ptr[0]->width;
        symbolTable.symbols[index].paramnum = T->ptr[0]->num;
        T->code = merge(2, T->code, T->ptr[0]->code); //连接函数名和参数代码序列
    }
    else
        symbolTable.symbols[index].paramnum = 0, T->width = 0;
}

//函数定义处理函数
void func_def(struct node *T)
{
	isReturn = 0;
    if (!strcmp(T->ptr[0]->type_id, "int"))
    {
        T->ptr[1]->type = INT;
    }
    if (!strcmp(T->ptr[0]->type_id, "float"))
    {
        T->ptr[1]->type = FLOAT;
    }
    if (!strcmp(T->ptr[0]->type_id, "double"))
    {
        T->ptr[1]->type = DOUBLE;
    }
    if (!strcmp(T->ptr[0]->type_id, "char"))
    {
        T->ptr[1]->type = CHAR;
    }
    if (!strcmp(T->ptr[0]->type_id, "void"))
    {
        T->ptr[1]->type = VOID;
    }
    //填写函数定义信息到符号表
    T->width = 0;                  //函数的宽度设置为0，不会对外部变量的地址分配产生影响
    T->offset = DX;                //设置局部变量在活动记录中的偏移量初值
    semantic_Analysis(T->ptr[1]);  //处理函数名和参数结点部分，这里不考虑用寄存器传递参数
    T->offset += T->ptr[1]->width; //用形参单元宽度修改函数局部变量的起始偏移量
    T->ptr[2]->offset = T->offset;
    strcpy(T->ptr[2]->Snext, newLabel()); //函数体语句执行结束后的位置属性
    semantic_Analysis(T->ptr[2]);         //处理函数体结点
	if(!isReturn && T->ptr[0]->type != VOID)
		semantic_error(T->pos, T->type_id, "函数缺少返回值");
    //计算活动记录大小,这里offset属性存放的是活动记录大小，不是偏移
    symbolTable.symbols[T->ptr[1]->place].offset = T->offset + T->ptr[2]->width;
    T->code = merge(3, T->ptr[1]->code, T->ptr[2]->code, genLabel(T->ptr[2]->Snext)); //函数体的代码作为函数的代码
	T->offset = offset0;
}

//复合语句处理函数
void comp_stm(struct node *T)
{
	// printf("\n进入复合语句块，当前符号表如下：\n");
    // display_symbol();//显示符号表
	//一个语句块增加一层
    LEV++;
    //设置层号加1，并且保存该层局部变量在符号表中的起始位置在symbol_scope_TX
    symbol_scope_TX.TX[symbol_scope_TX.top++] = symbolTable.index;
    T->width = 0;
    T->code = NULL;
	//有定义列表，处理定义列表
    if (T->ptr[0])
    {
        T->ptr[0]->offset = T->offset;
        semantic_Analysis(T->ptr[0]); //处理该层的局部变量DEF_LIST
        T->width += T->ptr[0]->width;
        T->code=T->ptr[0]->code;
    }
	//有语句列表，处理语句列表
    if (T->ptr[1])
    {
        T->ptr[1]->offset = T->offset + T->width;
        strcpy(T->ptr[1]->Snext, T->Snext); //S.next属性向下传递
        semantic_Analysis(T->ptr[1]);       //处理复合语句的语句序列
        T->width += T->ptr[1]->width;
        T->code = merge(2, T->code, T->ptr[1]->code);
    }
	// printf("\n在复合语句块，当前符号表如下：\n");
    // display_symbol();//显示符号表
    LEV--;                                                         //出复合语句，层号减1
    symbolTable.index = symbol_scope_TX.TX[--symbol_scope_TX.top]; //删除该作用域中的符号
	// if(isFunc)//如果是函数体，还要删除参数列表
	// {
	// 	symbolTable.index = symbol_scope_TX.TX[--symbol_scope_TX.top];
	// 	isFunc = 0;
	// }
	// printf("\n退出复合语句块，当前符号表如下：\n");
    // display_symbol();//显示符号表
	//T->width = 0;
}

//内部定义列表处理函数
void def_list(struct node *T)
{
    T->code = NULL;
	//有定义
    if (T->ptr[0])
    {
        T->ptr[0]->offset = T->offset;
        semantic_Analysis(T->ptr[0]); //处理一个局部变量定义
        T->code = T->ptr[0]->code;
        T->width = T->ptr[0]->width;
    }
    if (T->ptr[1])
    {
        T->ptr[1]->offset = T->offset + T->ptr[0]->width;
        semantic_Analysis(T->ptr[1]); //处理剩下的局部变量定义
        T->code = merge(2, T->code, T->ptr[1]->code);
        T->width += T->ptr[1]->width;//宽度增加
    }
}

//局部变量定义处理函数
void var_def(struct node *T)
{
    int index, num, width;
    struct node *T0;
    struct opn opn1, opn2, result;
    T->code = NULL;
    if (!strcmp(T->ptr[0]->type_id, "int"))
    {
        T->ptr[1]->type = INT;
        width = 4;
    }
    if (!strcmp(T->ptr[0]->type_id, "float"))
    {
        T->ptr[1]->type = FLOAT;
        width = 4;
    }
    if (!strcmp(T->ptr[0]->type_id, "double"))
    {
        T->ptr[1]->type = DOUBLE;
        width = 8;
    }
    if (!strcmp(T->ptr[0]->type_id, "char"))
    {
        T->ptr[1]->type = CHAR;
        width = 1;
    }
    T0 = T->ptr[1]; //T0为变量名列表子树根指针，对ID、ASSIGNOP类结点在登记到符号表，作为局部变量
    num = 0;
    T0->offset = T->offset;
    T->width = 0;
	//处理所有DEC_LIST结点
    while (T0)
    {
        num++;
        T0->ptr[0]->type = T0->type; //类型属性向下传递
		//还有下一个列表节点
        if (T0->ptr[1])
            T0->ptr[1]->type = T0->type;
        T0->ptr[0]->offset = T0->offset; //类型属性向下传递
		//还有下一个列表节点
        if (T0->ptr[1])
            T0->ptr[1]->offset = T0->offset + width;
        if (T0->ptr[0]->kind == ID)
        {
            index = add_symbolTable(T0->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width);
            if (index == -1)
                semantic_error(T0->ptr[0]->pos, T0->ptr[0]->type_id, "变量重复定义");
            else
                T0->ptr[0]->place = index;
            T->width += width;
        }
        else if (T0->ptr[0]->kind == ASSIGNOP)
        {
            index = add_symbolTable(T0->ptr[0]->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width);
            if (index == -1)
                semantic_error(T0->ptr[0]->ptr[0]->pos, T0->ptr[0]->ptr[0]->type_id, "变量重复定义");
            else
            {
                T0->ptr[0]->place = index;
                T0->ptr[0]->ptr[1]->offset = T->offset + T->width + width;
                Exp(T0->ptr[0]->ptr[1]);
                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T0->ptr[0]->ptr[1]->place].alias);
                opn1.offset = symbolTable.symbols[T0->ptr[0]->ptr[1]->place].offset;
                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T0->ptr[0]->place].alias);
                result.offset = symbolTable.symbols[T0->ptr[0]->place].offset;
                printf("opn1->offset:%d,result->offset:%d\n",opn1.offset,result.offset);
                T->code = merge(3, T->code, T0->ptr[0]->ptr[1]->code, genIR(ASSIGNOP, opn1, opn2, result));
            }
            T->width += width;
        }
        T0 = T0->ptr[1];
    }
}

//语句列表处理函数
void stm_list(struct node *T)
{
	//没有语句列表
    if (!T->ptr[0])
    {
        T->code = NULL;
        T->width = 0;
        return;
    }
    if (T->ptr[1]) //2条以上语句连接，生成新标号作为第一条语句结束后到达的位置
        strcpy(T->ptr[0]->Snext, newLabel());
    else //语句序列仅有一条语句，S.next属性向下传递
        strcpy(T->ptr[0]->Snext, T->Snext);
    T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]);
    T->code = T->ptr[0]->code;
    T->width = T->ptr[0]->width;
	//2条以上语句连接,S.next属性向下传递
    if (T->ptr[1])
    { 
        strcpy(T->ptr[1]->Snext, T->Snext);
        T->ptr[1]->offset = T->offset; //顺序结构共享单元方式
                                       //                  T->ptr[1]->offset=T->offset+T->ptr[0]->width; //顺序结构顺序分配单元方式
        semantic_Analysis(T->ptr[1]);
        //序列中第1条为表达式语句，返回语句，复合语句时，第2条前不需要标号
        if (T->ptr[0]->kind == RETURN || T->ptr[0]->kind == EXP_STMT || T->ptr[0]->kind == COMP_STM)
            T->code = merge(2, T->code, T->ptr[1]->code);
        else
            T->code = merge(3, T->code, genLabel(T->ptr[0]->Snext), T->ptr[1]->code);
        if (T->ptr[1]->width > T->width)
            T->width = T->ptr[1]->width; //顺序结构共享单元方式
                                         //                        T->width+=T->ptr[1]->width;//顺序结构顺序分配单元方式
    }
}

//表达式语句处理函数
void exp_stmt(struct node *T)
{
    T->ptr[0]->offset = T->offset;
    semantic_Analysis(T->ptr[0]);
    T->code = T->ptr[0]->code;
    T->width = T->ptr[0]->width;
}

//返回语句处理函数
void return_dec(struct node *T)
{
    int index, num;
    struct opn opn1, opn2, result;
	isReturn = 1;
	//有返回值
    if (T->ptr[0])
    {
        T->ptr[0]->offset = T->offset;
        Exp(T->ptr[0]);
        num = symbolTable.index;
        do
            num--;
        while (symbolTable.symbols[num].flag != 'F');//num指向当前函数在符号表中的位置
        if (T->ptr[0]->type != symbolTable.symbols[num].type)
        {
            semantic_error(T->pos, "返回值类型错误", "");
            T->width = 0;
            T->code = NULL;
            return;
        }
        T->width = T->ptr[0]->width;
        result.kind = ID;
        strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
        result.offset = symbolTable.symbols[T->ptr[0]->place].offset;
        T->code = merge(2, T->ptr[0]->code, genIR(RETURN, opn1, opn2, result));
    }
    else
    {
        T->width = 0;
        result.kind = 0;
        T->code = genIR(RETURN, opn1, opn2, result);
    }
}

//if语句处理函数
void if_then(struct node *T)
{
    strcpy(T->ptr[0]->Etrue, newLabel()); //设置条件语句真假转移位置
    strcpy(T->ptr[0]->Efalse, T->Snext);
    T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
	//bool表达式处理
    boolExp(T->ptr[0]);
    T->width = T->ptr[0]->width;
    strcpy(T->ptr[1]->Snext, T->Snext);
    semantic_Analysis(T->ptr[1]); //if子句
    if (T->width < T->ptr[1]->width)
        T->width = T->ptr[1]->width;
    T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code);
}

//if-else语句处理函数
void if_then_else(struct node *T)
{
    strcpy(T->ptr[0]->Etrue, newLabel()); //设置条件语句真假转移位置
    strcpy(T->ptr[0]->Efalse, newLabel());
    T->ptr[0]->offset = T->ptr[1]->offset = T->ptr[2]->offset = T->offset;
    boolExp(T->ptr[0]); //条件，要单独按短路代码处理
    T->width = T->ptr[0]->width;
    strcpy(T->ptr[1]->Snext, T->Snext);
    semantic_Analysis(T->ptr[1]); //if子句
    if (T->width < T->ptr[1]->width)
        T->width = T->ptr[1]->width;
    strcpy(T->ptr[2]->Snext, T->Snext);
    semantic_Analysis(T->ptr[2]); //else子句
    if (T->width < T->ptr[2]->width)
        T->width = T->ptr[2]->width;
    T->code = merge(6, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code,genGoto(T->Snext), genLabel(T->ptr[0]->Efalse), T->ptr[2]->code);
}

//while循环语句处理函数
void while_dec(struct node *T)
{
    strcpy(T->ptr[0]->Etrue, newLabel()); //子结点继承属性的计算
    strcpy(T->ptr[0]->Efalse, T->Snext);
    T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
    boolExp(T->ptr[0]); //循环条件，要单独按短路代码处理
    T->width = T->ptr[0]->width;
    strcpy(T->ptr[1]->Snext, newLabel());
	T->isWhile = T->ptr[1]->isWhile = 1;
	strcpy(T->ptr[1]->Ebreak, T->Snext);
	strcpy(T->ptr[1]->Econtinue, T->ptr[1]->Snext);
    semantic_Analysis(T->ptr[1]); //循环体语句处理
    if (T->width < T->ptr[1]->width)
        T->width = T->ptr[1]->width;
    T->code = merge(5, genLabel(T->ptr[1]->Snext), T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code, genGoto(T->ptr[1]->Snext));
}

//for循环语句处理函数
void for_dec(struct node *T)
{
	T->isWhile = T->ptr[1]->isWhile = 1;//标记为循环体节点，判断break和continue语句是否在循环体内使用
    strcpy(T->ptr[0]->ptr[1]->Etrue, newLabel()); //条件为真时，产生一个新label作为跳转标号
    strcpy(T->ptr[0]->ptr[1]->Efalse, T->Snext); //条件为假时，跳转语句为循环体的下个语句
    Exp(T->ptr[0]->ptr[0]);//处理for循环初始值
    boolExp(T->ptr[0]->ptr[1]);//处理for循环条件
    strcpy(T->ptr[0]->ptr[1]->Snext, newLabel());//为循环条件产生标签
    Exp(T->ptr[0]->ptr[2]);//处理for循环尾部
    T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
    T->width = T->ptr[0]->width;
    strcpy(T->ptr[1]->Snext, newLabel());//为循环体的下个语句产生比新label
	strcpy(T->ptr[1]->Ebreak, T->Snext);//break语句跳转标号为循环体的下个语句
	strcpy(T->ptr[1]->Econtinue, newLabel());//为continue语句的跳转语句产生新label，即循环体的尾部语句
    semantic_Analysis(T->ptr[1]); //循环体语句处理
    if (T->width < T->ptr[1]->width)
        T->width = T->ptr[1]->width;
    //Exp(T->ptr[0]->ptr[2]);//处理for循环后续语句
    T->code = merge(8, T->ptr[0]->ptr[0]->code, genLabel(T->ptr[1]->Snext), T->ptr[0]->ptr[1]->code, genLabel(T->ptr[0]->ptr[1]->Etrue), T->ptr[1]->code, genLabel(T->ptr[1]->Econtinue), T->ptr[0]->ptr[2]->code, genGoto(T->ptr[1]->Snext));
}

//对抽象语法树的先根遍历,按display的控制结构修改完成符号表管理和语义检查
void semantic_Analysis(struct node *T)
{
    int index, num, width;
    struct node *T0;
    struct opn opn1, opn2, result;
    if (T)
    {
        //处理循环语句的break、continue分支标号
        if(T->isWhile==1)
        {
            if(T->ptr[0])
            {
                T->ptr[0]->isWhile=1;
                strcpy(T->ptr[0]->Ebreak,T->Ebreak);
                strcpy(T->ptr[0]->Econtinue,T->Econtinue);
            }
            if(T->ptr[1])
            {
                T->ptr[1]->isWhile=1;
                strcpy(T->ptr[1]->Ebreak,T->Ebreak);
                strcpy(T->ptr[1]->Econtinue,T->Econtinue);
            }
            if(T->ptr[2])
            {
                T->ptr[2]->isWhile=1;
                strcpy(T->ptr[2]->Ebreak,T->Ebreak);
                strcpy(T->ptr[2]->Econtinue,T->Econtinue);
            }
        }
        switch (T->kind)
        {
        case EXT_DEF_LIST:
            ext_def_list(T);
            break;
        case EXT_VAR_DEF:
            ext_var_def(T);
            break;
		case EXT_DEC_LIST:
			ext_dec_list(T);
			break;
		case EXT_VAR_DEF_ASSIGN:
			ext_var_def_assign(T);
			break;
        case FUNC_DEF:
            func_def(T);
            break;
        case FUNC_DEC:
            func_dec(T);
            break;
        case PARAM_LIST:
            param_list(T);
            break;
        case PARAM_DEC:
            param_dec(T);
            break;
        case COMP_STM:
            comp_stm(T);
            break;
        case DEF_LIST:
            def_list(T);
            break;
        case VAR_DEF: //处理一个局部变量定义,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
                      //类似于上面的外部变量EXT_VAR_DEF，换了一种处理方法
            var_def(T);
            break;
        case STM_LIST:
            stm_list(T);
            break;
        case EXP_STMT:
            exp_stmt(T);
            break;
        case RETURN:
            return_dec(T);
            break;
        case IF_THEN:
            if_then(T);
            break; //控制语句都还没有处理offset和width属性
        case IF_THEN_ELSE:
            if_then_else(T);
            break;
        case WHILE:
            while_dec(T);
            break;
        case FOR:
			for_dec(T);
            break;
		//基本类型表达式
        case ID:
        case INT:
        case FLOAT:
        case DOUBLE:
        case CHAR:
        case STRING:
		//运算表达式
        case ASSIGNOP:
        case PLUS:
        case PRE_PLUS_SELF:
        case NEXT_PLUS_SELF:
        case ASSIGNOP_PLUS:
        case MINUS:
        case PRE_MINUS_SELF:
        case NEXT_MINUS_SELF:
        case ASSIGNOP_MINUS:
        case STAR:
        case ASSIGNOP_STAR:
        case DIV:
        case ASSIGNOP_DIV:
        case UMINUS:
		//函数调用、数组访问
        case FUNC_CALL:
        case EXP_ARRAY:
		//逻辑表达式
        case AND:
        case OR:
        case NOT:
        case RELOP:
		//这两条语句的处理过程在函数Exp中
		case BREAK:
		case CONTINUE:
            Exp(T); //处理基本表达式
            break;
        }
    }
}

void semantic_Analysis0(struct node *T)
{
    symbolTable.index = 0;
    symbol_scope_TX.TX[0] = 0; //外部变量在符号表中的起始序号为0
    symbol_scope_TX.top = 1;
    T->offset = 0; // 外部变量在数据区的偏移量
    semantic_Analysis(T);//进行语义分析
    if (error_index)
    {
        int i;
        printf("\n静态语义错误信息：\n");
        for(i = 0; i < error_index; i++)
        {
            printf("%s",error_msg[i]);//显示错误信息
        }
    }
    else//没有静态语言错误则生成目标代码
    {
        int i;
        //prnIR(T->code,T->code);
        objectCode(T->code,T->code);
        // fill_block_list(T->code);
        // for (i = 0; i < block_list_index; i++)
        // {
        //     if (BLOCK_LIST[i].valid)
        //         objectCode(BLOCK_LIST[i].BLOCK->begin,BLOCK_LIST[i].BLOCK->end->next);
        // }
        
    }
}
