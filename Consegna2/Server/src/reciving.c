#include "Server.h"
/** ****************************************************************************
 * \version     1.3
 * \date        15/02/2019
 * 
 * \brief       Invia un file tramite socket 
 * 
 * \param   sockFD      ID del socket 
 * \param   fs_name     Nome del file da inviare 
 * 
 * \return  Verifica dell'esito funzione  
 *
 * \details     La funzione e' molto semplice. Come prima cosa attende la
 *              lunghezza del nome del del file, per poter usare agevolmente il
 *              flag MSG_WAITALL nella funzione send(). Si evita' la possiilità
 *              che il nome del file venga invia a pezzi (anche se con una
 *              semplice stringa la possibilità e' remota, essendo i nomi dei
 *              file di massimo NAME_MAX(256) caratteri). Dopo attende il nome
 *              del file per salvarlo (adopera un piccolo controllo di esistenza
 *              dello stesso con relativa riciesta di sostituzione/Nuovo Nome).
 *              con lo stesso nome, e la dimensione di esso utile per 2 scopi.
 *              Il primo e' una semplice verifica della dimensione del file
 *              arrivato (Sicuramente verra' spedito in blocchi, e il TCP ha un
 *              controllo solo sul singolo blocco e non sul totale file, la
 *              seconda e' che, sapendo la dimensione totale del file so
 *              esattamente quanti dati aspettarmi, e posso impostare il buffer
 *              della recv() in maniera da attendere il giusto quantitativo di
 *              byte. Infine aspetto).
 *
 *******************************************************************************/
int recvFILE(int sockid, char *fr_name, int buff)
{
// VARIABILI E INIZIALIZZAZIONI
	size_t  countDT           	=  0; 	// Counter dati trasferiti
	size_t  sizeF            	=  0;	// Dimensione file
    int 	fdF              	= -1;	// File desceriptor file
	int 	lName               =  0; 	// Lunghezza nome del file
	int 	dim                 =  0;	// Dimensione
	int 	r                   =  1;	// Numera i file con lo stesso nome
	char 	copy[NAME_MAX+1];			// Copya temporanea del nome file
	char 	nameF[NAME_MAX+1];			// Nome file
	char 	pathAct[PATH_MAX];			// Path File 
	char 	revbuf[MAXBUF];    			// Buffer per la ricezione dati
	char 	str[NAME_MAX+1];			// Variabile d'appoggio per il nome File

	memset( nameF, 	 '\0', sizeof(char)*(NAME_MAX+1) );
	memset( pathAct, '\0', sizeof(char)*PATH_MAX );	
	memset( revbuf,  '\0', sizeof(char)*MAXBUF );	
	memset( copy, 	 '\0', sizeof(char)*(NAME_MAX+1) );
	memset( str, 	 '\0', sizeof(char)*(NAME_MAX+1) );		

// Salvo la directory corrente
	if( getcwd(pathAct,PATH_MAX)==NULL)
	{
		PRINTERR("Salvataggio work dir");
		return -1;
	};

// Imposto la directory di Salvataggio
	if(chdir(settaggi->saveDir)!=0)
	{
		PRINTERR("Cartella di Salvataggio");
		return -1;
	}

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

	dim  = NAME_MAX-strlen(nameF);
	strncpy(copy, nameF, NAME_MAX);
	copy[NAME_MAX-1]='\0';

// Verifico se il file esiste
	while( access(nameF, 0) == 0 )
	{
		printf("\rFile :%s gia' presente.",nameF);
		sprintf(str, " (Copia %d)", r);	
		strncpy(nameF, copy, NAME_MAX);
		nameF[NAME_MAX-1]='\0';

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
