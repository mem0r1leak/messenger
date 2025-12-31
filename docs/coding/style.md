# Coding Style
- C11
- 4 spaces indentation
- No tabs
## Headers
```C
#include <stdio.h>         // System headers comes first
#include <stdint.h>
                           // One empty line below
#include "crypto/sign.h"   // Local headers comes after
```
## Pointers
```C
unsigned char *buffer;     // The '*' symbol is aligned to variable name
```
## Functions
```C
int foo(void *arg) { // Braces on same line, space between ')' and '{'
    printf("Hello, world!");
    // One empty line between 'return' and main content
    
    return 0;
}
```
If argument list is too long:
```C
int foo(void *argument1, void *argument2 // One or several arguments per line
    void *argument3, void *argument1
){ // Braces on next line, no space between ')' and '{'
    // ...
}
```