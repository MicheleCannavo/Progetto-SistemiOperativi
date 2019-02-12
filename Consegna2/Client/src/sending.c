#include "s.h"
int sendFILE(int sockid, char *fs_name)
{
// Variabili
    char    	sdbuf[LENGTH] = {""}; // Send buffer	
	char 		risp[4]		  = {""}; // Risposta al client
	int     	fdF	 		  =	0; 	  // File descriptor file
	int 		lName		  = 0;    // Lunghezza nome file
	size_t 		sizeF      	  =	0; 	  // Dimensione totale del file da inviare
    ssize_t 	fs_block_sz	  =	0; 	  // Dimensione blocco dati da inviare
	size_t 		tmpFT      	  =	0; 	  // Dimensione dati totale inviati
	struct stat fileStat;
	
// Azzero la struct stat e il buffer per evitare errori
	memset((char*)sdbuf, '\0', sizeof(sdbuf) );
	memset((struct stat*)&fileStat, 0, sizeof(struct stat)); 

// Apro il file in lettura e ne prendo la dimensione tramite il fd
    fdF = open(fs_name, O_RDONLY);
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
	printf("\nInizio trasferimento del file: %s-[%zu bytes]\n\n",fs_name, sizeF);
	lName=strlen(fs_name)+1;
// Invio lunghezza nome file
	if(send(sockid,(void *)&lName,sizeof(int),MSG_WAITALL) != sizeof(int) )
	{
		PRINTERR("invio nome del file: ");
		return -1;
	}
// Invio il nome del file
	if(send(sockid, fs_name, strlen(fs_name)+1, 0) <0 )
	{
		PRINTERR("Invio nome file: ");
		return -1;
	}
	
// Invio la dimensione
	if(send(sockid,(void*)&sizeF, sizeof(size_t),0) <0 )
	{
		PRINTERR("Invio dimensione file: ");
		return -1;
	}
	printf("\nInizio trasferimento del file: %s-[%zu bytes]\n\n",fs_name,sizeF);

// Trasferimento file
	while((fs_block_sz =read(fdF,sdbuf, 512))>0)
	{
		tmpFT+=fs_block_sz;// Byte totali letti
		printf("\rTraferiti=%zu di %zu", tmpFT, sizeF);
	    if(send(sockid, sdbuf, fs_block_sz, 0) < 0)
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
// Ricezione risposta
	if(recv(sockid, risp, 4, 0) != 4 )
	{
		PRINTERR("Ricezione risposta:");
		return -1;
	}

// Verifica risposta
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
 //   close(fdF);
  //  return 0;
}