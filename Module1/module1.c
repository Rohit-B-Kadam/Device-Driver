

#include<linux/module.h>	//This header must include all module program

#include<linux/kernel.h>	//Needed for KERNINFO

int init_module(void)
{
	
	printk(KERN_INFO "Marvalleous Infosystem : Initailisation");
	
	return 0;

}

void cleanup_module(void)
{
		
	printk(KERN_INFO "Mavellous Infosystem: Module is remove");
}
