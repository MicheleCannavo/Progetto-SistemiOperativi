#include "Client.h"

/** ***************************************************************************
 * \brief   	Verifica se ci sia spazio libero a sufficenza per un file
 *
 * \param 	sizeF 	Dimensione da verificare
 * 
 * \return  Verifica dell'esito funzione 
 * 
 * \retval	-1		Errore (errno = errno<-statvfs() )
 * \retval	 0		Spazio disponibile (errno = SUCCESS)
 * \retval	 1		Spazio insufficente (errno = ENOSPC) 
 *
 * \details     La funzione verifica che ci sia spazio a sufficenza per salvare
 *              il file trasmesso. Verifica lo spazio dalla root.
 * 
 ******************************************************************************/
int freespace(unsigned long sizeF)
{
// VARIABILI E INIZZIALIZZAZIONE
    struct statvfs info;

	memset((struct statvfs *)&info, 0, sizeof(info));

// Recupero informazione dal sistema
	if (statvfs("/", &info) == 0)
	{
		unsigned long 	blsize   = info.f_bsize;        // Dimensione singolo blocco
		unsigned long	freeblck = info.f_bavail;       // Blocchi liberi usabili
		unsigned long 	freespcs = blsize * freeblck;   // Spazio libero in byte
		
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