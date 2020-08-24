# Linux I/O
就本质而言,内核只提供一种文件类型:字节流序列

UNIX系统没有文件结束符的概念,读取文件时如无数据返回,便会认定抵达文件末尾。

I/O系统调用使用非负整数来指代打开的文件,称为文件描述符。

针对每个进程,文件描述符都自成一套。

由shell启动的进程会继承3个已打开的文件描述符:
+ 描述符0为标准输入,指代为进程提供输入的文件
+ 描述符1为标准输出,指代供进程写入输出的文件
+ 描述符2为标准错误,指代供进程写入错误消息或异常通告的文件。

在stdio函数库中,这几种描述符分别与文件流stdin、stdout和stderr相对应。
![标准文件描述符](./标准文件描述符.png)

UNIX系统I/O模型最为显著的特性之一是其I/O通用性概念：
+ 同一套系统调用(open()、read()、write()、close()等)所执行的I/O 操作,可施之于所有文件类型,包括设备文件在内。
+ 应用程序发起的I/O请求,内核会将其转化为相应的文件系统操作,或者设备
驱动程序操作,以此来执行针对目标文件或设备的I/O操作。

## 通用I/O函数
### open()
open()调用既能打开一个已存在的文件,也能创建并打开一个新文件。
```
#include <sys/stat.h>
#include <fcntl.h>
int open(const char *pathname, int flags, .../*mode_t mode */);
```
+ pathname：要打开的文件，如果为符号链接，会对其进行解引用
+ flags：位掩码，用于指定文件的访问模式
![open()系统调用flags参数值介绍1](./open()系统调用的flags参数值介绍1.png)
![open()系统调用flags参数值介绍2](./open()系统调用的flags参数值介绍2.png)
+ mode：当调用open创建新文件时,位掩码参数mode指定了文件的访问权限。mode_t属于整数类型。
+ 返回值：成功返回文件描述符，出错返回-1并设置errno
SUSv3规定,如果调用open()成功,必须保证其返回值为进程未用文件描述符中数值最小者。

### creat()
creat()系统调用来创建并打开一个新文件。
```
#include <fcntl.h>
int creat(const char *pathname, mode_t mode);
```
+ pathname：要创建的文件名
+ 返回值：成功返回文件描述符，失败返回-1
若文件已存在,则打开文件,并清空文件内容,将其长度清0。

### read()
read()系统调用从文件描述符fd所指代的打开文件中读取数据。
```
#include <unistd.h>
ssize_t read(int fd, void *buffer, size_t count);
```
+ fd：要读取的文件的文件描述符
+ buffer：用来存放输入数据的内存缓冲区地址，缓冲区至少应有count个字节
+ count：最多能读取的字节数，size_t属于无符号整型
+ 返回值：成功返回实际读取的字节数,遇到文件结束(EOF)则返回0,出错则返回-1。ssize_t属于有符号的整数类型。
  
一次read()调用所读取的字节数可以小于请求的字节数。对于普通文件而言,这有可能是因为当前读取位置靠近文件尾部。

### write()
write()系统调用将数据写入一个已打开的文件中。
```
#include <unistd.h>
ssize_t write(int fd, void *buffer, size_t count);
```
+ fd：要写入文件的文件描述符
+ buffer：要写入文件中数据的内存地址
+ count：要从buffer写入文件爱你的数据字节
+ 返回值：成功返回实际写入文件的字节数,失败返回-1

返回值可能小于count参数值，这被称为“部分写”。对磁盘文件来说,造成“部分写”的原因可能是由于磁盘已满,或是因为进程资源对文件大小的限制。

对磁盘文件执行I/O操作时,write()调用成功并不能保证数据已经写入磁盘。因为为了减少磁盘活动量和加快write()系统调用,内核会缓存磁盘的I/O操作。

### close()
close()系统调用关闭一个打开的文件描述符,并将其释放回调用进程,供该进程继续使用。当一进程终止时,将自动关闭其已打开的所有文件描述符。
```
#include <unistd.h>
int close(int fd);
```
fd：已打开的文件描述符
返回值：成功返回0，出错返回-1

### lseek()
对于每个打开的文件,系统内核会记录其文件偏移量,有时也将文件偏移量称为读写偏移量或指针。文件偏移量是指执行下一个read()或write()操作的文件起始位置,会以相对于文件头部起始点的文件当前位置来表示。文件第一个字节的偏移量为0。

