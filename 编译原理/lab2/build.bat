flex lex.l
bison -d parser.y
gcc -o parser ast.c parser.tab.c lex.yy.c semantic.c -fexec-charset=GBK
parser test2.c > output1.txt
parser testsematics.c > output2.txt
