/** ***************************************************************************
 * \version     1.0
 * \date        17/12/2018
 * 
 * \brief       Funzione di gestione dei settaggi del programma.
 * 
 * \details     Questa funzione recupera il numero di core fisici nel file
 *              "/proc/cpuinfo" alla voce sibilings. Si usa la prima voce
 *              che ri riscontra.
 *
 * \retval  -1      Errore nei parametri di input
 * \retval   0      Funzione Fallita/L'elemento Non e' una cartella
 *****************************************************************************/
#include "FILDERX.h"

int testPath(char* wPath)
{
    struct stat *path;
    path=(struct stat*)calloc(1,sizeof(struct stat));
    if(path==NULL)
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        exit(-1);
    }
    if ( stat(wPath, path)==0 && S_ISDIR(path->st_mode) )
    {
        free(path);
        path=NULL;
        return 0;
    }
    else
    {
        perror(__FUNCTION__);
        free(path);
        path=NULL;
        return -1;
    }
}