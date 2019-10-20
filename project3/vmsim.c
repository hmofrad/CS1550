/*
 * vmsim.c: Virtual memory implementation skeleton code
 * with a single level 32-Bit page table and
 * fifo page replacement algorithm
 * ToDO: Implement other requested page replacement algorithms
 *       
 * (c) Mohammad Hasanzadeh Mofrad, 2019
 * (e) moh18@pitt.edu
 *
 */
 
#include "vmsim.h"

void* allocate(unsigned long int size) {
    void* ptr = NULL;
    if(size) {        
        ptr = malloc(size);
        if(!ptr) {
            fprintf(stderr, "Error on mallocing memory\n");
            exit(1);
        }
        memset(ptr, 0, size);
    }
    return(ptr);
}

int main(int argc, char* argv[]) {
   /*
    * Add sanity check for input arguments
    * Open the memory trace file 
    * and store it in an array
    */
    
    if(argc != 6) {
        fprintf(stderr, "USAGE: %s -n <numframes> -a <fifo> <tracefile>\n", argv[0]);
        exit(1);         
    }
    
    numframes = atoi(argv[2]);
    char* algorithm = argv[4];
    char* filename = argv[5];
    FILE* file = fopen(filename,"rb");
    if(!file) {
        fprintf(stderr, "Error on opening %s\n", filename);
        exit(1); 
    }

    /* 
     * Calculate the trace file's length
     * and read in the trace file
     * and write it into addr_arr and mode_arr arrays 
     */

    unsigned int numaccesses = 0;
    unsigned char mode = '\0';
    unsigned int addr = 0;
    unsigned int cycles = 0;

    // Calculate number of lines in the trace file
    while(fscanf(file, "%c %x %d\n", &mode, &addr, &cycles) == 3) {
        numaccesses++;
    }
    rewind(file);

    unsigned char mode_array[numaccesses];
    unsigned int address_array[numaccesses];
    unsigned int cycles_array[numaccesses];
   
    unsigned int i = 0;
    // Store the memory accesses 
    while(fscanf(file, "%c %x %d\n", &mode_array[i], &address_array[i], &cycles_array[i]) == 3) {
        i++;
    }

    if(fclose(file)) {
        fprintf(stderr, "Error on closing %s\n", filename);
        exit(1);
    }
    
    if(i != numaccesses) {
        fprintf(stderr, "Arrays are populated incorrectly\n");
        exit(1);
    }

    // Initialize the physical memory address space
    long frame_size = PAGE_SIZE_4KB / PAGE_SIZE_UNITS;
    long memory_size = frame_size * numframes;
    physical_frames = (unsigned int*) allocate(memory_size);
    
    // Create the first frame of the frames linked list
    struct frame_struct* head = NULL;
    struct frame_struct* curr = NULL;
    for(i = 0; i < numframes; i++) {
        if(i == 0) {
            head = (struct frame_struct*) allocate(sizeof(struct frame_struct));
            curr = head;
        }
        else {
            curr->next = (struct frame_struct*) allocate(sizeof(struct frame_struct));
            curr = curr->next;
        }
        curr->frame_number = i;
        curr->physical_address = physical_frames + (i * frame_size);
        curr->virtual_address = 0;
        curr->pte_pointer     = NULL;
    }

    // Initialize page table
    long page_table_size = PT_SIZE_1MB * PTE_SIZE_BYTES;
    page_table = (struct pte_32**) allocate(page_table_size * sizeof(struct pte_32*));
    
    struct pte_32* new_pte = NULL;
    unsigned char mode_type = '\0';
    unsigned int fault_address = 0;
    unsigned int cpu_elapsed_cycles = 0;
    unsigned int previous_fault_address = 0;
    int hit = 0;
    int page2evict = 0;
    int numfaults = 0;

    // Main loop to process memory accesses
    for(i = 0; i < numaccesses; i++) {
        fault_address = address_array[i];
        mode_type = mode_array[i];
        hit = 0;
        // Perform page walk for the fault address
        new_pte = (struct pte_32*) handle_page_fault(fault_address);
      
        /*
         * Traverse the frames linked list    
         * to see if the requested page is present in
         * the frames linked list.
         */
        curr = head;
        while(curr) {
            if(curr->physical_address == new_pte->physical_address) {
                if(new_pte->present) {
                    curr->virtual_address = fault_address;
                    hit = 1;
                    #ifdef DEBUG
                    printf("%5d: page hit   – no eviction %010u (0x%08x)\n", i, (unsigned int) ((uintptr_t) fault_address), fault_address);
                    printf("%5d: page hit   - keep page   %010u (0x%08x) accessed (0x%08x)\n", i, (unsigned int) ((uintptr_t) curr->physical_address), *((unsigned int*) &new_pte->physical_address), curr->virtual_address);
                    #endif
                }
                break;
            }
            else {
                curr = curr->next;
            }
        }

        /* 
         * If the requested page is not present in the
         * frames linked list use the fifo page replacement
         * to evict the victim frame and swap in the requested frame
         */  
        if(!hit) {
            // Fifo page replacement algorithm
            if(!strcmp(algorithm, "fifo")) {
                page2evict = fifo();
            }

           /* Traverse the frames linked list to
            * find the victim frame and swap it out
            * Set the present bit and collect some statistics
            * ToDO: Need to add your dirty bit implementation 
            * inside the while loop
            */
            curr = head;
            while(curr) {
                if(curr->frame_number == page2evict) {
                    previous_fault_address = curr->virtual_address;
                    numfaults++;
                    
                    if(curr->pte_pointer) {
                        curr->pte_pointer->present = 0;
                    }
                   
                    curr->pte_pointer = (struct pte_32*) new_pte;
                    new_pte->physical_address = curr->physical_address;
                    new_pte->present = 1;
                    curr->virtual_address = fault_address; 
                }
                curr = curr->next; 
            }
        }
    }
    
    /* ToDo: Release the memory you allocated for frames and page_table */
    
    printf("Algorithm:             %s\n", algorithm);
    printf("Number of frames:      %d\n", numframes);
    printf("Total memory accesses: %d\n", i);
    printf("Total page faults:     %d\n", numfaults);
    
    return(0);
}

