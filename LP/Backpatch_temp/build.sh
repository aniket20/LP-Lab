yacc -d -v backpatch.y
lex backpatch.l
g++ y.tab.c node.cpp lex.yy.c -o run -ll
./run
