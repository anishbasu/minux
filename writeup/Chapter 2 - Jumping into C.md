# Jumping into C
## Motivation

While assembly is fun to write, it is tiring to write well. So this time around we will be compiling C using no standard libraries (since we have to make them).

## C Calling Standards
*From the System V x86-64 ABI Documentation*

Often times we have to switch from writing in C to assembly. For this purpose, there is an inbuilt function in C called **asm** which allows us to call kernel functions and pass values around. Since there is almost nno documentation on the internet about how C code can be called by the assembly, I've decided to write one myself.

|Argument #|Register|
|----------|--------|
|1         |     RDI|
|2         |     RSI|
|3         |     RDX|
|4         |     RCX|
|5         |      R8|
|6         |      R9|
|7         |     RAX|
|8         |     R10|
|9         |     R11|
|10        |     RBX|
|11        |     R14|
|12        |     R15|

The rest of the arguments are stored on the stack pointed by the stack pointer *RSP* with a size of 4 bytes. Spillage of longer data is stored in the frame pointed to by the *RBP*.

The stack is populated in the order of the arguments and popped in the opposite direction.

This fact essential to keep in mind when writing C functions that inntermingle with assembly as we will see soon.

## Compiling C
We need to use a couple of flags in gcc to compile our C files into standalone object files to link later.

```
-nostdlib -nostdinc -fno-stack-protector -Wall -Wextra -Werror -Isrc/include -m64 -s -c
```

## Calling C Functions from assembly
We have a simple main function, called kmain in our kmain.c file:

**kmain.c**

```
void kmain() {
    asm("hlt");
}
```

Which just halts the system.

We can call this function from the asm as follows:

**asm/long_mode_init.asm**

```
call kmain
```