struct frame_struct * handle_page_fault(unsigned int fault_address) {
    pte = (struct pte_32*) page_table[PTE32_INDEX(fault_address)];
    if(!pte) {
        pte = allocate(sizeof(struct pte_32));
        if(!pte) {
            fprintf(stderr, "Error on mallocing memory\n");
            exit(1);
        }
        memset(pte, 0, sizeof(struct pte_32));
        pte->present = 0;
        pte->physical_address = NULL;
        page_table[PTE32_INDEX(fault_address)] = (struct pte_32*) pte;
    }
    #ifdef DEBUG
    printf("############## Page fault handler ##############\n");    
    printf("Fault address:           %010u (0x%08x)\n", (unsigned int) ((uintptr_t) fault_address), fault_address);
    printf("Page table base address: %010u (0x%08x)\n", (unsigned int) ((uintptr_t) page_table), *((unsigned int*) &page_table));
    printf("PTE offset:              %010u (0x%08x)\n", PTE32_INDEX(fault_address), PTE32_INDEX(fault_address));
    printf("PTE index:               %010u (0x%08x)\n", (unsigned int) ((uintptr_t)(PTE32_INDEX(fault_address) * PTE_SIZE_BYTES)), (unsigned int) ((uintptr_t)(PTE32_INDEX(fault_address) * PTE_SIZE_BYTES)));
    printf("PTE virtual address:     %010u (0x%08x)\n", (unsigned int) ((uintptr_t) page_table + PTE32_INDEX(fault_address)), *((unsigned int*) &*page_table + PTE32_INDEX(fault_address)));
    printf("Physcial base address:   %010u (0x%08x)\n", (unsigned int) ((uintptr_t) pte->physical_address), *((unsigned int*) &pte->physical_address));
    printf("Frame offset:            %010u (0x%08x)\n", FRAME_INDEX(fault_address), FRAME_INDEX(fault_address));
    printf("Frame index:             %010u (0x%08x)\n", FRAME_INDEX(fault_address) * PAGE_SIZE_UNITS, FRAME_INDEX(fault_address) * PAGE_SIZE_UNITS);
    printf("Frame physical address:  %010u (0x%08x)\n", (unsigned int) ((uintptr_t) pte->physical_address + FRAME_INDEX(fault_address)), *((unsigned int*) &pte->physical_address + FRAME_INDEX(fault_address)));
    #endif
    
    return ((struct frame_struct *) pte);
}

int fifo() {
    return (current_index = ++current_index % numframes);
}