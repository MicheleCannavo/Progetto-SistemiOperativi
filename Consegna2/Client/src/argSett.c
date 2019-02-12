//============================================================================
/// \author     Cannavo' Michele [046002210]
/// \date       07/12/2018
//============================================================================
/// \file       argSet.c
/// \brief      Motore di ricerca ricorsiva di FILDERX
/// \version    1.2
/// \copyright  GNU LGPL 3.0
/// \details    Motore che ricerca, con le impostazioni date, File e cartelle 
///             dentro una directory.
//==============================================================================
// Copyright (c) 2018, Michele Cannavo'
// All rights reserved.
//
// This file is part of FILDERX.
//
//   argSet.c is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//   argSet.c is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with argSet.c. If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
#include "Client.h"

// La funzione inserisce gli argomenti da linea di comando
// Verificato nel MyMain che 1 >= argc <= 2 
int argSett(int argc, char *argv[])
{
    int p=0;
    switch(argc)
    {
        case 1:// Parametri di default
            return 0;

        case 2:// Porta da riga di comando
            p=atoi(argv[1]);
            if(p<1023 || p>65535) 
            {
                errno=EINVAL;
                perror("Errore argSett");
                return -1;
            }
            settaggi->nPort=p;
            return 0;

        default:// troppi  argomenti-
            errno=EINVAL;
            perror("Errore argSett"); 
            return -1;
   }
}