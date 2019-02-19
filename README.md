# FILDERX

- INDICE
  - [__1.1 GENERALITA'__](#11-generalita)
  - [__1.2 Consegna1__](#12-consegna1)
  - [__1.3 Consegna2__](#13-consegna2)
  - [__1.4 COME SI USA__](#14-come-si-usa)
  - [__1.5 DOCUMENTAZIONE__](#15-documentazione)
  
## 1.1 GENERALITA'

Questo progetto prende il nome di  __FILDERX__ (<b>FIL</b>E SEN<b>DER</b> UNI<b>X</b>) e’ stato creata per il progetto di Sistemi Operativi del corso di Ingegneria Informatica, dallo studente

__Cannavo’ Michele _Matr=O46-002210___.

Il progetto e’ diviso in 2 Consegne (in allegato i testi delle consegne in .pdf). Il progetto e' svolto in ambiente Linux, 
con l'ausilio del compilatore __GCC 7.3.0__ e degli editor __GEDIT__ e __VISUAL STUDIO CODE__ in ambiente __Linux (Ubuntu 18-04 LTS )__.
E' stato scelto di dividere il progetto in varie sotto funzioni. In questo modo si ha il vantaggio di una migliore manutenibilita' 
del software e una piu' veloce compilazione (anche se vista l' eseguita' del codice, il tempo di compilazione non e' un problema).
Per entrambe le consegne e' stato creato anche un piccolo script che agevola la compilazione, l'esecuzione del progetto e la verifica 
statica del codice tramite __cppcheck__.

## 1.2 Consegna1

Crea una lista dinamica con l'elenco dei file presenti in una directory passata da linea di comando. Quando si avvia lo script, oppure direttamente l'eseguibile, e' necessario indicare dalla linea di comando la cartella di cui si vuole costruire la ista, ed a propria discrezione il pattern di ricerca. Esso dovra' seguire la sintassi utilizzata dalla shell bash. Per default se non viene specificato altro essa cerchera' tutti i file, senza filtrare nessuno (Pattern = __*__). Il cuore del programma risiede nella funzione _listDir_ che è quella che effettivamente ricerca i file dentro le directory. La ricerca viene gestita dalla funzione _MotoreFILDERX_ che organizza la ricerca tramite dei thread. Data la directory iniziale, si esegue subito una ricerca in essa e si costruisce la lista iniziale, successivamente vengono creati N(Numero  core del processore ) thread (fino ad un massimo di MAX_CORE, massimo molto ampio per poter agevolmente istanziare la memoria per l'array contenente gli ID dei thread, avendo sempre tutti gli ID a disposizione. (Se non si vogliono porre dei limiti si puo' allocare l'array dinamicamente con malloc/calloc). Ogni thread e' composto da un ciclo infinito, un mutex si occupa di sincronizzare l'accesso alla lista un thread alla volta. Nel ciclo viene controllata la presenza di elementi directory all'interno della lista. Se non trova elementi directory esce dal ciclo. Quando tutti i thread non trovano più directory. Esce dalla funzione e cancella i thread e distrugge i mutex. A contorno sono state create anche funzioni per la gestione facilitata dei settaggi, ermettendone pure la modiifca a programma avviato.

### Possibili Migliorie

- Migliorare l'algoritmo di ricerca dei file. 
- Possibilita' di usare la sintassi __REGEX__ come pattern di ricerca dei file.
- Log 

## 1.3 Consegna2

Piccolo Server-Client per lo scambio di file. E' stato aggiunto ad onuno dei due un piccolo scrip che ha la funzione di agevolare compilazione, creazione di file obj e esecuione del programma. inoltre se presente nel pc, è possibile controllare staticamente il codice tramite __CPPCHECK__.
Al momento non risultano __WARMINGS__ con il suddetto tool.

### SERVER
Il server per impostazione predefinita opera sulla porta 64000, ma essa è modificabile sia inserendola come parametro da linea di comando (non posssible con lo script), sia a programma avviato tramite la modifica dei settaggi. 
Come impostazione predefinita e' stata scelta la cartella __"/Scaricati"__ come cartella per contenere i file ricevuti. Anch'essa e' modificaile tramite la modifica settaggi. Il Server ha un menu' iniziale per vedere i settaggi, modificarli, vedere gli Account Registrati, vedere la Lista di file propri. La lista dei file è caricata ogni volta all'avvio del programma, per questo necessita di un paio di secondi per completarsi. Da quando si avvia il Server, esso non avrà più bisogno di interlocutore perchè tutte le operazioni saranno automatiche, oppure gestite dal client. Sullo schermo appariranno le operazioni compiute dal __Client__

### CLIENT
Per impostazione predefinita il client ha i seguenti settaggi:
+ IP __127.0.0.1__ 
+ porta __64000__
* Cartela Salvataggio __"/Scariccati"__

Ha diversi menu'. Inizialmente ha il solito menù per la visione dei settaggi o la loro modifica a runtime, Successivamente si potrà avviare il Client e comunicare col server. Innazitutto chiede se registrasi oppure autenticarsi. Dopo essersi autenticato, il client può procedere a scegiere l'opzione voluta:

+ Inviare file
+ Riceere una lista di file regolata dal __PATTERN__
+ Ricevere un file

### Possibili implementazioni generali

+ Criptare almeno la password
+ Utilizzare database per la gestione account
+ Inserire il comado per la shell remota
+ Inserire un sistema di LOG

