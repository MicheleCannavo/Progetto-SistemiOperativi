#include "Client.h"


void svuota(void)
{
  printf("\x1B[1;1H\x1B[2J");
}

void timeout(int sig)
{
    signal(SIGALRM, SIG_IGN);
    errno=ETIMEDOUT;
    closeSocket();
    //close
    signal(SIGALRM,timeout);
}

int main(int argc, char * argv[])
{
    atexit(svuota);
    signal(SIGALRM,timeout);
    return myMainC(argc, argv);
}