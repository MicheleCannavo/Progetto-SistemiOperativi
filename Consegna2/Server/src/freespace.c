#include "Server.h"

/** ***************************************************************************
 * \brief   	Verifica se ci sia spazio libero a sufficenza per un file
 *
 * \details     La funzione verifica che ci sia spazio a sufficenza per salvare
 *              il file trasmesso. Verifica lo spazio dalla cartella di root.
 *
 * \param 	sizeF 	Dimensione da verificare
 * 
 * \return  Verifica dell'esito funzione 
 * 
 * \retval	-1		Errore (errno = errno<-statvfs() )
 * \retval	 0		Spazio disponibile (errno = SUCCESS)
 * \retval	 1		Spazio insufficente (errno = ENOSPC)
 ******************************************************************************/
int freespace(unsigned long sizeF)
{
	// VARIABILI E INIZZIALIZZAZIONE
	struct statvfs info;


	memset((struct statvfs *)&info, 0, sizeof(info));

	// <recupero informazione dal sistema
	if (statvfs("/", &info) == 0)
	{
	    unsigned long freeblck = 0;
	    unsigned long blsize   = 0;
    	unsigned long freespcs = 0;
	    
	    blsize   = info.f_bsize;
		freeblck = info.f_bavail;
		freespcs = blsize * freeblck;
		if (sizeF < freespcs)
		{
			return 0;
		}
		else
		{
			errno = ENOSPC;  // No space left on device
			return 1;
		}
	}
	return -1;
}
