# Signal Handling Framework

## Introduction

This project demonstrates Linux signal handling using C programming.

It shows how a process can receive, handle, block, and unblock different signals.

## Technologies and Tools

- C Programming
- Linux / Ubuntu (WSL)
- GCC
- Makefile
- kill
- strace

## Signals Used

- **SIGUSR1** – User-defined signal 1
- **SIGUSR2** – User-defined signal 2
- **SIGCHLD** – Handles child process termination
- **SIGTERM** – Graceful program termination
- **SIGINT** – Handles Ctrl+C

## Features

- Signal handling using custom handlers
- Signal blocking and unblocking
- Parent and child process creation
- Child process handling using SIGCHLD
- Graceful termination
- Signal tracing using strace

## Project Structure

```text
Signal_Handling_Framework/
├── src/
│   └── signal_handling_framework.c
├── screenshots/
├── Makefile
├── README.md
└── signal_framework
