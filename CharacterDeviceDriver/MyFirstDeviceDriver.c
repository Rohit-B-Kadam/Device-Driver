
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>


#define DEVICE_NAME "Marvellous Driver 1"
#define CLASS_NAME "Marvellous Driver"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rohit kadam ....teach by Piyush sir");
MODULE_DESCRIPTION("Marvellous: visual Character Device Driver");
MODULE_VERSION("0.1");


//GLOBAL VARIABLE

static int majorNumber = 0;
static char message[256] = {0};
static short size_of_message;
static int numberOpens;
static struct class* charClass = NULL;
static struct device* charDevice = NULL;


static int dev_open( struct inode * , struct file * );
static int dev_release( struct inode * , struct file * );
static ssize_t dev_read( struct file * , char * , size_t  , loff_t  *);
static ssize_t dev_write( struct file * , const char * , size_t  , loff_t  *);

//Initialise file_operation structure

static struct file_operations fops = 
{
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};


//FUNCTION

static int __init char_init(void)
{
    printk( KERN_INFO "Marvellous : Driver loaded successfully");
    

    
    
    majorNumber = register_chrdev( 0 , DEVICE_NAME , &fops ); 
    
    if( majorNumber < 0 )
    {
        printk( KERN_ALERT "Marvellous : Failed to register a major number");
        return majorNumber;
    }
    printk( KERN_INFO "Marvellous : register correctly with majorNumber %d\n",majorNumber);


    
    
    
    charClass = class_create(THIS_MODULE , CLASS_NAME); //register class name

    if( IS_ERR( charClass ))
    {
        unregister_chrdev(majorNumber , DEVICE_NAME);
        printk( KERN_ALERT "Marvellous : Failed to register device class\n");
        return PTR_ERR(charClass);
    }
    printk( KERN_INFO "Marvellous : Device class registered correctly\n");


    
    
    
    charDevice = device_create(charClass , NULL , MKDEV(majorNumber , 0) , NULL , DEVICE_NAME);

    if( IS_ERR(charDevice) )
    {
        class_destroy(charClass);
        unregister_chrdev(majorNumber , DEVICE_NAME);
        printk( KERN_ALERT "Marvellous : Failed to register device class\n");
        return PTR_ERR(charDevice);
    }
    printk( KERN_INFO "Marvellous : Device class (driver) is created correctly\n");

    
    return 0;
}

static void __exit char_exit(void)
{
    device_destroy( charClass , MKDEV(  majorNumber , 0 ) );
    class_unregister(charClass);
    class_destroy(charClass);
    unregister_chrdev(majorNumber , DEVICE_NAME);
    printk( KERN_INFO "Marvellous: Goodbye from our driver!\n");
}




static int dev_open( struct inode * inodep , struct file * filep )
{
    numberOpens++;
    printk( KERN_INFO "Marvellous: Device has been opened %d time(s)\n",numberOpens);
    return 0;
}




static ssize_t dev_read( struct file * filep , char * buffer , size_t len , loff_t  * offset)
{
    unsigned long error_count = 0;

    error_count = copy_to_user(buffer,message,size_of_message);

    if(error_count == 0)
    {

        printk( KERN_INFO "Marvellous: Send %d character to user \n",size_of_message);
        return (size_of_message = 0 ); //clear the position to start and return 0
    
    }
    else
    {

        printk( KERN_INFO "Marvellous: Failed to send %lu character to the user\n",error_count);
        return -EFAULT; //Failed --return a bad address message (i.e -14)

    }

    return len;
}



static ssize_t dev_write( struct file * filep, const char * buffer, size_t len , loff_t  * offset )
{

    sprintf(message , "%s(%lu letter)" , buffer , len); 
    size_of_message = strlen(message);
    printk( KERN_INFO "Marvellous: Received %lu character from the user\n",len);
    return len;

}



static int dev_release( struct inode * inodep, struct file * filep )
{
    printk( KERN_INFO "Marvellous: Device successfully closed\n");
    return 0;
}


module_init(char_init);
module_exit(char_exit);
