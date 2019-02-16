/** ***************************************************************************
 * \version     1.0
 * \date        17/12/2018
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 *
 * \retval  ==0     Funzione Fallita/L'elemento Non e' una cartella
 * \retval  !=0     Successo. L'elemento e' riferito ad una cdirectory
 * 
 * \details     Questa funzione verifica se l'elemento della lista in input 
 *              si riferisce ad una directory o meno.
 * 
 ****************************************************************************/

#include "FILDERX.h"

int IsDir(listFILDERX *listNodo)
{
    struct stat stFilderx;

    stat(listNodo->elemento.absPath, &stFilderx);
    return S_ISDIR(stFilderx.st_mode) ;
}