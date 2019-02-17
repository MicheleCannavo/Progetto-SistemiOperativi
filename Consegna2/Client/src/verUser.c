#include "Client.h"

int verUser(int sockid)
{
// VARIABILI E INIZZIALIZZAZIONE
    char user[MAX_CHAR_USER];
    char pass[MAX_CHAR_PASS];
    char buff[MAXBUF];

    memset(user, '\0', sizeof(user) );
    memset(pass, '\0', sizeof(pass) );
    memset(buff, '\0', sizeof(buff) );

// Invio comando VER_USER
    if (wwconf(sockid, "VER_USER") != 0)
    {
        PRINTERR("Invio comando: ");
        return -1;
    }

// Inserisco nome e password
    printf("Inserisci nome utente : ");
    fgets(user, MAX_CHAR_USER, stdin);
    user[MAX_CHAR_USER - 1] = '\0';
    if (user[strlen(user) - 1] == '\n')
        user[strlen(user) - 1] = '\0';

    printf("Inserisci password   : ");
    fgets(pass, MAX_CHAR_PASS, stdin);
    pass[MAX_CHAR_PASS - 1] = '\0';
    if (pass[strlen(pass) - 1] == '\n')
        pass[strlen(pass) - 1] = '\0';

// Invio nome utente
    if (write(sockid_Client, user, MAX_CHAR_USER) < 0)
    {
        PRINTERR("Nome utente: ");
        return -1;
    }

// Invio password
    if (write(sockid_Client, pass, MAX_CHAR_PASS) < 0)
    {
        PRINTERR("Password: ");
        return -1;
    }

// Ricevo esito
    if (read(sockid_Client, buff, 3) < 0)
    {
        return -1;
    }

// Verifico esito
    if (strncmp(buff, "OK", 3) == 0)
    {
        PRINTERR("ACCESSO CONSENTITO: ");
        return 0;
    }
    else if (strncmp(buff, "KO", 3) == 0)
    {
        PRINTERR("ACCESSO NEGATO: ");
        return 1;
    }
    else
    {
        return -1;
    }
}