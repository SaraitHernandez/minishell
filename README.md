# Minishell

Welcome to **Minishell**, a simplified version of the Unix shell, built as a project to understand how shells work under the hood. This shell aims to replicate some of the basic functionalities of `bash`, including command execution, pipelines, redirections, and built-in commands, while adhering to specific project requirements.

---

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Signal Handling](#signal-handling)
- [Folder Structure](#folder-structure)
- [Limitations](#limitations)
- [Authors](#authors)

---

## Features

- Display a prompt while waiting for user input.
- Command history navigation using arrow keys.
- Execution of commands with absolute, relative, or `PATH`-resolved paths.
- Environment variable expansion, including special variables like `$?`.
- Handle single and double quotes as in `bash`.
- Input/output redirections (`<`, `>`, `>>`, `<<`).
- Command pipelines using the pipe (`|`) operator.
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- Proper signal handling for `ctrl-C`, `ctrl-D`, and `ctrl-\`.

---

## Installation

### Requirements

- GCC compiler
- GNU Readline library - For Debian/Ubuntu-based Systems 
  ```bash 
  sudo apt-get install libreadline-dev
  ```
- Make

### Steps

1. **Clone the Repository**

   ```bash
   git clone https://github.com/SaraitHernandez/minishell.git
   ```

2. **Navigate to the Project Directory**

   ```bash
   cd minishell
   ```

3. **Compile the Program**

   ```bash
   make
   ```

   This will generate the `minishell` executable in the root directory.

---

## Usage

Start the shell by running the executable:

```bash
./minishell
```

You should see a prompt like:

```bash
minishell$ 
```

Now you can start typing commands as you would in a regular shell.

### Examples

- **Running an External Command**

  ```bash
  minishell$ ls -la
  ```

- **Using a Built-in Command**

  ```bash
  minishell$ cd /path/to/directory
  ```

- **Pipelines**

  ```bash
  minishell$ ls -la | grep minishell | wc -l
  ```

- **Redirections**

  - Output Redirection:

    ```bash
    minishell$ echo "Hello, World!" > hello.txt
    ```

  - Input Redirection:

    ```bash
    minishell$ wc -w < hello.txt
    ```

  - Append Output:

    ```bash
    minishell$ echo "This is appended text." >> hello.txt
    ```

  - Heredoc:

    ```bash
    minishell$ cat << EOF
    > This is a heredoc input.
    > EOF
    ```

- **Environment Variable Expansion**

  ```bash
  minishell$ echo "Current user: $USER"
  ```

- **Exiting the Shell**

  ```bash
  minishell$ exit
  ```

---

## Built-in Commands

### `echo`

- Usage: `echo [-n] [string ...]`
- Options:
  - `-n`: Do not output the trailing newline.

### `cd`

- Usage: `cd [directory]`
- Changes the current directory to `directory`.

### `pwd`

- Usage: `pwd`
- Prints the current working directory.

### `export`

- Usage: `export [name[=value] ...]`
- Sets environment variables.

### `unset`

- Usage: `unset [name ...]`
- Unsets environment variables.

### `env`

- Usage: `env`
- Prints the list of environment variables.

### `exit`

- Usage: `exit [n]`
- Exits the shell with a status of `n`.

---

## Signal Handling

- **`ctrl-C` (`SIGINT`)**: Displays a new prompt on a new line.
- **`ctrl-D` (EOF)**: Exits the shell.
- **`ctrl-\` (`SIGQUIT`)**: Does nothing.

---

## Folder Structure

The project is organized into directories and files to enhance modularity and maintainability.

```
minishell/
├── Makefile
├── README.md
├── src/
│   ├── main.c
│   ├── init_shell.c
│   ├── input.c
│   ├── lexer.c
│   ├── expand_variables.c
│   ├── parser.c
│   ├── parser_utils.c
│   ├── executor.c
│   ├── exec_utils.c
│   ├── redirection.c
│   ├── pipes.c
│   ├── signals.c
│   ├── cleanup.c
│   ├── globals.c
│   ├── builtins/
│   │   ├── builtin_echo.c
│   │   ├── builtin_cd.c
│   │   ├── builtin_pwd.c
│   │   ├── builtin_export.c
│   │   ├── builtin_unset.c
│   │   ├── builtin_env.c
│   │   └── builtin_exit.c
│   ├── environment/
│   │   ├── environment.c
│   │   └── environment_utils.c
│   └── utils/
│       ├── utils_strings.c
│       ├── utils_memory.c
│       └── utils_errors.c
├── includes/
│   └── minishell.h
└── libft/
    └── [Your libft files or linked library]
```

### **Explanation of Folders and Files**

#### **`Makefile`**

- Automates the compilation process.
- Contains rules to build, clean, and rebuild the project.

#### **`README.md`**

- The document you're reading now.
- Provides an overview and instructions.

#### **`src/`**

- **Core Source Files**
  - **`main.c`**
    - Entry point of the shell program.
  - **`init_shell.c`**
    - Initializes the shell environment and signal handlers.
  - **`input.c`**
    - Handles user input and command history.
  - **`lexer.c`**
    - Tokenizes the input command line.
  - **`expand_variables.c`**
    - Expands environment variables in tokens.
  - **`parser.c`**
    - Parses tokens into an abstract syntax tree (AST).
  - **`parser_utils.c`**
    - Utility functions for the parser.
  - **`executor.c`**
    - Executes commands based on the AST.
  - **`exec_utils.c`**
    - Utility functions assisting in command execution.
  - **`redirection.c`**
    - Manages input/output redirections.
  - **`pipes.c`**
    - Handles piping between commands.
  - **`signals.c`**
    - Manages signal handling for the shell.
  - **`cleanup.c`**
    - Frees allocated resources before exiting.
  - **`globals.c`**
    - Contains the allowed global variable for signal indication.

- **Built-in Commands (`builtins/`)**
  - Each built-in command is implemented in its own file for clarity and modularity.
  - **`builtin_echo.c`**
  - **`builtin_cd.c`**
  - **`builtin_pwd.c`**
  - **`builtin_export.c`**
  - **`builtin_unset.c`**
  - **`builtin_env.c`**
  - **`builtin_exit.c`**

- **Environment Management (`environment/`)**
  - Manages environment variables for the shell.
  - **`environment.c`**
    - Functions to manipulate environment variables.
  - **`environment_utils.c`**
    - Utility functions for environment management.

- **Utilities (`utils/`)**
  - General-purpose helper functions used across the project.
  - **`utils_strings.c`**
    - String manipulation functions.
  - **`utils_memory.c`**
    - Memory allocation and management functions.
  - **`utils_errors.c`**
    - Error reporting and handling functions.

#### **`includes/`**

- Contains all header files.
- **`minishell.h`**
  - Main header file with structure definitions, function prototypes, and macros.

#### **`libft/`**

- Your custom library of standard functions (if applicable).
- Include or link your `libft` library here.

---

## Limitations

While `minishell` replicates many features of `bash`, there are some limitations:

- **No Wildcard Expansion**
  - Patterns like `*.c` won't be expanded automatically.
- **Limited Error Messages**
  - Error messages may not be as descriptive as those in `bash`.
- **No Job Control**
  - Background job management (`&`, `fg`, `bg`, etc.) is not implemented.
- **No Advanced Shell Features**
  - Features like command substitution, shell scripting, or functions are not supported.
- **No Support for Special Characters**
  - Characters like backslash (`\`) or semicolon (`;`) are not interpreted.

---

## Authors

- **Sarait Hernández** - [GitHub](https://github.com/SaraitHernandez/)
- **Artur Kacprzycki** - [GitHub](https://github.com/artkacp)

Feel free to contact us for any questions or suggestions!

---

Thank you for using **Minishell**! We hope this project helps you understand the inner workings of a shell and provides a solid foundation for further exploration.

---

# Notes

- **Contributions**: If you'd like to contribute to this project, please fork the repository and submit a pull request.
- **License**: This project is for educational purposes and may not be used for commercial applications.
- **Acknowledgments**: Thanks to the resources and community that provided guidance throughout this project.