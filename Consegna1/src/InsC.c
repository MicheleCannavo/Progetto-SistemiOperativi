/** ***************************************************************************
 * \file        iniSett.c 
 * \version     1.2
 * \date        20/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 * 
 * \details     Questa funzione inserisce un elemento ELEFILDERX in coda ad una 
 *              lista listFILDERX. Può essere utilizzata anche con una lista 
 *              vuota ma almeno il puntatore iniziale non deve puntare a NULL. 
 *              Se il nodo da inserire e' NULL ritorna errore.
 *
 * \retval  -1  Funzione Fallita
 * \retval   0  Successo
 *****************************************************************************/
#include "FILDERX.h"

int InsC(listFILDERX **miniList, ELEFILDERX *nodoF)
{ 
       listFILDERX *t;
       listFILDERX *s;

// Verifica input
    if(nodoF==NULL || miniList==NULL)
    {
        perror(__FUNCTION__);
        return -1;
    }

    t=(listFILDERX*)calloc(1,sizeof(listFILDERX));
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

        /* qui t punta all'ultima struttura della lista: ne
           creo una nuova e sposto il puntatore in avanti */
        s->next=t;

        t->elemento.idNumber=nodoF->idNumber;
        strncpy( t->elemento.absPath,nodoF->absPath,PATH_MAX);
        t->elemento.absPath[PATH_MAX-1]='\0';
        t->next=NULL;
    }

    return 0;
}