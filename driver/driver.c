#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include "driver.h"

/*-----------------------------------------*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAMUEL DALMAS<shdalmas@ucs.br> E MARIA CAROLINA<mcwplima@ucs.br>");
MODULE_DESCRIPTION("Trabalho SO - Jogo de Damas");

/*-----------------------------------------*/

// Parametros do Modulo
#define DEVICE 60
#define DEVICE_NAME "so"
#define BUFFER 6

/*-----------------------------------------*/

// Variaveis
// Flag para definir se driver esta aberto
static int aberto = 0;
static char msg[BUFFER];
static char *ptr;

/*-----------------------------------------*/

// Prototipos de funcoes
static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset);
static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset);
long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param);

/*-----------------------------------------*/

// Operacoes do Modulo
struct file_operations fops = {
	.open = device_open,
	.release = device_release,
	.read = device_read,
	.write = device_write,
	.unlocked_ioctl = device_ioctl
};
/*-----------------------------------------*/
int init_module(void) {
	int ret = register_chrdev(DEVICE, DEVICE_NAME, &fops);

	if (ret < 0) {
		printk("Erro ao carregar o dispositivo %d\n.", DEVICE);	
		return ret;
	}
	printk("O dispositivo %d foi carregado.\n", DEVICE);
	return 0;
}

static int device_open(struct inode *inode, struct file *file)
{
	printk("Tentando abrir o dispositivo %d.\n", DEVICE);

	// nao implementar dessa maneira se for concorrente (somente para FIFO e atomica)
	if (aberto)
	{
		return -EBUSY;
	}

	aberto++;
	// pega acesso ao modulo
	ptr = msg;
	try_module_get(THIS_MODULE);
	printk("O dispositivo %d foi aberto.\n", DEVICE);
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	printk("Tentando fechar o dispositivo %d.\n", DEVICE);
	aberto--;
	module_put(THIS_MODULE);
	printk("O dispositivo %d foi fechado.\n", DEVICE);
	return 0;
}

static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset)
{
	int bytes_read = 0;

	if (*ptr == 0)
		return 0;

	while(length && *ptr){
		put_user(*(ptr++), buffer++);
		length--;
		bytes_read++;
	}

	printk("Leu %d bytes correspondendo a mensagem %s\n", bytes_read, msg);
	return bytes_read;
}

static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset)
{
	int i;
	
	for (i = 0; i < length && i < BUFFER; i++)
	{
		// modo usuario para modo kernel, put user faz o contrario
		get_user(msg[i], buffer+i);
	}

	printk("Escreveu a mensagem: %s\n", msg);
	ptr = msg;
	return i;
}

long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
	int i;
	printk("IOCTL recebeu CASE %d\n", ioctl_num);
	switch (ioctl_num)
	{
		case WRITE_VALUE:		
			printk("IOCTL recebeu param para escrita\n");
			device_write(file, (char *)ioctl_param, BUFFER, 0);
		break;
		
		case READ_VALUE:
			printk("IOCTL recebeu param para leitura\n");
			i = device_read(file, (char *)ioctl_param, BUFFER, 0);
			put_user('\0', (char *)ioctl_param + i);
		break;

		default:
			printk("Essa operacao nao e permitida.\n");
			return -1;
	}
	return 0;
}

/*-----------------------------------------*/
void cleanup_module (void) {
	unregister_chrdev(DEVICE, DEVICE_NAME);
	printk("O dispositivo %d foi descarregado.\n", DEVICE);
}

/*-----------------------------------------*/