# 🐚 Meu Super Shell

Um shell interativo simples, desenvolvido como parte do curso de **Engenharia de Computação da UNIARA – Universidade de Araraquara**.  
Ele foi projetado para ser **leve** e **didático**, ilustrando os mecanismos fundamentais por trás dos shells mais complexos que usamos no dia a dia.  

---

## ✨ Funcionalidades

- **Execução de Comandos Externos:**  
  Roda qualquer comando disponível no `PATH` do sistema (como `ls`, `pwd`, `echo`, `git`, etc.), incluindo seus argumentos.
  
- **Comandos Embutidos (Built-in):**  
  Executados diretamente pelo shell, sem criar novos processos:
  - `cd [diretório]` → muda o diretório atual (ou vai para `HOME` se nenhum for especificado).  
  - `exit` → encerra o shell.

- **Loop Interativo:**  
  Mantém o shell rodando até o usuário digitar `exit`.

- **Parsing de Comandos:**  
  Divide a entrada do usuário em tokens (comando e argumentos) para execução correta.

---

## 🛠️ Tecnologias Utilizadas

- **Linguagem:** C  
- **Compilador:** GCC (ou qualquer compilador C padrão)  
- **APIs POSIX e da biblioteca padrão do C:**  
  - `fork()`  
  - `execvp()`  
  - `wait()`  
  - `chdir()`  
  - `strtok()`  

---

## 🚀 Como Compilar e Executar

Você precisará de um compilador C (como o **GCC**) e um ambiente Unix (Linux ou macOS).

1. **Clone ou salve o código-fonte:**  
   Exemplo: `meu_shell.c`

2. **Compile o programa:**  
   ```bash
   gcc -o meu_shell meu_shell.c
   ```

3. **Execute o shell:**  
   ```bash
   ./meu_shell
   ```

4. **Comece a usar!**  
   Você verá o prompt:  
   ```
   Meu Super Shell :D:
   ```

---

## 📝 Exemplos de Uso

```bash
# Inicia o shell
./meu_shell

# Executa comandos
Meu Super Shell :D: ls -l
total 8
-rwxr-xr-x 1 user user 8424 Sep 15 12:00 meu_shell
-rw-r--r-- 1 user user  857 Sep 15 11:58 meu_shell.c

Meu Super Shell :D: pwd
/home/user/meu_projeto_shell

Meu Super Shell :D: cd /tmp
Diretório atual: /tmp

Meu Super Shell :D: echo "Olá, mundo!"
Olá, mundo!

Meu Super Shell :D: exit
tchauzinho :D
```

---

## 👨‍💻 Autores

Este projeto foi desenvolvido por alunos da **Engenharia de Computação – UNIARA**:

- Diogo Marconato Garcia – RA: 05222-027  
- João Pedro Marucci Pagliuso – RA: 05222-040  
- Matheus Figueira Merlos – RA: 05222-016  


## 🚀 Link Para o Projeto no GitHub

https://github.com/Dexter99150/Meu-Shell

📅 **Setembro de 2025**
