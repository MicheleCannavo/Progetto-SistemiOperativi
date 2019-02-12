/** ***************************************************************************
 * \file       wwconf.c
 * \version    1.0
 * 
 * \brief       Scrittura comando con conferma
 * 
 * \param[in]   sockid  File descriptor della connessione
 * \param[out]  comm[9] Buffer che continene il comando
 *  
 * \retval      -1      FAILURE
 * \retval       0      SUCCESS
 *
 * \details     Questa funzione invia un comando tramite un socket, dopo attende
 *              la conferma della lettura. Serve per sincronizzare e verificare
 *              che server e client eseguano lo stesso comndo.
 *****************************************************************************/
#include "Client.h"

int wwconf(int sockid, const char comm[9])
{ 
// VARIABILI E INIZZIALIZZAZIONI
    char risp[3];
    memset(risp, '\0', 3);

// Invio i comando
    if(send(sockid, comm, 9, 0) != 9)
    {
        PRINTERR("Invio comando: ");
        return -1;
    }
// Imposto un timeout per riceere conferma
    alarm(TIMEOUT);

// Ricevo risposta
    if(recv(sockid, risp, 3, MSG_WAITALL) != 3)
    {
        return -1;
    }
    
// Disattivo timeout
    alarm(0);

// Verifico risposta
    if(strncmp(risp, "OK", 3) == 0)
    {
        return 0;
    }
    else if(strncmp(risp, "KO", 3) == 0)
    {
        PRINTERR("Comando non valido: ");
        return 1;
    }
    else
    {
        PRINTERR("Impossibile inviare comando: ");
        return -1;
    }
}