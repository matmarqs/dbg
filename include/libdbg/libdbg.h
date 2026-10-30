#ifndef DBG_LIBDBG_H
#define DBG_LIBDBG_H

#include <sys/types.h>
#include <libdbg/process.h>

#define UNUSED(x) (void)(x)

void usage();
process_t attach(int argc, const char **argv);

#endif
