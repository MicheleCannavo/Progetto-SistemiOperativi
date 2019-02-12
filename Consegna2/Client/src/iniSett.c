#include "Client.h"

/// Questa funzione alloca la memoria e inizializza una struct SettFILDERX 
/// che servirà a contenere i settaggi del programma. 
int iniSett()
{
    if(settaggi != NULL )
    {
        errno=EINVAL;
        perror("struct settaggi già inizializzata");
        return -1;
    }

    settaggi = calloc(1, sizeof(SettCLIENT) );
    if(settaggi == NULL)
    {
        perror("Errore nell'allocazione struttura per i settaggi");
        return -1;
    }

// Variabile per creare la directory di salvataggio
    char saveDir[PATH_MAX];
    memset((void*)saveDir, 0, PATH_MAX);

    char ipAdress[16];
    memset((void*)ipAdress, 0, 16);
   
// Settaggi statici
// il size di 16 include il terminatore
    strncpy(settaggi->IP_STRING, IP, 16  ); 

    settaggi->nPort      = PORT;
    settaggi->maxBuffer  = MAXBUF;
    
// Directory /HOME/Scaricati come directory di salvataggio di default.
    if(strlen( getenv("HOME"))  <= PATH_MAX- (strlen(SAVEDIR)+1) )
    {
        strncpy(settaggi->saveDir, getenv("HOME"), PATH_MAX- (strlen(SAVEDIR)+1)  );  
        strncat( settaggi->saveDir, SAVEDIR, strlen(SAVEDIR)+1 );
    } 


 




    return 0;
}