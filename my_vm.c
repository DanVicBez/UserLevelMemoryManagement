#include "my_vm.h"

int initialized = 0;
int offset_bits;
int directory_bits;
int page_bits;
int directory_size;
int num_frames;

/*
Function responsible for allocating and setting your physical memory
*/
void SetPhysicalMem() {
 	offset_bits = 0;
   	int page_size = PGSIZE;
   	while(page_size >>= 1) {
   		offset_bits++;
   	}
   	
	directory_bits = (32 - offset_bits) / 2;
	page_bits = 32 - offset_bits - directory_bits;
   	directory_size = 1 << directory_bits;
   	int page_table_size = 1 << page_bits;
   	num_frames = directory_size * page_table_size;
	directory = (pde_t *) malloc(sizeof(pde_t) * directory_size);
	page_tables = (pte_t **) malloc(sizeof(pte_t *) * directory_size);
	
	int i;
	for(i = 0; i < directory_size; i++) {
		directory[i] = -1;
		page_tables[i] = (pte_t *) malloc(sizeof(pte_t) * page_table_size);
		
		int j;
		for(j = 0; j < page_table_size; j++) {
			page_tables[i][j] = 0;
		}
	}

	virtual_bitmap = (char *) malloc(num_frames / 8);
	physical_bitmap = (char *) malloc(num_frames / 8);
	
	memory = mmap(NULL, MEMSIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS, -1, 0);
}

/*
 * Part 2: Add a virtual to physical page translation to the TLB.
 * Feel free to extend the function arguments or return type.
 */
int
add_TLB(void *va, void *pa)
{

    /*Part 2 HINT: Add a virtual to physical page translation to the TLB */

    return -1;
}


/*
 * Part 2: Check TLB for a valid translation.
 * Returns the physical page address.
 * Feel free to extend this function and change the return type.
 */
pte_t *
check_TLB(void *va) {

    /* Part 2: TLB lookup code here */

}


/*
 * Part 2: Print TLB miss rate.
 * Feel free to extend the function arguments or return type.
 */
void
print_TLB_missrate()
{
    double miss_rate = 0;

    /*Part 2 Code here to calculate and print the TLB miss rate*/




    fprintf(stderr, "TLB miss rate %lf \n", miss_rate);
}


/*
The function takes a virtual address and page directories starting address and
performs translation to return the physical address
*/
pte_t *Translate(pde_t *pgdir, void *va) {
    uintptr_t ptr = (uintptr_t) va;
    int directory_index = ptr >> (32 - directory_bits);
    pde_t index = pgdir[directory_index];
    pte_t *table = page_tables[index];
	int table_index = (ptr >> offset_bits) & ((1 << (page_bits + 1)) - 1);
	pte_t index2 = table[table_index];
	int offset = ptr & (1 << offset_bits);
	char *frame = memory + index2 * PGSIZE;
	
	return (pte_t *) (frame + offset);
}

/*
The function takes a page directory address, virtual address, physical address
as an argument, and sets a page table entry. This function will walk the page
directory to see if there is an existing mapping for a virtual address. If the
virtual address is not present, then a new entry will be added
*/
int PageMap(pde_t *pgdir, void *va, void *pa) {
    uintptr_t ptr = (uintptr_t) va;
    int directory_index = ptr >> (32 - directory_bits);
    int table_index = (ptr >> offset_bits) & (1 << page_bits);
    pde_t index = pgdir[directory_index];
    
    if(index == -1) { // no page table mapped to the directory index
    	// find a page table with the required index free
    	int i;
    	for(i = 0; i < directory_size; i++) {
    		pte_t *table = page_tables[i];
    		if(table[table_index] == -1) {
    			table[table_index] = ((char *) pa - memory) / PGSIZE;
    			pgdir[directory_index] = i;
    			return 1;
    		}
    	}
    } else { // there is a mapped page table
    	pte_t *table = page_tables[index];
    	if(table[table_index] == -1) {
    		table[table_index] = ((char *) pa - memory) / PGSIZE;
   			pgdir[directory_index] = i;
   			return 1;
    	}
    }

    return 0;
}


/*Function that gets the next available page
*/
void *get_next_avail(int num_pages) {
	
	
	return NULL;
}


/* Function responsible for allocating pages
and used by the benchmark
*/
void *myalloc(unsigned int num_bytes) {
	if(!initialized) {
		initialized = true;
		SetPhysicalMem();
	}

   /* HINT: If the page directory is not initialized, then initialize the
   page directory. Next, using get_next_avail(), check if there are free pages. If
   free pages are available, set the bitmaps and map a new page. Note, you will
   have to mark which physical pages are used. */

    return NULL;
}

/* Responsible for releasing one or more memory pages using virtual address (va)
*/
void myfree(void *va, int size) {

    //Free the page table entries starting from this virtual address (va)
    // Also mark the pages free in the bitmap
    //Only free if the memory from "va" to va+size is valid
}


/* The function copies data pointed by "val" to physical
 * memory pages using virtual address (va)
*/
void PutVal(void *va, void *val, int size) {

    /* HINT: Using the virtual address and Translate(), find the physical page. Copy
       the contents of "val" to a physical page. NOTE: The "size" value can be larger
       than one page. Therefore, you may have to find multiple pages using Translate()
       function.*/

}


/*Given a virtual address, this function copies the contents of the page to val*/
void GetVal(void *va, void *val, int size) {

    /* HINT: put the values pointed to by "va" inside the physical memory at given
    "val" address. Assume you can access "val" directly by derefencing them.
    If you are implementing TLB,  always check first the presence of translation
    in TLB before proceeding forward */


}



/*
This function receives two matrices mat1 and mat2 as an argument with size
argument representing the number of rows and columns. After performing matrix
multiplication, copy the result to answer.
*/
void MatMult(void *mat1, void *mat2, int size, void *answer) {

    /* Hint: You will index as [i * size + j] where  "i, j" are the indices of the
    matrix accessed. Similar to the code in test.c, you will use GetVal() to
    load each element and perform multiplication. Take a look at test.c! In addition to
    getting the values from two matrices, you will perform multiplication and
    store the result to the "answer array"*/


}
