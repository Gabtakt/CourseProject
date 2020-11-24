flex lex.l
bison -d parser.y
gcc -o parser ast.c parser.tab.c lex.yy.c semantic.c -fexec-charset=GBK
parser testsematics3.c > output.txt