文件打开时,会将文件偏移量设置为指向文件开始,以后每次read()或write()调用将自动对其进行调整,以指向已读或已写数据后的下一字节。

针对文件描述符fd参数所指代的已打开文件,lseek()系统调用依照offset 和 whence 参数值调整该文件的偏移量。
```
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);
```
+ fd：要操作的文件描述符
+ offset：以字节为单位的数值
+ whence：表示参照哪个基点来解释offset参数
    - SEEK_SET：将文件偏移量设置为从文件头部起始点开始的 offset 个字节。
    - SEEK_CUR：相对于当前文件偏移量,将文件偏移量调整 offset 个字节 。
    - SEEK_END：将文件偏移量设置为起始于文件尾部的 offset 个字节。
![解释lseek()函数中whence参数](./解释lseek()函数中whence参数.png)
+ 返回值：成功返回新的文件偏移量，出错返回-1

如果whence参数值为SEEK_CUR或SEEK_END,offset参数可以为正数也可以为负数;如果whence参数值为SEEK_SET,offset参数值必须为非负数。

lseek()调用只是调整内核中与文件描述符相关的文件偏移量记录,并没有引起对任何物理设备的访问。

如果程序的文件偏移量已然跨越了文件结尾,然后再执行I/O操作,read()调用将返回0,表示文件结尾。write()函数可以在文件结尾后的任意位置写入数据。

从文件结尾后到新写入数据间的这段空间被称为文件空洞。从编程角度看,文件空洞中是存在字节的,读取空洞将返回以0(空字节)填充的缓冲区。然而,文件空洞不占用任何磁盘空间。直到后续某个时点,在文件空洞中写入了数据,文件系统才会为之分配磁盘块。

文件空洞的主要优势在于,与为实际需要的空字节分配磁盘块相比,稀疏填充的文件会占用较少的磁盘空间。核心转储文件(core dump)是包含空洞文件的常见例子。

空洞的存在意味着一个文件名义上的大小可能要比其占用的磁盘存储总量要大。向文件空洞中写入字节,内核需要为其分配存储单元,即使文件大小不变,系统的可用磁盘空间也将减少。

### ioctl()
```
#include <sys/ioctl.h>
int ioctl(int fd, int request, .../* argp */);
```
+ fd：某个设备或文件已打开的文件描述符
+ request：将在fd上执行的控制操作。具体设备的头文件定义了可传递给 request参数的常量。
+ ...：第三个参数采用了标准C语言的省略符号(...)来表示(称为argp),可以是任意数据类型。ioctl()根据request的参数值来确定 argp 所期望的类型。
+ 返回值：成功返回0，出错返回-1 

### fcntl()
fcntl()系统调用对一个打开的文件描述符执行一系列控制操作。
```
#include <fcntl.h>
int fcntl(int fd, int cmd, ...);
```
+ fd：要操作的文件描述符
+ cmd：
    - F_GETFL：针对一个打开的文件,获取或修改其访问模式和状态标志
    要判定访问模式,需使用掩码O_ACCMODE与flag相与,将结果与3个常量进行比对。
    - F_SETFL：修改打开文件的某些状态标志，O_APPEND、O_NONBLOCK、O_NOATIME、O_ASYNC和O_DIRECT
    使用 fcntl()修改文件状态标志,尤其适用于如下场景
      + 文件不是由调用程序打开的,所以程序也无法使用open()调用来控制文件的状态标志
      + 文件描述符的获取是通过open()之外的系统调用。
    为了修改打开文件的状态标志,可以使用fcntl()的F_GETFL命令来获取当前标志的副本,然后修改需要变更的比特位,最后再次调用fcntl()函数的 F_SETFL命令来更新此状态标志。
    + F_DUPFD：复制文件描述符
    + F_DUPFD_CLOEXEC：复制文件描述符并为新文件描述符设置 close-on-exec 标志。
+ ...：内核会依据cmd参数的值来确定该参数的数据类型
+ 返回值：成功返回0，出错返回-1

### dup()
dup()调用复制一个打开的文件描述符oldfd,并返回一个新描述符,二者都指向同一打开的文件句柄。系统会保证新描述符一定是编号值最低的未用文件描述符。
```
#include <unistd.h>
int dup(int oldfd);
```
+ oldfd：要复制的文件描述符
+ 返回值：成功返回新的文件描述符，失败返回-1

