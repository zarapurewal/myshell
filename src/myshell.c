#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_LENGTH 1024

/* internal command handlers */
void cd(char **args) {
    if (args[1] == NULL) {
        /* no argument: report current directory */
        char cwd[MAX_LENGTH];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd() error");
        } else {
            printf("%s\n", cwd);
        }
    } else {
        /* change directory to argument */
        if (chdir(args[1]) != 0) {
            perror("chdir() error");
        } else {
            /* update PWD environment variable */
            if (setenv("PWD", args[1], 1) != 0) {
                perror("setenv() error");
            }
        }
    }
}

void clr() {
    printf("\033[2J"); /* ANSI escape code to clear screen */
    printf("\033[H"); /* ANSI escape code to move cursor to top-left corner */
}

void dir(char **args) {
    DIR *dir;
    struct dirent *ent;
    int fd;

    if (args[1] == NULL) {
        /* no argument: list contents of current directory */
        dir = opendir(".");
    } else {
        /* list contents of specified directory */
        dir = opendir(args[1]);
    }
    
    if (dir != NULL) {
        /* redirect stdout to a file */
        if (args[2] != NULL) {
            fd = open(args[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("open() error");
                return;
            }
            if (dup2(fd, STDOUT_FILENO) == -1) {
                perror("dup2() error");
                return;
            }
            close(fd);
        }

        while ((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent->d_name);
        }

        /* restore stdout */
        if (args[2] != NULL) {
            if (dup2(STDOUT_FILENO, fd) == -1) {
                perror("dup2() error");
                return;
            }
        }

        closedir(dir);
    } else {
        perror("opendir() error");
    }
}


void show_environ(FILE *out) {
    extern char **environ;
    char **env = environ;
    while (*env) {
        fprintf(out, "%s\n", *env);
        env++;
    }
}


void echo(char **args) {
    int i = 1;
    FILE *output = stdout;

    /* check for output redirection */
    if (args[i] != NULL && strcmp(args[i], ">") == 0 && args[i+1] != NULL) {
        /* open file for writing */
        output = fopen(args[i+1], "w");
        if (output == NULL) {
            perror("fopen() error");
            return;
        }
        /* remove the redirection arguments from args */
        args[i] = NULL;
        args[i+1] = NULL;
    }

    while (args[i] != NULL) {
        fprintf(output, "%s ", args[i]);
        i++;
    }
    fprintf(output, "\n");

    /* close file if it was opened for redirection */
    if (output != stdout) {
        fclose(output);
    }
}

void help() {
    char *more_args[] = {"more", "../manual/readme.md", NULL};
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork failed\n");
        return;
    } else if (pid == 0) {
        /* execute more command in child process */
        if (execvp(more_args[0], more_args) == -1) {
            fprintf(stderr, "command not found\n");
        }
        exit(EXIT_FAILURE);
    } else {
        /* wait for child process to complete */
        int status;
        waitpid(pid, &status, 0);
    }
}

void my_pause() {
    printf("Press Enter to continue...");
    fflush(stdout); /* clear output buffer */
    while (getchar() != '\n');
}

void quit() {
    exit(EXIT_SUCCESS);
}

/* main shell loop */
/* main shell loop */
int main(void) {
    char *args[MAX_LENGTH/2 + 1]; /* array to store user input */
    char cmd[MAX_LENGTH]; /* user input string */
    int should_run = 1; /* flag to determine when to exit */
    int status; /* status of child process */

    while (should_run) {
        printf("my-shell> ");
        fflush(stdout); /* clear output buffer */

        /* read user input */
        if (fgets(cmd, MAX_LENGTH, stdin) == NULL) {
            break; /* end of file (ctrl-d) */
        }

        /* tokenize user input */
        char *token;
        int i = 0;
        token = strtok(cmd, " \n"); /* split string into tokens */
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " \n");
        }
        args[i] = NULL; /* set last argument to NULL */

        /* handle user command */
        if (args[0] == NULL) {
            /* empty command */
            continue;
        } else if (strcmp(args[0], "cd") == 0) {
            cd(args);
        } else if (strcmp(args[0], "clr") == 0) {
            clr();
        } else if (strcmp(args[0], "dir") == 0) {
            if (args[1] != NULL) {
                /* redirect stdout to file */
                freopen(args[1], "w", stdout);
                /* print directory contents to stdout (which is now redirected to file) */
                dir(args);
                /* restore stdout to original state */
                freopen("/dev/tty", "w", stdout);
            } else {
                dir(args);
            }
        } else if (strcmp(args[0], "environ") == 0) {
            if (args[1] != NULL) {
                /* redirect stdout to file */
                freopen(args[1], "w", stdout);
                /* print environment variables to stdout (which is now redirected to file) */
                show_environ(stdout);
                /* restore stdout to original state */
                freopen("/dev/tty", "w", stdout);
            } else {
                show_environ(stdout);
            }
        } else if (strcmp(args[0], "echo") == 0) {
            echo(args);
        } else if (strcmp(args[0], "help") == 0) {
            help();
        } else if (strcmp(args[0], "pause") == 0) {
            my_pause();
        } else if (strcmp(args[0], "quit") == 0) {
            quit();
        } else {
            fprintf(stderr, "Unknown command: %s\n", args[0]);
        }
    }

}