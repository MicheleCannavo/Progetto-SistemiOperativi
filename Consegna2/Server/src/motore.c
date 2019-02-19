/** ***************************************************************************
 * \version     1.5
 * \date        25/12/2018
 * 
 * \brief       Motore del programma di ricerca file.
 * 
 * \details     Questa funzione e' il motore di ricerca.
 * 
 *****************************************************************************/
#include "Server.h"

/// VARIABILI GLOBALI PER TUTTI I FILE
unsigned long int            count;     // Contatore di file
listFILDERX             *headTList;     // Lista completa globale
pthread_t         thread[MAX_CORE];     // Variabile per i thread (fino a 32 gestibili)
pthread_mutex_t            muxList;     // Mutex1
pthread_mutex_t           muxList2;     // Mutex2
int MotoreFILDER( )
{
// VARIABILI E INIZZIALIZZAZIONI
    char      currDir[PATH_MAX]; //
    char      myHome[PATH_MAX];  //
    short int nCore;             //

// Reperisco il numero di core
    getNCore(&nCore);

// Salvo la cartella corrente
    if( getcwd(currDir,PATH_MAX)  == NULL)
    {
        perror("Errore 1 in motoreFILDERX");
        return -1;
    }   
    
// Ricavo la cartella home 
    strncpy(myHome, getenv("HOME"), PATH_MAX-1);
        myHome[PATH_MAX-1]='\0';

// Inizializzo i mutex
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

// Ricerca nella cartella principale SENZA ricorsione
    listFILDERX *miniList=listdir(myHome);//Elenco directory principale

// Inserisco nella lista completa
    if( totL(&headTList, miniList) != 0)
    {
        perror ("Errore 6 in motoreFILDERX");
        return -1;
    }

// Lock mutex2
    if(pthread_mutex_lock(&muxList2) != 0)
    {
        perror ("Errore 8 in motoreFILDERX");
        return -1;
    }

// Creazione thread
    for(int y=0; y<= nCore; y++)
    {
        if( pthread_create(&thread[y],NULL,funcT,NULL) !=0 )
        {
            perror (" in motoreFILDERX");
            return -1;
        }
    }

// Unlock mutex
    if(pthread_mutex_unlock(&muxList2) != 0 )
    {
        perror ("Errore 9 in motoreFILDERX");
        return -1;
    }

// join thread
    for(int y=0; y<=nCore; y++)
    {
        int ret;
        pthread_join(thread[y], (void*)&ret);
        if(ret!=0)
        {   
            return -1;
        }
    }

// Libero memroia della sola minilista
    free(miniList);

// Distruggo i Mutex
    pthread_mutex_destroy( &(muxList2) );
    pthread_mutex_destroy( &(muxList) );

// Riposizione la cartella di lavoro a quella iniziale
    if(chdir(currDir)!=0)
    {
        perror ("Errore 9 in motoreFILDERX");
        return -1;
    }

    return 0;
}

/** ***************************************************************************
 * \version     1.0
 * \date        25/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       FDunzione per il motore di ricerca file.
 * 
 * \param[in]   *arg Argomento della funzione dei thread
 * 
 * \details     Questa funzione e' la funzione utilizzata dai thread per la 
 *              ricerca dei file. Prende la lista completa che è stata creata a 
 *              livello goblale per essere comune a tutti i thread, e ne cerca
 *              le cartella. Quando ne trova una, esegue una scansione dellla
 *              stessa, e salva la lista generata nella lista completa. Ripete
 *              questo ciclo fintanto che trova una cartella da cui ricavare 
 *              altri elementi.
 * 
 *****************************************************************************/
void *funcT(void *arg)
{
// Ciclo infinito
    do
    {
        listFILDERX *tmp; 

// Lock sulla lista
        if(pthread_mutex_lock(&muxList) != 0)
        {
            perror ("Errore 1 in funcT");
            pthread_exit( (void*)-1);
        }

// Cerco una cartella tra gli elementi della Lista
        tmp=delFolder(&headTList);

// Se la trovo...
        if(tmp!=NULL)
        {     
           listFILDERX *miniList;
    // Creo una miniList
            miniList=listdir(tmp->elemento.absPath);
    // L'aggiungo alla Lista completa
            if(totL(&headTList,miniList)!=0)
            {
                perror ("Errore 2 in funcT");
                pthread_exit( (void*)-1);
            }
    // Sblocco a Lista per il successivo thread
            if(pthread_mutex_unlock(&muxList) != 0)
            {
                perror ("Errore 3 in funcT");
                pthread_exit( (void*)-1);
            }
        }
// Se non ne trovo....
        else
        {
    // Unlock mutex
            if(pthread_mutex_unlock(&muxList) != 0)
            {
                perror ("Errore 4 in funcT");
                pthread_exit( (void*)-1);
            }
            break;
        }
    }
    while(1); // Il while dura finchè vi sono directory
// Esco dal thread
    pthread_exit((void*)0);
}

/** ***************************************************************************
 * \version     1.0
 * \date        25/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       FDunzione per il motore di ricerca file.
 * 
 * \param[in]   *arg Argomento della funzione dei thread
 * 
 * \details     Questa funzione e' la funzione utilizzata dai thread per la 
 *              ricerca dei file. Prende la lista completa che è stata creata a 
 *              livello goblale per essere comune a tutti i thread, e ne cerca
 *              le cartella. Quando ne trova una, esegue una scansione dellla
 *              stessa, e salva la lista generata nella lista completa. Ripete
 *              questo ciclo fintanto che trova una cartella da cui ricavare 
 *              altri elementi.
 * 
 *****************************************************************************/
listFILDERX* listdir(const char *name)
{
// VARIABILI E INIZZIALIZZAZIONI
    char          fullPath[PATH_MAX];
    ELEFILDERX    *tmp        = NULL;
    DIR           *directory  = NULL;
    struct dirent *elementDir = NULL;
    listFILDERX   *miniList   = NULL;   

// Verififca argomento
    if(name==NULL)
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return NULL;
    }

// Mi sposto nella cartella da setacciare
    if( chdir(name) != 0 )
    {printf("%s--\n",name);
        perror(__FUNCTION__);
        return NULL;
    } 

// Apro la directory
    if ( !(directory = opendir(name)) )
    {
        return NULL;
    }

// Ciclo tutti i file in essa contenuti
    while ((elementDir = readdir(directory)) != NULL)
    { 
    // Esclude './', '../' e cartelle nascoste
          if (elementDir->d_name[0] == '.' )
            continue;

    // Esclude != Pattern 
        if ( fnmatch("*", elementDir->d_name, 0) != 0 )
            continue;

    // Path assoluto
        if(elementDir->d_name[0]=='/')
        {
            tmp= creaNodo1(elementDir->d_name, count++);
        }
    // Path relativo 
        else
        {
            realpath(elementDir->d_name,fullPath );
            tmp= creaNodo1(fullPath, count++);
            if(tmp==NULL)
            {
                perror("ERRORE IN MEMORIA2");
                return NULL;
            }
        }
    
    // Inserisco elemento in lista
        InsC(&miniList,tmp);  
        free(tmp);
        tmp=NULL;
    }
    
// Chiudo l'attuale directory
    closedir(directory);
    return miniList;
}

