#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include "driver.h"

/*-----------------------------------------*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAMUEL DALMAS E MARIA CAROLINA");
MODULE_DESCRIPTION("SO");

/*-----------------------------------------*/

#define DEVICE 60
#define DEVICE_NAME "so"
// Flag para definir se driver esta aberto
static int aberto = 0;

/*-----------------------------------------*/

// Prototipos de funcoes
static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset);
static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset);
long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param);

/*-----------------------------------------*/
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
	printk(KERN_ALERT "Essa operacao nao e permitida.\n");
	printk(KERN_ALERT "Tente executar a operacao de writer.\n");
	return 0;
}

static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset)
{
	int delay, i;
	char mensagem[100];
	for (i = 0; i < length; i++)
	{
		// modo usuario para modo kernel, put user faz o contrario
		get_user(mensagem[i], &buffer[i]);
	}
	sscanf(mensagem, "%d", &delay);
	printk("Recebi o valor de %d.\n", delay);
	//speaker(delay);
	return i;
}

long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
	int length;
	char *temp = NULL;
	printk("Vou usar o ioctl\n");
	switch (ioctl_num)
	{
	case IOCTL_SET_SPEAKER:
		temp = (char *)ioctl_param;
		length = 0;
		// ate encontrar \0
		while (*temp)
		{
			length++;
			temp++;
		}
		device_write(file, (char *)ioctl_param, length, 0);
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

