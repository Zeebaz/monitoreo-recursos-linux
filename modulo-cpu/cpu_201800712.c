// para creacion de modulos
#include <linux/module.h>
// para usar KERN_INFO (informacion del kernel)
#include <linux/kernel.h>
// header para los macros module_init y module_exit
#include <linux/init.h>
// header necesario porque se usara proc_fs, para escribir en el directorio proc
#include <linux/proc_fs.h>
// para usar copy_from_user, permisos de usuario
#include <asm/uaccess.h>
// header para usar la lib seq_file y manejar el archivo en /proc
#include <linux/seq_file.h>
// devuelve información sobre estadísticas globales del sistema
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulo de control de consumo de cpu");
MODULE_AUTHOR("Jairo Sebastian Ramirez Palacios");

// funcion que se ejecutara cada vez que se lea el archivo con el comando CAT
// aqui se debe de hacer la construccion del json para obtener la informacion
struct task_struct *cpu;
struct task_struct *child;
struct list_head *lstProcess;

static int escribir_archivo(struct seq_file *archivo, void *v)
{
    seq_printf(archivo, "{\n");
    for_each_process(cpu)
    {
        seq_printf(archivo, "%s", cpu->comm);
        seq_printf(archivo, "----->");
        seq_printf(archivo, "%d", cpu->pid);
        seq_printf(archivo, "\n");

        // list_for_each(lstProcess, &(cpu->children)){

        // }
    }
    seq_printf(archivo, "}");
    return 0;
}

// funcion que se ejecutara cada vez que se lea el archivo con el comando CAT
static int al_abrir(struct inode *inode, struct file *file)
{
    return single_open(file, escribir_archivo, NULL);
}

// si el kernel es 5.6 o mayor se usa la estructura proc_ops
static struct proc_ops operaciones =
    {
        .proc_open = al_abrir,
        .proc_read = seq_read};

// funcion a ejecuta al cargar el modulo en el kernel con insmod
static int _insert(void)
{
    proc_create("cpu_201800712", 0, NULL, &operaciones);
    printk(KERN_INFO "Jairo Sebastian Ramirez Palacios\n");
    return 0;
}

// funcion a ejecuta al remover el modulo del kernel con rmmod
static void _remove(void)
{
    remove_proc_entry("cpu_201800712", NULL);
    printk(KERN_INFO "Segundo Semestre 2022\n");
}

module_init(_insert);
module_exit(_remove);