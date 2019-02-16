/** ***************************************************************************
 * \file        freeL.c 
 * \version     1.0
 * \date        20/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 * 
 * \details     Libera la memoria allocata per la Lista.
 * 
 * \param[in]   **listNodo    Doppio puntatore alla Lista da deallocare

 * \retval  -1  Funzione Fallita
 * \retval   0  Successo
 *****************************************************************************/
#include "FILDERX.h"

int freeL(listFILDERX **listComp)
{  
// VARIABILI E INIZIALIZZAZIONI
    listFILDERX *Temp1;
    listFILDERX *Temp2;

// Verifica argomenti
    if(listComp==NULL || *listComp==NULL)
    {
        errno=EINVAL;
        return -1;
    }
    
// Liberazione memori della lista
    Temp1=*listComp;
    while( Temp1 )
    {
        Temp2 = Temp1->next;
        free( Temp1 );
        Temp1 = Temp2;
    }
    *listComp=NULL;
    return 0;
}