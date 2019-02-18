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

// Richiedo il pattern per la richiesta file
    printf("Inserisci il pattern: ");
    fgets(patt, PATT_MAX-1, stdin);
    patt[PATT_MAX-1]='\0';

// invio la richiesta
    recv(sockid, patt, PATT_MAX, 0);
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
                fnmatch(patt,basename(tmp->elemento.absPath), FNM_NOESCAPE)==0)
        {
            dPathF=strlen(tmp->elemento.absPath)+1;
            //Invio la lunghezza del pathFile
            send(sockid, (void*)&dPathF, sizeof(int), 0); 

            // invio il pathf file
            send(sockid, tmp->elemento.absPath, dPathF, 0); 
        }
        tmp=tmp->next;
    }

// Ultimo elemento    
    if(tmp->elemento.absPath[0] == '/' &&
            !fnmatch(patt,basename(tmp->elemento.absPath), FNM_NOESCAPE))
    {
            dPathF=strlen(tmp->elemento.absPath)+1;
            //Invio la lunghezza del pathFile
            send(sockid, (void*)&dPathF, sizeof(int), 0); 

            // invio il pathf file
            send(sockid, tmp->elemento.absPath, dPathF, 0); 
    }
    // Fine invio
    dPathF=-1;
    send(sockid, (void*)&(dPathF), sizeof(int), 0); 

    return 0;
}