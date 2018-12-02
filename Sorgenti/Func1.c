#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // getwd(), chdir()
#include <string.h>
#include <sys/stat.h> // stat()
#include <errno.h>
#include <dirent.h> // readdir()
//==============================================================================
//==============================================================================
/// \brief  La funzione legge dal file /proc/cinfo l'informazione richiesta
/// \param  *nCore Numero di core di un processore
/// \return Successo della funzione
/// \retval EXIT_SUCCESS Riuscita della funzione
/// \retval EXIT_FAILURE Insucesso della funzione
int getNCore(int *nCore)
{
    char tmpCore[PATH_MAX];
    int count=0;
    FILE *fp;
    
    fp=fopen("/proc/cpuinfo","r");
    if(fp==NULL)
    {
	    perror("Nn è stato possibile leggere il file");
	    exit(EXIT_FAILURE);
    }

    while( fgets(tmpCore,256,fp) )
    {
        if(!strncmp(tmpCore,"cpu cores",9) )
        {
            strtok(tmpCore,":");
            count=atoi(strtok(NULL,":"));
#ifdef DEBUG_
            printf("D)-Numero Core %d\n",count);
#endif
            break;
        }     
    }
     if(count==0) // Non trovo le info
        *nCore=1;
     else
        *nCore=count;
   
   return count;   
}

/// \brief  Verifica se una stringa corrisponda ad una directory
/// \param  *wPath stringa contenete il Path
/// \return Successo della funzione
/// \retval EXIT_SUCCESS Riuscita della funzione
/// \retval EXIT_FAILURE Insucesso della funzione
int testPath(char* wPath)
{
    struct stat path;

    if ( stat(wPath, &path)==0 && S_ISDIR(path.st_mode) )
    {
        return(EXIT_SUCCESS);
    }
    else
    {
        return(EXIT_FAILURE);
    }
}
