#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define PROC_NAME "justASimpleModule"
#define LOG_LEVEL KERN_ALERT

MODULE_AUTHOR("Slavi Georgiev");
MODULE_DESCRIPTION("Takes a string argument and stores it in /proc.");
MODULE_LICENSE("GPL");

static char* strArg; // `static' not needed but better
module_param(strArg, charp, 0); // name, type, permissions

static int show(struct seq_file *m, void *v)
{
	seq_printf(m, "String argument `strArg': %s\n", strArg);
	return 0; // success
}

static int open(struct inode *inode, struct file *file)
{
	return single_open(file, show, NULL); // file, show, data
}

static const struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open = open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release
};

static int __init init(void)
{
	proc_create(PROC_NAME, 0, NULL, &fops); // name, mode, paremt, fops
	return 0;
}

static void __exit exit(void)
{
	printk(LOG_LEVEL "Module unloaded.\n");
	// This message would be seen with `dmesg'.
	remove_proc_entry(PROC_NAME, NULL); // comment if needed
}

module_init(init);
module_exit(exit);
