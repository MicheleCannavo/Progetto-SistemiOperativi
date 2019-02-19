/** ****************************************************************************
 * \version     1.4
 * \date        15/02/2019
 * 
 * \brief       Motore di ricerca ricorsiva di FILDERX
 * 
 * \details     Motore che ricerca, con le impostazioni date, File e cartelle 
 *              dentro una directory.
 * 
 *****************************************************************************/
#include "Server.h"
SettSERVER  *settaggi = NULL;

// Funzione chiusura SERVER
void svuota(void)
{
    closefd(&server_sockfd);
    printf("\x1B[1;1H\x1B[2J");
}

// Funzione per evitare resti di PROCESSi ZOMBIE
void closeCHLD(int sig)
{
    signal(SIGCHLD, SIG_IGN);
    
    pid_t cpid=0;

    while((cpid=waitpid(-1, NULL, WNOHANG)) > 0 )
        continue;

    signal(SIGCHLD,closeCHLD);
}

void timeout(int sig)
{
    signal(SIGALRM, SIG_IGN);
    errno=ETIMEDOUT;
    closefd(&server_sockfd);
    signal(SIGALRM,timeout);
}

int myMainS(int argc, char* argv[])
{   
    atexit(svuota);
    signal(SIGALRM,timeout);

    if (argc<1 || argc>2 )
    {
        errno=EINVAL;
        perror(__FUNCTION__); 
        return -1;
    } 

// Inizializza la struttura dei settaggi con valori di default
    if( iniSett() != 0 )
    {
        perror(__FUNCTION__); 
        return -1;
    }

// Riempie la struttura dei settaggi con valori da linea di comadno
   if(argSett( argc, argv)==-1)
    {
        perror(__FUNCTION__); 
        free(settaggi);
        settaggi=NULL;
        return -1;
    }
    printf("Caricamento Lista...Attendere\n");
    if(MotoreFILDER() == -1)
    {
        PRINTERR("MotoreFILDERX");
        return -1;
    };

    if(menServ()==-1)
    {
        freeL(&headTList);
        free(settaggi);
        settaggi=NULL;
        return-1;
    }

    freeL(&headTList);
    free(settaggi);
    settaggi=NULL;
    return 0;
}