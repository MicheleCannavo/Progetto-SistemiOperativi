#include "FILDERX.h"

/** ***************************************************************************
 * \version     1.0
 * \date        22/12/2018
 * 
 * \brief       Funzione di  stampa per la lista concatenata.
 * 
 * \details     Questa funzione stampa tutti gli elementi di una listFILDERX
 *              e' possibile stampare attraverso un qualsiasi file descriptor 
 *              di un file precedentemente aperto.
 * 
 * \param[in]   *head       Puntatore alla lista da stampare
 * \param[in]    fdStream   Fd che identifica il file in cui stampare
 * 
 * \retval  -1      puntatore ad una lista di file e cartelle
 * \retval   0      Funzione Fallita/L'elemento Non e' una cartella
 ******************************************************************************/
int printList(listFILDERX *head,char *pattern)
{
    listFILDERX *tmp=head;

// Lista vuota
    if(tmp==NULL)
    {
        printf( "Non ci sono elementi nella lista");
        return -1;
    }

// Lista piena
    while(tmp->next!=NULL)
    {
        if(tmp->elemento.absPath[0] == '/' && 
                fnmatch(pattern,basename(tmp->elemento.absPath), FNM_NOESCAPE)==0)
        {
            printf("[%s]\n",tmp->elemento.absPath); 
        }
        tmp=tmp->next;
    }

// Ultimo elemento    
    if(tmp->elemento.absPath[0] == '/' &&
         !fnmatch(pattern,basename(tmp->elemento.absPath), FNM_NOESCAPE))
    {
        printf("[%s]\n",tmp->elemento.absPath); 
    }
    return 0;
}
/** ***************************************************************************
 * \version     1.0
 * \date        22/12/2018
 * 
 * \brief       Funzione di gestione settaggi
 * 
 * \param[out]  *nCore      Variabile per il numero dei core
 * 
 * \retval  -1      Numero di core correttamente ricavato
 * \retval   0      Funzione Fallita/
 * 
 * \details     Questa funzione ricerca nel file "/proc/cpuinfo" la stringa 
 *              "siblings" che indica il numero dei core del proccessore
 *              il funzionamento è molto semplice. Apre il file e lo esamina
 *              riga per riga, finchè non arriva allaprima riga con "siblings"
 *              Successivamente una doppia chiamata a strtok() permette lo slit
 *              della riga in occorenza dei :. In qesto modo estrapolo il numero
 *              dei core e lo converto in int.
 * 
 *****************************************************************************/
int getNCore(short *nCore)
{
// VARIABILI E INIZIALIZZAZIONI
    char tmpCore[20];
    int  countC=1;
    FILE  *fd;
    memset(tmpCore, '\0', 20);

// Verifica argomenti
    if(nCore==NULL)
    {
        errno=EINVAL;
        perror(__FUNCTION__);
        return -1;
    }

// Apro il file
    fd=fopen("/proc/cpuinfo", "r");
    if(fd == NULL  )
    {
        perror(__FUNCTION__);
        return -1;
    }

// Leggo riga per riga
    while( fgets(tmpCore, 19, fd) != NULL )
    {
        if(memcmp(tmpCore, "siblings", 8) == 0 )
        {
            strtok(tmpCore,":");
            countC=atoi(strtok(NULL,":"));
            break;
        }
        memset(tmpCore, 0, 20);
    }

// Comparo countC con MAX_CORE
    if(countC>MAX_CORE)
    {
    // Troppi core, non gestibili
       *nCore=MAX_CORE; 
    }
    else
    {
    // Numero di CORE gestibili
        *nCore=countC;
    }
    
// Chiudo ed esco
    fclose(fd);
    fd=NULL;
    return 0;
}