/*
 * hashmap.h: Hashmap header file
 * (c) Mohammad Hasanzadeh Mofrad, 2019
 * (e) moh18@pitt.edu
 *
 */

#ifndef _HASHMAP_INCLUDED_H
#define _HASHMAP_INCLUDED_H

struct value_object{
    unsigned int value;
};

struct values{
    unsigned int value;
    struct values* next;
};

struct hashmap{
    unsigned int key;
    struct values* head;
    struct values* tail;
};

struct hashmapbase{
    unsigned int size;
    struct hashmap** map;
};

struct hashmapbase* hashmap_initialize(unsigned int size);
void hashmap_print(struct hashmapbase* base);
void hashmap_insert(struct hashmapbase* base, unsigned int key, unsigned int value);
struct value_object* hashmap_top(struct hashmapbase* base, unsigned int key);
struct value_object* hashmap_peek(struct hashmapbase* base, unsigned int key);
    
#endif