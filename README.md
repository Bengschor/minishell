# 🐚 Minishell

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)]()
[![Version](https://img.shields.io/badge/version-1.0.0-blue)]()

A lightweight shell implementation that mimics basic functionalities of bash. This project aims to provide a simple yet functional command-line interface while serving as an educational tool for understanding how shells work.

## 📋 Table of Contents
<details>
<summary>Click to expand</summary>

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Customization](#customization)
- [How It Works](#how-it-works)
- [License](#license)

</details>

## ✨ Features
<details>
<summary>Click to expand</summary>

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

2. Install dependencies (Ubuntu/Debian):
```bash
sudo apt-get install libreadline-dev
```

3. Compile the project:
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

## ⚙️ Customization
<details>
<summary>Click to expand</summary>

Minishell supports customization through environment variables:

- `PROMPT`: Customize the shell prompt
  ```bash
  export PROMPT="mycustomshell> "
  ```
- `HISTSIZE`: Set the size of command history
  ```bash
  export HISTSIZE=1000
  ```

</details>

## 🔧 How It Works
<details>
<summary>Click to expand</summary>

Minishell operates in the following sequence:

1. **Input Processing**:
   - Reads input using readline library
   - Handles special characters and quotes
   - Splits input into tokens

2. **Parsing**:
   - Creates an Abstract Syntax Tree (AST)
   - Identifies commands, arguments, and operators
   - Validates syntax

3. **Execution**:
   - Creates child processes using fork()
   - Handles redirections and pipes
   - Executes built-in commands internally
   - Uses execve() for external commands

4. **Signal Handling**:
   - Manages interactive signals
   - Ensures proper process termination
   - Maintains shell stability

</details>