dup2()系统调用会为oldfd参数所指定的文件描述符创建副本,其编号由newfd参数指定。如果由 newfd 参数所指定编号的文件描述符之前已经打开,那么 dup2()会首先将其关闭。
```
#include <unistd.h>
int dup2(int oldfd, int newfd);
```
+ oldfd：要复制的文件描述符
+ newfd：创建的副本描述符
+ 返回值：成功返回新的文件描述符，失败返回-1
如果 oldfd 并非有效的文件描述符,那么 dup2()调用将失败并返回错误 EBADF,且不关闭 newfd。如果 oldfd 有效,且与 newfd 值相等,那么 dup2()将什么也不做,不关闭 newfd,并将其作为调用结果返回。

dup2()调用会默然忽略 newfd 关闭期间出现的任何错误。故此,编码时更为安全的做法是:在调用dup2()之前,若 newfd 已经打开,则应显式调用 close()将其关闭。

dup3()系统调用完成的工作与 dup2()相同,只是新增了一个附加参数 flag,这是一个可以修改系统调用行为的位掩码。
```
#define _GNU_SOURCE
#include <unistd.h>
int dup3(int oldfd, int newfd, int flags);
```
目前,dup3()只支持一个标志 O_CLOEXEC,这将促使内核为新文件描述符设置 close-on-exec标志(FD_CLOEXEC)。

### pread()和pwrite()
系统调用 pread()和 pwrite()完成与 read()和 write()相类似的工作,只是前两者会在 offset 参数所指定的位置进行文件 I/O 操作,而非始于文件的当前偏移量处,且它们不会改变文件的当前偏移量。
```
#include <unistd.h>
ssize_t pread(int fd, void *buf, size_t count, off_t offset);
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
```
多线程应用中，当调用pread()或 pwrite()时,多个线程可同时对同一文件描述符执行 I/O 操作,且不会因其他线程修改文件偏移量而受到影响。

### readv()和writev()
readv()和 writev()系统调用分别实现了分散输入和集中输出的功能。
```
#include <sys/uio.h>
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
struct iovec {
  void *iov_base; /* 缓冲区的开始地址 */
  size_t iov_len; /* 传输的字节数 */
}
```
数组 iov 定义了一组用来传输数据的缓冲区。整型数 iovcnt 则指定了 iov 的成员个数。

readv()系统调用实现了分散输入的功能:从文件描述符 fd 所指代的文件中读取一片连续的字节,然后将其散置(“分散放置”)于 iov 指定的缓冲区中。这一散置动作从 iov[0]开始,依次填满每个缓冲区。
原子性是 readv()的重要属性。换言之,从调用进程的角度来看,当调用 readv()时,内核在 fd 所指代的文件与用户内存之间一次性地完成了数据转移。这意味着,假设即使有另一进程(或线程)与其共享同一文件偏移量,且在调用 readv()的同时企图修改文件偏移量,readv()所读取的数据仍将是连续的。

调用 readv()成功将返回读取的字节数,若文件结束 将返回 0。调用者必须对返回值进行检查,以验证读取的字节数是否满足要求。若数据不足以填充所有缓冲区,则只会占用 部分缓冲区,其中最后一个缓冲区可能只存有部分数据。

writev()系统调用实现了集中输出:将 iov 所指定的所有缓冲区中的数据拼接(“集中”)起来,然后以连续的字节序列写入文件描述符 fd 指代的文件中。对缓冲区中数据的“集中”始于iov[0]所指定的缓冲区,并按数组顺序展开。

像 readv()调用一样,writev()调用也属于原子操作,即所有数据将一次性地从用户内存传输到 fd 指代的文件中。因此,在向普通文件写入数据时,writev()调用会把所有的请求数据连续写入文件,而不会在其他进程(或线程)写操作的影响下 分散地写入文件 。

如同 write()调用,writev()调用也可能存在部分写的问题。因此,必须检查 writev()调用的返回值,以确定写入的字节数是否与要求相符。

### preadv()和pwritev()
preadv()、pwritev(),将分散输入/集中输出和于指定文件偏移量处的 I/O 二者集于一身。
```
#define _BSD_SOURCE
#include <sys/uio.h>
ssize_t preadv(int fd, const struct iovec *iov, int iovcnt, off_t offset);
ssize_t pwritev(int fd, const struct iovec *iov, int iovcnt, off_t offset);
```
preadv()和 pwritev()系统调用所执行的任务与 readv()和 writev()相同,但执行 I/O 的位置将由 offset 参数指定(类似于 pread()和 pwrite()系统调用) 。

