#include "Server.h"

int server_sockfd=-1;
int client_sockfd=-1;


 /**
 ******************************************************************************
 *  \file       newsocket.c
 *  \version    1.0
 * 
 *  \brief      Crea una comnessione TCP
 * 
 *  \details    Questa funzione crea un socket AF_INET, SOCK_STREAM, TCP
 * 
 *  \param[out] *sock_fd    puntatore ad int per il file descriptor del socket
 *  \param[in]  port        porta in ascolto del socket
 *  \param[in]  addr        Indirizzo del socket
 *  
 *  \retval    -1   Errore nella funzione
 *  \retval     0   Socket creato
 *****************************************************************************/
int newSocket(int *sock_fd, unsigned short port, unsigned long addr) 
{

// Verifica input - addr è passato come MACRO INADDR_XXX
    if(sock_fd==NULL || (port>65535) )
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }

    struct sockaddr_in serveraddr;

// socket() 
    *sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (*sock_fd == -1)
    {
        // errno dal socket
        perror(__FUNCTION__);
        return -1;
    }

    memset((void*)&serveraddr, 0, sizeof(struct sockaddr_in));
    serveraddr.sin_family       = AF_INET;
    serveraddr.sin_addr.s_addr  = htonl(addr);
    serveraddr.sin_port         = htons(port);
    
// bind()
    if (bind(*sock_fd, (struct sockaddr *)&serveraddr, sizeof serveraddr) > 0)
    {
        // errno dalla bind
        perror(__FUNCTION__);
        return -1;
    }
    
// listen
    if (listen(*sock_fd, 100) != 0)
    {
        // errno dalla list()
        perror(__FUNCTION__);
        return -1;
    }

    return 0;
}

 /**
 ******************************************************************************
 *  \file       closefd.c
 *  \version    1.0
 * 
 *  \brief      Chiude un file descriptor
 * 
 *  \details    Questa funzione chiude un file puntato dal file descriptor
 *              e dopo one a -1 la variabile per indicarne che non è più 
 *              utilizzabile come file descriptor.
 * 
 *  \param[out] *sock_fd    puntatore per il file descriptor da chiuderr
 *  
 *  \retval    -1   Errore nella funzione
 *  \retval     0   File descriptor chiuso
 *****************************************************************************/
int closefd(int *sock_fd)
{          
    if(sock_fd==NULL )
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }
    
    if(close(*sock_fd) != 0)
    {
        // errno dalla close()
        perror(__FUNCTION__);
        return 1;
    }
    *sock_fd = -1;
    return 0;
}

 /**
 ******************************************************************************
 *  \file       closeSocket.c
 *  \version    1.0
 * 
 *  \brief      Chiude un socket con avviso. 
 * 
 *  \details    Questa funzione stampa su video un avviso della chiusura del 
 *              Socket usato per il server.
 * 
 *  \param[out] *sock_fd    puntatore per il file descriptor da chiudere
 *  
 *  \retval    -1   Errore nella funzione
 *  \retval     0   File descriptor chiuso
 *****************************************************************************/
int closeSocket(int *sock_fd)
{          
    for(int i=5;i>=0;i--)
    {
        printf("\rIl Server si chiuderà in %d second%c", i, i==1?'o':'i');
        sleep(1);
    }
    
    return  closefd(sock_fd);
}