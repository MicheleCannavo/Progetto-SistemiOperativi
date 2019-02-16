/** ***************************************************************************
 * \file        creaNodo1.c 
 * \version     1.0
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 * 
 * \details     Crea un nodo da inserire nella lista dei file.
 * 
 * \param[in]   *path   path assoluto del file  
 * \param[in]   id      id del file
 *
 * \return  Puntatore al nodo creato
 * \retval  NULL    Funzione Fallita
 *****************************************************************************/
#include "FILDERX.h"

ELEFILDERX *creaNodo1( const char* path, unsigned long id)
{
// Verifica input
    if(path==NULL)
    {
        return NULL;
    }
    
    char *tmpPath=calloc(PATH_MAX, sizeof(char));
    if(tmpPath==NULL)
    {
        return NULL;      
    }

    ELEFILDERX *tmp = calloc(1, sizeof( ELEFILDERX ) );
    if( !tmp )
    {
        perror( "Allocazione nodo fallita: " );
        free(tmpPath); tmpPath=NULL;
        return NULL;
    }

// Carico l'ID
    tmp->idNumber=id;

// Carico il path assoluto
    if(path[0]=='/')// Già Path assoluto
    {       
        strncpy(tmpPath, path, PATH_MAX-1);
        tmpPath[PATH_MAX-1]='\0';
    }
    else if( (realpath(path, tmpPath )==NULL ))
    {
        perror("Creazione pathname assoluto  non riuscita");
        free(tmpPath); tmpPath = NULL;
        free(tmp);         tmp = NULL;
        return NULL;
    }
    strncpy(tmp->absPath, tmpPath, PATH_MAX-1);
    tmp->absPath[PATH_MAX-1]='\0';

    free(tmpPath); tmpPath=NULL;
    return tmp;
}
