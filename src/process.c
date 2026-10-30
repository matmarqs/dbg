#include <libdbg/libdbg.h>
#include <libdbg/process.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

process_t proc_launch(const char *path) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* child process */
        if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) < 0) {
            perror("Tracing failed");
            exit(EXIT_FAILURE);
        }
        if (execlp(path, path, NULL) < 0) {
            perror("Exec failed");
            exit(EXIT_FAILURE);
        }
    }

    process_t proc = (process_t) { .pid = pid, .terminate_on_end = true };
    proc_waitOnSignal(&proc);

    return proc;
}

process_t proc_attach(pid_t pid) {
    if (pid <= 0) {
        perror("Invalid pid");
        exit(EXIT_FAILURE);
    }
    if (ptrace(PTRACE_ATTACH, pid, /*addr=*/NULL, /*data=*/NULL) < 0) {
        perror("Could not attach");
        exit(EXIT_FAILURE);
    }

    process_t proc = (process_t) { .pid = pid, .terminate_on_end = true };
    proc_waitOnSignal(&proc);

    return proc;
}

void proc_waitOnSignal(process_t *process) {
    pid_t pid = process->pid;
    int wait_status;
    int options = 0;
    if (waitpid(pid, &wait_status, options) < 0) {
        perror("waitpid failed");
        exit(EXIT_FAILURE);
    }
}

void proc_resume(process_t *process) {
    pid_t pid = process->pid;
    if (ptrace(PTRACE_CONT, pid, NULL, NULL) < 0) {
        perror("Couldn't continue");
        exit(EXIT_FAILURE);
    }
}

void proc_terminate(process_t *process) {
    UNUSED(process);
    return;
}
