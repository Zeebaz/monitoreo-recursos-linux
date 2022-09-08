#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulo de control de consumo de memoria ram");
MODULE_AUTHOR("Jairo Sebastian Ramirez Palacios");
MODULE_VERSION("1.0.0");

static int memory_proc(struct seq_file *sfile, void *v)
{
    struct sysinfo sys_info;
    si_meminfo(&sys_info);

    long total = sys_info.totalram * 4 / 1024;
    long free = sys_info.freeram * 4 / 1024;
    long in_use = total - free;

    seq_printf(sfile, "Total RAM memory: %ldMB\n", total);
    seq_printf(sfile, "Free RAM memory: %ldMB\n", free);
    seq_printf(sfile, "RAM memory in use: %ldMB\n", in_use);

    return 0;
}

static int open_proc(struct inode *inode, struct file *file)
{
    return single_open(file, memory_proc, NULL);
}

static ssize_t write_proc(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos)
{
    return 0;
}

static struct file_operations ops = {
    .owner = THIS_MODULE,
    .open = open_proc,
    .release = single_release,
    .read = seq_read,
    .llseek = seq_lseek,
    .write = write_proc,
};

static int __init memory_init(void)
{
    struct proc_dir_entry *entry = proc_create("ram2_201800712", 0, NULL, &ops);

    if (!entry)
    {
        return -1;
    }

    printk(KERN_INFO "201800712\n");
    return 0;
}

static void __exit memory_exit(void)
{
    remove_proc_entry("ram2_201800712", NULL);
    printk(KERN_INFO "Laboratorio Sistemas Operativos 1\n");
}

module_init(memory_init);
module_exit(memory_exit);