/** ***************************************************************************
 * \version     1.2
 * \date        27/12/2018
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 * 
 * \param[in] **headTList Doppio puntatore alla Lista 
 * 
 * \return 
 * \retval  -1  Funzione Fallita
 * \retval   0  Successo 
 * 
 * \details     Elimina le voci riferite a directory in una lista FILDERX
 * 
 *****************************************************************************/
#include "FILDERX.h"

listFILDERX* delFolder(listFILDERX **head)
{
// VARIABILI E INIZIALIZZAZIONI
    listFILDERX *s;

// Verifica argomenti
    if(*head == NULL)
    {
        return NULL;
    }

// Ricerca directory
    if( (*head)->next != NULL )
    {
        s=*head;
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
    if( IsDir(*head) )
    {
        s=*head;
        *head=(*head)->next;
        return s;
    }
    return NULL;
}
