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
// VARIABILI E INIZIALIZZAZIONI    
  char       *tmpPath = NULL;
  ELEFILDERX *tmp     = NULL;

// Verifica input
    if(path==NULL)
    {
        return NULL;
    }
    
// Allocazione memoria per il path
    tmpPath = calloc(PATH_MAX, sizeof(char));
    if(tmpPath==NULL)
    {
        return NULL;      
    }

// Allocazione memoria per il nodo
    tmp = calloc(1, sizeof( ELEFILDERX ) );
    if( !tmp )
    {
        free(tmpPath);
        tmpPath=NULL;
        return NULL;
    }

// Ricavo una stringa con il path assoluto
    // Già Path assoluto
    if(path[0]=='/')
    {       
        strncpy(tmpPath, path, PATH_MAX-1);
        tmpPath[PATH_MAX-1]='\0';
    }
    // Risalgo al path assoluto
    else if( (realpath(path, tmpPath ) == NULL ) )
    {
        free(tmpPath); tmpPath = NULL;
        free(tmp);         tmp = NULL;
        return NULL;
    }

// Copio le info nel Nodo
    tmp->idNumber=id;
    strncpy(tmp->absPath, tmpPath, PATH_MAX-1);
    tmp->absPath[PATH_MAX-1]='\0';

// Libero memoria e finisco la funzione
    free(tmpPath); 
    tmpPath=NULL;
    return tmp;
}