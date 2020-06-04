# Device Driver

Implementing Character Device Driver.

- Device driver are use to communicate with specific hardware devices.

- Every Device Driver is module but every  module are not device driver.

- There are three type of Device Driver
    1. Character device Driver  ( device which take and give input and output directly).
    1. Block Device Driver.
    1. Network Device Driver.
    1. USB Device Driver.

- Module is use for
    1. To increase the functionality .
    1. To write system call.

---

## Kernal Command

1. lsmod               : list of module in Kernal.
2. modinfo module_name  : to see information of module.
3. insmod               : use to insert .ko (module) file inside the kernal.
4. rmmod                : Use to remove module from kernal.

---

## Note

All the printk() message is written in a kernal log file ( syslog ). This file is present inn `/var/log`
You can also see this file using command dmesg

---

## Command To Load Custom Driver

```bash
$ make
$ sudo insmod MyFirstDeviceDriver.ko
$ lsmod
$ modinfo MyFirstDeviceDriver.ko
$ sudo rmmod MyFirstDeviceDriver.ko
$ dmesg
```
