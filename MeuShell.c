// Bibliotecas padrão para I/O, alocação de memória, strings e funções do sistema.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// Imprime o banner de boas-vindas do shell.
void exibir_banner() {
    printf("\033[1;32m");
    printf("\n");
    printf("                                     ████████████████                \n");
    printf("               ███               █████              █████             \n");
    printf("              ██ ██            ████                    █████          \n");
    printf("              ██ ██          █████████████      █████████████         \n");
    printf("              ██ ██       ███████       ██████████       ███████      \n");
    printf("             ███ ██       █████           ███████          █████      \n");
    printf("         ████ ██ ██      ███ ██     ████  ███ ██  ████     ██████     \n");
    printf("      ███  ██ ██ ██      ██  ██     ████  ███ ██  ████     ███ ███    \n");
    printf("    ██  █  ██████████   ███  ███         ███  ███         ███  ███    \n");
    printf("    ███ █  ██      ██   ██    ████     ████    ████     ████    ██    \n");
    printf("    ████ ██ █████   ██  ██      █████████        █████████      ███   \n");
    printf("    ██        ██    ██  ██                                      ███   \n");
    printf("    ██      ██     ███  ██           █████████████████          ██    \n");
    printf("     ███         ███    ███          █████      ██████         ███    \n");
    printf("       ██      ███       ██          ████████████████          ██     \n");
    printf("        █      ██        ███           ████████████           ███     \n");
    printf("        █      ██         ███            ████████            ███      \n");
    printf("        █████████          ████                            ████       \n");
    printf("                             ███                          ███         \n");
    printf("                               ████                    ████           \n");
    printf("                                 ███████           ██████             \n");
    printf("                                     ████████████████\n");
    printf("                          \nBem-vindo ao SUPER SHELL!\n\n");

    printf("\033[0m");
}

// Cria um processo filho (fork) para rodar comandos externos (execvp).
void executar_comando_externo(char **args) {
    pid_t idProcesso = fork();

    if (idProcesso < 0) {
        perror("Erro no fork");
        exit(1);
    } else if (idProcesso == 0) {
        // Processo filho: executa o comando.
        if (execvp(args[0], args) == -1) {
            perror("Erro ao executar comando");
            exit(1);
        }
    } else {
        // Processo pai: aguarda o término do filho.
        wait(NULL);
    }
}

// Trata comandos internos do shell, como 'exit' e 'cd'.
// Retorna 1 se o comando for interno, 0 caso contrário.
int executar_comando_embutido(char **args) {
    if (args[0] == NULL) {
        return 1; // Ignora linha em branco.
    }

    if (strcmp(args[0], "exit") == 0) {
        printf("tchauzinho :D\n\n");
        exit(0);
    }
    else if (strcmp(args[0], "cd") == 0) {
        // Se 'cd' não tiver argumento, usa o diretório HOME.
        char *destino = args[1] ? args[1] : getenv("HOME");
        
        if (chdir(destino) != 0) {
            perror("Erro ao mudar de diretório");
        } else {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Diretório atual: %s\n", cwd);
            }
        }
        return 1;
    }

    return 0; // Não é um comando embutido.
}

int main() {
    char *linha = NULL;
    char **args = NULL;
    size_t len = 0;

    exibir_banner();

    // Loop principal do shell.
    while (1) {
        printf("Meu Super Shell :D : ");

        // Lê a linha de comando com getline(), que gerencia a alocação de memória.
        if (getline(&linha, &len, stdin) == -1) {
            break; // Sai com Ctrl+D ou em caso de erro.
        }

        // Aloca espaço inicial para os argumentos.
        int capacidade = 10;
        args = malloc(capacidade * sizeof(char*));
        if (!args) {
            perror("Erro de alocação");
            exit(EXIT_FAILURE);
        }

        // Divide a linha de comando em tokens (argumentos) usando strtok.
        int i = 0;
        char *token = strtok(linha, " \t\r\n\a");
        while (token != NULL) {
            args[i++] = token;

            // Se o espaço para argumentos acabar, dobra a capacidade.
            if (i >= capacidade) {
                capacidade *= 2;
                args = realloc(args, capacidade * sizeof(char*));
                if (!args) {
                    perror("Erro de realocação");
                    exit(EXIT_FAILURE);
                }
            }
            token = strtok(NULL, " \t\r\n\a");
        }
        args[i] = NULL; // Termina a lista de argumentos com NULL para o execvp.

        // Se o comando não for embutido, executa como um comando externo.
        if (args[0] != NULL) {
            if (!executar_comando_embutido(args)) {
                executar_comando_externo(args);
            }
        }
        
        // Libera a memória alocada para os argumentos a cada loop.
        free(args);
    }

    // Libera a memória da linha lida antes de encerrar.
    free(linha);
    printf("\n");
    return 0;
}
