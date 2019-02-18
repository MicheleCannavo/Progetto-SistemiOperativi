 /** ***************************************************************************
 *  \file       settPrint.c
 *  \version    1.0
 * 
 *  \brief      Stampa la tabella dei settaggi
 *  
 *  \return Non ritorna valori 
 * 
 *  \details    Questa funzione stampa su un file aperto tramite 
 *              un file descriptor, una tabella contenete le attuali 
 *              impostazione del Server. La funzione e' utilizzabile sia per
 *              lo stream stdin sia per un normale file di testo.
 * 
 ******************************************************************************/
#include "Server.h"

void settPrint()
{
    printf( "\x1B[1;1H\x1B[2J");
    printf( "=========================== Settaggi Struttura ============================\n");
    printf( "Porta in ascolto                  = [%u]\n", settaggi->nPort);    
    printf( "Numero massimo client collegabili = [%d]\n", settaggi->nClientMax);
    printf( "Directory Salvataggio file        = [%s]\n", settaggi->saveDir);
    printf( "Buffer massimo invio              = [%d]\n", settaggi->maxBuffer);
    printf( "%s\n", "==================================================");
    return;
}
