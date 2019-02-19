 /** ***************************************************************************
 * \file        modSettServ.c
 * \version     1.3
 * \date        15/01/2019
 * 
 *  \brief      Modifica manualmente i settaggi del Server
 * 
 * \retval    -1   Fallimento funzione
 * \retval     0   Settaggi modiifcati 
 * 
 * \details     Questa funzione permette la modifica manuale dei settaggi del 
 *              server. Per ogni parametro è possibile specificarne uno nuovo. 
 *              Se non lo si vuole cambiare basterà non scrivere nulla, 
 *              se si scrive un parametro errato, esso non verrà modificato
 * 
 *****************************************************************************/
#include "Server.h"

int modSettServ()
{    
// Verifica allocazione della struct SettServer
    if(settaggi == NULL)  
    {
        errno=EINVAL;
        perror("Errore in modSettServ()");
        return -1;
    }

    unsigned int  port;
             int  nClient;
             int  maxBuff;
    
    char *saveDir = (char*)calloc(PATH_MAX,sizeof(char) );  
    if(saveDir==NULL)
    {
        perror(__FUNCTION__);
        return -1;
    }
//=============================== MENU SETTAGGI ===============================
    printf("\x1B[1;1H\x1B[2J");
    printf("\t\t           Modifica i Settaggi\n");
    printf("\t\t---- Invio vuoto per non modificare ---\n\n");

//=============================  PORTA IN ASCOLTO =============================
    printf("\n\nIl numero di porta impostato e': %u\n", settaggi->nPort);
    printf("Cambiarlo con: ");
    if( (inputUInt(&port) != -1) && (port>1023 && port<65535) )
    {
        settaggi->nPort=port;
    }

//=========================== NUMERO CLIENT MASSIMO ===========================
    printf("\n\nLimite connessioni simultanee: %d\n", settaggi->nClientMax);
    printf("Cambiare il limite con: ");
    if( (inputInt(&nClient) != -1) && (nClient>0 && nClient<100) )
    {
        settaggi->nClientMax=nClient;
    }

//========================== CARTELLA DI SALVATAGGIO ==========================
    printf("\n\nL'attuale directory per il salvataggio file è: %s\n",
                settaggi->saveDir);

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

//============================= BUFFER INVIO DATI =============================
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
    saveDir=NULL;
    return 0;
}