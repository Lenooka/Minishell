# Minishell
Minishell is a Unix shell project developed as a pair project for the 42 School curriculum. It supports command parsing, piping, redirection, and environment handling. I implemented command execution and heredoc functionality, while my partner focused on parsing and built-ins.

# Features
* Command execution with arguments
* Built-in commands (cd, echo, pwd, export, unset, env, exit)
* Piping between commands
* Input/output redirection (>, >>, <)
* Heredoc support (<<)
* Environment variable handling
* Signal handling (e.g., Ctrl+C, Ctrl+D)
* 
# Installation
```
git clone git@github.com:Lenooka/Minishell.git
cd Minishell
make
```
# Usage
```
./minishell
```
# Once started, you can execute commands as in a normal Unix shell:
```
> echo "Hello World"
Hello World
> ls -l | grep src
```

# Learning Goals
* Understanding Unix shell behavior and system calls
* Implementing process creation and management
* Handling piping, redirection, and heredoc
* Managing environment variables
