/** ***************************************************************************
 * \file        printNode.c 
 * \version     1.1
 * \date        20/12/2018
 * \copyright   Licenza GPL 3.0
 * 
 * \brief       Gestione di stampa lista concatenata per FILDERX.
 * 
 * \details     Stampa un elemento di una lista listFILDERX. La funzione 
 *              permette la stampa su un file associato adun file descriptor
 *              qualunque, e possibile utiòizarla anche per stampare su un 
 *              file di Log, oltre che su stdin.
 * 
 * \param[in]   listNodo    Elemento da stampare
 * \param[in]   fdStream    fd che identifica dove stampare l'elemento

 * \return 
 * \retval  -1  Funzione Fallita
 * \retval   0  Successo
 *****************************************************************************/
#include "FILDERX.h"

void printNode(ELEFILDERX element,int fdStream)
{
    struct stat stFilderx;
    stat(element.absPath, &stFilderx);
    dprintf(fdStream, "\n===============================================================================\n");
    dprintf(fdStream, "= %s\n",element.absPath);
    dprintf(fdStream, "----------------------------------------\n");
    dprintf(fdStream, "= File Size: \t\t%ld bytes\n", stFilderx.st_size);
    dprintf(fdStream, "= Number of Links: \t%ld\n",   stFilderx.st_nlink);
    dprintf(fdStream, "= File inode: \t\t%ld\n",      stFilderx.st_ino);
    dprintf(fdStream, "= File Permissions: \t");
    dprintf(fdStream, (S_ISDIR(stFilderx.st_mode))  ? "d" : "-");
    dprintf(fdStream, (stFilderx.st_mode & S_IRUSR) ? "r" : "-");
    dprintf(fdStream, (stFilderx.st_mode & S_IWUSR) ? "w" : "-");
    dprintf(fdStream, (stFilderx.st_mode & S_IXUSR) ? "x" : "-");
    dprintf(fdStream, (stFilderx.st_mode & S_IRGRP) ? "r" : "-");
    dprintf(fdStream, (stFilderx.st_mode & S_IWGRP) ? "w" : "-");
    dprintf(fdStream, (stFilderx.st_mode & S_IXGRP) ? "x" : "-");
    dprintf(fdStream, (stFilderx.st_mode & S_IROTH) ? "r" : "-");
    dprintf(fdStream, (stFilderx.st_mode & S_IWOTH) ? "w" : "-");
    dprintf(fdStream, (stFilderx.st_mode & S_IXOTH) ? "x" : "-");
    dprintf(fdStream, "\n===============================================================================\n");
    dprintf(fdStream, "\n\n");
}
