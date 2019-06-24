/*
 * vmsim.c: Virtual memory implementation skeleton code
 * with a single level 32-Bit page table and
 * fifo page replacement algorithm
 * (c) Mohammad Hasanzadeh Mofrad, 2019
 * (e) moh18@pitt.edu
 */
 
#include "vmsim.h"
int numframes;
unsigned int *physical_frames;
// Page Table
unsigned int *page_table = NULL;
// Page Table Entry
struct pte_32 *pte = NULL;

// Fifo page replacement current index
int current_index = -1;

int main(int argc, char *argv[]) {
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
    char *algorithm = argv[4];
    char *filename = argv[5];
    FILE *file = fopen(filename,"rb");
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
    
    if(i != numaccesses) {
        printf("Arrays are populated incorrectly\n");
        exit(0);
    }

    if(fclose(file)) {
        fprintf(stderr, "Error on closing %s\n", filename);
        exit(1);
    }
   
    // Initialize the physical memory address space
    long frame_size = PAGE_SIZE_4KB / PAGE_SIZE_BYTES;
    long memory_size = frame_size * numframes;
    physical_frames = malloc(memory_size);
    if(!physical_frames) {
        fprintf(stderr, "Error on mallocing physical frames\n");
        exit(1);
    }
    memset(physical_frames, 0, memory_size);
    
    // Create the first frame of the frames linked list
    struct frame_struct *frame = malloc(sizeof(struct frame_struct));
    if(!frame) {
        fprintf(stderr, "Error on mallocing frame struct\n");
        exit(1);
    }
    memset(frame, 0, sizeof(struct frame_struct));
    // Store the head of frames linked list
    struct frame_struct *head = frame;
    struct frame_struct *curr;
    // Initialize the frames linked list
    for(i = 0; i < numframes; i++) {
        frame->frame_number = i;
        frame->physical_address = physical_frames + (i * frame_size);
        frame->virtual_address = 0;
        frame->pte_pointer = NULL;
        #ifdef INFO
        printf("Frame#%d: Adding a new frame at memory address %ld (0x%08x)\n", i, frame->physical_address, frame->physical_address);
        #endif
        frame->next = malloc(sizeof(struct frame_struct));
        frame = frame->next;
        memset(frame, 0, sizeof(struct frame_struct));
    }
    
    // Initialize page table
    long page_table_size = PT_SIZE_1MB * PTE_SIZE_BYTES;
    page_table = malloc(page_table_size);
    if(!page_table) {
        fprintf(stderr, "Error on mallocing page table\n");
        exit(1);
    }
    memset(page_table, 0, page_table_size);
    
    struct pte_32 *new_pte = NULL;
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
        new_pte = (struct pte_32 *) handle_page_fault(fault_address);
      
        /*
         * Traverse the frames linked list    
         * to see if the requested page is present in
         * the frames linked list.
         */
        curr = head;
        while(curr->next) {
            if(curr->physical_address == new_pte->physical_address) {
                if(new_pte->present) {
                    curr->virtual_address = fault_address;
                    hit = 1;
                    #ifdef DEBUG
                    //if (i >19700) {
                    printf("%5d: page hit   – no eviction (0x%08x)\n", i, fault_address);
                    printf("%5d: page hit   - keep page   (0x%08x) accessed (0x%08x)\n", i, new_pte->physical_address, curr->virtual_address);
                    //}
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
            * Need to add your dirty bit implementation inside the while
            */
            curr = head;
            while(curr->next) {
                if(curr->frame_number == page2evict) {
                    previous_fault_address = curr->virtual_address;
                    numfaults++;
                    
                    if(curr->pte_pointer) {
                        curr->pte_pointer->present = 0;
                    }
                   
                    curr->pte_pointer = (struct pte_32 *) new_pte;
                    new_pte->physical_address = curr->physical_address;
                    new_pte->present = 1;
                    curr->virtual_address = fault_address; 
                }
                curr = curr->next; 
            }
        }
    }

    printf("Algorithm:             %s\n", algorithm);
    printf("Number of frames:      %d\n", numframes);
    printf("Total memory accesses: %d\n", i);
    printf("Total page faults:     %d\n", numfaults);
    return(0);
}

struct frame_struct * handle_page_fault(unsigned int fault_address) {
    pte = (struct pte_32 *) page_table[PTE32_INDEX(fault_address)];
    if(!pte) {
        pte = malloc(sizeof(struct pte_32));
        memset(pte, 0, sizeof(struct pte_32));
        pte->present = 0;
        pte->physical_address = NULL;
        page_table[PTE32_INDEX(fault_address)] = (unsigned int) pte;
    }

    #ifdef DEBUG
    printf("#############Page fault handler#############\n");
    printf("Fault address:           %010ld (0x%08x)\n", (unsigned int) fault_address, fault_address);
    printf("Page table base address: %010ld (0x%08x)\n", (unsigned int) page_table, page_table);
    printf("PTE offset:              %010ld (0x%08x)\n", PTE32_INDEX(fault_address), PTE32_INDEX(fault_address));
    printf("PTE index:               %010ld (0x%08x)\n", PTE32_INDEX(fault_address) * PTE_SIZE_BYTES, PTE32_INDEX(fault_address) * PTE_SIZE_BYTES);
    printf("PTE virtual address:     %010ld (0x%08x)\n", (unsigned int) page_table + PTE32_INDEX(fault_address), page_table + PTE32_INDEX(fault_address));

    printf("Physcial base address:   %010ld (0x%08x)\n", pte->physical_address, pte->physical_address);
    printf("Frame offset:            %010ld (0x%08x)\n", FRAME_INDEX(fault_address), FRAME_INDEX(fault_address));
    printf("Frame index:             %010ld (0x%08x)\n", FRAME_INDEX(fault_address) * PAGE_SIZE_BYTES, FRAME_INDEX(fault_address) * PAGE_SIZE_BYTES);
    printf("Frame physical address:  %010ld (0x%08x)\n", pte->physical_address + FRAME_INDEX(fault_address), pte->physical_address + FRAME_INDEX(fault_address));
    printf("############################################\n");
    #endif
    
    return ((struct frame_struct *) pte);
}

int fifo() {
    current_index++;
    current_index = current_index % numframes;            
    return (current_index);
}