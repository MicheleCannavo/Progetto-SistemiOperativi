//==============================================================================
/// \author  Cannavo' Michele [046002210]
/// \date    07/12/2018
//==============================================================================
/// \file  myMain.c
/// \brief Motore di ricerca ricorsiva di FILDERX
/// \version 1.2
/// \copyright GNU LGPL 3.0
/// \details Motore che ricerca, con le impostazioni date, File e cartelle dentro una directory.
#include "Client.h"

/// VARIABILI GLOBALI PER TUTTI I FILE
SettCLIENT  *settaggi = NULL;
int sockid_Client=-1;

int myMainC(int argc, char* argv[])
{
// Al massimo 2 argomenti più argv[0]
    if (argc<1 || argc>2 )
    {
        errno=EINVAL;
        perror("Errore in MyMain()");
        return(-1);
    }

// Disattivo il buffer di stdout perchè da fastidio
  if(setvbuf(stdout,NULL,_IONBF,0)!=0)
    { 
        perror("Errore in setvbuf()"); 
        return -1;
    }

// Inizializza la struttura dei settaggi con valori di default
    if( iniSett() != 0 )
    {
        perror("Errore in iniFILDERX()");
        free(settaggi);
        settaggi=NULL;
        return -1;
    }

// Riempie la struttura dei settaggi con valori da linea di comadno
   if(argSett( argc, argv)==-1)
    {
       perror("Errore in argSet()");
        free(settaggi);
        settaggi=NULL;
       return -1;
    }

    if(menCli()==-1)
    {
        free(settaggi);
        settaggi=NULL;
        return-1;
    }
    
    free(settaggi);
    settaggi=NULL;
    return 0;
}
