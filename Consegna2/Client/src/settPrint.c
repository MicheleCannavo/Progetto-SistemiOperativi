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

// Stama i settaggi sul file col descrittore fdStream
void settPrint( int fdStream)
{
    dprintf(fdStream, "\x1B[1;1H\x1B[2J");
    dprintf(fdStream, "%s\n", "=============== Settaggi CLIENT ============== "); 

    if(strncmp(settaggi->IP_STRING,"127.0.0.1",16) == 0)
        dprintf(fdStream, "indirizzo IP del Server (\"localhost\")        = [%s]\n", settaggi->IP_STRING);
    else
        dprintf(fdStream, "indirizzo IP del Server (\"Server Remoto\")    = [%s]\n", settaggi->IP_STRING);
        
    dprintf(fdStream, "Porta in ascolto                             = [%u]\n", settaggi->nPort);    
    dprintf(fdStream, "Directory Salvataggio file                   = [%s]\n", settaggi->saveDir);
    dprintf(fdStream, "Buffer massimo invio                         = [%d]\n", settaggi->maxBuffer);
    dprintf(fdStream, "%s\n", "==================================================");
    return;
}
