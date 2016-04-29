/*******************************************************************************

 File Name: kernel.c
 Author: Shaopeng Li
 mail: lsp001@mail.ustc.edu.cn
 Created Time: 2016年04月20日 星期三 10时07分44秒

*******************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <asm/uaccess.h>

MODULE_AUTHOR("lsp");
MODULE_LICENSE("LGPL");

#define CONTENT_SYSCALL 321

int test_syscall(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	printk(KERN_INFO "test_syscall %d %d %d %d %d %d %d %d\n", a1, a2, a3, a4,
		   a5, a6, a7, a8);
	return current->pid;
}

static unsigned int clear_and_return_cr0(void)
{
	unsigned int cr0 = 0;
	unsigned int ret;
	asm("movq %%cr0, %%rax":"=a"(cr0));
	ret = cr0;
	cr0 &= 0xfffeffff;
	asm("movq %%rax, %%cr0"::"a"(cr0));
	return ret;
}

static void setback_cr0(unsigned int val)
{
	asm volatile("movq %%rax, %%cr0"::"a"(val));
}

typedef void (*sys_call_ptr_t)(void);

static sys_call_ptr_t* sys_call_table;

static sys_call_ptr_t sys_ni_syscall;

static void syscall_register(void)
{
	unsigned int oldcr0 = clear_and_return_cr0();
	sys_ni_syscall = sys_call_table[CONTENT_SYSCALL];
	sys_call_table[CONTENT_SYSCALL] = (sys_call_ptr_t)test_syscall;
	setback_cr0(oldcr0);
}

static void syscall_unregister(void)
{
    unsigned int oldcr0 = clear_and_return_cr0();
	sys_call_table[CONTENT_SYSCALL] = sys_ni_syscall;
	setback_cr0(oldcr0);
}

#define SYS_CALL_TABLE_ADDR 0xffffffff81801400

static int __init content_proto_init(void)
{
	printk(KERN_INFO "Content Protocol Init\n");
	sys_call_table = (sys_call_ptr_t*) SYS_CALL_TABLE_ADDR;
	
	syscall_register();
	
	return 0;
}

static void __exit content_proto_exit(void)
{
	printk(KERN_INFO "Content Protocol Exit\n");
	syscall_unregister();
}

module_init(content_proto_init);
module_exit(content_proto_exit);
