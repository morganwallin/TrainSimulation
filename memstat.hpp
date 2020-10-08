#ifndef MEMSTAT_H
#define MEMSTAT_H

/*
 * Mittuniversitetet
 * Mikael Nilsson
 * Version 0.1
 * 2016-02-11
 */


#include "mempool.h"

static MemPool mempool;

void* operator new(std::size_t size) throw (std::bad_alloc){
    void* mem = mempool.create(size, false);
    if(mem == nullptr)
    {
        throw std::bad_alloc();
    }
    return mem;
}

void* operator new[](std::size_t size) throw (std::bad_alloc) {
    void* mem = mempool.create(size, true);
    if(mem == nullptr)
    {
        throw std::bad_alloc();
    }
    return mem;
}

void* operator new(std::size_t size, const std::nothrow_t&) throw(){
    return mempool.create(size, false);
}

void* operator new[](std::size_t size, const std::nothrow_t&) throw(){
    return mempool.create(size, true);
}

void operator delete(void* element) throw() {
    mempool.remove(element, false);
}

void operator delete[](void* element) throw() {
    mempool.remove(element, true);
}

void operator delete(void* element, const std::nothrow_t&) throw() {
    mempool.remove(element, false);
}

void operator delete[](void* element, const std::nothrow_t&) throw() {
    mempool.remove(element, true);
}

#endif // MEMSTAT_H

