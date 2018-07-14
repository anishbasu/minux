# Introduction
**Anish Basu**

*Minux* is an Operating System I am designing for my CS 370 class at Drexel University. Making an Operating System is a fun but time-consuming affair since a lot of things that we take for granted are not available in a bare metal system. We also need to build the compilers and binary utilities for compiling the Operating System and creating the disk image. The tutorial covers the set up of the build environment and makes headways into writing your bare metal kernel.

## Intentions
Making an Operating System is a rewarding endeavor. My intention for writing an Operating System is as follows:

- I want to know how you go from a processor that reads a single instruction at a time to a system that runs hundreds of tasks a minute
- How computers separate concerns between programs and effictively sandbox them
- How a computer knows to interact with foreign peripherals
- Program elegantly at such a low level
- It's fun!

Now that we know why we want to build an OS, let's get started with setting up a build environment. Instructions may vary due to the fact that I am using a Mac running OS X. Linux instructions should be similar.

## Setting Up
The programs we need to build the programs is:

- Netwide Assembler (NASM)
- x86-64_elf binutils installed at `~/opt/cross/bin`
- QEMU
- Linux installation that has GRUB installed

If you have all of these programs you can skip this part.

### Setting up our Development Environment on Arch Linux
#### QEMU
Installing via Homebrew:

```
brew install qemu
```

#### Download the Minimal Arch Linux ISO
The Arch Linux ISO can be downloaded from the official site [here](https://www.archlinux.org/download/). Once you have downloaded the ISO image, run:

```
qemu-img create -f qcow2 devmachine.qcow2 8G
```

Run the Virtual Machine as follows:

**./startdev.sh**

```
qemu-system-x86_64 devmachine.qcow2 -m 1G -net user,hostfwd=tcp::2200-:22 -net nic -cdrom <<PUT ISO HERE>>
```

Once the virtual machine has booted you into the terminal, proceed with installation from this [article](https://wiki.archlinux.org/index.php/installation_guide).

Some things you should have:
- Format the entire disk as a single partition and set the boot flag.
- Create your user and add a password.
- You might need to configure dhcp on first boot, run: `dhcpcd`
- On the first boot install the following: `pacman -Sy openssh nasm`
- Set up the services using systemctl `systemctl init dhcpcd.service && systemctl init openssh.service`
- Add your ssh key to your `~/.ssh/authorized_keys` file on the machine.
- SSH from your local machine using `ssh <user>@localhost -P 2200` and to test.


#### Compiling Binutils for the x86-64-elf Architecture
Since the Makefile makes use of x86-64 versions of the linker we need to cross compile a free standing version of our binutils.
The instructions on this page are enough to set it up: https://os.phil-opp.com/cross-compile-binutils/

Doing so on our dev machine will set up the environment to use this script:

**../dev/build.sh**

```
rm ../minux/minux.iso
scp -r -P 2200 ../minux localhost:~/
ssh localhost -p 2200 -t "cd minux && make"
scp -P 2200 localhost:~/minux/minux.iso ../minux/ 
ssh localhost -p 2200 -t "rm -rf minux"
```
This script shall copy our files to the dev server, build them and copy the ISO into minux.iso in the minux folder.

