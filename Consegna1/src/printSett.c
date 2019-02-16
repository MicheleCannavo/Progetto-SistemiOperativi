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
    dprintf(fdStream, "%s\n", "=============== Settings Struct ============== ");
    dprintf(fdStream, "Work Directory   = [%s]\n", settaggi->dirWork);
    dprintf(fdStream, "Save Directory   = [%s]\n", settaggi->dirSave);
    dprintf(fdStream, "Patern search    = [%s]\n", settaggi->patttFILDERX);
    dprintf(fdStream, "Number of core   = [%d]\n", settaggi->nCoreProcessor);
    dprintf(fdStream, "%s\n", "==================================================");
}
