NAME
      A Simple Shell
       
AUTHOR
      Zara Purewal
      21404176
      # I acknowledge DCU's Academic Integrity Policy

SYNOPSIS
      ./myshell
      Internal Commands (cd, exec, dir etc.)
      External Commands
      Environment Variables
      I/O Redirection
      Background execution

DESCRIPTION
      The Shell or Command Line Interpreter is the fundamental User interface 
      to an Operating System.      
      

     In a foreground execution, the shell waits for the process to complete before prompting the user for the next command. This means that the user cannot enter any other commands until the current process finishes executing. The shell will display the output of the process on the terminal as it is generated.

     In a background execution, the shell starts the process and immediately prompts the user for the next command without waiting for the process to complete. This means that the user can enter other commands while the current process is executing. The output of the process is not displayed on the terminal unless it is explicitly redirected to a file or another process.

     foreground execution is the default behavior. When the user enters a command, the shell creates a new process to execute the command and waits for the process to complete before prompting the user for the next command. To run a command in the background, the user can append an ampersand "&" to the end of the command. The shell will start the process and immediately prompt the user for the next command without waiting for the process to complete.

      The user can issue commands by entering them via the keyboard through standard input. See the COMMANDS LIST for the internal 
      commands that work with myshell. If the user runs a command that is 
      not on this list, then the shell will still run it externally.

      Input / Ouput Redirection is also possible to allow users to run programs 
      with inputs from a file or log the output from commands/programs to a file of 
      their choice.

      Background Execution is possible see below.

COMMANDS LIST
      cd <directory> - change the current default directory to <directory>
      clr - clear the screen
      dir <directory> - list the contents of directory <directory>
      environ - list all the environment strings
      echo <comment> - display <comment> on the display followed by a new line
      help - display the user manual (readme, i.e. THIS FILE)
      pause - pause operation of the shell until 'Enter' is pressed
      quit - quit the shell

BATCHFILE
      ./myshell batchfile

      Instead of taking commands from keyboard (stdin), the shell takes each
      line from the batchfile and runs it as the input command.

I/O REDIRECTION
      myshell supports i/o-redirection on either or both stdin and/or stdout.

      programname arg1 arg2 < inputfile > outputfile

      INPUT
            programname < inputfile

      Takes in the a list of arguments to run with the program.

      OUTPUT
            programname > outputfile

      Writes the program output to a file instead of printing it on the shell.
      If there was previously content in the file, it will be replaced.

      APPEND
            programname >> outputfile

      Similar to output but appends the current content of the outputfile and
      creates a new file if outputfile does not exist.

BACKGROUND EXECUTION
     To run a program in the background, you can use the & symbol at the end of the command. This symbol tells the shell to run the command in the background and immediately return to the prompt, allowing you to continue entering other commands while the program runs in the background

REFERENCES
    1. environ - man page: Retrieved March 11, 2023, https://man7.org/linux/man-pages/man7/environ.7.html
    2. fork - man page: Retrieved March 11, 2023, https://man7.org/linux/man-pages/man2/fork.2.html
    3. c programming: Retrieved March 14, 2023, https://www.gnu.org/software/libc/manual/pdf/libc.pdf
    4. Operating System Concepts. (n.d.). 10th Edition. Retrieved March 19, 2023, from https://os-book.com/OS10/index.html