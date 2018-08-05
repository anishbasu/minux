#ifndef SPINlOCK_H
#define SPINlOCK_H
#include <std/types.h>
typedef bool spinlock_t; 

bool try_lock(spinlock_t*);
void spin_lock(spinlock_t*);
bool spin_unlock(volatile spinlock_t*);
#endif