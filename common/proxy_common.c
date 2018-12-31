#include "proxy_common.h"

static int (*original_main)(int, char **, char **);

void *proxy_load_symbol(char *symbol_name, void *proxy_func)
{
    void *funcptr = dlsym(RTLD_NEXT, symbol_name);

    if(funcptr == NULL) {
        fprintf(stderr, "Cannot load symbol '%s', reason: %s\n", symbol_name, dlerror());
        exit(1);
    }

    if(funcptr == proxy_func) {
        fprintf(stderr, "Circular reference detected, aborting!\n");
        abort();
    }

    return funcptr;
}

int main_hook(int argc, char **argv, char **envp)
{
    int rv = 0;
    void (*hook_init)() = dlsym(RTLD_DEFAULT, "hook_init");

    if (hook_init) {
        hook_init();
    }
    rv = original_main(argc, argv, envp);

    return rv;
}

int __libc_start_main(
    int (*main)(int, char **, char **),
    int argc,
    char **argv,
    int (*init)(int, char **, char **),
    void (*fini)(void),
    void (*rtld_fini)(void),
    void *stack_end)
{
    original_main = main;
    typeof(&__libc_start_main)start_main = dlsym(RTLD_NEXT, "__libc_start_main");

    return start_main(main_hook, argc, argv, init, fini, rtld_fini, stack_end);
}
