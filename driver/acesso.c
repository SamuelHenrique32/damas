#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "driver.h"

#define DEVICE_NAME "/dev/damas"


int main(int argc, char **argv)
{
    //FILE *f = NULL;
    //int i, delay;

    //f = fopen(DEVICE_NAME, "w");
    //printf("Digite o delay: ");
    //scanf("%d", &delay);
    //fprintf(f, "%d", delay);
    //fclose(f);    

    fp = open("/dev/damas", "O_RDWR");
    if (fp < 0)
    {
        perror("Nao foi possivel acessar\n");
        exit(0);
    }

    sprintf(str, "%d", i);
    ret = ioctl(fp, IOCTL_SET_SPEAKER, str);

    if (ret < 0)
    {
        printf("Erro ao setar o delay");
        exit(0);
    }
    close(fp);
}