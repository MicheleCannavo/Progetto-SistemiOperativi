/** **************************************************************************
 *  \file       gestConn.c
 *  \version    1.0
 * 
 *  \brief      Funzione per'istaurazione e la gestione della connessione
 *  
 *  \retval    -1   FAILURE
 *  \retval     0   SUCCESS
 * 
 *  \details    Questa funzione avvia il serve per ricevere connessioni dai
 *              client abilitati e ne gestisce gli aspetti. La porta in ascolto
 *              e data dal valore delle impostazioni sìdi settaggi.nPort, invece
 *              gli IP accettati sono tutti tramite la macr INADDR_ANY.
 * 
 ******************************************************************************/
#include "Server.h"
#include <time.h>

int gestConn()
{
    // Variabili e inizzializzazione
    int client_sockfd = -1;
    int server_sockfd = -1;
    time_t ora;
    char l[900];
    char command[9];

    // Nuova connessione
    if (newSocket(&server_sockfd, settaggi->nPort, INADDR_ANY) != 0)
    {
        PRINTERR("Nuova connessione: ");
        return -1;
    }

    struct sockaddr_in clientaddr;
    socklen_t client_len;

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
            close(server_sockfd);

            while (1)
            {
                memset((void *)command, 0, 9);
                if (rwconf(client_sockfd, command) != 0)
                {
                    break;
                }
                // ADD_USER
                if (strncmp(command, ADD_USER, 9) == 0)
                {
                    printf("[%s] Tentativo di registrazione da %s\n",
                           strtok(ctime(&ora), "\n"),
                           inet_ntoa(clientaddr.sin_addr));
                    if (addUser(client_sockfd) != 0)
                    {
                        printf("Registrazione fallita\n");
                    }
                    else
                    {
                        printf("Registrazione Riuscita\n");
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
                        printf("Accesso negato!\n");
                        return -1;
                    }
                    else
                    {
                        printf("Accesso consentito\n");
                    }

                    memset((void *)command, 0, 9);
                    if (rwconf(client_sockfd, command) == 0)
                    {

                        // SEND_FIL
                        if (strncmp(command, SEND_FIL, 9) == 0)
                        {
                            recvFILE(client_sockfd, l, 1222);
                            continue;
                        }

                        // RECV_FIL
                        else if (strncmp(command, RECV_FIL, 9) == 0)
                        {
                            sendFILE(client_sockfd);
                            continue;
                        }

                        // SHELL
                        else if (strncmp(command, SHELL_FN, 9) == 0)
                        {
                        //    sendFILE(client_sockfd);
                            continue;
                        }
                        //
                    }
                }
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