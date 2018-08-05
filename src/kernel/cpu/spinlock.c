#include <cpu/spinlock.h>

bool try_lock(spinlock_t* lock) {
    return __sync_bool_compare_and_swap(lock, 0, 1);
}
void spin_lock(spinlock_t* lock) {
    while(!try_lock(lock)) {
        asm volatile ("hlt");
    }
}
bool spin_unlock(volatile spinlock_t* lock) {
    *lock = 0;
    return true;
}