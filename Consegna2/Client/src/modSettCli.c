
/// \file  FILDERX.c
/// \brief Motore di ricerca ricorsiva di FILDERX
/// \version 1.2
/// \copyright GNU LGPL 3.0
/// \details Motore che ricerca, con le impostazioni date, File e cartelle dentro una directory.

#include "Client.h"

int modSettCli()
{    
    if(settaggi == NULL)  
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }

    unsigned int  port;
             int  maxBuff;
     
    char *ipAdress = calloc(16, sizeof(char) );  
    if(ipAdress==NULL)
    {
        perror(__FUNCTION__);
        return -1;
    }

    char *saveDir = calloc(PATH_MAX,sizeof(char) );  
    if(saveDir==NULL)
    {
        free(ipAdress);
        perror(__FUNCTION__);
        return -1;
    }


    printf("\x1B[1;1H\x1B[2J");
    printf("\t\t           Modifica i Settaggi\n");
    printf("\t\t---- Invio vuoto per non modificare ---\n\n");

//================================ INDIRIZZO IP ==========================
    if(strncmp(settaggi->IP_STRING,"127.0.0.1",16) == 0)
    {
        printf("\n\nE' stato impostato l'indirizzo: %s \"localhost\"\n",
                         settaggi->IP_STRING);
    }
    else
    {
        printf("\n\nE' stato impostato l'indirizzo: %s \"Server Esterno\"\n",
                         settaggi->IP_STRING);
    }
    
    printf("Cambiarlo con: ");
    fgets(ipAdress, 16, stdin);

    if( ipAdress[strlen(ipAdress)-1]=='\n' )
        ipAdress[strlen(ipAdress)-1]='\0';

    if( 1 )
    {
        strncpy(settaggi->IP_STRING, ipAdress, 16);
    }

//=========================== PORTA IN ASCOLTO ==========================
    printf("\n\nIl numero di porta impostato e': %u\n", settaggi->nPort);
    printf("Cambiarlo con: ");
    if( (inputUInt(&port) != -1) && (port>1023 && port<65535) )
    {
        settaggi->nPort=port;
    }

//================================ CARTELLA DI SALVATAGGIO =============================
    printf("\n\nL'attuale directory per il salvataggio file è: %s\n",settaggi->saveDir);
    printf("Cambiarla con: ");
    fgets(saveDir, PATH_MAX, stdin);

    if( saveDir[strlen(saveDir)-1]=='\n' )
        saveDir[strlen(saveDir)-1]='\0';

    if( (saveDir[0]!='\n' && saveDir[0]!='\0') && testPath(saveDir)==0 )
    {
        strncpy(settaggi->saveDir, saveDir, PATH_MAX-1);
        settaggi->saveDir[PATH_MAX-1]='\0';

        if(settaggi->saveDir[strlen(settaggi->saveDir)-1]=='\n')
            settaggi->saveDir[strlen(settaggi->saveDir)-1]='\0';
    }

//================================ BUFFER INVIO DATI =====================================
    printf("\n\nIl buffer per l'invio dei dati e': %d\n", settaggi->maxBuffer);
    printf("Cambiarlo con: ");
    if( (inputInt(&maxBuff) != -1) && (maxBuff>0 && maxBuff<=1024) )
    {
        settaggi->maxBuffer=maxBuff;
    }
    // Tanto per dare la possibilità di vedere un attimo i nuovi settaggi 
    printf("\n\nSalvataggio in corso....\n\n");
    sleep(2);
    free(saveDir);
    free(ipAdress);
    ipAdress=saveDir=NULL;
    return 0;
}
