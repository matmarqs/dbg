#ifndef DBG_LIBDBG_H
#define DBG_LIBDBG_H

#include <sys/types.h>

#define UNUSED(x) (void)(x)

void usage();
pid_t attach(int argc, const char **argv);
void resume(pid_t pid);
void wait_on_signal(pid_t pid);

#endif
