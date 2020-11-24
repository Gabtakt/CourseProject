#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <QString>
#include <QMessageBox>

#include "cnfsolver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("数独游戏");
    //棋盘组件容器初始化
    this->textEdit[0][0] = ui->rank11;
    this->textEdit[0][1] = ui->rank12;
    this->textEdit[0][2] = ui->rank13;
    this->textEdit[0][3] = ui->rank14;
    this->textEdit[0][4] = ui->rank15;
    this->textEdit[0][5] = ui->rank16;
    this->textEdit[0][6] = ui->rank17;
    this->textEdit[0][7] = ui->rank18;
    this->textEdit[0][8] = ui->rank19;

    this->textEdit[1][0] = ui->rank21;
    this->textEdit[1][1] = ui->rank22;
    this->textEdit[1][2] = ui->rank23;
    this->textEdit[1][3] = ui->rank24;
    this->textEdit[1][4] = ui->rank25;
    this->textEdit[1][5] = ui->rank26;
    this->textEdit[1][6] = ui->rank27;
    this->textEdit[1][7] = ui->rank28;
    this->textEdit[1][8] = ui->rank29;

    this->textEdit[2][0] = ui->rank31;
    this->textEdit[2][1] = ui->rank32;
    this->textEdit[2][2] = ui->rank33;
    this->textEdit[2][3] = ui->rank34;
    this->textEdit[2][4] = ui->rank35;
    this->textEdit[2][5] = ui->rank36;
    this->textEdit[2][6] = ui->rank37;
    this->textEdit[2][7] = ui->rank38;
    this->textEdit[2][8] = ui->rank39;

    this->textEdit[3][0] = ui->rank41;
    this->textEdit[3][1] = ui->rank42;
    this->textEdit[3][2] = ui->rank43;
    this->textEdit[3][3] = ui->rank44;
    this->textEdit[3][4] = ui->rank45;
    this->textEdit[3][5] = ui->rank46;
    this->textEdit[3][6] = ui->rank47;
    this->textEdit[3][7] = ui->rank48;
    this->textEdit[3][8] = ui->rank49;

    this->textEdit[4][0] = ui->rank51;
    this->textEdit[4][1] = ui->rank52;
    this->textEdit[4][2] = ui->rank53;
    this->textEdit[4][3] = ui->rank54;
    this->textEdit[4][4] = ui->rank55;
    this->textEdit[4][5] = ui->rank56;
    this->textEdit[4][6] = ui->rank57;
    this->textEdit[4][7] = ui->rank58;
    this->textEdit[4][8] = ui->rank59;

    this->textEdit[5][0] = ui->rank61;
    this->textEdit[5][1] = ui->rank62;
    this->textEdit[5][2] = ui->rank63;
    this->textEdit[5][3] = ui->rank64;
    this->textEdit[5][4] = ui->rank65;
    this->textEdit[5][5] = ui->rank66;
    this->textEdit[5][6] = ui->rank67;
    this->textEdit[5][7] = ui->rank68;
    this->textEdit[5][8] = ui->rank69;

    this->textEdit[6][0] = ui->rank71;
    this->textEdit[6][1] = ui->rank72;
    this->textEdit[6][2] = ui->rank73;
    this->textEdit[6][3] = ui->rank74;
    this->textEdit[6][4] = ui->rank75;
    this->textEdit[6][5] = ui->rank76;
    this->textEdit[6][6] = ui->rank77;
    this->textEdit[6][7] = ui->rank78;
    this->textEdit[6][8] = ui->rank79;

    this->textEdit[7][0] = ui->rank81;
    this->textEdit[7][1] = ui->rank82;
    this->textEdit[7][2] = ui->rank83;
    this->textEdit[7][3] = ui->rank84;
    this->textEdit[7][4] = ui->rank85;
    this->textEdit[7][5] = ui->rank86;
    this->textEdit[7][6] = ui->rank87;
    this->textEdit[7][7] = ui->rank88;
    this->textEdit[7][8] = ui->rank89;

    this->textEdit[8][0] = ui->rank91;
    this->textEdit[8][1] = ui->rank92;
    this->textEdit[8][2] = ui->rank93;
    this->textEdit[8][3] = ui->rank94;
    this->textEdit[8][4] = ui->rank95;
    this->textEdit[8][5] = ui->rank96;
    this->textEdit[8][6] = ui->rank97;
    this->textEdit[8][7] = ui->rank98;
    this->textEdit[8][8] = ui->rank99;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//对棋盘进行行交换
