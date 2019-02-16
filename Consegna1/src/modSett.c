/** ***************************************************************************
 * \file        modSett.c 
 * \version     1.0
 * \date        18/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       Funzione di gestione dei settaggi del programma.
 * 
 * \details     Questa funzione permette la modifica manuale delle impostazioni
 *              del programma. Per ogni impostazioni prima n stampa il valore, 
 *              poi ne chiede la modifica. Se si da un input vuoto o sbagliato,
 *              non modifica l'impostazione
 *
 * \retval  -1      errore nei parametri di input
 * \retval   0      Funzione Fallita/L'elemento Non e' una cartella
 *****************************************************************************/
#include "FILDERX.h"

int modSett()
{
// Verifica argomenti in input
    if(settaggi==NULL)  
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }

    char *workDir = (char*)calloc(PATH_MAX,sizeof(char) );
    if(workDir==NULL )
    {
        errno=ENOMEM;
        return -1;
    }
    
    char *saveDir = (char*)calloc(PATH_MAX,sizeof(char) );
    if(saveDir==NULL)
    {
        free(workDir);
        errno=ENOMEM;
        return -1;
    }
    
    char *pattern = (char*)calloc(PATT_MAX,sizeof(char) );
    if(pattern==NULL)
    {
        free(workDir);
        free(saveDir);
        errno=ENOMEM;
        return -1;
    }

    printf("\x1B[1;1H\x1B[2J");
    printf("\t\t           Modifica i Settaggi\n");
    printf("\t\t---- Invio vuoto per non modificare ---\n\n");

//================================ CARTELLA DI LAVORO ==================================
    printf("L'attuale directory da setacciare è: %s\n",settaggi->dirWork);
    printf("---> Cambiarla con: ");
    if(fgets(workDir, PATH_MAX,stdin) != NULL )
    {
        if( workDir[strlen(workDir)-1]=='\n' )
        workDir[strlen(workDir)-1]='\0';

        if( (workDir[0]!='\n' && workDir[0]!='\0') && testPath(workDir)==0 )
        {
            strncpy(settaggi->dirWork, workDir, PATH_MAX-1);
            settaggi->dirWork[PATH_MAX-1]='\0';

            if(settaggi->dirWork[strlen(settaggi->dirWork)-1]=='\n')
                settaggi->dirWork[strlen(settaggi->dirWork)-1]='\0';
        }
    }

//================================ CARTELLA DI SALVATAGGIO =============================
    printf("\nL'attuale directory per il salvataggio file è: %s\n",settaggi->dirSave);
    printf("Cambiarla con: ");
    fgets(saveDir, PATH_MAX, stdin);

    if( saveDir[strlen(saveDir)-1]=='\n' )
        saveDir[strlen(saveDir)-1]='\0';

    if( (saveDir[0]!='\n' && saveDir[0]!='\0') && testPath(saveDir)==0 )
    {
        strncpy(settaggi->dirSave, saveDir, PATH_MAX-1);
        settaggi->dirSave[PATH_MAX-1]='\0';

        if(settaggi->dirSave[strlen(settaggi->dirSave)-1]=='\n')
            settaggi->dirSave[strlen(settaggi->dirSave)-1]='\0';
    }

//================================ PATTERN DI RICERCA ==================================
    printf( "\nL'attuale pattern di ricerca file è: %s\n",settaggi->patttFILDERX);
    printf( "Cambiarlo con: ");
    fgets(pattern, PATT_MAX, stdin);

    if( pattern[strlen(pattern)-1]=='\n' )
        pattern[strlen(pattern)-1]='\0';

    if( (pattern[0]!='\n' && pattern[0]!='\0') != 0 )
    {
        strncpy(settaggi->patttFILDERX, pattern, PATT_MAX-1);
        settaggi->patttFILDERX[PATT_MAX-1]='\0';

        if(settaggi->patttFILDERX[strlen(settaggi->patttFILDERX)-1]=='\n')
            settaggi->patttFILDERX[strlen(settaggi->patttFILDERX)-1]='\0';
    }

    free(workDir);
    free(saveDir);
    free(pattern);
    workDir=saveDir=pattern=NULL;
    return 0;
}
