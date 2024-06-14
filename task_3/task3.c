// Реализовать аналог командного интерпретатора bash. При запуске
// программы пользователю предлагается ввести имя программы и опции
// запуска программы. Программа порождает процесс и в нем выполняет
// введенную программу с заданными опциями, ждет завершения
// дочернего процесса. Снова возвращается к вводу следующей
// программы. Выход из интерпретатора по команде exit.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT 100
#define MAX_ARGS 10

int main() {
    char command[MAX_INPUT];
    char *args[MAX_ARGS];
    pid_t pid;

    while (1) {
        printf("Введите имя программы и опции запуска: ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            perror("Ошибка чтения команды");
            continue;
        }
        command[strcspn(command, "\n")] = 0; // Убираем символ новой строки

        // Проверяем команду на выход
        if (strcmp(command, "exit") == 0) {
            break;
        }

        // Разбиваем команду на аргументы
        int i = 0;
        args[i] = strtok(command, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            args[++i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid = fork();
        if (pid == 0) {
            // Если мы находимся в дочернем процессе, выполняем введенную программу
            execvp(args[0], args);
            perror("Ошибка выполнения команды");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            // Если мы находимся в родительском процессе, ожидаем завершения дочернего процесса
            wait(NULL);
        } else {
            perror("Ошибка создания процесса");
        }
    }

    return 0;
}
