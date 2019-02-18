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

### Possiili Migliorie

- Migliorare l'algoritmo di ricerca dei file.
- Possibilita' di usare la sintassi __REGEX__ come pattern di ricerca dei file.
- Log 

## 1.3 Consegna2

Piccolo Server-Client per lo scambio di file.
Per impostazione predefinita il client si connette

## 1.4 COME SI USA

Qui in seguito sarà data un descrizione di come si usa il software.

Inizialmente bisogna avviare il server nella
macchina in cui si vuole farlo girare. Bisogna anche sapere l’IP della macchina. L’indirizzo IP del server è
identiﬁcabile dal comando ifconfig in caso non si riuscisse a recuperare IP della macchina nella quale sarà
lanciato il server, impostare il client con localhost (IP 127.0.0.1). La porta scelta e’ la 5263, anch’ essa
impostabile se dovesse essere già utilizzata in altri applicativi.
server
Il server viene lanciato con il comando ./server apparirà un menù di dialogo . In questa fase il server ancora
non è attivo. Qui cercaherà tutti i ﬁle presenti nella home della macchina in cui e’ stato lanciato (a seconda
del numero di ﬁle presenti, potrebbe volerci un pò di tempo). Il menù di dialogo presenta delle voci per cambiare
qualche piccola opzione (ad esempio il numero di porta in ascolto se quella impostata dovesse essere già
impegnata con un’altro programma.). Appena pronto si potrà avviare. Una volta avviato si potrà avviare un
client per comunicare. il server è impostato in modo da poter gestire al MAX 5 client contemporaneamente.
Anche questo parametro è conﬁgurabile. una volta avviato, non ci saranno operazioni da compiere, lavorerà
in maniera automatica.
I ﬁle ricevuti veranno smistati nella directori \HOME\Scaricati\.
client
All’avvio il client apparirà un menu con solo 2 voci: chiederà di effettuare un login. Se non si è registrati si
potrà richiedere una registrazione.

## 1.5 DOCUMENTAZIONE


