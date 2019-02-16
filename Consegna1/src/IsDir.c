/** ***************************************************************************
 * \file        iniSett.c 
 * \version     1.0
 * \date        17/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 * 
 * \details     Questa funzione verifica se l'elemento in input si riferisce ad
 *              una directory o meno.
 *
 * \retval  ==0     Funzione Fallita/L'elemento Non e' una cartella
 * \retval  !=0     Successo. L'elemento e' riferito ad una cdirectory
 *****************************************************************************/

#include "FILDERX.h"

int IsDir(listFILDERX *listNodo)
{
    struct stat stFilderx;

    stat(listNodo->elemento.absPath, &stFilderx);
    return S_ISDIR(stFilderx.st_mode) ;
}