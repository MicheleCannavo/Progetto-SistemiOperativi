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
#include <unistd.h> // getwd(), chdir()
#include <string.h>
#include <sys/stat.h> // stat()
#include <errno.h>
#include <dirent.h> // readdir()

///// Variabili globali /////
long nCore=0;
char workPath[PATH_MAX]="~/";

///// PROTOTIPI ////
int getNCore(long*);
int testPath(char*);

/// \def DEBUG_
/// Macro per un primo debug
#define DEBUG_ 


/// \cond
int main(int argc,char* argv[])
{

    char* currDir=NULL;

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
        if( (currDir=getcwd(NULL,0))==0 ) 
            return(EXIT_FAILURE);
                
        if( chdir(argv[1]) )
            return(EXIT_FAILURE);       
                   
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
        

 //   if( chdir( currDir ) )
   //     return(EXIT_FAILURE); 
        
#ifdef DEBUG_
printf("Ritorno alla directory =%s\n",getcwd(NULL,0));
#endif
    
    free( currDir );      
    // Libero la memoria allocata con getcwd()
    currDir = NULL;         


    return(EXIT_SUCCESS);
}

/// \endcond

//==============================================================================
//==============================================================================
/// \brief  La funzione legge dal file /proc/cinfo l'informazione richiesta
/// \param  *nCore Numero di core di un processore
/// \return Successo della funzione
/// \retval EXIT_SUCCESS Riuscita della funzione
/// \retval EXIT_FAILURE Insucesso della funzione
int getNCore(long *nCore)
{
// Per test, da implementare con la lettura del file apposito
    *nCore=2;
}


/// \brief  Verifica se una stringa corrisponda ad una directory
/// \param  wPath stringa contenete il Path
/// \return Successo della funzione
/// \retval EXIT_SUCCESS Riuscita della funzione
/// \retval EXIT_FAILURE Insucesso della funzione
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

