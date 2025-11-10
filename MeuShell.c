#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>

char* remover_aspas(char *str) {
    if (str == NULL) return NULL;
    int len = strlen(str);
    
    if (len > 0 && (str[len-1] == '"' || str[len-1] == '\'')) {
        str[len-1] = '\0';
        len--;
    }
    if (len > 0 && (str[0] == '"' || str[0] == '\'')) {
        memmove(str, str + 1, len);
    }
    return str;
}


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

void executar_comando_externo(char **args, char *arquivo_saida, char *arquivo_append, char *arquivo_entrada, int background) {
    pid_t idProcesso = fork();

    if (idProcesso < 0) {
        perror("Aconteceu um erro ao criar o processo filho");
        exit(1);
    } else if (idProcesso == 0) {
        if (arquivo_saida != NULL) {
            int fd_saida = open(arquivo_saida, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_saida < 0) { perror("Erro ao abrir arquivo de saida"); exit(1); }
            if (dup2(fd_saida, STDOUT_FILENO) < 0) { perror("Erro ao redirecionar stdout"); exit(1); }
            close(fd_saida);
        }

        if (arquivo_append != NULL) {
            int fd_saida = open(arquivo_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd_saida < 0) { perror("Erro ao abrir arquivo de saida (append)"); exit(1); }
            if (dup2(fd_saida, STDOUT_FILENO) < 0) { perror("Erro ao redirecionar stdout (append)"); exit(1); }
            close(fd_saida);
        }

        if (arquivo_entrada != NULL) {
            int fd_entrada = open(arquivo_entrada, O_RDONLY);
            if (fd_entrada < 0) { perror("Erro ao abrir arquivo de entrada"); exit(1); }
            if (dup2(fd_entrada, STDIN_FILENO) < 0) { perror("Erro ao redirecionar stdin"); exit(1); }
            close(fd_entrada);
        }

        if (execvp(args[0], args) == -1) {
            perror("Aconteceu um erro ao executar o processo :( ");
            exit(1);
        }
    } else {
        if (!background) {
            wait(NULL); 
        } else {
            printf("Processo [%d] iniciado em background.\n", idProcesso);
        }
    }
}

void executar_pipe(char **args_cmd1, char **args_cmd2) {
    int fd[2]; 
    pid_t pid1, pid2;

    if (pipe(fd) < 0) {
        perror("Erro ao criar o pipe");
        return;
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror("Erro no primeiro fork do pipe");
        return;
    }

    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO); 
        close(fd[0]);
        close(fd[1]);
        if (execvp(args_cmd1[0], args_cmd1) == -1) {
            perror("Erro ao executar primeiro comando do pipe");
            exit(1);
        }
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("Erro no segundo fork do pipe");
        return;
    }

    if (pid2 == 0) {
        dup2(fd[0], STDIN_FILENO); 
        close(fd[0]);
        close(fd[1]);
        if (execvp(args_cmd2[0], args_cmd2) == -1) {
            perror("Erro ao executar segundo comando do pipe");
            exit(1);
        }
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int executar_comando_embutido(char **args) {
    if (args[0] == NULL) {
        return 1;
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
    char *linha = NULL;
    char **args = NULL;
    size_t len = 0;
    ssize_t lido;

    exibir_banner();

    while (1) {
        printf("Meu Super Shell :D : ");
        
        fflush(stdout); 

        char *arquivo_saida = NULL;
        char *arquivo_append = NULL;
        char *arquivo_entrada = NULL;
        char **args_pipe = NULL;
        int background = 0;
        int tem_pipe = 0;

        lido = getline(&linha, &len, stdin);
        if (lido == -1) {
            break;
        }

        int capacidade = 10;
        args = malloc(capacidade * sizeof(char*));
        if (args == NULL) {
            perror("Erro de alocação de memória");
            exit(EXIT_FAILURE);
        }

        int i = 0;
        char *token = strtok(linha, " \t\r\n\a"); 

        while (token != NULL) {
            
            args[i] = remover_aspas(token);
            i++;

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

        
        if (i > 0 && strcmp(args[i-1], "&") == 0) {
            background = 1;
            args[i-1] = NULL; 
            i--; 
        }
        
        for (int j = 0; j < i; j++) {
            if (strcmp(args[j], "|") == 0) {
                tem_pipe = 1;
                args[j] = NULL;       
                args_pipe = &args[j+1]; 
                break;
            }
        }

        if (!tem_pipe) {
            for (int j = 0; j < i; j++) {
                if (strcmp(args[j], ">") == 0) {
                    args[j] = NULL;
                    arquivo_saida = args[j+1];
                    break; 
                }
                if (strcmp(args[j], ">>") == 0) {
                    args[j] = NULL;
                    arquivo_append = args[j+1];
                    break; 
                }
                if (strcmp(args[j], "<") == 0) {
                    args[j] = NULL;
                    arquivo_entrada = args[j+1];
                    break; 
                }
            }
        }


        if (args[0] != NULL) {
            if (executar_comando_embutido(args)) {
            } 
            else if (tem_pipe) {
                executar_pipe(args, args_pipe);
            } 
            else {
                executar_comando_externo(args, arquivo_saida, arquivo_append, arquivo_entrada, background);
            }
        }

        free(args);
    }

    free(linha);
    printf("\n");
    return 0;
}
