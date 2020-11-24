flex lex.l
bison -d parser.y
gcc -o parser ast.c parser.tab.c lex.yy.c objectCode.c semantic.c -fexec-charset=GBK
parser testsematics4.c > object.asm
parser testfibonacci.c > fibonacci.asm