void MainWindow::RowTemp(int (*a)[9],int row1,int row2)
{
    int j,temp;
    for(j=0;j<9;j++)
    {
        temp=a[row1][j];
        a[row1][j]=a[row2][j];
        a[row2][j]=temp;
    }
}

//对棋盘进行列交换
void MainWindow::ColumnTemp(int (*a)[9],int column1,int column2)
{
    int i,temp;
    for(i=0;i<9;i++)
    {
        temp=a[i][column1];
        a[i][column1]=a[i][column2];
        a[i][column2]=temp;
    }
}

//对终盘进行挖洞，产生初始棋盘
void MainWindow::Digout(int (*a)[9])
{
    int flag,num,x,i,j;
    //获取难度选择
    flag = ui->radioButton_1->isChecked()?1:ui->radioButton_2->isChecked()?2:3;
    srand((unsigned int)time((time_t *)NULL));
    switch(flag)
    {
        case 1:
            num=rand()%10+30;
            break;
        case 2:
            num=rand()%10+40;
            break;
        case 3:
            num=rand()%15+50;
            break;
    }
    //挖洞
    while(num)
    {
        x=rand()%89+11;
        i=x/10-1;
        j=x%10-1;
        if(a[i][j])
        {
            a[i][j]=0;
            this->initBlock[i][j] = false;
            num--;
        }
    }
}

//在棋盘组件中显示初始化棋盘
void MainWindow::ShowMap()
{
    int i,j;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        {
            if(this->board[i][j] != 0)
            {
                this->textEdit[i][j]->setText(QString::number(this->board[i][j],10));
                this->textEdit[i][j]->setReadOnly(true);
            }
            else
            {
                this->textEdit[i][j]->setStyleSheet("QTextEdit{color:blue}");
            }
        }
}

//生成棋盘按钮事件，产生一个初始化棋盘
void MainWindow::on_pushButton_1_clicked()
{
    int i,j,num_1,num_2;
    //清空棋盘
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        {
            this->textEdit[i][j]->clear();
            this->textEdit[i][j]->setReadOnly(false);
            this->initBlock[i][j] = true;
            this->textEdit[i][j]->setStyleSheet("QTextEdit{color:black}");
        }
    //产生种子棋盘
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            this->board[i][j] = this->seedBoard[i][j];
    //对种子棋盘行列变换
    srand((unsigned int)time((time_t *)NULL));//根据系统时间获取种子
    do
    {
        num_1=rand()%3;
        num_2=rand()%3;
    }
    while(num_1==num_2);
    RowTemp(this->board,num_1,num_2);
    do
    {
        num_1=rand()%3+3;
        num_2=rand()%3+3;
    }
    while(num_1==num_2);
    RowTemp(this->board,num_1,num_2);
    do
    {
        num_1=rand()%3+6;
        num_2=rand()%3+6;
    }
    while(num_1==num_2);
    RowTemp(this->board,num_1,num_2);
    do
    {
        num_1=rand()%3;
        num_2=rand()%3;
    }
    while(num_1==num_2);
    ColumnTemp(this->board,num_1,num_2);
    do
    {
        num_1=rand()%3+3;
        num_2=rand()%3+3;
    }
    while(num_1==num_2);
    ColumnTemp(this->board,num_1,num_2);
    do
    {
        num_1=rand()%3+6;
        num_2=rand()%3+6;
    }
    while(num_1==num_2);
    ColumnTemp(this->board,num_1,num_2);
    Digout(this->board);//对数独终盘进行挖洞
    ShowMap();
    this->beginTime = clock() / CLOCKS_PER_SEC;
}

