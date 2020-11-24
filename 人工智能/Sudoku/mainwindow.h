#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int board[9][9];
    int seedBoard[9][9] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {4, 5, 6, 7, 8, 9, 1, 2, 3},
        {7, 8, 9, 1, 2, 3, 4, 5, 6},
        {8, 9, 1, 2, 3, 4, 5, 6, 7},
        {2, 3, 4, 5, 6, 7, 8, 9, 1},
        {5, 6, 7, 8, 9, 1, 2, 3, 4},
        {6, 7, 8, 9, 1, 2, 3, 4, 5},
        {9, 1, 2, 3, 4, 5, 6, 7, 8},
        {3, 4, 5, 6, 7, 8, 9, 1, 2} };
    QTextEdit* textEdit[9][9];
    double beginTime;
    double endTime;
    bool initBlock[9][9];

    void RowTemp(int (*a)[9],int row1,int row2);
    void ColumnTemp(int (*a)[9],int column1,int column2);
    void Digout(int (*a)[9]);
    void ShowMap();
    bool isNumeric(QString str);
    bool CheckMap(int a[9][9],int row,int column);

    bool TransSudokuToCNF();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
};

#endif // MAINWINDOW_H
