# Pipex

This project from the 42 School curriculum is a simulation of the shell pipeline (`|`) operator. The program takes four arguments: an input file, two commands, and an output file.

It executes the first command, taking the input file as its standard input, and pipes its output to the standard input of the second command. The standard output of the second command is then written to the output file.

## Features

Based on the provided source code, this `pipex` implementation includes:

* **Argument Handling**: The program strictly requires 4 arguments (for a total `argc` of 5): `infile`, `cmd1`, `cmd2`, and `outfile`.
* **File Management**:
    * Opens the `infile` in read-only mode (`O_RDONLY`).
    * Opens the `outfile` in write-only mode, creating it if it doesn't exist and truncating it if it does (`O_WRONLY | O_CREAT | O_TRUNC`).
* **Command Parsing**:
    * Fetches the `PATH` environment variable to find the location of executables.
    * Parses both `cmd1` and `cmd2` to find their full binary path. It searches through the `PATH` directories or handles relative/absolute paths.
    * Uses a custom `ft_split` to separate the command string (e.g., `"ls -l"`) into an argument vector (`arg[0] = "ls"`, `arg[1] = "-l"`).
* **Process and Pipe Management**:
    * Creates a `pipe()` to communicate between the two commands.
    * Uses `fork()` to create two child processes, one for each command.
    * **Child 1 (cmd1)**:
        * Redirects its standard input (`STDIN_FILENO`) from the `infile` using `dup2`.
        * Redirects its standard output (`STDOUT_FILENO`) to the write-end of the pipe (`pipefd[1]`).
        * Executes `cmd1` using `execve`.
    * **Child 2 (cmd2)**:
        * Redirects its standard input (`STDIN_FILENO`) from the read-end of the pipe (`pipefd[0]`).
        * Redirects its standard output (`STDOUT_FILENO`) to the `outfile`.
        * Executes `cmd2` using `execve`.
* **Error and Resource Management**:
    * The main process waits for both child processes to complete.
    * Handles errors such as "command not found" or file permission issues.
    * Properly closes all file descriptors in all processes.
    * Frees all allocated memory, including command paths and argument vectors, before exiting.

## Compilation

To compile the project, use the provided `Makefile`:

```bash
make
````

## Usage

````bash
./pipex <infile> <cmd1> <cmd2> <outfile>
````
