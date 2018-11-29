//==============================================================================
// Cannavo' Michele 046002210
//==============================================================================
// Progettino - V1.0
//
// Consegna 1
//==============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h> // stat()
#include <errno.h>

//// Variabili globali, non se serviranno come tali

// Numero di core del processore
long nCore=0;

// Cartella di lavoro inizzializzata su HOME 
char *workPath="\\HOME";

int getNCore(long*);
int testPath(char*);

int main(int argc,char* argv[])
{
    
// Testo che ci sia il path come argomento,
// in caso di altri argomenti modifico. 
    if (argc!=2)
    {
        errno=EINVAL;
        perror("Argomenti non validi\n");
        exit(EXIT_FAILURE);
    }
    
// Test Cartella
    if(!testPath(argv[1]))
    {
        printf("Cartella Trovata\n");
    }
    else
    {
        printf("Cartella non trovata\n");
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
    

    return(EXIT_SUCCESS);
}


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

