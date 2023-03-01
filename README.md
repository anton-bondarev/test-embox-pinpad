test-embox-pinpad 

This is a sample using keypad or ps-keyboard device to get 4-digit pin-code

You can run these sample on Embox (qemu, stm32)
Running on Embox

You need to have both repos cloned - embox and test-embox-pinpad.

```
$ cd embox/
$ make ext_conf EXT_PROJECT_PATH=<path-to>/test-embox-pinpad
```

Now templates are available:
```
$ make confload
...
ext_project/pinpad/arm-qemu
ext_project/pinpad/nucleo_f429zi
ext_project/pinpad/x86-qemu
```

## QEMU

```
$ make confload-ext_project/pinpad/x86-qemu
$ make 
```

Run:

./scripts/qemu/auto_qemu


## NUCLEO F429ZI

You can run some samples on NUCLEO F429ZI:

```
$ make confload-ext_project/pinpad/nucleo_f429zi
$ make
```

in new window:

`$ sudo openocd -f /usr/share/openocd/scripts/board/st_nucleo_f4.cfg`

in another new window:

`$ sudo minicom -D /dev/ttyACM0`

in the initial window:
```
$ gdb-multiarch /home/andrew/embox/build/base/bin/embox
   (gdb) tar ext :3333
   (gdb) monitor reset halt
   (gdb) load
   (gdb) c
```
now you can test this sample in minicom window:

`embox>getpin /dev/keypad`
   
in the initial window:
```
   <ctrl-c>
   (gdb) q
```

