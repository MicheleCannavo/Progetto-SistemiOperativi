/**  ***************************************************************************
 * \file        menuS.c
 * \version     3.2
 * \date        18/02/2019
 * 
 * \brief      Menu per il SERVER.
 * 
 *  
 * \retval    -1   Funzione fallita.
 * \retval     0   Input int.
 * \retval     1   Input non conforme. 
 * 
 * \details     Queste funzione gestiscono un piccolo menu' lato SERVER 
 *              fino all'avvio connessio
 * 
 *****************************************************************************/
#include "Server.h"

int menServ()
{
    do
    {
    int rep=0;
    int choose=0;
        do
        {
        fflush(stdout);
            printf("\x1B[1;1H\x1B[2J");
            printf("\t\t\t*****MENU SERVER*****\n\n");
            printf("\t\t=======================================\n");
            printf("\t\t1) Settaggi\n");
            printf("\t\t2) Avvia Server\n");
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
            gestConn();
            break;
            
        case 3:
            return 0;

        default:
            break;
        }
    } while(1);
    return 0;
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
            printf("\t\t\t*****MENU SERVER-SETTAGGI*****\n\n");
            printf("\t\t=======================================\n");
            printf("\t\t1) Visualizza Settaggi\n");
            printf("\t\t2) Cambia Settaggi \n");
            printf("\t\t3) Visualizza account registrati\n");
            printf("\t\t4) Visualizza lista dei file\n");
            printf("\t\t5) Indietro\n");
            if( rep++ )
                printf("\nScelta non corretta\nRiprova=");
            else
                printf("\nScelta: ");
        }
        while (isdigit_in(&choose) != 0 || ( choose<1 || choose>5) );

        switch(choose)
        {
        case 1: // Stampare settaggi
            settPrint(STDOUT_FILENO);
            printf("\nPremere [INVIO] per contniuare...\n");
            SBUFFER;
            break;

        case 2:// Modificare settagi
            modSettServ();
            printf("\nPremere [INVIO] per contniuare...\n");
            SBUFFER;
            break;
         
         case 3:// Lista utenti
            accountRead();
            printf("\nPremere [INVIO] per contniuare...\n");
            SBUFFER;
            break;
         
         case 4:// Lista file
            printList(headTList, "*");
            printf("\nPremere [INVIO] per contniuare...\n");
            SBUFFER;
            break;
            
        case 5:// Esci
            return 0;
        
        default:
            break;
        }
    } while(1);
    return 0;
}