 /**
 ******************************************************************************
 *  \file       settPrint.c
 *  \version    1.0
 * 
 *  \brief      Stampa la tabella dei settaggi
 * 
 *  \details    Questa funzione stampa su un file aperto tramite 
 *              un file descriptor, una tabella contenete le attuali 
 *              impostazione del Server. La funzione e' utilizzabile sia per
 *               lo stream stdin sia per un normale file di testo.
 * 
 *  \param[in]  fdStream Fd del file in cui si vogiono stampare i settaggi
 *  
 *  \return Non ritorna valori
 *****************************************************************************/
#include "Server.h"

void settPrint( int fdStream)
{
    dprintf(fdStream, "\x1B[1;1H\x1B[2J");
    dprintf(fdStream, "=========================== Settaggi Struttura ============================\n");
    dprintf(fdStream, "Porta in ascolto                  = [%u]\n", settaggi->nPort);    
    dprintf(fdStream, "Numero massimo client collegabili = [%d]\n", settaggi->nClientMax);
    dprintf(fdStream, "Directory Salvataggio file        = [%s]\n", settaggi->saveDir);
    dprintf(fdStream, "Buffer massimo invio              = [%d]\n", settaggi->maxBuffer);
    dprintf(fdStream, "%s\n", "==================================================");
    return;
}
