/*
//==============================================================================
 *  \author  Cannavo' Michele [046002210]
 *  \date    07/12/2018
//==============================================================================
 *  \file  main_Server.c
 *  \brief Motore di ricerca ricorsiva di FILDERX
 *  \version 1.2
 *  \copyright GNU LGPL 3.0
 *  \details Motore che ricerca, con le impostazioni date, File e cartelle dentro una directory.
*/
#include "Server.h"
#include "FILDERX.h"
int saveid;

SettSERVER  *settaggi = NULL;

int myMainS(int argc, char* argv[])
{
    if (argc<1 || argc>2 )
    {
        errno=EINVAL;
        perror(__FUNCTION__); 
        return -1;
    } 


// Inizializza la struttura dei settaggi con valori di default
    if( iniSett() != 0 )
    {
        perror(__FUNCTION__); 
        return -1;
    }

// Riempie la struttura dei settaggi con valori da linea di comadno
   if(argSett( argc, argv)==-1)
    {
        perror(__FUNCTION__); 
        free(settaggi);
        settaggi=NULL;
       return -1;
    }
    MotoreFILDER();

    if(menServ()==-1)
    {
        free(settaggi);
     //   free(headTList);
     //   headTList=NULL;
        settaggi=NULL;
        return-1;
    }

   // freeL(&headTList);
  //  headTList=NULL;
    free(settaggi);
    settaggi=NULL;
    close(saveid);
    return 0;
}