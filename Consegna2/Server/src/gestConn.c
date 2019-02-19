/** **************************************************************************
 * \file        gestConn.c
 * \version     1.7
 * \date        28/01/2019
 * 
 * \brief      Funzione per'istaurazione e la gestione della connessione
 *  
 * \retval    -1   FAILURE
 * \retval     0   SUCCESS
 * 
 * \details     Questa funzione avvia il serve per ricevere connessioni dai
 *              client abilitati e ne gestisce gli aspetti. La porta in ascolto
 *              e data dal valore delle impostazioni sìdi settaggi.nPort, invece
 *              gli IP accettati sono tutti tramite la macr INADDR_ANY.
 * 
 ******************************************************************************/
#include "Server.h"

int gestConn()
{
// VARIABILIE INIZIALIZZAZIONI
    int                 client_sockfd = -1;     // FD Socket connessione
    time_t              ora;                    // Per memorizzare ora attuale
    char                l[900];                 // Variabile per recvFILE
    char                command[9];             // Varibile per i comandi
    struct sockaddr_in  clientaddr;             // Per gestire indirizzi AF_INET
    socklen_t           client_len    = -1;     // Dimensione clientaddr

// Nuova connessione
    if (newSocket(&server_sockfd, settaggi->nPort, INADDR_ANY) != 0)
    {
        PRINTERR("Connessione fallita: ");
        return -1;
    }

// Intestazione
    printf("\x1B[1;1H\x1B[2J");
    printf("\t\t\t********** SERVER FILDERX **********\n");
    printf("\t\t\t            (Porta=%u)\n\n", settaggi->nPort);

    // Ciclo infinito per la comunicazione con i Client

    while (1)
    {
        client_len = sizeof(clientaddr);
        if ((client_sockfd = accept(server_sockfd, (struct sockaddr *)&clientaddr, &client_len)) < 0)
        {
            perror(__FUNCTION__);
            return -1;
        }
        ora = time(NULL);
        printf("[%s] Connessione da parte di : %s\n",
               strtok(ctime(&ora), "\n"),
               inet_ntoa(clientaddr.sin_addr));

    // Fork()
        int cpid = fork();
        if (cpid == -1)
        {
            perror(__FUNCTION__);
            return -1;
        }

        if (cpid == 0)
        {
        // Chiudo il socket_server del figlio per eliminare i vari
        // riferimenti che non permetterebbero la chiusura di esso
            close(server_sockfd); 

            while (1)
            {
            // Azzeramento variabile per i comandi e attesa ricezioe di uno di essi
                memset(command, '\0', 9);
                if (rwconf(client_sockfd, command) != 0)
                {
                    time_t ora=time(NULL);
       
                    printf("[%s] Chiusura Client [%s]\n",
                            strtok(ctime(&ora), "\n"),
                            inet_ntoa(clientaddr.sin_addr)); 

                    closefd(&client_sockfd);
                    _exit(-1);
                }

            // ADD_USER
                if (strncmp(command, ADD_USER, 9) == 0)
                {
                    printf("[%s] Tentativo di registrazione da %s\n",
                           strtok(ctime(&ora), "\n"),
                           inet_ntoa(clientaddr.sin_addr));

                    if (addUser(client_sockfd) != 0)
                    {
                        printf("[%s] Registrazione da %s FALLITA!\n",
                           strtok(ctime(&ora), "\n"),
                           inet_ntoa(clientaddr.sin_addr));
                        continue;
                    }
                    else
                    {
                        printf("[%s] Registrazione da %s RIUSCITA!\n",
                           strtok(ctime(&ora), "\n"),
                           inet_ntoa(clientaddr.sin_addr));
                        continue;
                    }
                    // return to menu'
                }

            // VER_USER
                else if (strncmp(command, VER_USER, 9) == 0)
                {
                    printf("[%s] Tentativo di accesso da %s\n",
                           strtok(ctime(&ora), "\n"),
                           inet_ntoa(clientaddr.sin_addr));

                    if (verUser(client_sockfd) != 0)
                    {
                        printf("[%s] Accesso da %s NEGATO!!\n",
                           strtok(ctime(&ora), "\n"),
                           inet_ntoa(clientaddr.sin_addr));
                        continue;
                    }
                    else
                    {
                        printf("[%s] Accesso da %s CONSENTITO\n",
                           strtok(ctime(&ora), "\n"),
                           inet_ntoa(clientaddr.sin_addr));
                        // Continuazione
                    }

                // Comandi secondari
                    memset((void *)command, 0, 9);
                    if (rwconf(client_sockfd, command) == 0)
                    {

                    // SEND_FIL
                        if (strncmp(command, SEND_FIL, 9) == 0)
                        {
                            recvFILE(client_sockfd, l, MAXBUF);
                            continue;                            
                        }

                    // REQ_FILE
                        else if (strncmp(command, REQ_FILE, 9) == 0)
                        {
                            searching(client_sockfd);
                            continue;
                        }

                    // RECV_FIL
                        else if (strncmp(command, RECV_FIL, 9) == 0)
                        {
                            sendFILE(client_sockfd);
                            continue;
                        }
                    }
                }

            // Comando sbagliato
                else
                    break;
            }
        }
        else
        {
            close(client_sockfd);
        }
    }
    exit(0);
}