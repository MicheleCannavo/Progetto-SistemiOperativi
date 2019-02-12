 /** ******************************************************************************
 * \file        testPath.c
 * \version     1.0
 * 
 * \brief       Testa l'esistenza di una directory
 * 
 * \param[in]   *wPath  file descriptor del socket
 * \param[out]   buff   buffer dove verrà salvato il comando
 * \param[in]    size   Dimensione massima del buffer
 *  
 * \retval      -1      Funzione fallita
 * \retval       0      Il path e' una directory
 * \retval       1      Il path non e' una directory
 *
 * \details    Questa funzione testa l'esistenza di una directory invia la
 *             conferma della lettura. Serve per sincronizzare server e client.
 *
 *****************************************************************************/
#include "Server.h"

int testPath(char* wPath)
{
// Verifica allocazione stringa
    if(wPath==NULL)
    {
        errno=EINVAL;
        PRINTERR("Argomenti:");
        return -1;
    }

// Creo struc stat 
    struct stat *path;
    path=(struct stat*)calloc(1,sizeof(struct stat));
    if(path==NULL)
    {
        PRINTERR("Controllo cartella ");
        return -1;
    }
// Se wPath contiene il percorso di una directory
    if ( stat(wPath, path)==0 && S_ISDIR(path->st_mode) )
    {
        free(path);
        path=NULL;
        return 0;
    }
    
// Se non contiene il percorso di una cartella
    else
    {
        free(path);
        path=NULL;
        errno=ENOTDIR;
        PRINTERR("Controllo cartella ");
        return 1;
    }
}