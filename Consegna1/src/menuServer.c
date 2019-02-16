//==============================================================================
/// \author     Cannavo' Michele [046002210]
/// \date       04/01/2019
//==============================================================================
/// \file       funcPrint.c
/// \brief      Funzioni per la stampa di informazioni di FILDERX
/// \version    1.1
/// \copyright  Licenza GPL 3.0
/// \details    File contenente l Header per le funzione di stampa di FILDERX
//==============================================================================
// Copyright (c) 2018, Michele Cannavo'
// All rights reserved.
//
// This file is part of FILDERX.
//
//   funcPrint.c is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//   funcPrint.c is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with funcPrint.c. If not, see <http://www.gnu.org/licenses/>.
// ===============================================================================
#include "FILDERX.h"

int menuF()
{  
    int choose;

    if(settaggi==NULL)
    {
        errno=EINVAL;
        perror("Errore in menuF()");
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
