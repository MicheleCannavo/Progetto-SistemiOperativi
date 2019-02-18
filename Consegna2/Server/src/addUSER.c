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
// VARIABILI E INIZZIALIZZAZIONE
    char            user[MAX_CHAR_USER];
    char            pass[MAX_CHAR_PASS];
    int             userfile            =0;
    int             test                =0;
    USER_FILDERX    input1;

    memset((char *)user,'\0', MAX_CHAR_USER);
    memset((char *)pass,'\0', MAX_CHAR_PASS);
    memset((struct accounting *)&input1, 0,
            sizeof(struct accounting) );

// Lettura del nome utente
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

// Inserisco i dati nel file e mando conferma
    // \TODO Implementare controllo esistenza utente
    // \TODO Implementare controllo password [0-9/A-Z/a-z/!"£$%&/()=?^"]
// Popolo la struct USER_FILDERX    
    srand(time(NULL));
    input1.ID=rand()%977+1;
    
    strncpy(input1.user, user, MAX_CHAR_USER);
    input1.user[MAX_CHAR_USER-1]='\0'; 
    
    strncpy(input1.pass, pass, MAX_CHAR_PASS);
    input1.pass[MAX_CHAR_PASS-1]='\0';   
    
// Open file per la scrittura
    userfile = open ("userlist.dat", O_WRONLY|O_CREAT|O_APPEND, S_IRWXU | S_IRWXO| S_IRWXG);
    if (userfile == -1)
    {
        perror(__FUNCTION__);
        return -1;
    }

// Scrittura sul file dell'account
    if(  write ( userfile, (struct accounting*)&input1, sizeof(struct accounting)) > 0 )
    {
        close(userfile);
        test=1;
    }
    else
    {
        close(userfile);
        return -1;
    }
    
// Invio risultatto salvataggio account
    if(test==1)
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