#ifndef DBG_LIBDBG_H
#define DBG_LIBDBG_H

#define UNUSED(x) (void)(x)

#include <sys/types.h>

pid_t attach(int argc, const char **argv);

#endif
