flex lex.l
bison -d parser.y
gcc -o parser ast.c parser.tab.c lex.yy.c -fexec-charset=GBK
parser ConsoleApplication2.cpp >output.txt
Start output.txt
