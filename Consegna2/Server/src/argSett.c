/** ***************************************************************************
 * \file       argSett.c
 * \version    1.0
 * 
 * \brief       Imposta una struct con gli argomenti da linea di comando
 * 
 * \details     Questa funzione memoorizza gli argomenti da linea di comando 
 *              (CLA - Commands line Arguments) in una struc SettServer.
 *              Accetta al momento un solo argmento che rappresentare la porta
 *              in ascolto, Il valore deve essere compreso nel range delle 
 *              porte effimere (1023<n<65535).
 * 
 * \param[int]  argc    Intero che indica il numero di CLA
 * \param[char] *argv[] Puntatore alle stringhe con gli CLA
 *  
 * \retval    -1    FAILURE
 * \retval     0    SUCCESS
 *****************************************************************************/
#include "Server.h"

int argSett(int argc, char *argv[])
{
//I controlli sulla corettezza degli CLA verrà gestita dalle apposite funzioni 
    int p=0;
    switch(argc)
    {
        case 1:// Parametri di default 
            return 0;

        case 2:// Porta da riga di comando
            p=atoi(argv[1]);
            if(p<1023 || p>65535) // Semplice verifica numero di porta effimera
            {
                errno=EINVAL;
                perror(__FUNCTION__);
                return -1;
            }
            settaggi->nPort=p;
            return 0;

        default:// Troppi argomenti
            errno=E2BIG;
            perror(__FUNCTION__); 
            return -1;
   }
}