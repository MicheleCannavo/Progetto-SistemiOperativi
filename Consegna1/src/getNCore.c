/** ***************************************************************************
 * \version     1.0
 * \date        17/12/2018
 * 
 * \brief       Funzione di gestione dei settaggi del programma.
 * 
 * \details     Questa funzione recupera il numero di core fisici nel file
 *              "/proc/cpuinfo" alla voce sibilings. Si usa la prima voce
 *              che si riscontra, essendo tutte uguali tra loro.
 *
 * \retval  -1      Errore nei parametri di input
 * \retval   0      Numero core recuperati
 *****************************************************************************/
#include "FILDERX.h"

int getNCore(short *nCore)
{   
// VARIABILI E INIZIALIZZAZIONI
    char  tmpCore[20];
    int   countC     =1;
    FILE *fd;
    memset(tmpCore, 0, 20);

// Verifica argomenti
    if(nCore==NULL)
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }

// Apertura file "/proc/cpuinfo"
    fd=fopen("/proc/cpuinfo", "r");
    if(fd == NULL  )
    {
        perror(__FUNCTION__);
        return -1;
    }

// Scorimento righe "/proc/cpuinfo"
    while( fgets(tmpCore, 19, fd) != NULL )
    {
    
    // Se trovo corrispondenza recupero i numero di core e esco dal while
        if(memcmp(tmpCore, "siblings", 8) == 0 )
        {
            strtok(tmpCore,":");
            countC=atoi(strtok(NULL,":"));
            break;
        }
        memset(tmpCore, 0, 20);
    }
    // Sia se trovo corrispondenza, sia se non ne trovo
    // memorizzo countC sulla variabile interessata
    // in quanto countC era inizializzata comunque a 1
    // che e' il minimo numero di core nella pratica
    *nCore=countC;

// Chiusura file e fine funzione
    fclose(fd);
    fd=NULL;
    return 0;
}