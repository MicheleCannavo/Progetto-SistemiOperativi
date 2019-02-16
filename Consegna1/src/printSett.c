/** ***************************************************************************
 * \file        sett.c 
 * \version     1.0
 * \date        17/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       Funzione di stampa dei settaggi del programma.
 * 
 * \details     Questa funzione stampa su di un file descriptor a scelta, la
 *              tabella dei settaggi del programma.
 *
 * \param[in]   fdStream    Descriptor del file in cu stampare i settaggi
 * 
 * \return      Non ritorna nulla.
 *****************************************************************************/
#include "FILDERX.h"

void printSett( int fdStream)
{
    dprintf(fdStream, "\x1B[1;1H\x1B[2J");
    dprintf(fdStream, "%s\n", "=============== Settaggi Struttura ============== ");
    dprintf(fdStream, "Directory di lavoro    = [%s]\n", settaggi->dirWork);
    dprintf(fdStream, "Directory Salvataggio  = [%s]\n", settaggi->dirSave);
    dprintf(fdStream, "Pattern di ricerca     = [%s]\n", settaggi->patttFILDERX);
    dprintf(fdStream, "Numero di core         = [%d]\n", settaggi->nCoreProcessor);
    dprintf(fdStream, "%s\n", "==================================================");
}
