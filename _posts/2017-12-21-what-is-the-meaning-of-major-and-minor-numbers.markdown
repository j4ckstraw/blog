---
layout: post
title : What is the meaning of major and minor numbers
key: 20171221
category: blog
tags: linux major minor
lang: zh
---


## 问题
在我最初学习linux的ls命令时，就有这个问题，就是`ls -l /dev`打印结果的第五列和第六列的含义是什么？
通过查阅相关资料，我知道了它们是主设备号和次设备号，然而什么又是主设备号和次设备号？

## 初探
使用`ls -l /dev`命令可以列出/dev下的文件。
比如loop0的第一列中的“b”表示loop0是一个块设备文件(block device)，主设备号为7，次设备号为0，
>brw-rw----  1 root    disk      7,   0 12月 21 22:49 loop0

tty0第一列中的“c”表示tty0是一个字符设备文件(char device)，主设备号为4，次设备号为0。
>crw--w----  1 root    tty       4,   0 12月 21 22:49 tty0

null第一列中的“c”表示tty0是一个字符设备文件(其实是pseudo device)，主设备号为1，次设备号为3。
>crw-rw-rw-  1 root    root      1,   3 12月 21 22:49 null
and so on。


TLDR

以下是我设备中`ls -l /dev`输出:
{% highlight console %}
$ls -l /dev
total 0
crw-------  1 root    root     10, 235 12月 21 22:49 autofs
drwxr-xr-x  2 root    root         300 12月 21 22:49 block
drwxr-xr-x  2 root    root          80 12月 21 22:49 bsg
crw-------  1 root    root     10, 234 12月 21 22:49 btrfs-control
drwxr-xr-x  3 root    root          60 12月 22  2017 bus
lrwxrwxrwx  1 root    root           3 12月 21 22:49 cdrom -> sr0
drwxr-xr-x  2 root    root        3580 12月 21 22:49 char
crw-------  1 root    root      5,   1 12月 21 22:49 console
lrwxrwxrwx  1 root    root          11 12月 21 22:49 core -> /proc/kcore
drwxr-xr-x  2 root    root          60 12月 22  2017 cpu
crw-------  1 root    root     10,  59 12月 21 22:49 cpu_dma_latency
crw-------  1 root    root     10, 203 12月 21 22:49 cuse
drwxr-xr-x  5 root    root         100 12月 21 22:49 disk
drwxr-xr-x  2 root    root          80 12月 21 22:49 dri
lrwxrwxrwx  1 root    root           3 12月 21 22:49 dvd -> sr0
crw-------  1 root    root     10,  61 12月 21 22:49 ecryptfs
crw-rw----  1 root    video    29,   0 12月 21 22:49 fb0
lrwxrwxrwx  1 root    root          13 12月 21 22:49 fd -> /proc/self/fd
crw-rw-rw-  1 root    root      1,   7 12月 21 22:49 full
crw-rw-rw-  1 root    root     10, 229 12月 21 22:49 fuse
crw-------  1 root    root    248,   0 12月 21 22:49 hidraw0
crw-------  1 root    root     10, 228 12月 21 22:49 hpet
drwxr-xr-x  2 root    root           0 12月 21 22:49 hugepages
crw-------  1 root    root     10, 183 12月 21 22:49 hwrng
crw-------  1 root    root     89,   0 12月 21 22:49 i2c-0
lrwxrwxrwx  1 root    root          25 12月 21 22:49 initctl -> /run/systemd/initctl/fifo
drwxr-xr-x  4 root    root         320 12月 21 22:49 input
crw-r--r--  1 root    root      1,  11 12月 21 22:49 kmsg
drwxr-xr-x  2 root    root          60 12月 22  2017 lightnvm
lrwxrwxrwx  1 root    root          28 12月 21 22:49 log -> /run/systemd/journal/dev-log
brw-rw----  1 root    disk      7,   0 12月 21 22:49 loop0
brw-rw----  1 root    disk      7,   1 12月 21 22:49 loop1
brw-rw----  1 root    disk      7,   2 12月 21 22:49 loop2
brw-rw----  1 root    disk      7,   3 12月 21 22:49 loop3
brw-rw----  1 root    disk      7,   4 12月 21 22:49 loop4
brw-rw----  1 root    disk      7,   5 12月 21 22:49 loop5
brw-rw----  1 root    disk      7,   6 12月 21 22:49 loop6
brw-rw----  1 root    disk      7,   7 12月 21 22:49 loop7
crw-rw----  1 root    disk     10, 237 12月 21 22:49 loop-control
drwxr-xr-x  2 root    root          60 12月 22  2017 mapper
crw-------  1 root    root     10, 227 12月 21 22:49 mcelog
crw-r-----  1 root    kmem      1,   1 12月 21 22:49 mem
drwxr-xr-x  2 root    root          60 12月 22  2017 net
crw-rw-rw-  1 root    root      1,   3 12月 21 22:49 null
crw-r-----  1 root    kmem      1,   4 12月 21 22:49 port
crw-------  1 root    root    108,   0 12月 21 22:49 ppp
crw-------  1 root    root     10,   1 12月 21 22:49 psaux
crw-rw-rw-  1 root    tty       5,   2 12月 22 09:52 ptmx
drwxr-xr-x  2 root    root           0 12月 22  2017 pts
crw-rw-rw-  1 root    root      1,   8 12月 21 22:49 random
crw-rw-r--+ 1 root    netdev   10,  62 12月 21 22:49 rfkill
lrwxrwxrwx  1 root    root           4 12月 21 22:49 rtc -> rtc0
crw-------  1 root    root    251,   0 12月 21 22:49 rtc0
brw-rw----  1 root    disk      8,   0 12月 21 22:49 sda
brw-rw----  1 root    disk      8,   1 12月 21 22:49 sda1
brw-rw----  1 root    disk      8,   2 12月 21 22:49 sda2
brw-rw----  1 root    disk      8,   5 12月 21 22:49 sda5
crw-rw----+ 1 root    cdrom    21,   0 12月 21 22:49 sg0
crw-rw----  1 root    disk     21,   1 12月 21 22:49 sg1
drwxrwxrwt  2 root    root         240 12月 22 09:42 shm
crw-------  1 root    root     10, 231 12月 21 22:49 snapshot
drwxr-xr-x  3 root    root         180 12月 21 22:49 snd
brw-rw----+ 1 root    cdrom    11,   0 12月 21 22:49 sr0
lrwxrwxrwx  1 root    root          15 12月 21 22:49 stderr -> /proc/self/fd/2
lrwxrwxrwx  1 root    root          15 12月 21 22:49 stdin -> /proc/self/fd/0
lrwxrwxrwx  1 root    root          15 12月 21 22:49 stdout -> /proc/self/fd/1
crw-rw-rw-  1 root    tty       5,   0 12月 22 09:45 tty
crw--w----  1 root    tty       4,   0 12月 21 22:49 tty0
crw--w----  1 root    tty       4,   1 12月 22 09:40 tty1
crw--w----  1 root    tty       4,   2 12月 21 22:49 tty2
crw--w----  1 root    tty       4,   3 12月 21 22:49 tty3
crw--w----  1 root    tty       4,   4 12月 21 22:49 tty4
crw--w----  1 root    tty       4,   5 12月 21 22:49 tty5
crw--w----  1 root    tty       4,   6 12月 21 22:49 tty6
crw--w----  1 root    tty       4,   7 12月 21 22:49 tty7
crw--w----  1 root    tty       4,   8 12月 21 22:49 tty8
crw--w----  1 root    tty       4,   9 12月 21 22:49 tty9
crw-------  1 root    root      5,   3 12月 21 22:49 ttyprintk
crw-rw----  1 root    dialout   4,  64 12月 21 22:49 ttyS0
crw-rw----  1 root    dialout   4,  65 12月 21 22:49 ttyS1
crw-rw----  1 root    dialout   4,  66 12月 21 22:49 ttyS2
crw-rw----  1 root    dialout   4,  68 12月 21 22:49 ttyS4
crw-rw----  1 root    dialout   4,  69 12月 21 22:49 ttyS5
crw-rw----  1 root    dialout   4,  70 12月 21 22:49 ttyS6
crw-rw----  1 root    dialout   4,  71 12月 21 22:49 ttyS7
crw-rw----  1 root    dialout   4,  72 12月 21 22:49 ttyS8
crw-rw----  1 root    dialout   4,  73 12月 21 22:49 ttyS9
crw-------  1 root    root     10, 239 12月 21 22:49 uhid
crw-------  1 root    root     10, 223 12月 21 22:49 uinput
crw-rw-rw-  1 root    root      1,   9 12月 21 22:49 urandom
crw-rw----  1 root    tty       7,   0 12月 21 22:49 vcs
crw-rw----  1 root    tty       7,   1 12月 21 22:49 vcs1
crw-rw----  1 root    tty       7,   2 12月 21 22:49 vcs2
crw-rw----  1 root    tty       7,   3 12月 21 22:49 vcs3
crw-rw----  1 root    tty       7,   4 12月 21 22:49 vcs4
crw-rw----  1 root    tty       7,   5 12月 21 22:49 vcs5
crw-rw----  1 root    tty       7,   6 12月 21 22:49 vcs6
crw-rw----  1 root    tty       7,   7 12月 21 22:49 vcs7
crw-rw----  1 root    tty       7, 128 12月 21 22:49 vcsa
crw-rw----  1 root    tty       7, 129 12月 21 22:49 vcsa1
crw-rw----  1 root    tty       7, 130 12月 21 22:49 vcsa2
{% endhighlight %}

