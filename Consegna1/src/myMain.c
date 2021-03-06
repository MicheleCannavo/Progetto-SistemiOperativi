//==============================================================================
/// \author  Cannavo' Michele [046002210]
/// \date    07/12/2018
//==============================================================================
/// \file  myMain.c
/// \brief Motore di ricerca ricorsiva di FILDERX
/// \version 1.2
/// \copyright GNU LGPL 3.0
/// \details Motore che ricerca, con le impostazioni date, File e cartelle dentro una directory.
#include "FILDERX.h"

/// VARIABILI GLOBALI PER TUTTI I FILE
unsigned long int      count = 1;
listFILDERX       *headTList = NULL;
SettFILDERX        *settaggi = NULL;

int myMain(int argc, char* argv[])
{
// Al massimo 2 argomenti più argv[0]
    if (argc<2 || argc>3 )
    {
        errno=EINVAL;
        perror("Errore in MyMain()");
        return(-1);
    }

// Inizializza la struttura dei settaggi con valori di default
    if( iniSett() ==-1)
    {
        perror("Errore in iniSett()");
        free(settaggi);
        settaggi=NULL;
        return -1;
    }

// Riempie la struttura dei settaggi con valori da linea di comadno
   if(argSett( argc, argv)==-1)
    {
        perror("Errore in argSett()");
        free(settaggi);
        settaggi=NULL;
        return -1;
    }

// Apre il menu del programma
    if(menuF() == -1)
    {
        perror("Errore in MenuF");
        free(settaggi);
        settaggi=NULL;
        return-1;
    }

// Dealloca la memoria ed esce dal programma senza errori
    freeL(&headTList);
    headTList=NULL;
    free(settaggi);
    settaggi=NULL;
    return 0;
}
