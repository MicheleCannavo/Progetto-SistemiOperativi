#include "Client.h"

/**
 * @brief 
 * 
 * @return int 
 */
int gestClient()
{   
    alarm(TIMEOUT);
    printf("Connessione in corso...\n");
    sleep(2);
    if( newSocket() !=0 )
    {
        perror(__FUNCTION__);
            sleep(2);
        return -1;
    }   
    alarm(0);
    return menAcc();
}