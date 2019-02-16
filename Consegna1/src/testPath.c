/** ***************************************************************************
 * \version     1.0
 * \date        17/12/2018
 * 
 * \brief       Funzione di gestione dei settaggi del programma.
 * 
 * \details     Questa funzione testa l'esistenza di un percorso.
 *
 * \retval  -1      Errore nei parametri di input
 * \retval   0      Funzione Fallita/L'elemento Non e' una cartella
 *****************************************************************************/
#include "FILDERX.h"

int testPath(char* wPath)
{
    struct stat *path;
    path = calloc(1, sizeof(struct stat));
    if(path==NULL)
    {
        errno=EINVAL;
       return -1;
    }

// Popolamento struct stat
    if ( stat(wPath, path)==0 && S_ISDIR(path->st_mode) )
    {
        free(path);
        path = NULL;
        return 0;
    }
    else
    {
        free(path);
        path = NULL;
        return -1;
    }
}