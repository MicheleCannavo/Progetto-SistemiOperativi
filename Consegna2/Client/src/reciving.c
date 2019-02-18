#include "Client.h"
#include <limits.h>
/**
 * \brief   Invia un file tramite socket 
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
 * \param   sockFD      ID del socket 
 * \param   fs_name     Nome del file da inviare 
 * 
 * \return  Verifica dell'esito funzione 
 */
int recvFILE(int sockFD, char *fr_name, int buff)
{
// Variabili 
	char 	nameF[NAME_MAX+1]	= {""};	// Nome file   
	char 	pathAct[PATH_MAX];
	char 	revbuf[2048] 		= {""};	// Receiver buffer	
	size_t  sizeF				=	 0;	// Dimensione file
    int 	fdF					=   -1;	// File desceriptor file
	int 	lName				=	 0; // Lunghezza nome del file
    ssize_t	byteRecv 			= 	 0; // Dimensione dati letti da trasferire
	size_t countDT				=	 0; // Counter dati trasferiti
	size_t	buf2				=	 0; // Buffer di trasferimento

// Verifica argomenti
	if(sockFD==-1 || fr_name==NULL || buff<0)
	{
		errno=EINVAL;
		PRINTERR("Input: ");
		return -1;
	}
	memset((char*)nameF,'\0',sizeof(char)*(NAME_MAX));
		getcwd(pathAct,PATH_MAX);
		chdir(settaggi->saveDir);

printf("Digigta il nome del file da importare: ");
fgets(nameF,NAME_MAX,stdin);
	nameF[NAME_MAX]='\0';
	if(nameF[strlen(nameF)-1]=='\n')
		nameF[strlen(nameF)-1]='\0';
int hh=strlen(nameF);
// Mando dimensione nome del file;
	send(sockFD, &hh, sizeof(int), 0) ;
int h=strlen(nameF)+1;
// Mando il nome del file
	if(send(sockFD, nameF,h ,0 )!=strlen(nameF)+1)
	{
		PRINTERR("Nome file: ");
		return -1;
	}
	lName=(lName>NAME_MAX?NAME_MAX:lName);

// Ricevo la dimensione del file
	if(recv(sockFD, &sizeF, sizeof(size_t), MSG_WAITALL) != sizeof(size_t) )
	{
		PRINTERR("Dimensione file: ");
		return -1;
	}
	if(freespace(sizeF)!=0)
	{
		PRINTERR("Spazio Disco: ");
		return -1;
	}
	send(sockid_Client,"ok",3,0);

// Verifico se il file esiste
	while( access(nameF, 0) == 0 )
	{
		int r = 0;

		printf("File :%s gia' presente.\nSovrascriverlo?[S/n]",nameF);
		isalpha_in(&r);
		if(r=='S')
		{
			break;
		}
		printf("Inserisci il nome modificato:");
		fgets(nameF, NAME_MAX, stdin);
		nameF[NAME_MAX]='\0';
		if(nameF[strlen(nameF)-1]=='\n')
			nameF[strlen(nameF)-1]='\0';
	}

// Apro il nuovo file in scrittura
	fdF = open(nameF, O_WRONLY| O_CREAT, S_IRWXU | S_IRWXG);
	if(fdF == -1)
	{
        PRINTERR("Apertura file: ");
        return -1;
    }	

while(countDT!=sizeF)
{
	// Azzero il buffer
	memset(revbuf, 0, sizeof(char)); 
	// Minimo tra DimBuff e byte restanti
	buf2=(sizeF-countDT>buff)?buff:(sizeF-countDT);
	byteRecv=recv(sockFD,revbuf,buf2,MSG_WAITALL);
	if(byteRecv<0)
	{
		PRINTERR("Ricezione dati: ");
		return -1;
	}
	countDT+=byteRecv;
	printf("\rRicevuto %10zu di %10zu",countDT,sizeF);
	fflush(stdout);
	int write_sz=write(fdF,revbuf,byteRecv);
	if(write_sz<byteRecv)
	{
		PRINTERR("Scrittura file: ");
		return -1;
	}
}close(fdF);
chdir(pathAct);
// Verifica sommaria dalla dimensione del file arrivato
	if(countDT == 0 )
	{
		printf("File non ricevuto\n");
		send(sockFD, "ZER", 4, 0);
		return -1;
	}
	else if(countDT != sizeF && countDT !=0)
	{

		printf("File danneggiato\n");
		send(sockFD, "DMG", 4, 0);
		return -1;
	}
	else
	{
		{
			printf("File ricevuto con successo\n");
			send(sockFD,"INT",4,0);
			return 0;
		}
	}
}