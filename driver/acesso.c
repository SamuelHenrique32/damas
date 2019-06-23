#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "driver.h"

#define DEVICE_NAME "/dev/damas"


int main(int argc, char **argv)
{
    int fp, ret;   

    fp = open("/dev/damas", O_RDWR);
    if (fp < 0)
    {
        perror("Nao foi possivel acessar\n");
        exit(0);
    }

    // Pos atual pos final
    ret = ioctl(fp, 1, 4678);

    if (ret < 0)
    {
        printf("Erro ao setar o delay");
        exit(0);
    }
    close(fp);
}