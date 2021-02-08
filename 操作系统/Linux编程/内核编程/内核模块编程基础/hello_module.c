#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>

/*数据可以被定义为__initdata，对于只是初始化阶段需要的数据，内核在初始化完成之后，可以释放它们占用的内存*/
static char *init_print_string __initdata = "Hello World!";
/*只是退出阶段使用的数据可以用__exitdata来形容*/
static char *exit_print_string __exitdata = "Goodbye World!";

/*
 * 可以用module_param(参数名, 参数类型, 参数读/写权限)为模块定义一个参数
 * 在装载内核模块时，用户可以向模块传递参数，形式未insmode(modprobe)模块名 参数名=参数值，如果不传递，参数将使用模块内定义的缺省值
 * 参数类型可以是byte、short、ushort、int、uint、long、ulong、charp、bool、invbool
 * 模块也可以拥有参数数组，形式为module_param_array(数组名, 数组类型, 数组长, 参数读/写权限)，运行insmod或modprobe时，应使用逗号分隔输入的数组元素
 */
static int param_int = 1;
module_param(param_int, int, S_IRWXU);
// MOUDLE_PARM_DESC(param_int, "a int param");
static int param_int_array[2] = { 0, 1 };
static int param_int_array_args = 2;
module_param_array(param_int_array, int, &param_int_array_args, S_IRUSR | S_IRGRP | S_IROTH);
// MOUDLE_PARM_DESC(param_int_array, "a int array param");

/* 
 * 宏module_param_string()让内核把字符串直接复制到程序中的字符数组内。
 * module_param_string(name, string, len, perm);
 * 这里，name是外部的参数名，string是内部的变量名，len是以string命名的buffer大小
 */
static char param_string_array[100] = "a string array";
module_param_string(param_string_array, param_string_array, 100, S_IRUSR | S_IRGRP | S_IROTH);
// MOUDLE_PARM_DESC(param_string_array, "a int array param");

/*
 * 内核模块加载函数
 * 当通过insmod或modeprobe命令加载内核模块时，模块的加载函数会自动被内核执行，完成本模块的相关初始化工作
 * Linux内核加载函数一般以__init标识声明，它返回整形值，若初始化成功、应返回0，若初始化失败，应该返回错误编码（在<linux/errno.h>中）
 */
static int __init hello_module_init(void)
{
    /*
     * printk（）是内核的日志记录机制，用于记录信息或发出警告。
     * 每个printk（）语句都带有一个优先级 。 有8个优先级，可以在<linux/kernel.h>中查看。
     * 如果未指定优先级，则将使用默认优先级DEFAULT_MESSAGE_LOGLEVEL 。
     * 如果优先级小于int console_loglevel ，则会在当前终端上打印该消息。 
     * 如果syslogd和klogd都在运行，那么该消息也会附加到/var/log/messages，无论它是否打印到控制台。
     */
    printk(KERN_INFO "%s\n", init_print_string);

    return 0;
}

/*
 * 内核模块卸载函数
 * 当通过rmmod命令卸载某模块时，模块的卸载函数会自动被内核执行，完成与模块加载函数相反的功能
 * linux内核模块卸载函数一般以__exit标识声明，模块卸载函数会在模块卸载的时候执行，而不返回任何值
 */
static void __exit hello_module_exit(void)
{
    printk(KERN_INFO "%s\n", exit_print_string);
}

/*模块加载函数以module_init(函数名)的形式被指定*/
module_init(hello_module_init);
/*模块卸载函数必须以module_exit(函数名)的形式来指定*/
module_exit(hello_module_exit);
/*
 *模块许可证声明
 *许可证声明描述内核模块的许可权限，如果不声明LICENSE，模块加载时，将收到内核被污染的警告
 */
MODULE_LICENSE("GPL");
/*声明模块描述*/
MODULE_DESCRIPTION("A simple Hello World Module");
/*声明模块别名*/
MODULE_ALIAS("a simplest module");
/*声明模块版本*/
MODULE_VERSION("version 1.0");