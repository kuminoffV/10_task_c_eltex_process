// Реализовать программу, которая порождает процесс. Родительский
// процесс и дочерний выводят на экран свой pid, ppid. Затем родительский
// ждет завершения дочернего и выводит его статус завершения.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    // Создаем переменную для хранения pid процесса
    pid_t pid;

    // Создаем дочерний процесс
    pid = fork();
    if (pid == 0) {
        // Если мы находимся в дочернем процессе, выводим pid и ppid
        printf("Child process: pid = %d, ppid = %d\n", getpid(), getppid());
        // Завершаем дочерний процесс
        exit(0);
    } else {
        // Если мы находимся в родительском процессе, ожидаем завершения дочернего процесса
        wait(NULL);
        // После завершения дочернего процесса, выводим pid и ppid родительского процесса
        printf("Main process: pid = %d, ppid = %d\n", getpid(), getppid());
        // Ожидаем завершения дочернего процесса еще раз, чтобы получить его статус завершения
        int status;
        wait(&status);
        // Выводим статус завершения дочернего процесса
        printf("Child procex completion status: %d\n", WEXITSTATUS(status));
    }

    return 0;
}
