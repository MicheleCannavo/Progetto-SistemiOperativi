#include "Client.h"

int newSocket() 
{ 
    struct sockaddr_in serv_addr;

    if(sockid_Client > -1) // Socket già in uso
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }

/* socket() */        
    sockid_Client = socket(AF_INET, SOCK_STREAM, 0);      
    if(sockid_Client == -1)
    {
        perror(__FUNCTION__);
        return -1;
    }   

    memset( (void*)&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(settaggi->IP_STRING);
    serv_addr.sin_port        = htons(settaggi->nPort);
/* connect() */  
    if(connect(sockid_Client, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror(__FUNCTION__);
        close(sockid_Client);
        return -1;
    } 
    
    return 0;
}