#include "proxy_common.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void* (*original_malloc)(size_t size) = NULL;
static void* (*original_calloc)(size_t nmemb, size_t size) = NULL;
static void (*original_free)(void *p) = NULL;

void *malloc(size_t size)
{
    assert(original_malloc != NULL);

    void *p = original_malloc(size);

    return p;
}

void *calloc(size_t nmemb, size_t size)
{
    assert(original_calloc != NULL);

    void *p = original_calloc(nmemb, size);

    return p;
}

void free(void *p)
{
    assert(original_free != NULL);

    original_free(p);
}

void hook_init()
{
    GET_ORIGINAL_FUNC(malloc);
    GET_ORIGINAL_FUNC(calloc);
    GET_ORIGINAL_FUNC(free);
}
