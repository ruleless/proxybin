#ifndef __PROXY_COMMON_H__
#define __PROXY_COMMON_H__

#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#define GET_ORIGINAL_FUNC(X) do { original_##X = proxy_load_symbol(#X, X); } while(0)

void *proxy_load_symbol(char *symbol_name, void *proxy_func);

#endif /* __PROXY_COMMON_H__ */
