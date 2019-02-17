/** **************************************************************************
 *  \file       addUser.c
 *  \version    1.0
 * 
 *  \brief      Funzione che permette la registrazione di un utente
 * 
 *  \details    Questa funzione riceve da un client nome utente e password
 *              e li inserisce nel file degli utenti. 
 * 
 *  \param[in]  sockfd  riferito ad fd di una connessione TCP già stabilita
 *  
 *  \retval    -1   Funzione fallita
 *  \retval     0   Nome utente e password registrati
 *  \retval    -1   Nome utente e password non registrati
 *****************************************************************************/
#include "Client.h"

int addUser(int sockid)
{       
// VARIABILI E INIZIALIZZAZIONI
    char user1[MAX_CHAR_USER];
    char pass1[MAX_CHAR_PASS];
    char pass2[MAX_CHAR_PASS];
    char risp[3];
    int s   = 0;

    memset(user1, '\0', sizeof(user1) );
    memset(pass1, '\0', sizeof(pass1) );
    memset(pass2, '\0', sizeof(pass2) );
    memset( risp, '\0', 3 );

// Invio Comando ADD_USER
    if(wwconf(sockid, "ADD_USER") != 0)
    {
        PRINTERR("Invio comando:");
        return 1;
    }

// Digitazione nome e pass
    printf("Digita il Nome Utente: ");
    fgets(user1, MAX_CHAR_USER-1, stdin);
    user1[MAX_CHAR_USER-1]='\0';    
    if(user1[strlen(user1)-1]=='\n')
        user1[strlen(user1)-1]='\0';
    
    do{
        if(s)
            printf("Le password non corrispondono. Riprovare");
        s++;
            
        printf("Digita password: ");
        fgets(pass1,MAX_CHAR_PASS,stdin);
        pass1[MAX_CHAR_USER-1]='\0';    
        if(pass1[strlen(pass1)-1]=='\n')
            pass1[strlen(pass1)-1]='\0';
    
        printf("Ripeti password: ");
        fgets(pass2,MAX_CHAR_PASS,stdin);
        pass2[MAX_CHAR_USER-1]='\0';    
        if(pass2[strlen(pass2)-1]=='\n')
            pass2[strlen(pass2)-1]='\0';
        // Se corrispondono
        if( strncmp(pass1, pass2, MAX_CHAR_PASS ) == 0)
        {
            break;
        }
        if(s>3)
        {
            return 1;
        }
    
    }while( 1 );

// Invia nome
    if(write(sockid_Client, user1, MAX_CHAR_USER) <0)
    {
        perror(__FUNCTION__);
        return -1;
    }    

// Invia password
    if(write(sockid_Client, pass1, MAX_CHAR_USER) <0)
    {
        perror(__FUNCTION__);
        return -1;
    }    

// Ricevi e verifica conferma o meno
    if(read(sockid_Client,risp, 3) > 0)
    {
        if(strncmp(risp, "OK", 3) == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    perror(__FUNCTION__);
    return -1;
}