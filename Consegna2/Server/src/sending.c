#include "Server.h"
/** ***************************************************************************
 * \brief   	Invia un file tramite socket 
 *
 * \details     La funzione e' molto semplice. Innanzitutto invio la lunghezza
 *              del nome del file, per poter usare agevolmente il flag
 *              MSG_WAITALL nella funzione send(). Evito quindi la possibilità
 *              che il nome del file venga inviato a pezzi (anche se con una
 *              semplice stringa la possibilità e' remota, essendo i nomi dei
 *              file di massimo NAME_MAX(256) caratteri). Invio successivamente
 *              il nome del file per verificare per poterlo salvare con lo
 *              stesso nome, e infine invio la dimensione del file, utile per
 *              due scopi. Il primo e' una semplice verifica della dimensione
 *              del file arrivato sicuramente verrà spedito in blocchi, e il TCP
 *              ha un controllo solo sul singolo blocco e non sul totale file,
 *              la seconda e' che, sapendo la dimensione totale del file, il
 *              ricevente sa esattamente quanti dati aspettarmi, e posso
 *              impostare il buffer della recv() in maniera da attendere il
 *              giusto quantitativo di byte. Infine aspetto che il ricevente
 *              inoltri l'esito della verifica dell'invio del file.    
 *
 * \param 	sockFD      ID del socket
 * \param   fs_name     Nome del file da inviare 
 * 
 * \return  Verifica dell'esito funzione 
 ******************************************************************************/
int sendFILE(int sockFD)
{
// Variabili con inizializzazione
	char 		nameF[NAME_MAX];
    char    	sdbuf[LENGTH] 	; 	// Send buffer	
	char 		risp[4]			;	// Stringa per la verifica
	int     	fdF	 		  =	0;  // File descriptor file
	int 		lName		  = 0;  // Lunghezza nome file
	size_t 		sizeF      	  =	0; 	// Dimensione totale del file da inviare
    ssize_t 	fs_block_sz	  =	0; 	// Dimensione blocco dati da inviare
	size_t 		tmpFT      	  =	0; 	// Dimensione dati totale inviati
	struct stat fileStat		;	// Struct stat per dimensione file

// Azzeramento stringhe e struct per evitre errori
	memset((char*)nameF, '\0', sizeof(char)*NAME_MAX);
	memset((char*)sdbuf, '\0', sizeof(char)*LENGTH );
	memset((char*)risp, '\0', 4);
	memset((struct stat*)&fileStat, 0, sizeof(struct stat)); 	

// Ricevo lunghezza nome file
	if(recv(sockFD,&lName,sizeof(int), MSG_WAITALL) != sizeof(int) )
	{
		PRINTERR("Lunghezza nome file: ");
		return -1;
	}
	lName=(lName>NAME_MAX?NAME_MAX:lName);

// Ricevo il nome del file
	if(recv(sockFD, nameF, lName, MSG_WAITALL) != lName)
	{
		PRINTERR("Nome file: ");
		return -1;
	}

// Verifico esistenza file
	if(access(nameF,0)!=0)
	{
		if(send(sockFD,0,sizeof(size_t),0)<1)
		{
			return -1;
		}
		return 1;
	}

// Apertura file in lettura e calcolo dimensione Nome e File
    fdF = open(nameF, O_RDONLY);
	if(fdF == -1)
	{
        PRINTERR("Apertura file: ");
		return -1;
    }
	if(fstat(fdF, &fileStat) != 0)
	{
		PRINTERR("Dimensione file: ");
		return -1;
	}
	sizeF=fileStat.st_size;
	lName=strlen(nameF)+1;
	
// Invio dimensione file
	if(send(sockFD, &sizeF, sizeof(size_t),0) <0 )
	{
		PRINTERR("Invio dimensione file: ");
		return -1;
	}
	printf("\nInizio trasferimento del file: %s-[%zu bytes]\n\n",nameF,sizeF);


	recv(sockFD,risp,4,MSG_WAITALL);


// Trasferimento file
	while((fs_block_sz =read(fdF,sdbuf, settaggi->maxBuffer))>0)
	{
		tmpFT+=fs_block_sz;// Byte totali letti
		printf("\rTraferiti=%zu di %zu", tmpFT, sizeF);
	    if(send(sockFD, sdbuf, fs_block_sz, 0) < 0)
	    {
	        PRINTERR("send()");
	        return -1;
	    }
	    memset(sdbuf, '\0', sizeof(sdbuf));
	}
	close(fdF);
	if(fs_block_sz<0)
	{
		PRINTERR("sending()-write()");
		return -1;
	}
// Ricezione e verifica esito invio
	if(recv(sockFD, risp, 4, 0) != 4 )
	{
		PRINTERR("Ricezione risposta:");
		return -1;
	}

	if(strncmp(risp,"ZER",4)==0)
	{
		printf("\nNon ricevuto\n");
		return -1;
	}
	else if(strncmp(risp,"DMG",4)==0)
	{
		printf("\nFile danneggiato\n");
		return 1;
	}
	else //if(strncmp(risp, "INT", 4) == 0 )
	{
		printf("\nFile integro\n");
		return 0;
	}
}