### truncate()和ftruncate()
truncate()和 ftruncate()系统调用将文件大小设置为 length 参数指定的值。
```
#include <unistd.h>
int truncate(const char *pathname, off_t length);
int ftruncate(int fd, off_t length);
```
若文件当前长度大于参数 length,调用将丢弃超出部分,若小于参数 length,调用将在文件尾部添加一系列空字节或是一个文件空洞。

两个系统调用之间的差别在于如何指定操作文件。truncate()以路径名字符串来指定文件,并要求可访问该文件 ,且对文件拥有写权限。若文件名为符号链接,那么调用将对其进行解引用。而调用 ftruncate()之前,需以可写方式打开操作文件,获取其文件描述符以指代该文件,该系统调用不会修改文件偏移量。

### mkstemp()和tmpfile()
基于调用者提供的模板,mkstemp()函数生成一个唯一文件名并打开该文件,返回一个可用于 I/O 调用的文件描述符。
```
#include <stdlib.h>
int mkstemp(char *template);
```

模板参数采用路径名形式,其中最后 6 个字符必须为 XXXXXX。这 6 个字符将被替换,以保证文件名的唯一性,且修改后的字符串将通过 template 参数传回。因为会对传入的 template参数进行修改,所以必须将其指定为字符数组,而非字符串常量。

文件拥有者对 mkstemp()函数建立的文件拥有读写权限(其他用户则没有任何操作权限),且打开文件时使用了 O_EXCL 标志,以保证调用者以独占方式访问文件。

tmpfile()函数会创建一个名称唯一的临时文件,并以读写方式将其打开。(打开该文件时使用了 O_EXCL 标志,以防一个可能性极小的冲突,即另一个进程已经创建了一个同名文件。)
```
#include <stdio.h>
FILE *tempfile(void);
```
tmpfile()函数执行成功,将返回一个文件流供 stdio 库函数使用。文件流关闭后将自动删除临时文件。为达到这一目的,tmpfile()函数会在打开文件后,从内部立即调用 unlink()来删除该文件名 。

所有系统调用都是以原子操作方式执行的。内核保证了某系统调用中的所有步骤会作为独立操作而一次性加以执行,其间不会为其他进程或线程所中断。

竞争状态是这样一种情形:操作共享资源的两个进程(或线程),其结果取决于一个无法预期的顺序,即这些进程获得CPU使用权的先后相对顺序。

## 文件描述符和打开文件之间的关系
针对每个进程,内核为其维护打开文件的描述符(open file descriptor)表。该表的每一条
目都记录了单个文件描述符的相关信息。
+ 控制文件描述符操作的一组标志。
+ 对打开文件句柄的引用。
  
内核对所有打开的文件维护有一个系统级的描述表格(open file description table)，称之为打开文件表(open file table),并将表中各条目称为打开文件句柄(open file handle) 。一个打开文件句柄存储了与一个打开文件相关的全部信息。
+ 当前文件偏移量
+ 打开文件时所使用的状态标志
+ 文件访问模式
+ 对该文件i-node对象的引用

每个文件系统都会为驻留其上的所有文件建立一个i-node表，每个文件的i-node信息包含
+ 文件类型和访问权限
+ 一个指针,指向该文件所持有的锁的列表
+ 文件的各种属性

## /dev/fd目录
对于每个进程,内核都提供有一个特殊的虚拟目录/dev/fd。该目录中包含“/dev/fd/n”形式的文件名,其中 n 是与进程中的打开文件描述符相对应的编号。
打开/dev/fd 目录中的一个文件等同于复制相应的文件描述符。

/dev/fd 实际上是一个符号链接,链接到 Linux 所专有的/proc/self/fd 目录。后者又是 Linux特有的/proc/PID/fd 目录族的特例之一,此目录族中的每一目录都包含有符号链接,与一进程所打开的所有文件相对应。

方便起见,系统还提供了 3 个符号链接:/dev/stdin、/dev/stdout 和/dev/stderr,分别链接到/dev/fd/0、/dev/fd/1 和/dev/fd/2。