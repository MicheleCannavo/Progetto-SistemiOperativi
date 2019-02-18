#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>       // All 
#include <stdlib.h>      // All 
#include <string.h>      // All 
#include <limits.h>      // All 
#include <unistd.h>      // read, write
#include <ctype.h>       // All 
#include <arpa/inet.h>   // All 
#include <sys/types.h>   // socket, bind, accept, open
#include <sys/socket.h>  // socket, bind, listen, accept
#include <sys/stat.h>    // open
#include <fcntl.h>       // open
#include <errno.h>       // All 
#include <sys/statvfs.h> // freespace()
#include <signal.h>      // TIMEOUT,
#include <netinet/in.h>  // freespace()
#include <netdb.h>       // freespace()

///////////////////////////////////// MACRO ///////////////////////////////////

/// \def     DECIMO_UINT
/// \brief   1/10 del valore di UNIT_MAX
#define DECIMO_UINT ((UINT_MAX)/10)

/// \def     UNITA_UINT
/// \brief   Valore dell'unita' di UINT_MAX
#define UNITA_UINT  ((UINT_MAX)-((DECIMO_UINT)*10))

/// \def     DECIMO_INT
/// \brief   1/10 del valore di INT_MAX
#define DECIMO_INT  (INT_MAX / 10)

/// \def     UNITAP
/// \brief   Valore dell'unita' di INT_MAX
#define UNITAP      ((INT_MAX) - (DECIMO_INT *10))

/// \def     UNITAN
/// \brief   Valore dell'unita' di INT_MIN
#define UNITAN      (UNITAP + 1)

/// \def    IP
/// \brief  Macro per definire l'IP di default a cui connettersi
#define IP          "127.0.0.1"

/// \def    MAXBUF
/// \brief  Macro per definire il buffer per l'invio dei dati tramite socket
#define MAXBUF      (1024)

/// \def    PORT
/// \brief  Macro per definire la porta di comunicazione del socket
#define PORT        (64000)

/// \def    SAVEDIR
/// \brief  Macro per definire la cartella di salvataggio dei file ricevuti
#define SAVEDIR     "/Scaricati"

/// \def    PATT_MAX
/// \brief  Macro che definisce i caratteri massimi del pattern
#define PATT_MAX (20)

/// \def    TIMEOUT
/// \brief  Definisce il tempo massimo di attessa per la connessione col Server
#define TIMEOUT     (5)

/// \def    PRINTERR
/// \brief  Macro che definisce una funzione di stampa per evenuteli errori
#define PRINTERR(x) printf("[%s:%d] - %s-%s\n", \
        __FUNCTION__,__LINE__,x,strerror(errno))

/// \def    MAX_CHAR_USER
/// \brief  Macro che definisce i caratteri massimi del nome utente
#define MAX_CHAR_USER (20)

/// \def    MAX_CHAR_PASS
/// \brief  Macro che definisce i caratteri massimi dell password
#define MAX_CHAR_PASS (20)

/// \def    SBUFFER
/// \brief  Macro di puizia del buffer stdin
#define SBUFFER do{int ch; \
                    while ( ( ch=getchar() ) !='\n' && (ch != EOF) );\
                }while(0)

/// \def    PATH_MAX
/// \brief  Macro che definisce la dimensione massima dei PATH
#ifndef PATH_MAX
#define PATH_MAX 2048
#endif

/// \def    NAME_MAX
/// \brief  Macro che definisce la dimensione massima del nome di un file
#ifndef NAME_MAX
#define NAME_MAX 256
#endif

//////////////////////////////////// STRUCT ////////////////////////////////////

typedef struct _SettCLIENT //<! Struct per i settaggi del client
{
    char               IP_STRING[16]; ///< IP del Server
    unsigned short             nPort; ///< Porta in ascolto
    char           saveDir[PATH_MAX]; ///< CXartella di salvataggio dei file
    int                    maxBuffer; ///< Buffer per l'invio/ricezione dei file
}SettCLIENT; ///< Alias

/////////////////////////////// VARIABILI GLOBALI //////////////////////////////

/// \var    settaggi
/// \brief  Struttura per i settaggi del programma
extern SettCLIENT *settaggi;

/// \var    socid_Client
/// \brief  variabile goblale per memorizzare l'ID del socket
extern int  sockid_Client;

/////////////////////////////////// PROTOTIPI //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

///////////////////////////// Gestione Account  ///////////////////////////////
int mainWrite (int id, const char* nomeUser, const char *passser);
int mainRead ();
int mainVer(int id, const char *name, const char *pass);

/////////////////////////////////// SETTAGGI //////////////////////////////////
int  myMainC(int argc, char *argv[]);
int  iniSett();
int  argSett(int argc, char *argv[]);
int  modSettCli();
void settPrint();

/////////////////////////////////// MENU' //////////////////////////////////
int menCli();
int menSett();
int menAcc();
int menFilderx();

/////////////////////////////////// TEST INPUT-OTHER //////////////////////////////////
int isdigit_in( int  *caracter );
int  inputUInt( unsigned int  *result );
int   inputInt( int  *result   );
int isalpha_in( int  *caracter );
int   testPath( char  *wPath   );
int  freespace( unsigned long  sizeF );

/////////////////////////////////// SOCKET //////////////////////////////////
int   newSocket();
int closeSocket();
int  gestClient();

//////////////////////////////// COMANDI ////////////////////////////////////
int wwconf( int sockid, const char buff[9]);
int rwconf( int sockid, char buff[9]);

int  verUser( int sockid);
int  addUser( int sockid);
int sendFILE( int sockid);
int recvFILE( int sockFD, char *fr_name, int buff);
int searching(int sockid);
#endif