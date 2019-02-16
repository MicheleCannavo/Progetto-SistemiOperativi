/** ***************************************************************************
 * \version     1.1
 * \date        27/12/2019
 * 
 * \brief      Funzioni per la stampa di informazioni di FILDERX
 * 
 * \details    Memu' di utilizzo de programma 
 * 
 *****************************************************************************/ 
#include "FILDERX.h"

int menuF()
{  
    int choose;

    if(settaggi==NULL)
    {
        errno=EINVAL;
        return -1;
    }

    do
    {
    unsigned short rep=0;
    choose=0;
        do
        {
            fflush(stdout);
            printf("\x1B[1;1H\x1B[2J");
            printf("\t\t\t*****Consegna1 FILDERX*****\n\n");
            printf("\t\t=======================================\n");
            printf("\t\t1) Visualizzare i settaggi\n");
            printf("\t\t2) Modificare i settaggi\n");
            printf("\t\t3) Ricercare nella cartella impostata\n");
            printf("\t\t4) Visualizzare Lista di file\n");
            printf("\t\t5) Visualizzare Lista di file dettagliata\n");
            printf("\t\t6) Esci\n");
            if( rep++ )
            {
               printf("\nScelta non corretta\nRiprova=");
                if(rep == USHRT_MAX -1)
                    rep=1; // Evita overflow
            }

            else
                printf("\nScelta: ");
        }
        while (isdigit_in(&choose) != 0 || ( choose<1 || choose>6) );

        switch(choose)
        {
        case 1:
            printSett(STDOUT_FILENO);
            printf("\nPremere [INVIO] per contniuare...\n");
            SBUFFER;
            break;

        case 2:
            modSett(settaggi);
            printf("\nPremere [INVIO] per contniuare...\n");
            SBUFFER;
            break;

        case 3: 
            printf("\nAttendere ricerca in corso...");  
            MotoreFILDER(*settaggi);        
            printf("\rRicerca finita - Premere [INVIO] per contniuare...");
            SBUFFER;
            break;

        case 4:
            printList(headTList,STDOUT_FILENO);
            printf("\nPremere [INVIO] per contniuare...");
            SBUFFER;
            break;

        case 5:
            printDetList(headTList,STDOUT_FILENO);
            printf("\nPremere [INVIO] per contniuare...");
            SBUFFER;
            break;
            
        case 6:
            return(0);

        default:
            break;
        }
    } while(1);
    return 0;
}
