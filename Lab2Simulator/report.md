# Process Management Simulator Report

## Introduction

This project demonstrates the fundamental concepts of process creation, execution, and synchronization in Unix-like operating systems using C. By utilizing system calls such as `fork()`, `execvp()`, and `waitpid()`, the code shows how a parent process can spawn and manage multiple children.

## Implementation Summary

My program is structured to : 
- Create **10 child processes** from a single parent using a loop and `fork()`.
- In each child process, we call a different linux command, that is fetched from a premade array. 
- The parent process uses `waitpid(-1, ...)` to wait for **all children to complete**, regardless of their order of termination.
- I decided to store the exit information (PID and status) for each child within a 2D array. I did this so it would all be printed at once at the end by the parent. Without this it gets mixed in to the childrens prints.
- After all children have finished, the parent prints a summary of each child’s exit status, reporting whether it exited normally or was terminated by a signal, along with the pid of the child.

Basic error checking ensures that any `fork()` or `execvp()` failures are printed for reporting.

## Program Results/Observations

### A. Process Creation and Management

- The parent process forks 10 children using `fork()`, which duplicates the current process.
- Each child immediately replaces its code with a different command using `execvp()`, this shows how a process image can be replaced.
- PIDs are collected for identification, but the program uses `waitpid(-1, ...)` to reap children as they terminate, avoiding zombie processes that could be accidentally created if this was not here. 

### B. Parent and Child Process Interaction

- Children print their own PID and the command they are about to execute.
- The parent collects the results asynchronously and records them in a results array.
- At the end of execution, the parent outputs a **synchronized summary** for all children, which includes:
  - The PID of each child.
  - Whether it exited normally or was killed by a signal.
  - The corresponding exit code or signal number.

This approach separates process handling from reporting, improving readability and demonstrating real-world synchronization patterns.

## Screenshot Breakdown

The screenshot provided displays what is printed to the console after `make` is used to compile the program, and then it is subsequently ran (using ./simulator).

The highlighting is there to display the important sections of the printed result, since some of the children processes print to the terminal while executing their task. 

The first highlighted block displays that each child is printing their pid along with the task they will execute. Each of the intended processes are present and print correctly. 

We see that two of the processes fail to execute their commands, this is because one is trying to remove `nonExistantDir`, which of course does not exist.

Finally, when all children are finished executing we print from the parent process the resulting status of each child process. 

## Makefile Breakdown

This Makefile compiles my C program using gcc with extra warning flags `(-Wall -Wextra)` to catch potential issues early. I set the output binary to be called simulator, and the default rule builds it from `main.c`. I also included a clean rule so I can run `make clean` to remove the compiled binary when I want to rebuild from scratch or clean up my directory. In short, the makefile saves me from having to type out the full compile command every time or search through my recent commands with the up arrow. 

## Conclusion

The Process Management Simulator C code illustrates the core mechanisms of Unix process control. By combining `fork()`, `execvp()`, and `waitpid()`, the program provides a hands-on demonstration of how a parent process can manage and synchronize with multiple child processes performing independent tasks. This lab helped to reinforce my knowledge of system calls and helped me to understand process control at a deeper level.
