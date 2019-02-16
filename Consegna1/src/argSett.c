/** ***************************************************************************
 * \file        argSett.c 
 * \version     1.0
 * 
 * \brief       Funzione di gestione dei settaggi del programma.
 * 
 * \details     La funzione inserisce i CLA (Commands Line Arguments)
 *              Verifica che gli argomenti siano 1 o 2 (più argv[0] che identi-
 *              fica il nome del programma).
 * 
 * \param[in]   argc    Numero di CLA  
 * \param[in]   argv    Array contenente i CLA
 *
 * \retval  -1  Funzione Fallita
 * \retval   0  Successo
 *****************************************************************************/
#include "FILDERX.h"

int argSett(int argc, char**argv)
{
// Verifica input
    if(argc<2 || argc>3 || argv==NULL)
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }

// Verifica argv[1]
    if(testPath(argv[1]) != 0) 
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }    

    strncpy(settaggi->dirWork, argv[1], PATH_MAX-1);
    settaggi->dirWork[PATH_MAX-1]='\0'; 

// Se si hanno 3 CLA
    if(argc==3) // Patter
    {
        if(strlen(argv[2]) >= PATT_MAX) 
        {
            perror(__FUNCTION__);
            return -1;
        }    
        // anche una semplice strcpy andava bene qui visto che la dimensione è stata verificata prima
        strncpy(settaggi->patttFILDERX, argv[2], PATT_MAX-1);
        settaggi->patttFILDERX[PATT_MAX-1]='\0';
    }
    return 0;
}