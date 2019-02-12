#ifndef S_H
#define S_H
 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>          
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <stdio.h>

#define PRINTERR(x) printf("[%s:%d] - %s-%s\n",__FUNCTION__,__LINE__,x,strerror(errno))

#define PORT 20000 
#define BACKLOG 5
#define LENGTH 512 

int   sendFILE( int  sockFD, char *fs_name);
int   recvFILE( int  sockFD, char *fr_name, int buff);
int   verTrnsf( int  sockFD, int   dimF,    int dimR);
int isalpha_in( int *caracter );
int freespace(unsigned long sizeF);
#endif