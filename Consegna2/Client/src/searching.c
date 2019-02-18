#include "Client.h"

int searching(int sockid)
{
// VARIABILI E INIZIALIZZAZIONI
    char patt[PATT_MAX];
    char list[PATT_MAX];
    int  dPathaF=0;

    memset(patt,'\0',PATT_MAX);
    memset(list,'\0',PATH_MAX);

// Comando per la richiesta file
    if(wwconf(sockid,"REQ_FILE")!=0)
    {
        PRINTERR("Errore nel comando");
        return -1;
    }
// Richiedo il pattern per la richiesta file
    printf("Inserisci il pattern: ");
    fgets(patt, PATT_MAX-1, stdin);
    patt[PATT_MAX-1]='\0';
    if(patt[strlen(patt)-1]=='\n')
        patt[strlen(patt)-1]='\0';

// invio la richiesta
    dPathaF=strlen(patt)+1;
    send(sockid, &dPathaF,sizeof(int),0);
    send(sockid, patt, PATT_MAX, 0);

// Ricevo la lista
    while( recv(sockid, (void*)&dPathaF, sizeof(int), 0) != -1 )
    {
        recv(sockid, list, dPathaF, MSG_WAITALL);
        printf("%s\n",list);
    }
    return 0;
}