## 一切皆文件
“一切皆文件”是Unix的基本哲学之一。
这里的主设备号和次设备号也是这样的，实际使用中有很多设备，linux把设备分类为字符设备（Char devices），块设备（Block devices）。可以使用`cat /proc/devices`查看机器支持的设备类型。我们知道不同的设备需要不同的驱动，linux就是根据主设备号来区分设备，从而确定该使用什么驱动来操作设备。而同一种设备可能不止一个，比如我机器上可以插两块硬盘，次设备号是该类设备的编号，用以区分同种设备。

TLDR

以下是我设备中`cat /proc/devices`的输出:
{% highlight console %}
$cat /proc/devices
Character devices:
  1 mem
  4 /dev/vc/0
  4 tty
  4 ttyS
  5 /dev/tty
  5 /dev/console
  5 /dev/ptmx
  5 ttyprintk
  6 lp
  7 vcs
 10 misc
 13 input
 21 sg
 29 fb
 89 i2c
 99 ppdev
108 ppp
116 alsa
128 ptm
136 pts
180 usb
189 usb_device
226 drm
247 aux
248 hidraw
249 bsg
250 watchdog
251 rtc
252 dimmctl
253 ndctl
254 tpm

Block devices:
259 blkext
  7 loop
  8 sd
  9 md
 11 sr
 65 sd
 66 sd
 67 sd
 68 sd
 69 sd
 70 sd
 71 sd
