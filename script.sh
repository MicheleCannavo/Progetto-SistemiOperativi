#! /bin/bash

clear
s1="S"
echo "Vuoi attivare il debug?[S/n]"
read choose
FileSorgenti=`ls ./Sorgenti/*.c`
echo -e " File da compilare $FileSorgenti\n\n"
if [[  "S" = $choose ]]; then
    echo -e "      ***** Debug Attivo *****\n\n"
    cc -D DEBUG_ -o ./bin/Debugging $FileSorgenti
    ./bin/Debugging $1
else    
    echo -e "\n"
    cc -o ./bin/Consegna1 $FileSorgenti
    ./bin/Consegna1 $1
fi