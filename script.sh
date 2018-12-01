#! /bin/bash

clear
s1="S"
echo "Vuoi attivare il debug?[S/n]"
read choose
if [[  "S" = $choose ]]; then
    echo "Debug Attivo"
    cc -D DEBUG_ -o ./bin/Consegna1 ./Sorgenti/Consegna1.c ./Sorgenti/Func1.c
else    
    cc -o ./bin/Consegna1 ./Sorgenti/Consegna1.c ./Sorgenti/Func1.c
fi

./bin/Consegna1 $1
