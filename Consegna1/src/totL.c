/** ***************************************************************************
 * \file        totL.c 
 * \version     1.0
 * \date        17/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 * 
 * \details     Questa funzione unisce due iste concatenate. Funziona anche se 
 *              la lista madre è vuota. Non effettua controlli sulla lista da 
 *              inseriere, se è vuota o nulla non modificherà la lista Head.
 *
 * \param[in]   **Head      Lista finale dove incollare un'altra lista
 * \param[in]    *mini      Lista da incollare nella lista finale
 * 
 * \return      Non ritorna nulla.
 *****************************************************************************/
#include "FILDERX.h"
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