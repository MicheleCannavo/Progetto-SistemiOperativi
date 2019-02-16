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
