#ifndef DBG_LIBDBG_H
#define DBG_LIBDBG_H

#define UNUSED(x) (void)(x)

#include <sys/types.h>

pid_t attach(int argc, const char **argv);
void resume(pid_t pid);
void wait_on_signal(pid_t pid);

#endif
