# Device Driver

Implementing Character Device Driver.

---

## Kernal Command

1. lsmod                : list of module in Kernal.
2. modinfo module_name  : to see information of module.
3. insmod               : use to insert .ko (module) file inside the kernal.
4. rmmod                : Use to remove module from kernal.

---

## Note

All the printk message is written in kernal log file ( syslog ). This file is present inn /var/log
You can also see this file throgh command  dmesg

### Important points

- Every Device Driver is module but every  module are not device driver.

- There are three type of Device Driver
    1. Character device Driver  ( device which take and give input and output directly).
    2. Block Device Driver.
    3. Network Device Driver.
    4. USB Device Driver.

- Module is use for
    1. To increase the functionality .
    2. To write system call.

---

## Command To Run

load driver

1. make
2. sudo insmod MyFirstDeviceDriver.ko
3. lsmod
4. modinfo MyFirstDeviceDriver.ko
5. sudo rmmod MyFirstDeviceDriver.ko
6. dmesg
