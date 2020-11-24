#ifndef CNFSOLVER_H
#define CNFSOLVER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define UNCERTAIN -1
#define MY_OVERFLOW -2
typedef int status;//函数返回值类型定义
typedef int variable;//变元类型定义
typedef struct cell//单元格类型定义
{
    int row;//行
    int column;//列
    int number;//数
}cell;
typedef struct check//决策变量查询表定义
{
    variable *base;//决策变量
    int num;//决策变量数
}check;
typedef struct variableflag//变量标记定义
{
    variable x;//变元
    int assinnum;//赋值次数
    int v_flag;//赋值标记
    int weight;//权值
}variableflag;
typedef struct literal//文字类型定义
{
    variable x;//变元
    int flag;//标记赋值
    struct literal *next;//指向下一文字结点
}literal;
typedef struct clause//子句类型定义
{
    literal *liter;//文字指针
    int flag;//标记赋值
    int liternum;//文字数
}clause;
typedef struct formula//公式类型定义
{
    clause *cla;//子句结点指针
    int clausenum;//子句数
    int variablenum;//变元数
}formula;

status IsEmptyFormula(formula *p)
{
    int i;
    for(i=0;i<p->clausenum;i++)
        if(p->cla[i].flag==0)//有未满足子句
            return FALSE;
    return TRUE;
}
status IsUnitaryClause(formula *p,int *loc)
{
    int i;
    literal *q;
    for(i=0;i<p->clausenum;i++)
    {
        if(p->cla[i].flag==1)//子句已满足
            continue;
        else if(p->cla[i].liternum==1)
        {
            q=p->cla[i].liter;
            while(q)//查找单子句文字
            {
                if(q->flag==0)
                {
                    *loc=q->x;
                    return TRUE;
                }
                q=q->next;//向下搜索
            }
        }
    }
    return FALSE;
}
status IsEmptyClause(formula *p)
{
    int i;
    for(i=0;i<p->clausenum;i++)
    {
        if(p->cla[i].flag==1)//子句已满足
            continue;
        else if(p->cla[i].liternum==0)
            return TRUE;
    }
    return FALSE;
}
void Remove(formula *p,int loc)
{
    int i;
    literal *q;
    for(i=0;i<p->clausenum;i++)//搜索子句表
    {
        q=p->cla[i].liter;
        while(q!=NULL)//搜索当前子句的文字链表
        {
            if(q->x==-loc)//标记负文字
            {
                q->flag=-1;//标记负文字
                p->cla[i].liternum--;//文字数减1
                break;//搜索下一子句
            }
            else if(q->x==loc)//含有单子句文字，将该子句标记为真
            {
                p->cla[i].flag=1;//标记子句
                q->flag=1;//标记文字
                p->cla[i].liternum--;//文字数减1
                break;//搜索下一子句
            }
            q=q->next;//向下搜索
        }
    }
}
status DeleteAssign(formula *p,variableflag *index,int *stack,int *top,check *basep)
{
    literal *r;
    int i,j,num,flag=0;
    variable loc,basevar;//决策变量
    j=p->variablenum;
    num=basep->num;//栈顶指针
    while(num)//复原至最近可改变决策变量
    {
        basevar=basep->base[num-1];//正文字
        num--;
        if(basevar>0)
        {
            if(index[basevar-1].assinnum==1)//可改变
            {
                flag=1;
                break;
            }
        }
        else
        {
            if(index[-basevar+j-1].assinnum==1)//可改变
            {
                flag=1;
                break;
            }
        }
    }
    basep->num=num;
    if(flag==0)//决策变量已空，命题不可满足
        return FALSE;
    if(basevar>0)//决策层变量索引表复原
    {
        index[basevar+j-1].v_flag=0;
        index[basevar-1].v_flag=0;
    }
    else
    {
        index[-basevar-1].v_flag=0;
        index[-basevar+j-1].v_flag=0;
    }
    loc=stack[--(*top)];//弹出栈顶文字
    while(loc!=basevar)//复原传递层
    {
        if(loc>0)//正文字索引表复原
        {
            index[loc-1].assinnum=0;
            index[loc-1].v_flag=0;
            index[loc+j-1].assinnum=0;
            index[loc+j-1].v_flag=0;
        }
        else//负文字索引表复原
        {
            index[-loc-1].v_flag=0;
            index[-loc-1].assinnum=0;
            index[-loc+j-1].assinnum=0;
            index[-loc+j-1].v_flag=0;
        }
        for(i=0;i<p->clausenum;i++)//公式复原
        {
            r=p->cla[i].liter;
            while(r!=NULL)//搜索文字链表
            {
                if(r->x==loc||r->x==-loc)//文字复原
                {
                    r->flag=0;
                    p->cla[i].liternum++;
                    break;
                }
                r=r->next;//向下搜索
            }
            r=p->cla[i].liter;
            while(r!=NULL)//确定当前子句状态
            {
                if(r->flag==1)
                {
                    p->cla[i].flag=1;
                    break;
                }
                r=r->next;//向下搜索
            }
            if(r==NULL)//子句状态未确定
                p->cla[i].flag=0;
        }
        loc=stack[--(*top)];
    }
    for(i=0;i<p->clausenum;i++)//确定决策层变量所在子句状态
    {
        r=p->cla[i].liter;
        while(r!=NULL)//搜索文字链表
        {
            if(r->x==loc||r->x==-loc)//文字复原
            {
                r->flag=0;
                p->cla[i].liternum++;
                break;
            }
            r=r->next;//向下搜索
        }
        r=p->cla[i].liter;
        while(r!=NULL)//确定当前子句状态
        {
            if(r->flag==1)
            {
                p->cla[i].flag=1;
                break;
            }
            r=r->next;//向下搜索
        }
        if(r==NULL)//子句状态未确定
            p->cla[i].flag=0;
    }
    return OK;
}
int LiteralDecide(formula *p,variableflag *index,variable *array)
{
    int i,j,k;
    variable var;
    j=p->variablenum;
    k=2*j;
    for(i=0;i<k;i++)
    {
        var=array[i];
        if(var>0)//正文字
        {
            if(index[var-1].assinnum==0&&index[var-1].v_flag==0&&index[-var+j-1].v_flag==0)//未被赋值且当前值未确定
            {
                index[var-1].v_flag=1;
                index[var+j-1].v_flag=-1;
                index[var+j-1].assinnum=1;
                index[var-1].assinnum=1;
                return var;//将该文字赋值为真
            }
            else if(index[var-1].assinnum==1&&index[var-1].v_flag==0&&index[-var+j-1].v_flag==0)//赋值一次且当前值未确定
            {
                index[var-1].v_flag=-1;
                index[var+j-1].v_flag=1;
                index[var-1].assinnum=2;
                index[var+j-1].assinnum=2;
                return -var;//将该文字赋值为假
            }
        }
        else//负文字
        {
            if(index[-var+j-1].assinnum==0&&index[-var+j-1].v_flag==0&&index[-var-1].v_flag==0)//未被赋值且当前值未确定
            {
                index[-var-1].v_flag=-1;
                index[-var-1].assinnum=1;
                index[-var+j-1].v_flag=1;
                index[-var+j-1].assinnum=1;
                return var;//将该文字赋值为假
            }
            else if(index[-var+j-1].assinnum==1&&index[-var+j-1].v_flag==0&&index[-var-1].v_flag==0)//赋值一次且当前值未确定
            {
                index[-var-1].v_flag=1;
                index[-var+j-1].v_flag=-1;
                index[-var-1].assinnum=2;
                index[-var+j-1].assinnum=2;
                return -var;//将该文字赋值为真
            }
        }
    }
    return 0;//未选取到文字
}
status OutputRes(variableflag *index,int n,status res)
{
    FILE *fp=NULL;
    int i;
    if ((fp=fopen("sudoku.out","w"))==NULL)
        return ERROR;
    if(res==TRUE)
    {
        for(i=0;i<n;i++)
            if(index[i].v_flag==1)
                fprintf(fp,"%d ",index[i].x);
            else if(index[i].v_flag==-1)
                fprintf(fp,"%d ",-index[i].x);
    }
    fclose(fp);
    return OK;
}
status BCP(formula *p,variableflag *index,int *stack,int *top)
{
    int loc;//记录单子句文字
    while(IsUnitaryClause(p,&loc))//有单子句时循环
    {
        stack[(*top)++]=loc;
        if(loc>0)
        {
            index[loc+p->variablenum-1].v_flag=-1;
            index[loc-1].v_flag=1;
        }
        else
        {
            index[-loc-1].v_flag=-1;
            index[-loc+p->variablenum-1].v_flag=1;
        }
        Remove(p,loc);
        if(IsEmptyFormula(p))//删除后公式为空，命题可满足
            return TRUE;
        else if(IsEmptyClause(p))//删除后公式含空子句，命题不可满足
            return FALSE;
    }
    return UNCERTAIN;//命题可满足性未确定
}
void VariableSort(variableflag index[],variable *array,int n)
{
    int i,j,flag=1;
    variable temp1;
    variableflag temp2;
    for(i=0;i<n;i++)
        array[i]=index[i].x;
    for(i=0;i<n-1&&flag;i++)
    {
        flag=0;
        for(j=0;j<n-i-1;j++)
            if(index[j].weight<index[j+1].weight)
            {
                temp2=index[j];
                index[j]=index[j+1];
                index[j+1]=temp2;
                temp1=array[j];
                array[j]=array[j+1];
                array[j+1]=temp1;
                flag=1;
            }
    }
}
status LoadingCNF(formula *p,variableflag **index)
{
    FILE *fp;
    int i,variable_num,clause_num,num;
    char ch;
    literal *q,*r;
    if((fp=fopen("sudoku.cnf","r"))==NULL)//打开失败
        return ERROR;
    fscanf(fp,"%c",&ch);
    while(ch=='c')//读去注释行
    {
        fscanf(fp,"%c",&ch);
        while(ch!='\n')
            fscanf(fp,"%c",&ch);
        fscanf(fp,"%c",&ch);
    }
    for(i=0;i<5;i++)//读去前序信息
        fscanf(fp,"%c",&ch);
    fscanf(fp,"%d",&variable_num);//读取变元范围
    fscanf(fp,"%d",&clause_num);//读取子句数
    p->variablenum=variable_num;
    p->cla=(clause*)malloc(clause_num*sizeof(clause));//子句顺序表申请
    if(!p->cla) exit(MY_OVERFLOW);
    (*index)=(variableflag*)malloc(variable_num*2*sizeof(variableflag));//索引表申请
    if(!(*index)) exit(MY_OVERFLOW);
    p->clausenum=clause_num;
    for(i=0;i<variable_num*2;i++)//索引表初始化
    {
        (*index)[i].weight=0;
        (*index)[i].assinnum=0;
        (*index)[i].v_flag=0;
    }
    for(i=0;i<clause_num;i++)//读取每条子句的文字
    {
        p->cla[i].liternum=0;
        p->cla[i].flag=0;
        fscanf(fp,"%d",&num);
        if(num>0)//正文字
        {
            (*index)[num-1].x=num;
            (*index)[num-1].weight++;
        }
        else//负文字
        {
            (*index)[-num+variable_num-1].x=num;
            (*index)[-num+variable_num-1].weight++;
        }
        q=(literal*)malloc(sizeof(literal));//首结点单独处理
        if(!q) exit(MY_OVERFLOW);
        q->x=num;
        q->next=NULL;
        q->flag=0;
        p->cla[i].liter=q;
        p->cla[i].liternum++;
        while(fscanf(fp,"%d",&num),num)//处理之后的结点
        {
            if(num>0)
            {
                (*index)[num-1].x=num;
                (*index)[num-1].weight++;
            }
            else
            {
                (*index)[-num+variable_num-1].x=num;
                (*index)[-num+variable_num-1].weight++;
            }
            r=(literal*)malloc(sizeof(literal));
            if(!r) exit(MY_OVERFLOW);
            r->x=num;
            r->next=NULL;
            r->flag=0;
            q->next=r;
            q=q->next;
            p->cla[i].liternum++;
        }
    }
    fclose(fp);
    return OK;
}
status DPLL(formula *p,variableflag *index)
{
    int i,v,top=0;
    status res=UNCERTAIN;//结果状态变量
    int *stack=NULL;//赋值变量存储栈
    variable *array=NULL;
    check bases;//决策变量查询表
    bases.base=(int*)malloc(p->variablenum*10000*sizeof(int));
    if(!bases.base) exit(MY_OVERFLOW);
    stack=(int*)malloc(p->variablenum*10000*sizeof(int));
    if(!stack) exit(MY_OVERFLOW);
    array=(variable*)malloc(p->variablenum*2*sizeof(variable));
    if(!array) exit(MY_OVERFLOW);
    bases.num=0;
    variableflag index_2[p->variablenum*2];
    for(i=0;i<p->variablenum*2;i++)
        index_2[i]=index[i];
    VariableSort(index_2,array,p->variablenum*2);
    while(res!=TRUE)
    {
        if(res==FALSE)
            if(DeleteAssign(p,index,stack,&top,&bases)==FALSE)//删除决策变量
                break;
        v=LiteralDecide(p,index,array);//获得决策变量
        if(v==0)
            break;
        stack[top++]=v;
        bases.base[bases.num]=v;
        bases.num++;
        Remove(p,v);
        res=BCP(p,index,stack,&top);
    }
    OutputRes(index,p->variablenum*2,res);
    free(stack);
    free(bases.base);
    free(array);
    if(res==TRUE)
        return TRUE;
    return FALSE;
}

#endif // CNFSOLVER_H
