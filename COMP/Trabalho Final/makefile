all:
	flex expr.l
	bison --verbose expr.y
	gcc expr.c expr.tab.c eda.c -Ofast -o "Compilador"

clean:
	rm -f expr.tab.c
	rm -f expr.output
	rm -f Compilador.o
