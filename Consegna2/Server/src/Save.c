#include "Server.h"

int accountWrite (int id, const char* nomeUser, const char *passUser)
{
    int userfile;
    USER_FILDERX input1;
    
    input1.ID = id;
    
    strncpy(input1.user, nomeUser, 10);
    input1.user[9]='\0'; 
    
    strncpy(input1.pass, passUser,10);
    input1.pass[9]='\0';  

// Apertura file userlist.dat
    userfile = open ("userlist.dat", O_WRONLY|O_CREAT|O_APPEND, S_IRWXU | S_IRWXO| S_IRWXG);
    if (userfile == -1)
    {
        perror(__FUNCTION__);
        return -1;
    }

// Scrittura sul file dell'account
    if(  write ( userfile, (struct accounting*)&input1, sizeof(struct accounting)) > 0 )
    {
        close(userfile);
        return 0;
    }
    else
    {
        close(userfile);
        return -1;
    }
}

// Driver program
int accountRead ()
{
    int userfile;
    USER_FILDERX input;

    userfile = open ("userlist.dat", O_RDONLY);
    if (userfile == 0)
    {
        perror("Errore nel recupero lista account\n");
        exit (1);
    }

    while( read(userfile, (USER_FILDERX *)&input, sizeof(USER_FILDERX) ) != 0 )
        printf ("id = %4u name = %20s \n", input.ID, input.user);

    close (userfile);

    return 0;
}


// Verifica se l'utente da argomento è inserito tra gli utenti accreditati
int accountVer(const char *name)
{
 ///VARIABILI E INIZIALIZZAZIONI
    int   userfile=0;
    USER_FILDERX input;

    memset((USER_FILDERX*)&input, 0, sizeof(USER_FILDERX));

// Verifica argomenti
    if(name==NULL)
    {
        errno=EINVAL;
        perror("Errore nei dati di input");
        return -1;
    } 

// Apertura accounting.dat in lettura
    userfile = open ("userlist.dat", O_RDONLY);
    if (userfile == 0)
    {
        perror("Errore nel recupero lista account\n");
        return -1;
    }  
         
    // read file contents till end of file
    while( read(userfile, (struct accounting *)&input, sizeof(struct accounting) ) != 0 )
    {       
        if( strcmp(name, input.user) == 0 )
        {
            return 0;
        }
    }  

    close (userfile);
    return 1;
}

int accountVer2(const char *name, const char *pass)
{ 
    int userfile;
    struct accounting input;  
    
// Open accounting.dat in lettura
    userfile = open ("userlist.dat", O_RDONLY);
    if (userfile == -1)
    {
        perror(__FUNCTION__);
        return -1;
    }  
int comp=1;
// Preleva e confronta gli account salvati
    while( read(userfile, (struct accounting *)&input, sizeof(struct accounting) ) > 0 )
    {       
        if( strcmp(name,input.user) == 0 )
        {
            if(strcmp( pass, input.pass) == 0 )
            {
                comp=0;
                break;
            }
        }
    }  

    if(close (userfile) != 0)
    {
        perror(__FUNCTION__);
        return -1;
    }
    return comp;
}
