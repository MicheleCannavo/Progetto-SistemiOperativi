#include "Server.h"
 /**
 ******************************************************************************
 * \file        verUser.c
 * \version     1.0
 * 
 * \brief       Funzione per il comando VER_USER
 * 
 * \param[in]  sockfd  file descriptor del socket
 *  
 * \retval    -1   FAILURE
 * \retval     0   SUCCESS 
 *  
 * \details     Questa funzione gestisce le operazioni da effettuare quando il
 *              server riceve il comando di VER_USER. Questo comando richiede al 
 *              server di verificare l'autorizzazzione da parte di un client
 *              ad utilizzare le funzione del Server.
 * 
 *****************************************************************************/
int verUser(int sockfd)
{  
    char user[MAX_CHAR_USER];
    char pass[MAX_CHAR_PASS];

// Il controllo sull'input 
    if(socket<0)
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }

// Leggo il nome utente
    if(read(sockfd, user, MAX_CHAR_USER) < 0)
    {
        perror(__FUNCTION__);
        return -1;
    }

// Leggo la password
    if(read(sockfd, pass, MAX_CHAR_PASS) < 0)
    {
        perror(__FUNCTION__);
        return -1;
    }

// Verifico se esiste la coppia nome-pass
    if( accountVer2(user, pass ) == 0)
    {
        if(write(sockfd,"OK",3) > 0)
        {// Accesso consentito
            return 0;
        }
    }
    else
    {
        if(write(sockfd,"KO",3) > 0)
        {// Accesso negato
            return 1;
        }
    }   
    perror(__FUNCTION__);
    return -1;
}
