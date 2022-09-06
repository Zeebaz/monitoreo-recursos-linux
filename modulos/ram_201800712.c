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
#include <sys/sysinfo.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulo de control de consumo de memoria ram");
MODULE_AUTHOR("Jairo Sebastian Ramirez Palacios");

// funcion que se ejecutara cada vez que se lea el archivo con el comando CAT
// aqui se debe de hacer la construccion del json para obtener la informacion
static int escribir_archivo(struct seq_file *archivo, void *v)
{
    // int sysinfo(struct sysinfo *info)
    // struct sysinfo si;
    // sysinfo(&si);
    // const double porcentaje = (si.totalram - si.freeram)* (100/si.totalram);

   /* Conversion constants. */
    const long minute = 60;
    const long hour = minute * 60;
    const long day = hour * 24;
    const double megabyte = 1024 * 1024;
    /* Obtain system statistics. */
    struct sysinfo si;
    sysinfo(&si);
    /* Summarize interesting values. */
    // printf("system uptime : %ld days, %ld:%02ld:%02ld\n",
    //        si.uptime / day, (si.uptime % day) / hour,
    //        (si.uptime % hour) / minute, si.uptime % minute);
    // printf("total RAM   : %5.1f MB\n", si.totalram / megabyte);
    // printf("free RAM   : %5.1f MB\n", si.freeram / megabyte);
    // printf("process count : %d\n", si.procs);


    seq_printf(archivo, "{");
    seq_printf(archivo, "}");
    return 0;
}

// seq_printf(archivo, "\"porcentaje\":\"" + porcentaje + "\"");
/* Conversion constants. */
// const double megabyte = 1024 * 1024;

/* Obtain system statistics. */
// int sysinfo(struct sysinfo *info);
// struct sysinfo si =

/* Summarize interesting values. */
// printf("total RAM   : %5.1f MB\n", si.totalram / megabyte);
// printf("free RAM   : %5.1f MB\n", si.freeram / megabyte);
// printf("process count : %d\n", si.procs);

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
    proc_create("ram_201800712", 0, NULL, &operaciones);
    printk(KERN_INFO "201800712\n");
    return 0;
}

// funcion a ejecuta al remover el modulo del kernel con rmmod
static void _remove(void)
{
    remove_proc_entry("ram_201800712", NULL);
    printk(KERN_INFO "Laboratorio Sistemas Operativos 1\n");
}

module_init(_insert);
module_exit(_remove);