128 sd
129 sd
130 sd
131 sd
132 sd
133 sd
134 sd
135 sd
252 device-mapper
253 virtblk
254 mdp
{% endhighlight %}

## 创建设备文件
可以通过mknod命令来创建设备文件。
`man mknod`给出的描述是

{% highlight text %}
$mknod --mode=640 myhd b 3 10
{% endhighlight %}
可以创建一个主设备号为3，次设备号为10的块设备文件。

具体使用可以查看`man mknod`


## 打破砂锅问到底
那这些设备号又是由谁规定的呢，为啥主设备号3表示IDE设备，而主设备号8表示SCIS设备呢？
这当然是由内核规定。

在内核头文件中有定义，查看usr/src/linux-headers-xxx/include/uapi/linux/major.h文件。

{% highlight c %}
#define IDE0_MAJOR    3 
#define SCSI_DISK0_MAJOR  8
{% endhighlight %}

所以主设备号3表示IDE设备，而主设备号8表示SCIS设备，遇到不知名的设备号，可以通过查看/usr/src/linux-headers-xxx/include/uapi/linux/major.h来获得信息。

在linux内核源代码中有一个Documents文件夹，这里有很多说明文档。其中有一个[devices.txt](https://github.com/torvalds/linux/blob/master/Documentation/admin-guide/devices.txt)文件是对设备号的说明，这里的信息更加完整，而且我还发现即使主设备号相同，因为设备类型的不同，设备也是不同的。例如

{% highlight text %}
   3 char Pseudo-TTY slaves
      0 = /dev/ttyp0  First PTY slave
      1 = /dev/ttyp1  Second PTY slave
        ...
    255 = /dev/ttyef  256th PTY slave

    These are the old-style (BSD) PTY devices; Unix98
    devices are on major 136 and above.

   3 block  First MFM, RLL and IDE hard disk/CD-ROM interface
      0 = /dev/hda    Master: whole disk (or CD-ROM)
     64 = /dev/hdb    Slave: whole disk (or CD-ROM)

    For partitions, add to the whole disk device number:
      0 = /dev/hd?    Whole disk
      1 = /dev/hd?1   First partition
      2 = /dev/hd?2   Second partition
        ...
     63 = /dev/hd?63  63rd partition

    For Linux/i386, partitions 1-4 are the primary
    partitions, and 5 and above are logical partitions.
    Other versions of Linux use partitioning schemes
    appropriate to their respective architectures.
{% endhighlight %}

主设备号都是1，字符设备表示Memory devices，块设备表示RAM disk；
主设备号都是3，字符设备表示Pseudo-TTY slaves，块设备表示First MFM, RLL and IDE hard disk/CD-ROM interface。
竟然有这么多类型的Memory devices，一般我们用来生成空文件的/dev/zero （通过dd if=/dev/zero of=hda.img bs=$[1024*1024] count=512），还有“黑洞设备”/dev/null都是Memory devices，Interesting！


TLDR

以下是我设备中`cat /usr/src/linux-headers-4.4.0-103/include/uapi/linux/major.h`输出:

{% highlight console %}
#ifndef _LINUX_MAJOR_H
#define _LINUX_MAJOR_H

/*
 * This file has definitions for major device numbers.
 * For the device number assignments, see Documentation/devices.txt.
 */

#define UNNAMED_MAJOR   0
#define MEM_MAJOR   1
#define RAMDISK_MAJOR   1
#define FLOPPY_MAJOR    2
#define PTY_MASTER_MAJOR  2
#define IDE0_MAJOR    3
#define HD_MAJOR    IDE0_MAJOR
#define PTY_SLAVE_MAJOR   3
#define TTY_MAJOR   4
#define TTYAUX_MAJOR    5
#define LP_MAJOR    6
#define VCS_MAJOR   7
#define LOOP_MAJOR    7
#define SCSI_DISK0_MAJOR  8
#define SCSI_TAPE_MAJOR   9
#define MD_MAJOR    9
#define MISC_MAJOR    10
#define SCSI_CDROM_MAJOR  11
#define MUX_MAJOR   11  /* PA-RISC only */
#define XT_DISK_MAJOR   13
#define INPUT_MAJOR   13
#define SOUND_MAJOR   14
#define CDU31A_CDROM_MAJOR  15
#define JOYSTICK_MAJOR    15
#define GOLDSTAR_CDROM_MAJOR  16
#define OPTICS_CDROM_MAJOR  17
#define SANYO_CDROM_MAJOR 18
#define CYCLADES_MAJOR    19
#define CYCLADESAUX_MAJOR 20
#define MITSUMI_X_CDROM_MAJOR 20
#define MFM_ACORN_MAJOR   21  /* ARM Linux /dev/mfm */
#define SCSI_GENERIC_MAJOR  21
#define IDE1_MAJOR    22
#define DIGICU_MAJOR    22
#define DIGI_MAJOR    23
#define MITSUMI_CDROM_MAJOR 23
#define CDU535_CDROM_MAJOR  24
#define STL_SERIALMAJOR   24
#define MATSUSHITA_CDROM_MAJOR  25
#define STL_CALLOUTMAJOR  25
#define MATSUSHITA_CDROM2_MAJOR 26
#define QIC117_TAPE_MAJOR 27
#define MATSUSHITA_CDROM3_MAJOR 27
#define MATSUSHITA_CDROM4_MAJOR 28
#define STL_SIOMEMMAJOR   28
#define ACSI_MAJOR    28
#define AZTECH_CDROM_MAJOR  29
#define FB_MAJOR    29   /* /dev/fb* framebuffers */
#define MTD_BLOCK_MAJOR   31
#define CM206_CDROM_MAJOR 32
#define IDE2_MAJOR    33
#define IDE3_MAJOR    34
#define Z8530_MAJOR   34
#define XPRAM_MAJOR   35   /* Expanded storage on S/390: "slow ram"*/
#define NETLINK_MAJOR   36
#define PS2ESDI_MAJOR   36
#define IDETAPE_MAJOR   37
#define Z2RAM_MAJOR   37
#define APBLOCK_MAJOR   38   /* AP1000 Block device */
#define DDV_MAJOR   39   /* AP1000 DDV block device */
#define NBD_MAJOR   43   /* Network block device  */
#define RISCOM8_NORMAL_MAJOR  48
#define DAC960_MAJOR    48   /* 48..55 */
#define RISCOM8_CALLOUT_MAJOR 49
#define MKISS_MAJOR   55
#define DSP56K_MAJOR    55   /* DSP56001 processor device */

#define IDE4_MAJOR    56
#define IDE5_MAJOR    57

#define SCSI_DISK1_MAJOR  65
#define SCSI_DISK2_MAJOR  66
#define SCSI_DISK3_MAJOR  67
#define SCSI_DISK4_MAJOR  68
#define SCSI_DISK5_MAJOR  69
#define SCSI_DISK6_MAJOR  70
#define SCSI_DISK7_MAJOR  71

#define COMPAQ_SMART2_MAJOR 72
#define COMPAQ_SMART2_MAJOR1  73
#define COMPAQ_SMART2_MAJOR2  74
#define COMPAQ_SMART2_MAJOR3  75
#define COMPAQ_SMART2_MAJOR4  76
#define COMPAQ_SMART2_MAJOR5  77
#define COMPAQ_SMART2_MAJOR6  78
#define COMPAQ_SMART2_MAJOR7  79

#define SPECIALIX_NORMAL_MAJOR  75
#define SPECIALIX_CALLOUT_MAJOR 76

#define AURORA_MAJOR    79

#define I2O_MAJOR   80  /* 80->87 */

#define SHMIQ_MAJOR   85   /* Linux/mips, SGI /dev/shmiq */
#define SCSI_CHANGER_MAJOR      86

#define IDE6_MAJOR    88
#define IDE7_MAJOR    89
#define IDE8_MAJOR    90
#define MTD_CHAR_MAJOR    90
#define IDE9_MAJOR    91

#define DASD_MAJOR    94

#define MDISK_MAJOR   95

#define UBD_MAJOR   98

#define PP_MAJOR    99
#define JSFD_MAJOR    99

#define PHONE_MAJOR   100

#define COMPAQ_CISS_MAJOR 104
#define COMPAQ_CISS_MAJOR1  105
#define COMPAQ_CISS_MAJOR2      106
#define COMPAQ_CISS_MAJOR3      107
#define COMPAQ_CISS_MAJOR4      108
#define COMPAQ_CISS_MAJOR5      109
#define COMPAQ_CISS_MAJOR6      110
#define COMPAQ_CISS_MAJOR7      111

#define VIODASD_MAJOR   112
#define VIOCD_MAJOR   113

#define ATARAID_MAJOR   114

#define SCSI_DISK8_MAJOR  128
#define SCSI_DISK9_MAJOR  129
#define SCSI_DISK10_MAJOR 130
#define SCSI_DISK11_MAJOR 131
#define SCSI_DISK12_MAJOR 132
#define SCSI_DISK13_MAJOR 133
#define SCSI_DISK14_MAJOR 134
#define SCSI_DISK15_MAJOR 135

#define UNIX98_PTY_MASTER_MAJOR 128
#define UNIX98_PTY_MAJOR_COUNT  8
#define UNIX98_PTY_SLAVE_MAJOR  (UNIX98_PTY_MASTER_MAJOR+UNIX98_PTY_MAJOR_COUNT)

#define DRBD_MAJOR    147
#define RTF_MAJOR   150
#define RAW_MAJOR   162

#define USB_ACM_MAJOR   166
#define USB_ACM_AUX_MAJOR 167
#define USB_CHAR_MAJOR    180

#define MMC_BLOCK_MAJOR   179

#define VXVM_MAJOR    199 /* VERITAS volume i/o driver    */
#define VXSPEC_MAJOR    200 /* VERITAS volume config driver */
#define VXDMP_MAJOR   201 /* VERITAS volume multipath driver */

#define XENVBD_MAJOR    202 /* Xen virtual block device */

#define MSR_MAJOR   202
#define CPUID_MAJOR   203

#define OSST_MAJOR    206 /* OnStream-SCx0 SCSI tape */

#define IBM_TTY3270_MAJOR 227
#define IBM_FS3270_MAJOR  228

#define VIOTAPE_MAJOR   230

#define BLOCK_EXT_MAJOR   259
#define SCSI_OSD_MAJOR    260 /* open-osd's OSD scsi device */

#endif
{% endhighlight %}

## 延伸
然而随着内核版本的不断更新，出现了[devfs](https://en.wikipedia.org/wiki/Device_file)，这个东西(其实早就出现了,大概在linux2.4)，后来又有了[udev](https://en.wikipedia.org/wiki/Udev)，设备管理机制越来越复杂，安全性也渐渐提高。

## 参考
[Major and Minor Numbers](https://www.safaribooksonline.com/library/view/linux-device-drivers/0596000081/ch03s02.html)

[Wiki-Device file](https://en.wikipedia.org/wiki/Device_file)

<!--more-->
