#include "Server.h"

int mainWrite (int id, const char* nomeUser, const char *passUser)
{
    FILE *userfile;
    USER_FILDERX input1;
    
    input1.ID = id;
    
    strncpy(input1.user, nomeUser, 10);
    input1.user[9]='\0'; 
    
    strncpy(input1.pass, passUser,10);
    input1.pass[9]='\0';   
    
    // open file for writing
    userfile = fopen ("userlist.dat", "a");
    if (userfile == NULL)
    {
        perror("Errore su userlist.dat\n");
        return -1;
    }

    // write struct to file
    if(  fwrite ( (struct accounting*)&input1, sizeof(struct accounting), 1, userfile) )
        printf("contents to file written successfully !\n");
    else
        printf("error writing file !\n");

    // close file
    fclose (userfile);

    return 0;
}

// Driver program
int mainRead ()
{
    int userfile;
    struct accounting input;

    userfile = open ("userlist.dat", O_RDONLY);
    if (userfile == 0)
    {
        perror("Errore nel recupero lista account\n");
        exit (1);
    }

    while( read(userfile, (struct accounting *)&input, sizeof(struct accounting) ) != 0 )
        printf ("id = %4u name = %20s \n", input.ID, input.user);

    close (userfile);

    return 0;
}


// Verifica se l'utente da argomento è inserito tra gli utenti accreditati
int mainVer (int id,const char *name,const char *pass)
{
    int userfile;
    struct accounting input;
    if(name==NULL || pass==NULL)
    {
        errno=EINVAL;
        perror("Errore nei dati di input");
        exit(-1);
    } 

    // Open accounting.dat for reading
    userfile = open ("userlist.dat", O_RDONLY);
    if (userfile == 0)
    {
        perror("Errore nel recupero lista account\n");
        exit (-2);
    }  
         
    // read file contents till end of file
    while( read(userfile, (struct accounting *)&input, sizeof(struct accounting) ) != 0 )
    {       
        if( strcmp(name,input.user) == 0 )
        {
            if(strcmp( pass, input.pass) == 0 )
            {
                close(userfile);
                return 0;
            }
        }
     }  
    close (userfile);
    return 1;
}
