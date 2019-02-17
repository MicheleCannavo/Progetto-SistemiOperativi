//==============================================================================
/// \author     Cannavo' Michele [046002210]
/// \date       04/01/2019
//==============================================================================
/// \file       funcPrint.c
/// \brief      Funzioni per la stampa di informazioni di FILDERX
/// \version    1.1
/// \copyright  Licenza GPL 3.0
/// \details    File contenente l Header per le funzione di stampa di FILDERX
//==============================================================================
#include "Client.h"

// Stampa i settaggi 
void settPrint()
{
    printf( "\x1B[1;1H\x1B[2J");
    printf( "%s\n", "=============== Settaggi CLIENT ============== "); 

    if(strncmp(settaggi->IP_STRING,"127.0.0.1",16) == 0)
        printf( "indirizzo IP del Server (\"localhost\")        = [%s]\n", settaggi->IP_STRING);
    else
        printf( "indirizzo IP del Server (\"Server Remoto\")    = [%s]\n", settaggi->IP_STRING);
        
    printf( "Porta in ascolto                             = [%u]\n", settaggi->nPort);    
    printf( "Directory Salvataggio file                   = [%s]\n", settaggi->saveDir);
    printf( "Buffer massimo invio                         = [%d]\n", settaggi->maxBuffer);
    printf( "%s\n", "==================================================");
    return;
}
