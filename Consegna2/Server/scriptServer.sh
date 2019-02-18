#! /bin/bash


clear
echo -e "                    Menu' Script Server"
echo -e "  ================================================"
echo -e "      1) Compila"
echo -e "      2) Genera file object"
echo -e "      3) Esegui"
echo -e "      4) Compila ed Esegui"
echo -e "      5) Verifica con cppcheck"
echo -e "      6) Esci"
echo -e -n "\n--------------------------------------------------\nScegli opzione:"
read choose1
ServerList=$(ls ./src/*.c)
case $choose1 in
"1")
	gcc -Wall -o ./bin/server ./$ServerList -lpthread
	;;
"2")
	gcc -Wall -c ./$ServerList -lpthread
	mv $(ls *.o) ./obj
	;;
"3")
	./bin/server
	;;
"4")
	gcc -Wall -o ./bin/server ./$ServerList -lpthread
	./bin/server
	;;
"5")
	cppcheck --enable=all --inconclusive ./ 2>./cppcheck.txt
	chmod 777 ./cppcheck.txt
	gedit ./cppcheck.txt
	;;
esac