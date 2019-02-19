
#include "Server.h"
SettSERVER  *settaggi = NULL;
/** ****************************************************************************
 * \version     1.0
 * \date        18/02/2019
 * 
 * \brief       Funzione chiusura SERVER
 * 
 * \details     Funzione chiamata da atexit() che dopo aver chiuso il socket 
 *              della listen() pulisce lo schermo. * 
 * 
 *****************************************************************************/
void svuota(void)
{
    closeSocket(&server_sockfd);
    printf("\x1B[1;1H\x1B[2J");
}

/** ****************************************************************************
 * \version     1.0
 * \date        18/02/2019
 * 
 * \brief       Gestore SIGCHLD
 * 
 * \details     Funzione per evitare resti di PROCESSi ZOMBIE. gestisce il 
 *              segnale di chiusura del processo figlio (SIGCHLD) e attende
 *              tramite waipid l'effettiva chiusura per evitare processi zombie
 * 
 *****************************************************************************/
void closeCHLD(int sig)
{
    signal(SIGCHLD, SIG_IGN);
    
    pid_t cpid=0;

    while((cpid=waitpid(-1, NULL, WNOHANG)) > 0 )
        continue;

    signal(SIGCHLD,closeCHLD);
}

/** ****************************************************************************
 * \version     1.0
 * \date        18/02/2019
 * 
 * \brief       gestore SIGALARM
 * 
 * \details     Funzione per la gestione del segnale SIGALARM ricevuto in caso 
 *              che il Client impiegi troppo tempo a rispondere
 * 
 *****************************************************************************/
void timeout(int sig)
{
    signal(SIGALRM, SIG_IGN);
    errno=ETIMEDOUT;
    closefd(&server_sockfd);
    signal(SIGALRM,timeout);
}

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