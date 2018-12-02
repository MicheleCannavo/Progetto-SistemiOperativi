***Progetto-SistemiOperativi***
=========================

## **Consegna 1**
Sviluppare un software che, dato un path, scansiona tutti i file del file system in maniera ricorsiva. 
La struttura proposta prevede un pool di thread, uno per ogni core del processore. 
Il main thread inizia facendo un "ls" (list directory, ma con funzioni C) alla directory corrente, quindi inserisce in una lista i nomi degli elementi trovati:
Nella lista di stringhe verranno memorizzati file e directory con il path assoluto. Dopo il primo inserimento in lista gli altri thread in esecuzione
accedono alla lista e ognuno di questi elimina dalla lista un elemento di tipo directory, quindi scansiona (ls) a sua volta la directory e inserisce in lista i nuovi elementi trovati. L'accesso alla lista è protetto da mutex. 
A fine processo si otterrà una lista contenente path assoluti di tutti i file dal path iniziale in giù.
La directory iniziale deve essere scelta dinamicamente tramite argomento.
