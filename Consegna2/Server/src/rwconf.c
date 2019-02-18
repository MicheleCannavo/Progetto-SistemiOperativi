 /** **************************************************************************
 * \file       rwconf.c
 * \version    1.0
 * 
 * \brief      Lettura comando con conferma
 * 
 * \param[in]    sockid     File descriptor del socket
 * \param[out]  *comm       Buffer di almeno 9 caratteri per salvare il comando
 *  
 * \retval      -1      FAILURE
 * \retval       0      SUCCESS 
 *
 * \details     Questa funzione legge un comando da un socket e dopo invia la
 *              conferma della lettura. Serve per sincronizzare server e client.
 ******************************************************************************/
#include "Server.h"
/**
 * \brief  Array di stringhe con i comandi 
 */
const char *_COMMAND_[]={
    "VER_USER",
    "ADD_USER",
    "RES_FILE",
    "REQ_FILE",
    "SEND_FIL",
    "RECV_FIL",
    "SHELL_LN"
};

int rwconf(int sockid, char *comm)
{
// VARIABILI E INIZZIALIZZAZIONI
    int test=0;

// Ricezione comando
int t=recv(sockid, comm, 9, MSG_WAITALL);
    if(t != 9 )
    {
        printf("%s-%d\n\n",comm,t);
        PRINTERR("Invio comando: ");
        return -1;
    }

// Verifica comando   
    for(short i=0;i<N_COMM;i++)
    {// ciclo tutto _COMMAND_ per verificare se il comando e' codificato
        if(strncmp(comm, _COMMAND_[i], 9) == 0)
        {
            test=1; // Test vero
            break; 
        }
    }

// Se test e' VERO
    if(test==1)
    {
        if(send(sockid,"OK", 3, 0) == 3)
        {
            return 0;
        }
        else
        {
            PRINTERR("Verifica comando: ");
            memset(comm,'\0',9);
            return -1;
        }
    }
// Se FALSO
    else
    {
        if(send(sockid,"KO", 3,0) == 3)
        {
            memset(comm,'\0',9);
            errno=ENOSYS;// Command not implementated
            PRINTERR("Verifica comando: ");
            return 1;
        }
    }
    PRINTERR("Verifica comando: ");
    memset(comm,'\0',9);
    return -1;
}