#include "Server.h"
#include "FILDERX.h"


int searching(int sockid)
{
// VARIABILI E INIZIALIZZAZIONI
    char    patt[PATT_MAX];
    char    list[PATT_MAX];
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
            send(sockid, &dPathF, sizeof(int), 0); 

            // invio il pathf file
            send(sockid, tmp->elemento.absPath, dPathF, 0); 
            printf("--%s\n",tmp->elemento.absPath);
        }
        tmp=tmp->next;
    }

// Ultimo elemento    
    if(tmp->elemento.absPath[0] == '/' &&
            !fnmatch(patt,basename(tmp->elemento.absPath), FNM_NOESCAPE))
    {
            dPathF=strlen(tmp->elemento.absPath)+1;
            //Invio la lunghezza del pathFile
            send(sockid, &dPathF, sizeof(int), 0); 

            // invio il pathf file
            send(sockid, tmp->elemento.absPath, dPathF, 0); 
            printf("--%s\n",tmp->elemento.absPath);
    }
    // Fine invio
    dPathF=-1;
    send(sockid, &dPathF, sizeof(int), 0); 
    printf("FINE INVIO");

    return 0;
}