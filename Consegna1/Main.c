/// \cond
//==============================================================================
/// \author  Cannavo' Michele [046002210]
/// \date    07/12/2018
//==============================================================================
/// \file  main.c
/// \brief Main del programma FILDERX.Consegna1
/// \version 1.01
/// \copyright GNU GPL 3.0
/// \details Main che gestisce il programma.

#include "FILDERX.h"

int main(int argc, char* argv[])
{
    MotoreFILDER();
    printList(headTList,"*r.c");
    freeL(&headTList);
    return 0;
}
/// \endcond
