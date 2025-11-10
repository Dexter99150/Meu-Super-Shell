# 🐚 Meu Super Shell

Um shell interativo simples, desenvolvido como parte do curso de **Engenharia de Computação da UNIARA – Universidade de Araraquara**.  
Ele foi projetado para ser **leve** e **didático**, ilustrando os mecanismos fundamentais por trás dos shells mais complexos que usamos no dia a dia.

---

## ✨ Funcionalidades

O MyShell agora está completo, implementando todas as funcionalidades essenciais e avançadas:

- **Execução de Comandos Externos:** Roda qualquer comando disponível no `PATH` do sistema (como `ls`, `pwd`, `echo`, `git`, etc.), incluindo seus argumentos.

- **Comandos Embutidos (Built-in):** Executados diretamente pelo shell, sem criar novos processos:
  - `cd [diretório]` → muda o diretório atual (ou vai para `HOME` se nenhum for especificado).
  - `exit` → encerra o shell.

- **Loop Interativo:** Mantém o shell rodando até o usuário digitar `exit`.

- **Parsing de Comandos:** Divide a entrada do usuário em tokens, usando alocação dinâmica (`getline`, `realloc`) para suportar comandos de qualquer tamanho e removendo aspas (`"`).

---

### 🚀 Funcionalidades Avançadas (Módulo 2)

| Funcionalidade | Sintaxe | Descrição |
| :--- | :--- | :--- |
| **Redirecionamento de Saída** | `comando > arquivo` | Sobrescreve o conteúdo do arquivo com a saída padrão (`stdout`). |
| **Append de Saída** | `comando >> arquivo` | Anexa a saída padrão ao final do arquivo, sem apagar o conteúdo existente. |
| **Redirecionamento de Entrada** | `comando < arquivo` | Redireciona a entrada padrão (`stdin`) a partir de um arquivo. |
| **Pipes ( )** | `cmd1 | cmd2` | Encadeia comandos; a saída do primeiro processo (`cmd1`) serve como entrada para o segundo (`cmd2`), utilizando a chamada de sistema `pipe()`. |
| **Execução em Background** | `comando &` | O shell detecta o caractere e retorna imediatamente ao prompt, permitindo que o comando execute em segundo plano sem a espera do pai. |

---

## 🛠️ Tecnologias Utilizadas

O projeto é escrito em **Linguagem C** e utiliza chamadas de sistema POSIX:

- **Processos e Controle:** `fork()`, `execvp()`, `wait()`, `waitpid()`.
- **E/S e Arquivos:** `open()`, `dup2()`, `pipe()`, `close()`.
- **Gestão de Memória:** `getline()`, `malloc()`, `realloc()`, `free()`, `strtok()`.

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
./MyShell

# Executa comandos com background e pipe
Meu Super Shell :D : sleep 3 &
Processo [PID] iniciado em background.
Meu Super Shell :D : ls -l | grep .c
-rw-r--r-- 1 user user 10720 Nov  8 16:02 meu_shell.c

# Executa comandos com redirecionamento (sobrescrever e append)
Meu Super Shell :D : echo "Linha A" > log.txt
Meu Super Shell :D : echo "Linha B" >> log.txt

# Verifica o resultado
Meu Super Shell :D : cat log.txt
Linha A
Linha B

Meu Super Shell :D : exit
tchauzinho :D
```

---

## 👨‍💻 Autores e Contato

<table width="100%" border="0">
<tr>
<td width="33.3%" align="center">
<table>
<tr>
<td valign="middle">
<a href="https://www.linkedin.com/in/diogo-garcia-6210bb235/" target="_blank">
<img src="https://skillicons.dev/icons?i=linkedin&theme=dark" height="40px" />
</a>
</td>
<td valign="middle">
<b>Diogo Marconato Garcia</b><br>
<small>RA: 05222-027</small>
</td>
</tr>
</table>
</td>
<td width="33.3%" align="center">
<table>
<tr>
<td valign="middle">
<a href="https://www.linkedin.com/in/jo%C3%A3o-pedro-marucci-pagliuso-0b8876385/" target="_blank">
<img src="https://skillicons.dev/icons?i=linkedin&theme=dark" height="40px" />
</a>
</td>
<td valign="middle">
<b>João Pedro Marucci Pagliuso</b><br>
<small>RA: 05222-040</small>
</td>
</tr>
</table>
</td>
<td width="33.3%" align="center">
<table>
<tr>
<td valign="middle">
<a href="https://www.linkedin.com/in/matheus-merlos-531089243/" target="_blank">
<img src="https://skillicons.dev/icons?i=linkedin&theme=dark" height="40px" />
</a>
</td>
<td valign="middle">
<b>Matheus Figueira Merlos</b><br> 
<small>RA: 05222-016</small>
</td>
</tr>
</table>
</td>
</tr>
</table>

📅 **Novembro de 2025**
