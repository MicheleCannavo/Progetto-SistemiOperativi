/** ***************************************************************************
 * \file        iniSett.c
 * \version     1.0
 * \date        03/01/2019
 * 
 * \brief      inizzializza struct per i settaggi
 *  
 * \retval    -1    FAILURE
 * \retval     0    SUCCESS
 *  
 * \details     Questa funzione alloca la memoria e inizializza un puntatore
 *              in ingresso ad una struct SettFILDERX che servirà a contenere 
 *              i settaggi del programma. Nececcisa di una variabile globale
 *              (puntatore a SettServer) dal valore NULL, altrimenti 
 *              la struct verràa' consdeerata gia' alloata. 
 *              Il chiamante deve occuparsi anche della chiamata a free().
 * 
 *****************************************************************************/
#include "Server.h"

int iniSett()
{
// Controllo che la variabile globale settaggi non sia già allocata
    if(settaggi != NULL )
    {
        return -1;
    }

// Alloco la memoria
    settaggi = calloc(1, sizeof(SettSERVER) );
    if(settaggi == NULL)
    {
        perror(__FUNCTION__);
        return -1;
    }

// Variabile per creare la directory di salvataggio
    char saveDir[PATH_MAX];
    memset((void*)saveDir, 0, PATH_MAX);
   
// Settaggi statici
    settaggi->nPort      = PORT;
    settaggi->nClientMax = MAX_CLIENT;
    settaggi->maxBuffer  = MAXBUF;
    
// Directory /HOME/Scaricati come directory di salvataggio di default.
    if(strlen( getenv("HOME"))  <= PATH_MAX- (strlen(SAVEDIR)+1) )
    {
        strncpy(settaggi->saveDir, getenv("HOME"), PATH_MAX- (strlen(SAVEDIR)+1)  );  
        strncat( settaggi->saveDir, SAVEDIR, strlen(SAVEDIR)+1 );
    }   
    return 0;
}