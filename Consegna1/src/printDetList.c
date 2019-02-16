/** ***************************************************************************
 * \file        printDetList.c 
 * \version     1.1
 * \date        22/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       Funzione di gestione della lista concatenata del programma.
 * 
 * \details     Questa funzione stampa tutti gli elementi che rappresentano 
 *              un file con path assoluto. E' possibile stampare attraverso un
 *              qualsiasi file descriptor di un file precedentemente aperto. A
 *              differenza di listPritnS, questa funzione stampa tutti gli ele-
 *              menti in dettagliio.
 *
 * \param[in]   *headTList       Puntatore alla lista da stampare
 * \param[in]    fdStream   Fd che identifica il file in cui stampare
 *
 * \retval  -1      errore nei parametri di input
 * \retval   0      Funzione Fallita/L'elemento Non e' una cartella
 *****************************************************************************/
#include "FILDERX.h"

int printDetList(listFILDERX *headTList, int fdStream)
{  
    listFILDERX *ltmp=headTList;
// Verifica argomenti in input
    if(  (headTList==NULL) || (fdStream<0) )
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }

    if(ltmp==NULL)
    {
        dprintf(fdStream, "Non ci sono elementi nella lista");
        return 0;
    }

    while(ltmp->next!=NULL)
    {
        if(ltmp->elemento.absPath[0] == '/')
        {
            printNode(ltmp->elemento,fdStream);
        }
        ltmp=ltmp->next;
    }
    
    if(ltmp->elemento.absPath[0] == '/')
    {
        printNode(ltmp->elemento,fdStream);
    }
    return 0;
}