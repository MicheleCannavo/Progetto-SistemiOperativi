 /** **************************************************************************
 * \author      Cannavo' Michele [046002210]
 * \file        FILDERX.h
 * \version     1.0
 * \date        11/12/2018
 * \brief       Header per FILDERX.c
 * \details     File contenente l header per le funzione di ricerca per FOILDERX
*******************************************************************************/
#ifndef FILDERIX_H
#define FILDERIX_H

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  HEADER  ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>          // Generico
#include <stdlib.h>         // Generico
#include <string.h>         // Generico
#include <sys/types.h>      // getNCore(),
#include <sys/stat.h>       // testPath(), isDIR()
#include <fcntl.h>          // getNCore()
#include <unistd.h>         // listDir()
#include <dirent.h>         // MotoreFILDERX(), listDir()
#include <pthread.h>        // MotoreFILDERX(),
#include <errno.h>          // errno
#include <fnmatch.h>        // listDir(), 
#include <libgen.h>         // listPrintS(),
#include <linux/limits.h>

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  STRUCT  ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/// \def    MAX_CORE
/// \brief  Numero massimo di core gestibil
#define MAX_CORE    (32)

typedef struct _ELEFILDERX          //! Struttura per i dati della lista di file
{
    unsigned long          idNumber; //!< ID del file
    char          absPath[PATH_MAX]; //!< FullPath File
}ELEFILDERX;

typedef struct _listFILDERX //! Struttura per la lista dinamica dei file
{
    struct _ELEFILDERX   elemento; //!< Rappresenta un file nella lista dinamica
    struct _listFILDERX *next;     //!< Puntatore al succ. elemento della lista
} listFILDERX;

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// VARIABII GLOBALI ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/// \var    unsigned long int count
/// \brief  serve per tenere il conto dei file presenti nella lista
extern unsigned long int count;

/// \var ListFILDERX *headTList
/// \brief Contiene l'indirizzo del primo elemento della lista completa
/// contenente solo i file desiderati
extern listFILDERX *headTList;

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////    PROTOTIPI    ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int           getNCore( short *nCore);
int           testPath( char  *wPath);
int       MotoreFILDER( );
void            *funcT( void *arg);
int               InsC( listFILDERX **miniList, ELEFILDERX *nodoF );
int              freeL( listFILDERX **listComp );
int               totL( listFILDERX **Head,     listFILDERX *mini);
int              IsDir( listFILDERX  *listNodo);
int          printList( listFILDERX  *head, char *pattern);
ELEFILDERX  *creaNodo1( const char   *path, unsigned long id);
listFILDERX   *listdir( const char   *name);
listFILDERX *delFolder( listFILDERX **miniList);

#endif