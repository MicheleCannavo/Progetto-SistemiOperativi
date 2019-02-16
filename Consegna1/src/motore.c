//==============================================================================
/// \author  Cannavo' Michele [046002210]
/// \date    07/12/2018
//==============================================================================
/// \file  FILDERX.c
/// \brief Motore di ricerca ricorsiva di FILDERX
/// \version 1.2
/// \copyright GNU LGPL 3.0
/// \details Motore che ricerca, con le impostazioni date, File e cartelle dentro una directory.
/** ***************************************************************************
 * \file        motore.c 
 * \version     1.5
 * \date        25/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       Motore del programma di ricerca file.
 * 
 * \details     Questa funzione e' il motore di ricerca.
 *
 * \retval  -1      errore nei parametri di input
 * \retval   0      Funzione Fallita/L'elemento Non e' una cartella
 *****************************************************************************/
#include "FILDERX.h"

// Variabile per l'ID dei Thread creati
pthread_t thread[MAX_CORE];

// mutex del motore
pthread_mutex_t muxList;
pthread_mutex_t muxList2;

int MotoreFILDER(SettFILDERX settaggi )
{
    char currDir[PATH_MAX];

// Salvo la posizione corrente della cartella di lavoro
    if( getcwd(currDir, PATH_MAX)  == NULL)
    {
        perror("Errore 1 in motoreFILDERX");
        return -1;
    }

    if(pthread_mutex_init(&muxList,  NULL) != 0)
    {
        perror ("Errore 2 in motoreFILDERX");
        return -1;
    }

    if(pthread_mutex_init(&muxList2, NULL) !=0)
    {
        perror ("Errore 3 in motoreFILDERX");
        return -1;
    }

    listFILDERX *miniList=listdir(settaggi.dirWork);//Elenco directory principale
    
    if( totL(&headTList, miniList) != 0)
    {
        perror ("Errore 6 in motoreFILDERX");
        return -1;
    }

    if(pthread_mutex_lock(&muxList2) != 0)
    {
        perror ("Errore 8 in motoreFILDERX");
        return -1;
    }

    for(int y=0; y<= settaggi.nCoreProcessor; y++)
    {
        if( pthread_create(&thread[y],NULL,funcT,NULL) !=0 )
        {
            perror (" in motoreFILDERX");
            return -1;
        }
    }

    if(pthread_mutex_unlock(&muxList2) != 0 )
    {
        perror ("Errore 9 in motoreFILDERX");
        return -1;
    }

    for(int y=0; y<=settaggi.nCoreProcessor; y++)
    {
        int ret;
        pthread_join(thread[y], (void*)&ret);
        if(ret!=0)
        {   
            return -1;
        }
    }

    free(miniList);

    pthread_mutex_destroy( &(muxList2) );
    pthread_mutex_destroy( &(muxList) );

    if(chdir(currDir)!=0)
    {
        perror ("Errore 9 in motoreFILDERX");
        return -1;
    }
    return 0;
}

void *funcT(void*arg)
{
    do
    {
        listFILDERX *i; 
       
        i=delFolder(&headTList);
        if(pthread_mutex_lock(&muxList) != 0)
        {
            perror ("Errore 1 in funcT");
            pthread_exit( (void*)-1);
        }

        if(i!=NULL)
        {
          listFILDERX *miniList=listdir(i->elemento.absPath);

            if(totL(&headTList,miniList)!=0)
            {
                perror ("Errore 2 in funcT");
                pthread_exit( (void*)-1);
            }

            if(pthread_mutex_unlock(&muxList) != 0)
            {
                perror ("Errore 3 in funcT");
                pthread_exit( (void*)-1);
            }
        }
        else
        {
            if(pthread_mutex_unlock(&muxList) != 0)
            {
                perror ("Errore 4 in funcT");
                pthread_exit( (void*)-1);
            }
            break;
        }
    }
    while(1); // Il while dura finchè vi sono directory
    pthread_exit((void*)0);
}