#! /bin/bash


clear
echo -e "                  Menu' Script CONSEGNA1"
echo -e "  ================================================"
echo -e "      1) Compila"
echo -e "      2) Genera file object"
echo -e "      3) Esegui"
echo -e "      4) Compila ed Esegui"
echo -e "      5) Verifica con cppcheck"
echo -e "      6) Esci"
echo -e -n "\n------------------------------------------------\nScegli opzione:"
read choose1
SourceList=$(ls ./src/*.c)
case $choose1 in
"1")
	gcc -Wall ./$SourceList -lpthread -o ./bin/cons1
	chmod 777 ./bin/cons1
	;;
"2")
	gcc -Wall -c ./$SourceList -lpthread
	mv $(ls *.o) ./obj
	;;
"3")
	./bin/cons1 $1
	;;
"4")
	gcc -Wall -o ./bin/cons1 ./$SourceList -lpthread
	./bin/cons1 $1
	;;
"5")
	cppcheck --enable=all --inconclusive ./ 2>./cppcheck.txt
	chmod 777 ./cppcheck.txt
	gedit ./cppcheck.txt
	;;
"5")
	exit 0
	;;
esac