//判断SQtring字符串是否是数字
bool MainWindow::isNumeric(QString str)
{
    for(int i = 0; i < str.length(); i++)
    {
        if(str.at(i) < '0' || str.at(i) > '9')
            return false;
    }
    return true;
}

//棋盘冲突检测
bool MainWindow::CheckMap(int a[9][9],int row,int column)
{
    int i,j,m,n;
    for(j=0;j<9;j++)//搜索行
    {
        if(j==column-1)//跳过当前格
            continue;
        else if(a[row-1][j]==a[row-1][column-1])
            return false;
    }
    for(i=0;i<9;i++)//搜索列
    {
        if(i==row-1)//跳过当前格
            continue;
        else if(a[i][column-1]==a[row-1][column-1])
            return false;
    }
    if(row<4)//1-3号宫
        m=0;
    else if(row<7)//4-6号宫
        m=1;
    else//7-9号宫
        m=2;
    if(column<4)//1
        n=0;
    else if(column<7)//2
        n=1;
    else//3
        n=2;
    for(i=3*m;i<3*m+3;i++)//处理所在宫
        for(j=3*n;j<3*n+3;j++)
        {
            if(i==row-1&&j==column-1)
                continue;
            if(a[i][j]==a[row-1][column-1])
                return false;
        }
    return true;
}

//确认按钮事件，监测棋盘冲突，若有冲突则提示用户，并将输入字体置为红色
void MainWindow::on_pushButton_2_clicked()
{
    int i,j;
    bool full =true;
    bool conflict = false;
    //将空的棋盘格子置为0
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        {
            if(this->textEdit[i][j]->toPlainText().length() == 0)
            {
                this->board[i][j] = 0;
                full = false;
            }
        }
    //判断输入是否合法
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        {
            //若是初始生成的棋盘格，则跳过
            if(this->initBlock[i][j])
            {
                continue;
            }
            //判断输入是否是单个0~9的数字
            if(this->textEdit[i][j]->toPlainText().length() > 1 || !isNumeric(this->textEdit[i][j]->toPlainText()))
            {
                QMessageBox::about(NULL, "提示", "请输入0~9间的数字");
                this->textEdit[i][j]->clear();
                this->board[i][j]=0;
            }
            //输入了数字，进行冲突检测
            else if(this->textEdit[i][j]->toPlainText().length() != 0)
            {
                bool ok;
                this->board[i][j] = this->textEdit[i][j]->toPlainText().toInt(&ok,10);
                //有冲突，提示用户
                if(!CheckMap(this->board,i+1, j+1))
                {
                    QMessageBox::about(NULL,"提示",QString("在%1行%2列出现冲突").arg(i+1,1,10,QLatin1Char('0')).arg(j+1,1,10,QLatin1Char('0')));
                    this->textEdit[i][j]->setStyleSheet("QTextEdit{color:red}");
                    conflict = true;
                }
                else
                {
                    bool ok;
                    this->board[i][j] = this->textEdit[i][j]->toPlainText().toInt(&ok,10);
                    this->textEdit[i][j]->setStyleSheet("QTextEdit{color:blue}");
                }
            }
        }
    //棋盘格子填满且未发生冲突，成功解出数独
    if(full && !conflict)
    {
        this->endTime = clock() / CLOCKS_PER_SEC;
        int totalTime = (int)(endTime - beginTime);
        QMessageBox::about(NULL,"提示",QString("恭喜你完成数独！用时%1秒").arg(totalTime,4,10,QLatin1Char(' ')));
    }
}

