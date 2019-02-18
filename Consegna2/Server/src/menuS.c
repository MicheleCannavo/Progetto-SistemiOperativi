/*//==============================================================================
 *  \author     Cannavo' Michele [046002210]
 *  \date       04/01/2019
//==============================================================================
 *  \file       funcPrint.c
 *  \brief      Funzioni per la stampa di informazioni di FILDERX
 *  \version    1.1
 *  \copyright  Licenza GPL 3.0
 *  \details    File contenente l Header per le funzione di stampa di FILDERX
*/
#include "Server.h"
#include "FILDERX.h"

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
            mainRead();
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