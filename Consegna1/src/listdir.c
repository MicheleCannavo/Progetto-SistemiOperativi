/** ***************************************************************************
 * \file        listdir.c 
 * \version     1.0
 * \date        22/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 * 
 * \details     Questa funzione crea una lista NON RICORSIVA, dei file dentro 
 *              una directory, non opera filtri sul tipo di file ma solo in ba-
 *              se al pattern di ricerca impostato nei settaggi.
 *
 * \return puntatore ad una lista di file e cartelle
 * \retval  NULL     Funzione Fallita/L'elemento Non e' una cartella
 *****************************************************************************/
#include "FILDERX.h"

// Dato una directory, crea una minilista con i file in maniera NON ricorsiva!!
listFILDERX* listdir(const char *name)
{   
    char          *fullPath   = NULL;
    ELEFILDERX    *tmp        = NULL;
    DIR           *directory  = NULL;
    struct dirent *elementDir = NULL;
    listFILDERX *miniList=NULL;

    if(name==NULL)
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return NULL;
    }

// Mi sposto nella cartella di ricerca
    if( chdir(name) != 0 )
    {
        perror(__FUNCTION__);
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

    //Escludo i file esclusi dal pattern
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
            fullPath=realpath(elementDir->d_name,NULL );
            if( fullPath == NULL )
            {
                perror("errore memoria");
                return NULL;
            }
             
            tmp= creaNodo1(fullPath, count++);
            if(tmp==NULL)
            {
                perror("ERRORE IN MEMORIA2");
                return NULL;
            }
            
            free(fullPath);
            fullPath=NULL;
        }
        InsC(&miniList,tmp);  
        free(tmp);
        tmp=NULL;
    }

// Chiudo l'attuale directory
    closedir(directory);
    return miniList;
}