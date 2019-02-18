#include "Client.h"

int searching(int sockid)
{
// VARIABILI E INIZIALIZZAZIONI
    char patt[PATT_MAX];
    char list[PATT_MAX];

    memset(patt,'\0',PATT_MAX);
    memset(list,'\0',PATH_MAX);

// Richiedo il pattern per la richiesta file
    printf("Inserisci il pattern: ");
    fgets(patt, PATT_MAX-1, stdin);
    patt[PATT_MAX-1]='\0';

// invio la richiesta
    send(sockid, patt, PATT_MAX, 0);

// Ricevo la lista
    recv(sockid, list, PATH_MAX, 0);
    return 0;
}