 /** **************************************************************************
 * \version     1.3
 * \date        17/02/2019
 * 
 * \brief       Header per le funzioni del Server
 * 
 * \details     Questo è un header file cumulativo per tutte le funzioni del 
 *              Server FILDERX 
 * 
 *****************************************************************************/
#ifndef SERVER_H
#define SERVER_H

///////////////////////////////// HEADER FILE /////////////////////////////////
#include <stdio.h>        // All
#include <stdlib.h>       // All
#include <string.h>       // All
#include <limits.h>       // 
#include <unistd.h>       // read, write
#include <ctype.h>        //
#include <arpa/inet.h>    //
#include <sys/types.h>    // socket, bind, accept, open
#include <sys/socket.h>   // socket, bind, listen, accept
#include <sys/stat.h>     // open
#include <fcntl.h>        // open
#include <errno.h>        //
#include <netinet/in.h>   //
#include <sys/wait.h>     //
#include <signal.h>       //
#include <netdb.h>        //
#include <sys/statvfs.h>  //
#include <time.h>         // 
#include "FILDERX.h"

/// \def    PRINTERR
/// \brief  Semplice Macro per creare ua stringa di LOG per eventuali Errori
#define PRINTERR(x) printf( "[%s:%d] - %s-%s\n" \
                    , __FUNCTION__, __LINE__, x, strerror(errno))

/// \def    SBUFFER
/// \brief  Macro di puizia del buffer stdin
#define SBUFFER do{int ch; \
                    while ( ( ch=getchar() ) !='\n' && (ch != EOF) );\
                }while(0)

#ifndef PATH_MAX
#define PATH_MAX    (2048)
#endif

#ifndef PATT_MAX
#define PATT_MAX    (20)
#endif

#ifndef NAME_MAX
#define NAME_MAX    (256)
#endif

/// \def    MAX_CHAR_USER
/// \brief  Valore di caratteri massimo del nome utente
#define MAX_CHAR_USER (20)

/// \def     MAX_CHAR_PASS
/// \brief   Valore di caratteri massimo del nome utente
#define MAX_CHAR_PASS (20)

/// \def    DECIMO_UINT
/// \brief  A1/10 del valore di UNIT_MAX
#define DECIMO_UINT ((UINT_MAX)/10)

 /// \def    UNITA_UINT
 /// \brief  Valore dell'unita' di UINT_MAX
#define UNITA_UINT  ((UINT_MAX)-((DECIMO_UINT)*10))

/// \def    DECIMO_INT
/// \brief  1/10 del valore di INT_MAX
#define DECIMO_INT  (INT_MAX / 10)


/// \def    UNITAP
/// \brief  Valore dell'unita' di INT_MAX
#define UNITAP      ((INT_MAX) - (DECIMO_INT *10))


/// \def    UNITAN
/// \brief  Valore dell'unita' di INT_MIN
#define UNITAN      (UNITAP + 1)



/**
 * \def     PORT
 * \brief   Porta in ascolto del Server
 * 
 * \def     MAX_CLIENT
 * \brief   Numero massimo di connessioni simultanee possibili
 * 
 * \def     SAVEDIR
 * \brief   Percorso relativo dalla home per la cartella di salvataggio
 * 
 * \def     MAXBUF
 * \brief   Valore massimo del buffer per lo scambio di dati col client
 */
#define PORT        (64000)
#define MAX_CLIENT  (5)
#define SAVEDIR     "/Scaricati"
#define MAXBUF      (1024)
#define TIMEOUT     (5)
#define MAX_CORE    (32)





#define N_COMM (5)

extern const char *_COMMAND_[];

#define VER_USER _COMMAND_[0]
#define ADD_USER _COMMAND_[1]
#define REQ_FILE _COMMAND_[2]
#define SEND_FIL _COMMAND_[3]
#define RECV_FIL _COMMAND_[4]

//////////////////////////////////// STRUCT ////////////////////////////////////

struct _SettSERVER //<! Struttura per i Settaggi
{
    unsigned short            nPort; //!< numero di porta
    int                  nClientMax; //!< Numero di client massimi
    char          saveDir[PATH_MAX]; //!< Cartella di salvataggio
    int                   maxBuffer; //!< Massimo buffer per lo scambio di dati
};
// Alias per struct _SetttSERVER
typedef struct _SettSERVER SettSERVER;

struct accounting //<! Struttura per gli account
{ 
    unsigned ID;                    //!< ID Account
    char     user[MAX_CHAR_USER];   //!< Nome utente
    char     pass[MAX_CHAR_PASS];   //!< Password
};
//Alias per struct accounting
typedef struct accounting USER_FILDERX;

////////////////////////////// VARIABILI GLOBALI ///////////////////////////////

/// \var    settaggi
/// \brief  variabile per i settaggi del SERVER
extern SettSERVER *settaggi;

/// \var    server_sockfd
/// \brief  Variabile contenente l'ID del socket server
extern int server_sockfd;

////////////////////////////////// PROTOTIPI ///////////////////////////////////

int accountWrite (int id, const char* nomeUser, const char *passUser);
int mainRead ();
int accountVer(const char *name);

int isdigit_in( int *caracter );
int  inputUInt( unsigned int *result );
int   inputInt( int *result );
int   testPath( char *wPath );
int isalpha_in( int *caracter );
int  freespace( unsigned long sizeF);

int myMainS(int argc, char *argv[]);
int iniSett();
int  argSett(int argc, char *argv[]);
void settPrint( );
int modSettServ();

int menServ();
int menSett();
int menAcc();

int gestConn();
int newSocket(int *sock_fd, unsigned short port, unsigned long addr);
int closefd(int *sock_fd);

int   rwconf( int sockid,       char comm[9]);

int  verUser( int id);
int verUser2( const char *name, const char *pass);
int addUser2( int sockid, char *name,  char *pass);
int  addUser( int sockfd);

int  sendFILE( int sockFD);
int  recvFILE( int sockid, char *fr_name, int buff);
int searching( int sockid);

#endif