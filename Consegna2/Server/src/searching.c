#include "Server.h"
/** ****************************************************************************
 * \version     1.3
 * \date        15/02/2019
 * 
 * \brief       Cerca i file col PATTERN disegnato 
 * 
 * \param   sockFD      ID del socket 
 * 
 * \return  Verifica dell'esito funzione  
 *
 * \details     Prende la lista completa headTList, la scorre e ne stampa solo 
 *              i file che seguono le regole del PATTERN
 *
 *******************************************************************************/

int searching(int sockid)
{
// VARIABILI E INIZIALIZZAZIONI
    char    patt[PATT_MAX];
    char    list[PATH_MAX];
    int     dPathF  =    0;

    memset(patt,'\0',PATT_MAX);
    memset(list,'\0',PATH_MAX);

// Ricevo la richiesta
    recv(sockid, &dPathF, sizeof(int), MSG_WAITALL);
    recv(sockid, patt, dPathF, MSG_WAITALL);
    printf("Patter selezionato:[%s]\n", patt);

    listFILDERX *tmp=headTList;

// Lista vuota
    if(tmp==NULL)
    {
        printf( "Non ci sono elementi nella lista");
    }

// Lista piena

    while(tmp->next!=NULL)
    {
        if(tmp->elemento.absPath[0] == '/' && 
                fnmatch(patt, basename(tmp->elemento.absPath), FNM_NOESCAPE)==0)
        {
            dPathF=strlen(tmp->elemento.absPath)+1;
            //Invio la lunghezza del pathFile
            send(sockid, (void*) &dPathF, sizeof(int), 0); 

            // invio il pathf file
            send(sockid, tmp->elemento.absPath, dPathF, 0); 
            printf("--%s\n",tmp->elemento.absPath);
        }
        tmp=tmp->next;
    }

// Ultimo elemento    
    if(tmp->elemento.absPath[0] == '/' &&
            fnmatch(patt,basename(tmp->elemento.absPath), FNM_NOESCAPE)==0)
    {
            dPathF=strlen(tmp->elemento.absPath)+1;
            //Invio la lunghezza del pathFile
            send(sockid,(void*)&dPathF, sizeof(int), 0); 

            // invio il pathf file
            send(sockid, tmp->elemento.absPath, dPathF, 0); 
            printf("--%s\n",tmp->elemento.absPath);
    }
    // Fine invio
    dPathF=0;
    send(sockid,(void*)&dPathF, sizeof(int), 0); 
    printf("FINE INVIO");

    return 0;
}