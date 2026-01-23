#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
struct arena
{
    char* base_ptr;
    size_t reserved_size;
    size_t commited_size;
    size_t current_offset;
};

size_t PAGE_SIZE;

void init_page_size(void) {
    PAGE_SIZE = (size_t)sysconf(_SC_PAGE_SIZE);
}

size_t round_up_to_page_size(size_t size)
{
    return (size + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
}

struct arena* create_arena(size_t reserved_size)
{
    struct arena* parena = (struct arena*)malloc(sizeof(struct arena));

    if(!parena) return NULL;
    reserved_size = round_up_to_page_size(reserved_size);
    
    void* block = mmap(NULL, reserved_size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if(block == MAP_FAILED)
    {
	free(parena);
	return NULL;
    }

    parena->base_ptr = (char*)block;
    parena->commited_size = 0;
    parena->reserved_size = reserved_size;
    parena->current_offset = 0;
    return parena;
}

void* ArenaAlloc(struct arena* parena, size_t size)
{
    if(!parena || size == 0) return NULL;

    size_t new_offset = parena->current_offset + size;

    if(new_offset > parena->reserved_size)
    {
	return NULL;
    }

    if(new_offset > parena->commited_size)
    {
	size_t new_commit_target = round_up_to_page_size(new_offset);
	
	size_t size_to_commit = new_commit_target - parena->commited_size;
	void* commit_start_addr = parena->base_ptr + parena->commited_size;
	    
	if (mprotect(commit_start_addr, size_to_commit, PROT_READ | PROT_WRITE) != 0) {
	    return NULL;
	}

	parena->commited_size = new_commit_target;	
    }

    void* memory = parena->base_ptr + parena->current_offset;
    parena->current_offset = new_offset;

    return memory;
}


void arena_reset(struct arena* parena)
{
    mprotect(parena->base_ptr, parena->commited_size, PROT_NONE);
    parena->commited_size = 0;
    parena->current_offset = 0;
}
void arena_release(struct arena* parena)
{
    munmap(parena->base_ptr, parena->reserved_size); 
    free(parena); 
}

int main()
{ 
    init_page_size();
    struct arena* arena = create_arena(1024 * 1024);
						    
    int* a = (int*)ArenaAlloc(arena, sizeof(int));
    int* b = (int*)ArenaAlloc(arena, sizeof(int));

    *a = 40;
    *b = 2;

    int sum = *a + *b;
    printf("sum = %d\n", sum);

    arena_release(arena);
    return 0;
}
