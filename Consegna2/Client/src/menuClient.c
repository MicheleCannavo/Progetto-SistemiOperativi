/** ***************************************************************************
 * \version     1.1
 * \date        04/01/2019
 * 
 * \brief   	Menu per il Client
 *
 * \retval   -1		Funzione fallita
 * \retval	  0		Connessione riuscita
 * 
 * \details         Queste funzioni contengono i menu' di gestione delle scelte
 *                  per operare con il Client.
 * 
 ******************************************************************************/
#include "Client.h"

int menCli()
{ 
// Ciclo per reiiterare il menu' 
// e non avere solo una scelta da eseguire
    do
    {
        int rep       = 0;
        int choose    = 0;

        do
        {
    // Menu'
            fflush(stdout);
            printf("\x1B[1;1H\x1B[2J");
            printf("\t\t\t***** MENU CLIENT *****\n\n");
            printf("\t\t=======================================\n");
            printf("\t\t1) Settaggi\n");
            printf("\t\t2) Avvia Connessione\n");
            printf("\t\t3) Esci\n");
        
    // Verifica se si e' reiterato il menu'
            if( rep++ )
            {     
                printf("\nScelta non corretta\nRiprova=");
                if(rep == INT_MAX)
                {
                    rep=1; 
                }
            }
            else
            {
                printf("\nScelta: ");
            }
        }
        while (isdigit_in(&choose) != 0 || ( choose<1 || choose>3) );

    // Scelta
        switch(choose)
        {
        
        // Gestione dei settaggi
        case 1:
            menSett();
            break;

        // Connessione al Server
        case 2:
            gestClient();
            break;
            
        // Uscita dal programma
        case 3:
            return 0;
        // Scelta non conforme
        default:
            break;
        }
    } while(1);
}

int menSett()
{
// Ciclo per reiiterare il menu' 
// e non avere solo una scelta da eseguire
    do
    {
        int rep       = 0;
        int choose    = 0;

        do
        {
    // Menu'
            fflush(stdout);
            printf("\x1B[1;1H\x1B[2J");
            printf("\t\t\t*****MENU CLIENT-SETTAGGI*****\n\n");
            printf("\t\t=======================================\n");
            printf("\t\t1) Visualizza Settaggi\n");
            printf("\t\t2) Cambia Settaggi\n");
            printf("\t\t3) Indietro\n");
    
    // Verifica se si e' reiterato il menu'
            if( rep++ )
            {     
                printf("\nScelta non corretta\nRiprova=");
                if(rep == INT_MAX)
                {
                    rep=1; 
                }
            }
            else
            {
                printf("\nScelta: ");
            }
        }
        while (isdigit_in(&choose) != 0 || ( choose<1 || choose>3) );

    // Scelta
        switch(choose)
        {

        // Stampa i settaggi del programma
        case 1:
            settPrint();
            printf("\nPremere [INVIO] per contniuare...\n");
            SBUFFER;
            break;

        // Modifica i settaggi del programma
        case 2:
            modSettCli();
            break;
            
        // Ritorna al menu' precedente
        case 3:
            return 0;
        
        // Scelta non prevista
        default:
            break;
        }
    } while(1);
    return 0;
}

int menAcc()
{
// Ciclo per reiiterare il menu' 
// e non avere solo una scelta da eseguire
    do
    {
        int rep    = 0;
        int choose = 0;
        int res    = 0; 
        do
        {
    // Menu'
        fflush(stdout);
        printf("\x1B[1;1H\x1B[2J");
        printf("\t\t\t*****MENU CLIENT FILDERX*****\n");
        printf("\t\t\t  (IP=%s - Porta=%u)\n\n",settaggi->IP_STRING,settaggi->nPort);
        printf("\t\t=======================================\n");
        printf("\t\t1) Registrati\n");
        printf("\t\t2) Accedi\n");
        printf("\t\t3) Chiudi Client\n");
    
    // Verifica se si e' reiterato il menu'
            if( rep++ )
            {     
                printf("\nScelta non corretta\nRiprova=");
                if(rep == INT_MAX)
                {
                    rep=1; 
                }
            }
            else
            {
                printf("\nScelta: ");
            }
        }
        while (isdigit_in(&choose) != 0 || ( choose<1 || choose>3) );
    
    // Scelta
        switch(choose)
        {
        // ADD_USER
        case 1:
            res= addUser(sockid_Client);
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
            else // res == 0
            {                
                printf("User Reistrato\n");
                printf("\nPremere [INVIO] per contniuare...\n");
                SBUFFER;
                break;
            }

        // VER_USER
        case 2:
            res= verUser(sockid_Client);
            if(res<0) 
            {
                printf("Errore nella convalida accesso\n");
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
        // Chiusura client
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
        int rep     = 0;
        int choose  = 0;
        do
        {
            fflush(stdout);
            printf("\x1B[1;1H\x1B[2J");
            printf("\t\t\t*****MENU CLIENT FILDERX*****\n");
            printf("\t\t\t  (IP=%s - Porta=%u)\n\n", settaggi->IP_STRING,  settaggi->nPort);
            printf("\t\t=======================================\n");
            printf("\t\t1) Invia File\n");
            printf("\t\t2) Richiedi File\n");
            printf("\t\t3) Preleva File\n");
            printf("\t\t4) Indietro\n");
    
    // Verifica se si e' reiterato il menu'
            if( rep++ )
            {     
                printf("\nScelta non corretta\nRiprova=");
                if(rep == INT_MAX)
                {
                    rep=1; 
                }
            }
            else
            {
                printf("\nScelta: ");
            }
        }
        while (isdigit_in(&choose) != 0 || ( choose<1 || choose>4) );

        switch(choose)
        {
    //SEND_FIL
        case 1:
            wwconf(sockid_Client,"SEND_FIL");
            sendFILE( sockid_Client);
            printf("\nPremere [INVIO] per contniuare...\n");
            SBUFFER;
            break;
            
        // REQ_FILE
        case 2:
            break;
        // RECV_FIL
        case 3:
            wwconf(sockid_Client,"RECV_FIL");
            recvFILE(sockid_Client,"",4);
            printf("\nPremere [INVIO] per contniuare...\n");
            SBUFFER;
            break;

        case 4:
            return 0;

        default:
            break;
        }
    } while(1);
}