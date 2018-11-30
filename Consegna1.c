//==============================================================================
// Cannavo' Michele 046002210
// Anno 2018/2019
// Sistemi Operativi
//==============================================================================
// Progettino - V1.0
// Licenza GPL 3.0
//
// Consegna 1
//==============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h> // stat()
#include <errno.h>
#include <dirent.h> // getwd(), chdir()

///// Variabili globali /////
long nCore=0;
char workPath[PATH_MAX]="~/";

///// PROTOTIPI ////
int getNCore(long*);
int testPath(char*);

#define DEBUG_ 

int main(int argc,char* argv[])
{
// Stringa per memorizzare l'attuale directory
    char* currDir=NULL;

// Testo che ci sia il path come argomento,
// in caso di altri argomenti modifico. 
    if (argc!=2)
    {
        errno=EINVAL;
        perror("Argomenti non validi\n");
        exit(EXIT_FAILURE);
    }

#ifdef DEBUG_
printf("directory attuale= [%s]\n",getcwd(NULL,0));
#endif
 
// Test directory
    if(!testPath(argv[1]))
    {  
        printf("directory di lavoro= [%s]\nMi sposto su di essa...\n",argv[1]);  
        if( (currDir=getcwd(NULL,0))==0 ) // Salvo l'attuale directory e...
            return(EXIT_FAILURE);
                
        if( chdir(argv[1]) )
            return(EXIT_FAILURE);        // ..mi sposto in quella di lavoro...
       
       strncpy(workPath, argv[1], PATH_MAX);
       printf("Nuova directory di lavoro= [%s]\n",workPath); 
    }
    
    else
    {
        printf("directory non trovata\n");
        exit(EXIT_FAILURE);
    }
    
    if(getNCore(&nCore))    
    {
        
        printf("Rilevati %ld Core\n",nCore);
    }
    else
    {
        printf("Impossibile reperire numero di core\n");
        exit(EXIT_FAILURE);
    }
        

    if( chdir( currDir ) )
        return(EXIT_FAILURE); // Ritorno alla directory iniziale
        
#ifdef DEBUG_
printf("Ritorno alla directory =%s\n",getcwd(NULL,0));
#endif
    
    free( currDir );      // Libero la memoria allocata con getcwd()
    currDir = NULL;         


    return(EXIT_SUCCESS);
}

//==============================================================================
//==============================================================================
/// @func getNCore
/// @brief La funzione legge dal file /proc/cinfo l'informazione richiesta
/// @return Numero di core del processore
int getNCore(long *nCore)
{
// Per test, da implementare con la lettura del file apposito
    *nCore=2;
}

/// @func getNCore()
/// @param stringa contenete il Path
int testPath(char* wPath)
{
struct stat path;

    if (stat(wPath, &path) == 0 && S_ISDIR(path.st_mode))
    {
        return(EXIT_SUCCESS);
    }
    else
    {
        return(EXIT_FAILURE);
    }

}

