#ifndef DBG_PROCESS_H
#define DBG_PROCESS_H

#include <sys/types.h>
#include <stdbool.h>

enum {
    STOPPED,
    RUNNING,
    EXITED,
    TERMINATED,
};

typedef struct {
    pid_t pid;
    bool terminate_on_end;
} process_t;

process_t proc_launch(const char *path);
process_t proc_attach(pid_t pid);
void proc_waitOnSignal(process_t *process);
void proc_resume(process_t *process);
void proc_terminate(process_t *process);

#endif
