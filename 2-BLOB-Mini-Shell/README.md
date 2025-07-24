# 🐚 BLOB Shell — A Custom Unix-Like Command Line Shell

BLOB Shell (Binary Line Operating Bash) is a lightweight and fully functional command-line shell implemented in **C++**. It mimics the behavior of popular Unix shells like `bash` or `zsh` with support for built-in commands, redirection, background processes, and pipelines.

This project was built from scratch to deepen understanding of **OS-level system calls**, **process management**, and **shell architecture**.

---

## 🚀 Features

✅ Command execution for all standard Linux binaries  
✅ Input and Output Redirection (`<`, `>`, `>>`)  
✅ Command Piping (`|`)  
✅ Background process execution (`&`)  
✅ Built-in `cd` and `exit` commands  
✅ Dynamic shell prompt with username, hostname, and current directory  
✅ Command history across sessions  
✅ Tab-based autocomplete for commands (under development)

---

## Project Structure

BLOB-Shell/
│
├── src/
│ ├── main.cpp # Entry point and shell loop
│ ├── Parser.cpp # Command parsing and tokenizing
│ ├── Executor.cpp # Executes commands with redirection/piping/bg
│
├── include/
│ ├── Parser.h
│ ├── Executor.h
│
├── Makefile # Compile all files
├── README.md
└── .blob_history # Saved history file (auto-created)

---

## 🛠️ Build and Run

### 🔧 Prerequisites

- Linux/macOS terminal (or WSL on Windows)
- `g++` compiler
- GNU Make

---

### 🔨 Build

```bash
git clone https://github.com/snehil-dev/BLOB-Shell.git
cd BLOB-Shell
make







```
