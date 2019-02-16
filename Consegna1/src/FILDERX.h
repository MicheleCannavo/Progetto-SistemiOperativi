 /** **************************************************************************
 * \author      Cannavo' Michele [046002210]
 * \date        11/12/2018* 
 * 
 * \file        FILDERX.h
 * \version     1.0
 * \copyright   Copyright (c) 2018,2019 Cannavo' Michele
 * \license     GNU GPL 3.0
 * \brief       Header per FILDERX.c
 * \details     File contenente l header per le funzione di ricerca per FOILDERX
******************************************************************************/
#ifndef FILDERIX_H
#define FILDERIX_H

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////  HEADER  ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <fnmatch.h>
#include <limits.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////  DEFINE  ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

/// \def PATH_MAX
///  \brief Definisce, qualora non fosse definito il valore massimo di un percorso
#ifndef PATH_MAX
    #define PATH_MAX 1024
#endif

/// Definisce il massimo numero di core gestibili
#define MAX_CORE 64

/// \def    PATT_MAX
/// \brief  Dimensione massima del pattern di richerca
#define PATT_MAX 10

/// \def    PATTERN
/// \brief  Pattern di default
#define PATTERN "*"

/// \def    SAVEDIR
/// \brief  Percorso cartella di salvataggio dalla $HOME
#define SAVEDIR "/Documenti"

/// \def    MY_FILEO
/// \brief  Permette di associare un descrittore personale per il file
#define MY_FILENO STDOUT_FILENO


/// \def    SBUFFER
/// \brief  Macro di puizia del buffer stdin
#define SBUFFER do{int ch; \
                    while ( ( ch=getchar() ) !='\n' && (ch != EOF) );\
                }while(0)

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////  ENUM  ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////  STRUCT  ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

struct SettFILDERX_   //! Struct per i sattaggi del programma
{
    char        dirWork[PATH_MAX];  //!< Cartella dove cercare File e Directory
    char        dirSave[PATH_MAX];  //!< Cartella dove salvare la lista di File e Directory
    char   patttFILDERX[PATT_MAX];  //!< Patter di ricerca per i file (MAX 9 caratteri)
    short          nCoreProcessor;  //!< Core del processore
};
/// Alias per il tipo enum SettFILDERX_
typedef struct SettFILDERX_  SettFILDERX;


struct _ELEFILDERX //! Struttura per i dati della lista di file
{
    unsigned long          idNumber; //!< ID del file
    char          absPath[PATH_MAX]; //!< FullPath File
 //   struct stat          stFilderx; //!< stat File
};
/// Alias per la struct _ELEFILDERX
typedef struct _ELEFILDERX ELEFILDERX;

struct _listFILDERX //! Struttura per la lista dinamica dei file
{
    struct _ELEFILDERX   elemento;  //!< Rappresenta un file nella lista dinamica
    struct _listFILDERX *next;      //!< Puntatore al successivo elemento della lista
};
/// Alias per la struc _listFILDERX
typedef struct _listFILDERX listFILDERX;

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// VARIABII GLOBALI /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
/// VARIABILI GLOBALI PER TUTTI I FILE

extern SettFILDERX *settaggi ;

/// \var    unsigned long int count
/// \brief  serve per tenere il conto dei file presenti nella lista
extern unsigned long int count;

/// \var ListFILDERX *headTList
/// \brief Contiene l'indirizzo del primo elemento della lista completa
/// contenente solo i file desiderati
extern listFILDERX *headTList;

extern char *argv[];
extern int   argc;






///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////    PROTOTIPI    ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

/// \brief  Funzione di interfacciamento tra un classico main e tutt la Consegna1.
///         Una sua diversa implementazione servirà ad interfacciarsi con il server della Consegna2
///
/// \param[IN]  argc    numero di argomenti passati da linea di comando
/// \param[IN] *argv[]  Stringhe che contengono gli argomenti da linea di comando
/// \return             Successo della funzione
/// \retval      0      Riuscita della funzione
/// \retval     -1      Insucesso della funzione
int myMain(int argc, char* argv[]);

///////////////////////////////// PROTOTIPI SETTAGGI //////////////////////////

/// \brief  La funzione legge dal file /proc/cinfo l'informazione richiesta
///
/// \param  *nCore Numero di core di un processore
/// \return             Successo della funzione
/// \retval      0      Riuscita della funzione
/// \retval     -1      Insucesso della funzione
int getNCore(short *nCore);

/// \brief  Verifica se una stringa corrisponda ad una directory esistente
/// \param  *wPath stringa contenete il Path
/// \return             Successo della funzione
/// \retval      0      Riuscita della funzione
/// \retval     -1      Insucesso della funzione
int testPath(char *wPath);

