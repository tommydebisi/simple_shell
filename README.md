# SIMPLE SHELL
![Gates of Shell](./img/shell.jpeg)
**Replication of little _unix_ processes using knowledge of C Programming language functions learnt so far**
<br>
## AIM & OBJECTIVES
**At the end of this project we should be able:**

- To know how the shell works
- To be able to explain to anyone the concepts applied in building the simple shell
- To know the creator of the unix process

## COMPILATION
**The shell should be compiled this way:** <br>
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh` <br>

## PROCESSES IMPLEMENTED
***Here are some features implemented in the shell so far*** <br>

- **Execution of Executable files**
- **Handling of `ctrl + c` and `EOF`**
- **Handling of arguments.**
- **Handling of executables in `PATH` environment variable.**
- **Handling of builtins `exit`, `env`, `setenv`, `unsetenv`, `cd`**

## EXAMPLES
``` py
#cisfun$ ls -l /tmp
total 20
-rw------- 1 julien julien    0 Dec  5 12:09 config-err-aAMZrR
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-colord.service-V7DUzr
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-rtkit-daemon.service-ANGvoV
drwx------ 3 root   root   4096 Dec  5 12:07 systemd-private-062a0eca7f2a44349733e78cb4abdff4-systemd-timesyncd.service-CdXUtH
-rw-rw-r-- 1 julien julien    0 Dec  5 12:09 unity_support_test.0
#cisfun$ /bin/ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell_0.3  stat    test_scripting.sh  wait.c
#cisfun$
```

## AUTHORS
- **ADEBISI OLUWATOMIWA**
- **BRIGHT OKON**