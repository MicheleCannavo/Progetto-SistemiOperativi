#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>          // All 
#include <stdlib.h>         // All 
#include <string.h>         // All 
#include <limits.h>         // All 
#include <unistd.h>         // read, write
#include <ctype.h>          // All 
#include <arpa/inet.h>      // All 
#include <sys/types.h>      // socket, bind, accept, open
#include <sys/socket.h>     // socket, bind, listen, accept
#include <sys/stat.h>       // open
#include <fcntl.h>          // open
#include <errno.h>          // All 
#include <sys/statvfs.h>    // freespace()

#define IP       "127.0.0.1"
#define PORT          (64000)
#define MAXBUF         (1024)
#define SAVEDIR "/Scaricati"
#define TIMEOUT (5)
#define PRINTERR(x) printf("[%s:%d] - %s-%s\n",__FUNCTION__,__LINE__,x,strerror(errno))
#define MAX_CHAR_USER (20)
#define MAX_CHAR_PASS (20)

/// \def    SBUFFER
/// \brief  Macro di puizia del buffer stdin
#define SBUFFER do{int ch; \
                    while ( ( ch=getchar() ) !='\n' && (ch != EOF) );\
                }while(0)

#ifndef PATH_MAX
#define PATH_MAX 8096
#endif

struct _SettCLIENT
{
    char               IP_STRING[16];
    unsigned short             nPort;
    char           saveDir[PATH_MAX];
    int                    maxBuffer;
};
typedef struct _SettCLIENT SettCLIENT;



/// \def     DECIMO_UINT
/// \brief   1/10 del valore di UNIT_MAX
/// 
/// \def     UNITA_UINT
/// \brief   Valore dell'unita' di UINT_MAX
/// 
/// \def     DECIMO_INT
/// \brief   1/10 del valore di INT_MAX
/// 
/// \def     UNITAP
/// \brief   Valore dell'unita' di INT_MAX
/// 
/// \def     UNITAN
/// \brief   Valore dell'unita' di INT_MIN
#define DECIMO_UINT ((UINT_MAX)/10)
#define UNITA_UINT  ((UINT_MAX)-((DECIMO_UINT)*10))
#define DECIMO_INT  (INT_MAX / 10)
#define UNITAP      ((INT_MAX) - (DECIMO_INT *10))
#define UNITAN      (UNITAP + 1)


/////////////////////////// VARIABILI GLOBALI //////////////////////////////
extern SettCLIENT *settaggi;
extern int         sockid_Client;







































int mainWrite (int id, const char* nomeUser, const char *passser);
int mainRead ();
int mainVer(int id, const char *name, const char *pass);


/////////////////////////////////// SETTAGGi //////////////////////////////////
int  myMainC(int argc, char *argv[]);
int  iniSett();
int  argSett(int argc, char *argv[]);
int  modSettCli();
void settPrint( int fdStream);

/////////////////////////////////// MENU' //////////////////////////////////
int menCli();
int menSett();
int menAcc();
int menFilderx();

/////////////////////////////////// TEST INPUT-OTHER //////////////////////////////////
int isdigit_in( int *caracter );
int  inputUInt( unsigned int *result );
int   inputInt( int *result );
int   testPath( char* wPath);

/////////////////////////////////// SOCKET //////////////////////////////////
int   newSocket();
int closeSocket();
int  gestClient();

///////////////////////////////////////////////////////////////////////////////////
int wwconf(int sockid, const char buff[9]);
int rwconf(int sockid, char buff[9]);

///////////////////////////////////////////////////////////////////////////////////
int verUser(int sockid);
int addUser(int sockid);
//int addUser2( char *name, char *pass);
//int verUser2( char *name, char *pass);
#endif