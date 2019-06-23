#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAMUEL DALMAS<shdalmas@ucs.br> E MARIA CAROLINA<mcwplima@ucs.br>");
MODULE_DESCRIPTION("Trabalho SO - Jogo de Damas");

/*----------------------------------------------------------------------------*/
#define DEVICE 60
#define DEVICE_NAME "/dev/damas"
#define BUF_MSG 6

/*----------------------------------------------------------------------------*/
int device_init(void);
void device_cleanup(void);
static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *file, char __user *buffer, size_t length,loff_t * offset);
static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset);
//long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param);

/*----------------------------------------------------------------------------*/
module_init(device_init);
module_exit(device_cleanup)

/*----------------------------------------------------------------------------*/
static int is_open = 0;
static char message[BUF_MSG];
static char *ptr;

/*----------------------------------------------------------------------------*/
struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	//.unlocked_ioctl = device_ioctl
};

/*----------------------------------------------------------------------------*/
int device_init()
{
	int ret;

	ret = register_chrdev(DEVICE, DEVICE_NAME, &fops);

	if (ret < 0) {
		printk("Erro ao carregar o dispositivo %d\n.",DEVICE);
		return ret;
	}

	printk("O dispositivo %d foi carregado.\n", DEVICE);

	return 0;
}

/*----------------------------------------------------------------------------*/
void device_cleanup()
{
	unregister_chrdev(DEVICE, DEVICE_NAME);
	printk("O dispositivo %d foi descarregado.\n", DEVICE);
}

/*----------------------------------------------------------------------------*/
static int device_open(struct inode *inode, struct file *file)
{
	printk("Tentando abrir o dispositivo %d.\n", DEVICE);
	if (is_open){
		return -EBUSY;
	}
	is_open = 1;
    ptr = message;
	try_module_get(THIS_MODULE);
	printk("O dispositivo %d foi aberto.\n", DEVICE);
	return 0;
}

/*----------------------------------------------------------------------------*/
static int device_release(struct inode *inode, struct file *file)
{
	printk("Tentando fechar o dispositivo %d.\n", DEVICE);
	is_open = 0;
	module_put(THIS_MODULE);
	printk("O dispositivo %d foi fechado.\n", DEVICE);
	return 0;
}

/*----------------------------------------------------------------------------*/
static ssize_t device_read(struct file *file, char __user * buffer, size_t length, loff_t * offset){

	int bytes_read = 0;

	if (*ptr == 0){
		return 0;
	}

	while (length && *ptr) {
		put_user(*(ptr++), buffer++);
		length--;
		bytes_read++;
	}
	printk("Leu %d bytes correspondendo a mensagem: %s\n", bytes_read, message);

	return bytes_read;
}

/*----------------------------------------------------------------------------*/
static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset){

	int i;

	for (i = 0; i < length && i < BUF_MSG; i++){
		get_user(message[i], buffer + i);
	}

	printk("Escreveu a mensagem: %s\n", message);

	ptr = message;

	return i;
}

/*----------------------------------------------------------------------------*/
//long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
//{
//	int length;
//	char *temp = NULL;
//	printk("Vou usar o ioctl\n");
//	switch (ioctl_num)
//	{
//	case SET_MOVIMENTACAO:
		
//		printk("IOCTL recebeu %ld", ioctl_param);
		
//		device_write(file, (char *)ioctl_param, SET_MOVIMENTACAO_LENGTH, 0);
//	break;
//	default:
//		printk("Essa operacao nao e permitida.\n");
//		return -1;
//	}
//	return 0;
//}
