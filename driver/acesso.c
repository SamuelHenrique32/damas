#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "driver.h"

#define DEVICE_NAME "/dev/damas"


int main(int argc, char **argv)
{
    int fp, ret;
    char message[7];
    
    fp = open("/dev/damas", 0);
    if (fp < 0)
    {
        perror("Nao foi possivel acessar\n");
        exit(0);
    }

    // Escrita
    char str[10];
    sprintf(str, "%d", 46789);
    ret = ioctl(fp, WRITE_VALUE, str);
    
    // Leitura
    //ret = ioctl(fp, READ_VALUE, message);

    if (ret < 0)
    {
        printf("Erro ao efetuar operacao");
        exit(0);
    }

    //printf("Mensagem recuperada: %s\n", message);

    close(fp);
}