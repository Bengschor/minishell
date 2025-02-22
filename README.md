# 🐚 Minishell

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)]()
[![Version](https://img.shields.io/badge/version-1.0.0-blue)]()

A lightweight shell implementation that mimics basic functionalities of bash. This project aims to provide a simple yet functional command-line interface while serving as an educational tool for understanding how shells work.

## ✨ Features
<details>

- **Command Execution**: Run both built-in commands and external programs
- **Input/Output Redirection**: Support for `>`, `>>`, `<` operators
- **Pipes**: Connect multiple commands using `|`
- **Environment Variables**: Handle environment variables including `$?`
- **Signal Handling**: Proper handling of Ctrl+C, Ctrl+D, and Ctrl+\
- **Command History**: Navigate through previous commands
- **Quote Handling**: Support for both single and double quotes
- **Built-in Commands**:
  - `echo`: Display messages with option `-n`
  - `cd`: Change directory with relative or absolute paths
  - `pwd`: Print working directory
  - `export`: Set environment variables
  - `unset`: Remove environment variables
  - `env`: Display environment variables
  - `exit`: Exit the shell with status code

</details>

## 🔄 Program Workflow

#### 1. **Input Reading**
   - The shell begins by capturing raw input from the user via the standard input (stdin).
   - The input string is stored for future reference in the command history, allowing users to access previously executed commands.
   - It handles the EOF (Ctrl+D) condition gracefully, terminating the shell if the user signals the end of input.

#### 2. **Lexical Analysis**
   - The raw input string is processed to break it into smaller components known as tokens. 
   - Tokens are categorized into different types such as commands, operators, arguments, etc.
   - Command operators like pipes (`|`), redirection (`>`, `>>`, `<`), and other special symbols are identified.
   - **Quote Handling**: The shell respects single (`'`) and double (`"`) quotes, ensuring that content inside quotes is preserved as a single token and special characters within quotes are not expanded.
   - **Escape Sequences**: The lexer also detects escape sequences (e.g., `\n`, `\t`) and processes them correctly.
   - **Environment Variable Expansion**: Variables like `$HOME` and `$USER` are expanded at this stage into their respective values (e.g., `/home/user`), ensuring they are available for command execution.

#### 3. **Syntax Analysis**
   - The parsed tokens are then examined for correctness. This involves checking for potential syntax errors, such as mismatched parentheses or invalid operator usage.
   - A command table is constructed, where the tokens are grouped into individual commands. This structure facilitates the next stages of execution.
   - The shell verifies that operators like pipes and redirections are placed correctly within the command structure.
   - An execution pipeline is created based on the parsed tokens and operators. This determines how multiple commands will interact (e.g., through pipes) and ensures that redirections are set up correctly.

#### 4. **Command Execution**
   - **Redirection & Pipes**: The shell sets up necessary file descriptors to handle redirection (e.g., `>` for output redirection, `<` for input redirection). Pipes (`|`) are also set up to allow the output of one command to be passed directly to the input of another.
   - **Process Forking**: For each command in the pipeline, a new process is created using `fork()`. This allows the shell to execute multiple commands concurrently if needed.
   - **Built-in Commands**: The shell checks if a command is a built-in (e.g., `cd`, `exit`) and executes it internally without forking a new process.
   - **External Commands**: If the command is not built-in, the shell searches for the command in the directories listed in the system's `PATH` variable and executes it in a new process using `execvp()` or similar system calls.
   - The shell handles the exit status of each command to propagate success or failure back to the user.

#### 5. **Cleanup & Reset**
   - After executing the command, the shell ensures that all file descriptors are properly closed to avoid resource leaks.
   - Memory that was dynamically allocated during the execution of the command is freed, ensuring that the shell does not use unnecessary resources.
   - Signal handlers are reset to their default state, preparing the shell for the next command.
   - The shell is ready to process the next user input, repeating the cycle of reading, parsing, executing, and cleaning up.

### Program Flow Diagram

## 🚀 Installation
<details>
<summary>Click to expand</summary>

### Prerequisites
- GCC compiler
- Make
- readline library

### Steps

1. Clone the repository:
```bash
git clone https://github.com/Bengschor/minishell.git
cd minishell
```
2. Compile the project:
```bash
make
```

</details>

## 💻 Usage
<details>
<summary>Click to expand</summary>

1. Launch the shell:
```bash
./minishell
```

2. Example commands:
```bash
# Basic command execution
$ ls -l

# Input/Output redirection
$ echo "Hello" > output.txt
$ cat < input.txt

# Piping commands
$ ls -l | grep ".txt"

# Environment variables
$ echo $HOME
$ export MY_VAR=value

# Built-in commands
$ pwd
$ cd documents
$ echo -n "Hello World"
```

3. Exit the shell:
```bash
exit
```
or press Ctrl+D

</details>

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
