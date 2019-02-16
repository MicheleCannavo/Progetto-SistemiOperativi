//==============================================================================
/// \author     Cannavo' Michele [046002210]
/// \date       04/01/2019
//==============================================================================
/// \file       funcPrint.c
/// \brief      Funzioni per la stampa di informazioni di FILDERX
/// \version    1.1
/// \copyright  Licenza GPL 3.0
/// \details    File contenente l Header per le funzione di stampa di FILDERX
#include "FILDERX.h"

int  isdigit_in( int* caracter )
{
    if( caracter == NULL )
        return -1;

    *caracter = getchar();
    if( isdigit( *caracter ) && getchar() == '\n' )
    {
        *caracter -= '0';
        return 0;
    }

   if(*caracter!=10)
        SBUFFER;
        
    *caracter = -1;
    return -1;
}
