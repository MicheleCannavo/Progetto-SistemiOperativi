#include "Server.h"
int recvFILE(int sockid, char *fr_name, int buff)
{
// Variabili 
	char 	nameF[NAME_MAX]	= {""};	// Nome file   
	char 	pathAct[PATH_MAX];
	char 	revbuf[LENGTH] 	  	= {""};	// Receiver buffer	
	size_t  sizeF				=	 0;	// Dimensione file
    int 	fdF					=   -1;	// File desceriptor file
	int 	lName				=	 0; // Lunghezza nome del file
	size_t countDT				=	 0; // Counter dati trasferiti

	getcwd(pathAct,PATH_MAX);
	chdir(settaggi->saveDir);
// Verifica argomenti
	if(sockid==-1 || fr_name==NULL || buff<0)
	{
		errno=EINVAL;
		PRINTERR("Input: ");
		return -1;
	}

// Ricevo lunghezza nome file
	if(recv(sockid,&lName,sizeof(int), MSG_WAITALL) != sizeof(int) )
	{
		PRINTERR("Lunghezza nome file: ");
		return -1;
	}
	lName=(lName>NAME_MAX?NAME_MAX:lName);

// Ricevo il nome del file
	if(recv(sockid, nameF, lName, MSG_WAITALL) != lName)
	{
		PRINTERR("Nome file: ");
		return -1;
	}
	access(nameF,0);

// Ricevo la dimensione del file
	if(recv(sockid, &sizeF, sizeof(size_t), MSG_WAITALL) != sizeof(size_t) )
	{
		PRINTERR("Dimensione file: ");
		return -1;
	}
	freespace(sizeF);

	printf("Ricezione file: %s [%zu bytes]\n", nameF, sizeF);
		int r = 1;
		char copy[NAME_MAX+1];
		int dim=NAME_MAX-strlen(nameF);
		char str[NAME_MAX+1];

		memset(copy, '\0', sizeof(char)*(NAME_MAX+1) );
		memset( str, '\0', sizeof(char)*(NAME_MAX+1) );		
		strncpy(copy, nameF, NAME_MAX);

// Verifico se il file esiste
	while( access(nameF, 0) == 0 )
	{
		printf("\rFile :%s gia' presente.",nameF);
		sprintf(str, " (Copia %d)", r);	
		strncpy(nameF,copy, NAME_MAX);
		strncat(nameF, str, dim);
		r++;
	}
	
// Apro il nuovo file
	fdF = open(nameF, O_WRONLY| O_CREAT, S_IRWXU | S_IRWXG);
	if(fdF == -1)
	{
        PRINTERR("Apertura file: ");
        return -1;
    }	

// Ricevo il file
	countDT=0;

    while(countDT!=sizeF)
    {
        ssize_t	byteRecv 	= 0; // Dimensione dati letti da trasferire
	    size_t	buf2		= 0; // Buffer di trasferimento
    	int     write_sz    = 0;
	// Azzero il buffer
	    memset(revbuf, 0, sizeof(char)); 
	
	// Minimo tra DimBuff e byte restanti
	    buf2=(sizeF-countDT>buff)?buff:(sizeF-countDT);
    	byteRecv=recv(sockid,revbuf,buf2,MSG_WAITALL);
	    if(byteRecv<0)
	    {
		    PRINTERR("Ricezione dati: ");
		    return -1;
	    }
	    countDT+=byteRecv;
	    printf("\rRicevuto %10zu di %10zu",countDT,sizeF);
	    fflush(stdout);
	    write_sz=write(fdF,revbuf,byteRecv);
	    if(write_sz<byteRecv)
	    {
		    PRINTERR("Scrittura file: ");
		    return -1;
	    }
    }close(fdF);
    chdir(pathAct);
    
// Verifica sommaria dalla dimensione del file arrivato
	if(countDT==0)
	{
		printf("\nFile non ricevuto\n");
		send(sockid,"ZER",4,0);
		return -1;
	}
	else if( countDT!=sizeF )
	{
		printf("\nFile danneggiato\n");
		send(sockid,"DMG",4,0);
		return 1;
	}
	else // countDT == sizeF
	{
		printf("File ricevuto con successo\n");
		send(sockid, "INT", 4, 0);
		return 0;
	}
}
