#include "Client.h"

int searching(int sockid)
{
    char patt[21];
    printf("Inserisci il pattern: ");
    fgets(patt,20,stdin);
    patt[20]='\0';
    write(sockid,patt,20);
}