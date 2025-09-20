#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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

// Função para executar um comando externo (com fork e execvp)
void executar_comando_externo(char **args) {
    pid_t idProcesso = fork();

    if (idProcesso < 0) {
        perror("Aconteceu um erro ao criar o processo filho");
        exit(1);
    } else if (idProcesso == 0) {
        // Processo filho
        if (execvp(args[0], args) == -1) {
            perror("Aconteceu um erro ao executar o processo :( ");
            exit(1);
        }
    } else {
        // Processo pai
        wait(NULL);
    }
}

// Função para lidar com comandos embutidos
// Retorna 1 se o comando foi embutido, 0 caso contrário
int executar_comando_embutido(char **args) {
    if (args[0] == NULL) {
        return 1; // Linha vazia, não faz nada
    }

    if (strcmp(args[0], "exit") == 0) {
        printf("tchauzinho :D\n\n");
        exit(0);
    }
    else if (strcmp(args[0], "cd") == 0) {
        char *destino = args[1];
        if (destino == NULL) {
            destino = getenv("HOME");
            if (destino == NULL) {
                fprintf(stderr, "Variável HOME não definida\n");
                return 1;
            }
        }

        if (chdir(destino) != 0) {
            perror("Erro ao mudar de diretório");
        } else {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Diretório atual: %s\n", cwd);
            } else {
                perror("Erro ao obter diretório atual");
            }
        }
        return 1;
    }

    return 0;
}

int main() {
    // ALTERAÇÃO: Variáveis agora são ponteiros para alocação dinâmica.
    char *linha = NULL;
    char **args = NULL;
    size_t len = 0;
    ssize_t lido;

    exibir_banner();

    while (1) {
        printf("Meu Super Shell :D : ");

        // ALTERAÇÃO: Leitura do comando com getline(), que aloca memória sozinho.
        lido = getline(&linha, &len, stdin);
        if (lido == -1) {
            break; // Sai do loop se ocorrer erro ou Ctrl+D
        }

        // ALTERAÇÃO: Alocação inicial para a lista de argumentos.
        int capacidade = 10;
        args = malloc(capacidade * sizeof(char*));
        if (args == NULL) {
            perror("Erro de alocação de memória");
            exit(EXIT_FAILURE);
        }

        // Parsing do comando em tokens
        int i = 0;
        char *token = strtok(linha, " \t\r\n\a");
        while (token != NULL) {
            args[i] = token;
            i++;

            // ALTERAÇÃO: Dobra o tamanho da lista se ela encher.
            if (i >= capacidade) {
                capacidade *= 2;
                args = realloc(args, capacidade * sizeof(char*));
                if (args == NULL) {
                    perror("Erro de realocação de memória");
                    exit(EXIT_FAILURE);
                }
            }
            token = strtok(NULL, " \t\r\n\a");
        }
        args[i] = NULL;

        // Executa comando embutido (cd, exit) ou comando externo
        if (args[0] != NULL) {
            if (!executar_comando_embutido(args)) {
                executar_comando_externo(args);
            }
        }
        
        // ALTERAÇÃO: Libera a memória da lista de argumentos a cada loop.
        free(args);
    }

    // ALTERAÇÃO: Libera a memória da linha lida antes de sair.
    free(linha);
    printf("\n");
    return 0;
}
