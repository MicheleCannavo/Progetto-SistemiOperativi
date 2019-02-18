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
SettSERVER  *settaggi = NULL;
void svuota(void)
{
    closefd(&server_sockfd);
    printf("\x1B[1;1H\x1B[2J");
}

void timeout(int sig)
{
    signal(SIGALRM, SIG_IGN);
    errno=ETIMEDOUT;
    closefd(&server_sockfd);
    signal(SIGALRM,timeout);
}

int myMainS(int argc, char* argv[])
{   
    atexit(svuota);
    signal(SIGALRM,timeout);

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
    printf("Caricamento Lista...Attendere\n");
    MotoreFILDER();

    if(menServ()==-1)
    {
        free(settaggi);
        settaggi=NULL;
        return-1;
    }

    free(settaggi);
    settaggi=NULL;
    return 0;
}