/** ***************************************************************************
 * \file        listPrintS.c 
 * \version     1.1
 * \date        22/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       Funzione di  stampa per la lista concatenata.
 * 
 * \details     Questa funzione stampa tutti gli elementi di una listFILDERX
 *              e' possibile stampare attraverso un qualsiasi file descriptor 
 *              di un file precedentemente aperto.
 * 
 * \param[in]   *headTList       Puntatore alla lista da stampare
 * \param[in]    fdStream   Fd che identifica il file in cui stampare
 * 
 * \retval  -1      puntatore ad una lista di file e cartelle
 * \retval   0      Funzione Fallita/L'elemento Non e' una cartella
 *****************************************************************************/
#include "FILDERX.h"

int printList(listFILDERX *headTList, int fdStream)
{
    listFILDERX *l=headTList;
// Verifica input
    if( (fdStream<0) || (headTList==NULL) )
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }

    if(l==NULL)
    {
        dprintf(fdStream, "Non ci sono elementi nella lista");
        return -1;
    }

    while(l->next!=NULL)
    {
        if(l->elemento.absPath[0] == '/')
        {
                dprintf(fdStream, "[%s]-[%ld]\n",l->elemento.absPath,l->elemento.idNumber); 
        }
        l=l->next;
    }
    
    if(l->elemento.absPath[0] == '/')
    {
        dprintf(fdStream, "[%s]-[%ld]\n",l->elemento.absPath,l->elemento.idNumber); 
    }
    return 0;
}