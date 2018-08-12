#include <util/multiboot.h>
#include <std/types.h>

struct multiboot_tag* get_tag_by_type(struct multiboot_tag * tag, unsigned int type){
    for(tag = (struct multiboot_tag *) (tag + 8);
        tag->type != MULTIBOOT_TAG_TYPE_END;
        tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag
        + ((tag->size + 7) & ~7))) {
            if(tag->type == type){
                return tag;
            }
        }
    return NULL;
}

struct multiboot_tag_basic_meminfo* mb_get_basic_meminfo_tag(struct multiboot_tag * root){
    return (struct multiboot_tag_basic_meminfo*) get_tag_by_type(root, MULTIBOOT_TAG_TYPE_BASIC_MEMINFO);
}

struct multiboot_tag_mmap* mb_get_mmap_tag(struct multiboot_tag * root) {
    return (struct multiboot_tag_mmap*) get_tag_by_type(root, MULTIBOOT_TAG_TYPE_MMAP);
}

multiboot_memory_map_t* get_mmap_entry(struct multiboot_tag_mmap * mmap_tag, int index) {
    return (multiboot_memory_map_t *) (mmap_tag->entries + index * mmap_tag->entry_size);
}

int num_mmap_entries(struct multiboot_tag_mmap * mmap_tag) {
    return (((unsigned long) mmap_tag + mmap_tag->size) - ((unsigned long) mmap_tag->entries)) / mmap_tag->entry_size;
}
/*
for(mmap = tag->entries;mmap < tag + tag->size; mmap = mmap + tag->entry_size)
*/