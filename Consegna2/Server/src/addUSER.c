/** **************************************************************************
 *  \file       addUser.c
 *  \version    1.0
 * 
 *  \brief      Funzione che permette la registrazione di un utente
 * 
 *  \param[in]  sockfd  riferito ad fd di una connessione TCP già stabilita
 *  
 *  \retval    -1   Funzione fallita
 *  \retval     0   Nome utente e password registrati
 *  \retval    -1   Nome utente e password non registrati
 * 
 *  \details    Questa funzione riceve da un client nome utente e password
 *              e li inserisce nel file degli utenti. 
 * 
 *****************************************************************************/
 #include "Server.h"

int addUser(int sockfd)
{  
// VARIABILI E INIZIALIZZAZIONE

    int  ID       = 0;  
    char user[MAX_CHAR_USER];
    char pass[MAX_CHAR_PASS];

    memset((char *)user,'\0', MAX_CHAR_USER);
    memset((char *)pass,'\0', MAX_CHAR_PASS);

// Inserisco i dati nel file e mando conferma
// \TODO Implementare controllo password [0-9/A-Z/a-z/!"£$%&/()=?^"]
// Popolo la struct USER_FILDERX  
// Lettura del nome utente

    srand(time(NULL));
    ID=rand()%998999+1;

    if(read(sockfd, user, MAX_CHAR_USER) <1 )
    {
        PRINTERR("Ricezione nome utente: ");
        return -1;
    }

// Lettura della password
    if(read(sockfd, pass, MAX_CHAR_PASS) <0 )
    {
        PRINTERR("Ricezione password: ");
        return -1;
    }

    sleep(1);

    if(accountVer(user) ==0 )
    {
    // Account esistente
        if(write(sockfd,"!!", 3) == 3)
        {
            return 1;
        }
    }
    
// Invio risultatto salvataggio account
    if(accountWrite(ID,user,pass)==0)
    {
        if(write(sockfd,"OK", 3) == 3)
        {
            return 0;
        }
    }
    else 
    {
        if(write(sockfd, "KO", 3) == 3)
        {
            return 1;
        }
    }

    PRINTERR("Registrazione account: ");
    return -1;    
}