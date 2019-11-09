/*
 * hashmap.c: Hashmap implementation
 * (c) Mohammad Hasanzadeh Mofrad, 2019
 * (e) moh18@pitt.edu
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

void* hashmap_allocate(unsigned long size) {
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

void hashmap_deallocate(void* ptr) {
    free(ptr);
    ptr = NULL;
}

struct hashmapbase* hashmap_initialize(unsigned int size) {
    struct hashmapbase* base = (struct hashmapbase*) hashmap_allocate(sizeof(struct hashmapbase));
    base->size = size;
    base->map = (struct hashmap**) hashmap_allocate(size * sizeof(struct hashmap*));
    return(base);
}

/* Print the hashmap*/
void hashmap_print(struct hashmapbase* base) {
    struct hashmap** map = base->map;
    unsigned int size = base->size;
    int i = 0;
    printf("############### HashMap Content ################\n");
    for(i = 0; i < size; i++) {
        unsigned int key = i;
        struct hashmap* hashmap_entry = (struct hashmap*) map[key];
        if(hashmap_entry) {
            printf("0x%8x(%10d): ", hashmap_entry->key, hashmap_entry->key);
            struct values* head = hashmap_entry->head;
            while(head) {
                printf("%d ", head->value);
                head = head->next;
            }
            printf("\n");
        }
    }
}

/* Insert into the hashmap*/
void hashmap_insert(struct hashmapbase* base, unsigned int key, unsigned int value) {
    struct hashmap** map = base->map;
    
    struct hashmap* hashmap_entry = (struct hashmap*) map[key];
    if(hashmap_entry == NULL) {
        hashmap_entry =  (struct hashmap*) hashmap_allocate(sizeof(struct hashmap));
        hashmap_entry->key = key;
        map[key] = hashmap_entry;
    }

    if(hashmap_entry->head == NULL) {
        hashmap_entry->head = (struct values*) hashmap_allocate(sizeof(struct values));
        hashmap_entry->head->value = value;
        hashmap_entry->head->next = NULL;
        hashmap_entry->tail = hashmap_entry->head;
    }
    else {
        hashmap_entry->tail->next = (struct values*) hashmap_allocate(sizeof(struct values));
        hashmap_entry->tail = hashmap_entry->tail->next;
        hashmap_entry->tail->value = value;
        hashmap_entry->tail->next = NULL;
    }        
}

/* Return the first value from the hashmap*/
struct value_object* hashmap_top(struct hashmapbase* base, unsigned int key) {
    struct hashmap** map = base->map;
    unsigned int size = base->size;
    struct hashmap* hashmap_entry = (struct hashmap*) map[key];
    struct value_object* value_obj = NULL;
    if(key < size) {
        if(hashmap_entry) {
            struct values* head = hashmap_entry->head;
            if(head) {
                value_obj = (struct value_object*) hashmap_allocate(sizeof(struct value_object));
                value_obj->value = head->value;
            }
        }
    }
    return(value_obj);
}

/* Remove and return the first value from the hashmap*/
struct value_object* hashmap_peek(struct hashmapbase* base, unsigned int key) {
    struct hashmap** map = base->map;
    unsigned int size = base->size;
    struct hashmap* hashmap_entry = (struct hashmap*) map[key];
    struct value_object* value_obj = NULL;
    if(key < size) {
        if(hashmap_entry) {
            struct values** head = &hashmap_entry->head;
            struct values** tail = &hashmap_entry->tail;
            if(head) {
                value_obj = (struct value_object*) hashmap_allocate(sizeof(struct value_object));
                value_obj->value = (*head)->value;
                if(*head == *tail) { 
                    hashmap_deallocate((void*) *head);
                    *head = NULL;
                    *tail = NULL;
                    hashmap_deallocate((void*) hashmap_entry);
                    map[key] = NULL;
                }
                else {
                    struct values* temp = *head;
                    *head = (*head)->next;
                    hashmap_deallocate((void*) temp);
                }
            }
        }
    }
    return(value_obj);
}