#include "Client.h"

int closeSocket()
{          
    if(sockid_Client==-1)
    {
        errno=EBADFD;
        perror(__FUNCTION__);
        return 1;
    }

    for(int i=5;i>0;i--)
    {
        printf("\rIl programma si chiuderà in %d second%c", i, i==1?'o':'i');
        sleep(1);
    }

    if( close(sockid_Client) != 0)
    {
        perror(__FUNCTION__);
        sockid_Client=-1;
        return -1;
    }
    sockid_Client = -1;
    return 0;
}