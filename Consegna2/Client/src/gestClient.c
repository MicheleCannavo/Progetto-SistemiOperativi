#include "Client.h"

/** ***************************************************************************
 * \brief   	Verifica se ci sia spazio libero a sufficenza per un file
 *
 * \return  Verifica dell'esito funzione 
 * 
 * \retval   == -1		Funzione fallita
 * \retval	 != -1		Connessione riuscita
 * 
 * \details     Avvia una connession con il Server disegnato dalle impostazioni
 *              Il responso della connessione deve avvenire entro TIMEOUT
 *              altrimenti si avra' la chiusura del client
 * 
 ******************************************************************************/
int gestClient()
{   
    printf("Connessione in corso...\n");
    sleep(2); 
    alarm(TIMEOUT);
    if( newSocket() !=0 )
    {
        perror(__FUNCTION__);
        sleep(2);
        return -1;
    }   
    alarm(0);
    return menAcc();
}