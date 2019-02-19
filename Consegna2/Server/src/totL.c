#include "FILDERX.h"

/** ***************************************************************************
 * \version     1.0
 * \date        17/12/2018
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 *
 * \param[in]   **miniLis   Lista parziale creata 
 * \param[in]    *nodoF     Nodo da inserire in coda alla minilista
 *  
 * \retval      -1      Funzione fallita
 * \retval       0      Nodo inserito
 *  
 * \details     Questa funzione copia un nodo precededentemente creato in 
 *              una lista temporanea che verrà successivamente aggiunta a 
 *              quella completa. 
 * 
 *****************************************************************************/
int InsC(listFILDERX **miniList, ELEFILDERX *nodoF)
{  
// VARIABILI E INIZZZIAIZZAZIONI
    listFILDERX *t;
    listFILDERX *s;

// Verifica argomenti in input
    if(nodoF==NULL || miniList==NULL)
    {
        perror(__FUNCTION__);
        return -1;
    }

// Allocazione lista temporanea
    t=calloc(1,sizeof(listFILDERX));
    if(t==NULL)
    {
        perror(__FUNCTION__);
        return -1;
    }

// Lista vuota
    if((*miniList)==NULL)
    {
        *miniList=t;
            t->elemento.idNumber=nodoF->idNumber;
    strncpy( t->elemento.absPath,nodoF->absPath,PATH_MAX);
    t->elemento.absPath[PATH_MAX-1]='\0';
    t->next=NULL;
    }
// Lista con elementi
    else
    {
        s=*miniList;

        /* vado avanti fino alla fine della lista */
        while(s->next!=NULL)
            s=s->next;

        /* qui t punta all'ultima struttura della lista */
        s->next=t;
            t->elemento.idNumber=nodoF->idNumber;
    strncpy( t->elemento.absPath,nodoF->absPath,PATH_MAX);
    t->elemento.absPath[PATH_MAX-1]='\0';
    t->next=NULL;
    }
    return 0;
}

/** ***************************************************************************
 * \version     1.0
 * \date        17/12/2018
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 *
 * \param[in]   **Head      Lista Completa finale 
 * \param[in]    *mini      Lista temportanea parziale
 *  
 * \retval      -1      Funzione fallita
 * \retval       0      Nodo inserito
 *  
 * \details     Questa funzione unisce una lista temporanea parziale,
 *              creta da ogni singolo thread, a quella completa data dallo 
 *              apporto della ricerca ricorsiva in ogni singola sottocartella
 * 
 *****************************************************************************/
int totL(listFILDERX **Head, listFILDERX *mini)
{
// Verifica argomenti in input
    if(Head==NULL )
    {
        perror(__FUNCTION__);
        return -1;
    }

    listFILDERX *tmp;// Elemento temporaneo
// Head vuota
    if( (*Head)==NULL)
    {
        (*Head)=mini;
        return 0;
    }

// Head con elementi
    tmp=*Head;
    while(tmp->next!=NULL)
        tmp=tmp->next;

    tmp->next=mini;
    return 0;
}

/** ***************************************************************************
 * \version     1.0
 * \date        17/12/2018
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 *
 * \param[in]   **miniList     Lista parziale con cartelle
 * 
 * \retval      -1      Funzione fallita
 * \retval       0      Nodo inserito
 *  
 * \details     Questa funzione , data una lista, controllo se al suo interno, 
 *              gli elementi si riferiscono ad una directory. In caso di esito
 *              positivo, elimina l'elemento e lo restituisce per effettuare 
 *              una ricerca all'interno di esso.
 * 
 *****************************************************************************/
listFILDERX* delFolder(listFILDERX **miniList)
{
// VARIABILI E INIZZIALIZZAZIONI
    listFILDERX *s;    
    if(*miniList == NULL)
    {
        return NULL;
    }

// Scansiono la lista, nel caso di lista con più elementi
    if( (*miniList)->next != NULL )
    {
        s=*miniList;
        while(s->next!=NULL)
        {
            if( IsDir(s->next) )
            {    
                listFILDERX *l;
                l=s->next;
                s->next=s->next->next;
                return l;
            }
            else
            {
                s=s->next;
            }
        }
    }

// Testo l'unico elemento se c'è un solo elemento 
    if( IsDir(*miniList) )
    {
        s=*miniList;
        *miniList=(*miniList)->next;
        return s;
    }
    return NULL;
}

/** ***************************************************************************
 * \version     1.0
 * \date        17/12/2018
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 *
 * \param[in]   *listNodo      Nodo inserito nella lista 
 *  
 * \retval      !=0      Funzione fallita
 * \retval       =0      Nodo inserito
 *  
 * \details         Questa funzione verifica se il nodo della lista dinamica 
 *                  rappresenta una directory.
 * 
 *****************************************************************************/
int IsDir(listFILDERX *listNodo)
{
    struct stat stFilderx;

    if(stat(listNodo->elemento.absPath, &stFilderx) !=0 )
    {
        return -1;
    }

    return S_ISDIR(stFilderx.st_mode);
}

/** ***************************************************************************
 * \version     1.0
 * \date        17/12/2018
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 *
 * \param[in]   **listComp      Lista di file 
 * 
 * \retval      -1      Funzione fallita
 * \retval       0      Nodo inserito
 *  
 * \details     Questa funzione libera la memoria precedentemente allocata per 
 *              ogni singolo nodo della lista dinamica di file.
 * 
 *****************************************************************************/
int freeL(listFILDERX **listComp)
{    
// VARIABILI E INIZZIALIZZAZIONi
    listFILDERX *Temp1;   // Lista temporanea1
    listFILDERX *Temp2;   // Lista temporanea2

// Lista non valida
    if(listComp==NULL || *listComp==NULL)
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }
     
    Temp1=*listComp;  

// Lista valida
    while( Temp1 )
    {
        Temp2 = Temp1->next;
        free( Temp1 );
        Temp1 = Temp2;
    }
    *listComp=NULL;
    return 0;
}

/** ***************************************************************************
 * \file        totL.c 
 * \version     1.0
 * \date        17/12/2018
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 *
 * \param[in]   **Head      Lista Completa finale 
 * \param[in]    *mini      Lista temportanea parziale
 *  
 * \retval      -1      Funzione fallita
 * \retval       0      Nodo inserito
 *  
 * \details     Questa funzione unisce una lista temporanea parziale,
 *              creta da ogni singolo thread, a quella completa data dallo 
 *              apporto della ricerca ricorsiva in ogni singola sottocartella
 * 
 *****************************************************************************/
ELEFILDERX *creaNodo1( const char* path, unsigned long id)
{
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
