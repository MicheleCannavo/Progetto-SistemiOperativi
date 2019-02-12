//==============================================================================
/// \author     Cannavo' Michele [046002210]
/// \date       04/01/2019
//==============================================================================
/// \file       funcPrint.c
/// \brief      Funzioni per la stampa di informazioni di FILDERX
/// \version    1.1
/// \copyright  Licenza GPL 3.0
/// \details    File contenente l Header per le funzione di stampa di FILDERX
#include "Client.h"

int menCli()
{
    if(settaggi==NULL)
    {
        errno=EINVAL;
        perror("Errore in menuServer()");
        return -1;
    }

    do
    {
    int rep=0;
    int choose=0;
        do
        {
            printf("\x1B[1;1H\x1B[2J");
            printf("\t\t\t***** MENU CLIENT *****\n\n");
            printf("\t\t=======================================\n");
            printf("\t\t1) Settaggi\n");
            printf("\t\t2) Avvia Connessione\n");
            printf("\t\t3) Esci\n");
            if( rep++ )
                printf("\nScelta non corretta\nRiprova=");
            else
                printf("\nScelta: ");
        }
        while (isdigit_in(&choose) != 0 || ( choose<1 || choose>3) );

        switch(choose)
        {
        case 1:
            menSett();
            break;

        case 2:
            gestClient();
            break;
            
        case 3:
            

            break;
            return 0;

        default:
            break;
        }
    } while(1);
}

int menSett()
{
    do
    {
    int rep=0;
    int choose=0;
        do
        {
        fflush(stdout);
            printf("\x1B[1;1H\x1B[2J");
            printf("\t\t\t*****MENU CLIENT-SETTAGGI*****\n\n");
            printf("\t\t=======================================\n");
            printf("\t\t1) Visualizza Settaggi\n");
            printf("\t\t2) Cambia Settaggi\n");
            printf("\t\t3) Indietro\n");
            if( rep++ )
                printf("\nScelta non corretta\nRiprova=");
            else
                printf("\nScelta: ");
        }
        while (isdigit_in(&choose) != 0 || ( choose<1 || choose>3) );

        switch(choose)
        {
        case 1:
            settPrint(STDOUT_FILENO);
            printf("\nPremere [INVIO] per contniuare...\n");
            SBUFFER;
            break;

        case 2:
            modSettCli();
            break;
            
        case 3:
            return 0;
        
        default:
            break;
        }
    } while(1);
    return 0;
}

int menAcc()
{
    do
    {
    int rep=0;
    int choose=0;
        do
        {
            printf("\x1B[1;1H\x1B[2J");
            printf("\t\t\t*****MENU CLIENT-ACCONUT*****\n");
            printf("\t\t\t  (IP=%s - Porta=%u)\n",settaggi->IP_STRING,settaggi->nPort);
            printf("\t\t=======================================\n");
            printf("\t\t1) Registrati\n");
            printf("\t\t2) Accedi\n");
            printf("\t\t3) Indietro\n");
            if( rep++ )
                printf("\nScelta non corretta\nRiprova=");
            else
                printf("\nScelta: ");
        }
        while (isdigit_in(&choose) != 0 || ( choose<1 || choose>3) );
        int res;

        switch(choose)
        {
        case 1:
            res= addUser();
            if(res<0)
            {
                printf("Errore nella registrazione \n");
                printf("\nPremere [INVIO] per contniuare...\n");
                SBUFFER;
                break;
            }
            else if (res>0)
            {        
                printf("Tentativo di registrazione fallito\n");
                printf("\nPremere [INVIO] per contniuare...\n");
                SBUFFER;
                break;
            }
            else //res == 0
            {
                printf("\nPremere [INVIO] per contniuare...\n");
                SBUFFER;
                break;
            }

        case 2:
            res= verUser();
            if(res<0) 
            {
                printf("Errore nel Server\n");
                printf("\nPremere [INVIO] per contniuare...\n");
                SBUFFER;
                break;
            }
            else if(res>0)
            {
                printf("Tentativo di accesso fallito\n");
                printf("\nPremere [INVIO] per contniuare...\n");
                SBUFFER;
                break;
            }
            else 
            {
                menFilderx();
                break;
            }

        case 3:
            closeSocket();
            return 0;

        default:
            break;
        }
    } while(1);
}

int menFilderx()
{
    do
    {
    int rep=0;
    int choose=0;
        do
        {
        fflush(stdout);
            printf("\x1B[1;1H\x1B[2J");
            printf("\t\t\t*****MENU CLIENT FILDERX*****\n\n");
            printf("\t\t=======================================\n");
            printf("\t\t1) Invia File\n");
            printf("\t\t2) Preleva File\n");
            printf("\t\t3) Indietro\n");
            if( rep++ )
                printf("\nScelta non corretta\nRiprova=");
            else
                printf("\nScelta: ");
        }
        while (isdigit_in(&choose) != 0 || ( choose<1 || choose>3) );

        switch(choose)
        {
        case 1:
        
            printf("\nPremere [INVIO] per contniuare...\n");
            SBUFFER;
            break;
            
        case 2:
            printf("\nPremere [INVIO] per contniuare...\n");
            SBUFFER;
            break;

        case 3:
            return 0;

        default:
            break;
        }
    } while(1);
}