/** ***************************************************************************
 * \file        iniSett.c 
 * \version     1.2
 * \date        20/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       Funzione di gestione dei settaggi del programma.
 * 
 * \details     Questa alloca la memoria e inizzializza con valori di default
 *              la struct che memorizza i settaggi del programma.
 * 
 * \retval  -1  Funzione Fallita
 * \retval   0  Successo
 *****************************************************************************/
#include "FILDERX.h"

int iniSett()
{
// Controllo che la variabile globale settaggi non sia già allocata
    if(settaggi != NULL )
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }

// Alloco la memoria
    settaggi = calloc(1, sizeof(SettFILDERX) );
    if(settaggi==NULL)
    {
        perror(__FUNCTION__);
        return -1;
    }

// Variabile per creare la directory di salvataggio
    char saveDir[PATH_MAX];
    memset((void*)saveDir, 0, PATH_MAX);
   
// Directory HOME come directory di lavoro di default.
// Controllo che non ecceda settaggi->dirWork
    if( strlen(getenv("HOME") ) <= PATH_MAX )
    {
        strncpy(settaggi->dirWork, getenv("HOME"), PATH_MAX-1);
        settaggi->dirWork[PATH_MAX-1]='\0';
    }
    else // Se la getenv(HOME) è troppo grande
    {
        strncpy(settaggi->dirWork, "/", 2);
    }
    
// Directory /HOME/Documenti come directory di salvataggio di default.
    strncpy( saveDir, settaggi->dirWork, PATH_MAX-1 );  
    saveDir[PATH_MAX-1]='\0';
    if( (strlen(saveDir)+11) <= PATH_MAX ) // per non eccedere PATH_MAX
        strncat( saveDir/* e' un Array*/, SAVEDIR, strlen(SAVEDIR) );
    strncpy(settaggi->dirSave, saveDir, PATH_MAX-1);
    settaggi->dirSave[PATH_MAX-1]='\0'; 

// Pattern generico per tutti
    strncpy(settaggi->patttFILDERX, PATTERN, PATT_MAX-1);
    settaggi->patttFILDERX[PATT_MAX-1]='\0'; 
 
// Setto il numero di core
    short int core=1;
    getNCore(&core);   
    settaggi->nCoreProcessor=core;

    return 0;
}