//将数独棋盘转换为CNF
bool MainWindow::TransSudokuToCNF()
{
    FILE *fp=NULL;
    int x,y,z,i,j,k,l,num=0;
    if((fp=fopen("sudoku.cnf","w"))==NULL)//打开失败
       return false;
    for(x=0;x<9;x++)//读取已填数目
        for(y=0;y<9;y++)
            if(this->board[x][y]!=0)
                num++;
    num+=8829;
    fprintf(fp,"p cnf %d %d\n",729,num);//变元范围1-729，子句数为81+8748+已填数目
    for(i=0;i<9;i++)//已填入的数视为单子句处理
        for(j=0;j<9;j++)
            if(this->board[i][j]!=0)
                fprintf(fp,"%d 0\n",81*i+9*j+this->board[i][j]);
    for(x=0;x<9;x++)//每空至少填一个数，为含9个文字的子句
        for(y=0;y<9;y++)
        {
            for(z=1;z<10;z++)
                fprintf(fp,"%d ",81*x+9*y+z);
            fprintf(fp,"0\n");
        }
    for(y=0;y<9;y++)//每行每个数最多出现一次
        for(z=1;z<=9;z++)
            for(x=0;x<8;x++)
                for(i=x+1;i<9;i++)
                    fprintf(fp,"%d %d 0\n",-(81*x+9*y+z),-(81*i+9*y+z));
    for(x=0;x<9;x++)//每列每个数最多出现一次
        for(z=1;z<=9;z++)
            for(y=0;y<8;y++)
                for(i=y+1;i<9;i++)
                    fprintf(fp,"%d %d 0\n",-(81*x+9*y+z),-(81*x+9*i+z));
    for(z=1;z<=9;z++)//每个3*3方格里每个数最多出现一次
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                for(x=0;x<3;x++)
                    for(y=0;y<3;y++)
                        for(k=y+1;k<3;k++)
                            fprintf(fp,"%d %d 0\n",-(81*(3*i+x)+9*(3*j+y)+z),-(81*(3*i+x)+9*(3*j+k)+z));
    for(z=1;z<=9;z++)//每个3*3方格里每个数最多出现一次
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                for(x=0;x<3;x++)
                    for(y=0;y<3;y++)
                        for(k=x+1;k<3;k++)
                            for(l=0;l<3;l++)
                                fprintf(fp,"%d %d 0\n",-(81*(3*i+x)+9*(3*j+y)+z),-(81*(3*i+k)+9*(3*j+l)+z));
    fclose(fp);
    return true;
}

//求解按钮事件，将数独棋盘翻译成CNF，然后对CNF求解，最后将结果呈现到棋盘上
void MainWindow::on_pushButton_4_clicked()
{
    formula p;//CNF公式
    variableflag *index=NULL;
    if(!TransSudokuToCNF())
    {
        QMessageBox::about(NULL,"提示","转换sudoku.cnf失败！");
        return;
    }
    if(LoadingCNF(&p,&index) != OK)
    {
        QMessageBox::about(NULL,"提示","sudoku.cnf加载失败！");
        return;
    }
    DPLL(&p,index);
    free(p.cla);
    free(index);
    FILE *fp = NULL;
    if((fp = fopen("sudoku.out","r")) == NULL)
    {
        QMessageBox::about(NULL,"提示","suduku.out加载失败！");
        return;
    }
    int result[81];
    //读取解析结果到一维向量
    int j = 0;
    for(int i = 0; i < 729; i++)
    {
        fscanf(fp,"%d",&result[j]);
        if(result[j] >0)
            j++;
    }
    j = 0;
    fclose(fp);
    //将cnf求解器得到的结果显示到棋盘上
    for(int i = 0; i < 9; i++)
        for(int k = 0; k < 9 ;k++)
        {
            this->board[i][k] = ((result[j] - 1) % 9) + 1;
            this->textEdit[i][k]->setText(QString::number(this->board[i][k],10));
            j++;
        }
}