/// \brief  Inizializza con valori di default la struct per i settaggi.
/// 
/// \return             Successo della funzione
/// \retval      0      Riuscita della funzione
/// \retval     -1      Insucesso della funzione
int iniSett();

int argSett(int argc, char **argv);

/// \return             Successo della funzione
/// \retval      0      Riuscita della funzione
/// \retval     -1      Insucesso della funzione
int modSett();

//////////////////////////////////// PROTOTIPI MOTORE //////////////////////////////////

/// \brief  Funzione principale di gestione del MOTORE di ricerca.
///
/// \return     Successo della funzione.
/// \retval  0  Riuscita della funzione.
/// \retval -1  Insucesso della funzione.
int MotoreFILDER( );

/// \brief  Funzione per i thread. Permette l'uso di più thread per velocizzare 
///         la ricercha ricorsiva dei file
///
/// \return     Successo della funzione tramite il valore in pthread_join.
/// \retval  0  Riuscita della funzione.
/// \retval -1  Insucesso della funzione.
void *funcT(void* arg);

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// PROTOTIPI STAMPE /////////////////////////

/// \brief La funzione stampa a video i campi di una struttura SettFILDERX
/// \param[in] setting struttura di tipo SettFILDERX da stampare
/// \param[in] fdStream file desriptor che identifica dove stampare l'informazione
/// \return Non ritorna nessun valore
void printSett(int fdStream);

/// \brief La funzione stampa un singolo elemento della ista concatenat di file
/// \param[in] listNodo Elemento da stampare
/// \param[in] fdStream file desriptor che identifica dove stampare l'informazione
void printNode(ELEFILDERX element, int fdStream);

/// \brief Stampa l'intera lista concatenata
/// \param[in] *headList Puntatore alla testa della Lista concatenata.
/// \param[in]  fdStream file desriptor che identifica dove stampare l'informazione
int printList(listFILDERX* headTList, int fdStream);

// \brief   Stampa l'intera lista concatenata
///
/// \param[in] *headList Puntatore alla testa della Lista concatenata.
/// \param[in]  fdStream file desriptor che identifica dove stampare l'informazione
int printDetList(listFILDERX* headTList, int fdStream);

int isdigit_in(int*);
int menuF();

/// \brief  Crea un elemento nodo per la lista concatenata
///
/// \param[in] *path Path name del file da memorizzare nella lista
/// \param[in]  id Id associato al file nella lista.
/// \return Successo della funzione
/// \retval EXIT_SUCCESS Riuscita della funzione
/// \retval EXIT_FAILURE Insucesso della funzione
ELEFILDERX *creaNodo1( const char* path,unsigned long id);

/// \brief  Crea una minilista con i soli file contenuti in una directory.
///         Non effettua ricerche ricorsive.
///
/// \param[in] *name path name della directory in cui cercare i FILE.
/// \return puntatore alla miilista
/// \retval  NULL errore nell'elaborazione della minilista
/// \retval !NULL puntatore valido ad una lista di tipo listFILDERX     
listFILDERX *listdir(const char *name);

/// \brief Inserisce un elemento in coda alla lista
///
/// \param[in] **listComp Puntatore al puntatore della testa della lista
/// \param[in]  *TempC elemento temporaneo da inserire in coda alla lista.
/// \return         Successo della funzione
/// \retval     0   Riuscita della funzione
/// \retval    -1   Errore nella funzione
int  InsC( listFILDERX **miniList, ELEFILDERX *nodoF );

/// \brief Libera la memoria allocata per la lista concatenata
/// \param[in] **listComp Puntatore a puntatore dela testa della lista
/// \return Successo della funzione
/// \retval 0 Riuscita della funzione
/// \retval -1 Errore - Insucesso della funzione
int freeL( listFILDERX **listComp );

/// \brief Inserisce una lista secondaria nella lista completa di FILDERX
/// \param[in] **Head Puntatore alla testa della lista completa
/// \param[in]  *mini Lista minore da inserire nella lista completa
/// \return Successo della funzione
/// \retval 0 Riuscita della funzione
/// \retval -1 Errore/Insucesso della funzione
int  totL( listFILDERX **Head, listFILDERX *mini);

/// \brief Creao un elemento nodo per la lista concatenata
/// \param[in] **listNodo Verifica se l'elemento come argomento è una cartella
/// \return Successo della funzione
/// \retval 0 Riuscita della funzione
/// \retval -1 Errore - Insucesso della funzione
int IsDir( listFILDERX *listNodo);

/// \brief Creao un elemento nodo per la lista concatenata
/// \param[in] **head Puntatore della Lista da completa in cui cercare gli elementi cartella
/// \return Successo della funzione
listFILDERX* delFolder(listFILDERX **head);

#endif
