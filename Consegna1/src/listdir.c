/** ***************************************************************************
 * \version     1.0
 * \date        22/12/2018
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.

 * \retval  !NULL       Puntatore ad una lista di file e cartelle
 * \retval  NULL        Funzione Fallita/L'elemento Non e' una cartella
 * 
 * \details     Questa funzione crea una lista NON RICORSIVA, dei file dentro 
 *              una directory, non opera filtri sul tipo di file ma solo in ba-
 *              se al pattern di ricerca impostato nei settaggi.
 *
 *****************************************************************************/
#include "FILDERX.h"

listFILDERX* listdir(const char *name)
{   
// VARIABILI E INIZIALIZZAZIONI
    char          fullPath[PATH_MAX]  ;
    ELEFILDERX    *tmp        = NULL;
    DIR           *directory  = NULL;
    struct dirent *elementDir = NULL;
    listFILDERX   *miniList   = NULL;

// verifica argomenti
    if(name == NULL)
    {
        errno = EINVAL;
        return NULL;
    }

// Mi sposto nella cartella di ricerca
    if( chdir(name) != 0 )
    {
        return NULL;
    } 

// Apro la directory
    if ( !(directory = opendir(name)) )
    {
        return NULL;
    }

// Ricerca nella directory
    while ((elementDir = readdir(directory)) != NULL)
    {

    // Escludo le cartelle speciali
        if (elementDir->d_name[0] == '.' )
            continue;

    // Escludo i file esclusi dal pattern
        if ( fnmatch(settaggi->patttFILDERX, elementDir->d_name, 0) != 0 )
        {
            continue;
        }
    
    // Path assoluto
        if(elementDir->d_name[0]=='/')
        {
            tmp= creaNodo1(elementDir->d_name, count++);
        }
    
    // Path relativo
        else
        { 
            realpath(elementDir->d_name, fullPath);
             
            tmp = creaNodo1(fullPath, count++);
            if(tmp == NULL)
            {
                return NULL;
            }
            
        }

    // Inserisco nodo e libero la memoria
        InsC(&miniList,tmp);  
        free(tmp);
        tmp=NULL;
    }

// Chiudo l'attuale directory
    closedir(directory);
    return miniList;
}