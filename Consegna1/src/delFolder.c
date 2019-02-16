/** ***************************************************************************
 * \file        delFolder.c 
 * \version     1.0
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 * 
 * \details     Elimina le voci riferite a directory in una lista FILDERX
 * 
 * 
 * \param[in] **head Puntatore doppio alla Lista da cui cercare gli elementi cartella
 *
 * \return 
 * \retval  -1  Funzione Fallita
 * \retval   0  Successo
 *****************************************************************************/
#include "FILDERX.h"

listFILDERX* delFolder(listFILDERX **head)
{
    listFILDERX *s;
    if(*head == NULL)
    {
        return NULL;
    }

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
