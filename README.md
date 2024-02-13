# PIPEX 42

the project is all about discovering the UNIX mechanism : pipe

the main functions you are going to use are :

* pipe()
* fork()
* access()
* execve()
* dup and dup2()
* wait and waitpid()
* unlink()
* open()
* close()

PLEASE TAKE YOUR TIME AND READ THE MAN PAGES OF ALL THE FUNCTIONS

Understanding every aspect of these functions is crutial

## parsing

the main function has to be declared as follows :

```main
int	main(int ac, char **av, char **environ)
```

the environ variable is an array that contains the envirement varibles (it is null terminated)

"Each process has an associated array of strings called the environment list, or simply the environment. Each of these strings is a definition of the form name=value. Thus, the environment represents a set of name-value pairs that can be used to hold arbitrary information. The names in the list are referred to as environment variables."

we are going to use this variable called array to extract the paths. these paths are going to be used whenever we want to execute a command.

## MANDATORY :

the parsing part is very easy, all i did was creat a structure that contains the paths that i got from the environ variables, alongside the first command and the second command splited with ft_split and stored in an array, and the last thing to is a two integer array that will be used with pipe() to hold the file descriptors of the pipe, 0 for the ReadEnd and 1 for WriteEnd.

the main idea is to create two child processes using the function fork(), and have them execute the command using execv(), and the first child has to pass it's output to the second child using a pipe.

Keep in mind the execve() function replaces the current process with a new process, that is the command to be executed, normally each process has it's own stdin, stdout and stderr. but in our case we need to read and write from and to files or pipes. so we should redirect the input and output accordingly. to do just that we will use the function dup2();

### What should each child do :

* child 1 : close pipe[0] as it is of no use, open the infile, turn it into the stdin, turn pipe[1] to stdout, then execute the first cmd.
* child 2 : close pipe[1] as it is of no use, turn pipe[1] to stdout, open the outfile, turn it into the stdout, then execute the first cmd.

### Redirecting the input :

in order for us to redirect the input we will use the function dup2() to do the following changes :
* child 1 : infile -> stdin, pipe[1] -> stdout
* child 2 : pipe[0] -> stdin, outfile -> stdout

all unused file descriptor must be closed. 
* child 1 : close(pipe[0])
* child 1 : close(pipe[1])
* parent : close(pipe[0]), close(pipe[1])

The parent has to wait for the two childs to execute after forking both children (! it should not wait after forking the first child and then wait again after creating the second child)
The reason for this is that if you execute
```
sleep 4 | sleep 8
```
it will wait 4 + 8 seconds
it should only wait 8 seconds, that is the biggest value.



Parent :

		|
		|pipe()
		|
		|fork()
		|
		|__________ child 1 ____________
		|				|open()
		|				|close()
		|fork()				|dup2()
		|				|execve()
		|_____ child 2 _________
		|			|open()
		|			|close()
		|			|dup2()
		|			|execve()
		|
		|waitpid()
		|closefds()
		|exit()

You could as well creat only one child and have it execute the first cmd and then have the parent execute the second cmd, but i just prefer using two childs.

### ERROR MANAGEMENT :

Error management is mandatory, all system calls should be protected in case of failure. then call the perror() function to print the corresponding error.

that includes :
* if (-1 == pipe()) {perror();}
* if (-1 == fork()) {perror();}
* if (-1 == dup()) {perror();}
* if (-1 == dup2()) {perror();}

LOL 
```
if (-1 == exit(1))
	kill(getpid());
```

## BONUS

### MULTIPE CMDS

In this part of the bonus, our program needs to handle multiple commands. the challenge with multiple commands is that you have to fork() multiple times, for as many commands you have, exactly argc - 3, and that you have to pipe and redirect input and output multiple times, eactly argc - 4.
for example : say that you have 5 commands, you are only going to need four pipes to pass the output from the first to the last.

infile -> cmd1 <===> cmd2 <===> cmd3 <===> cmd4 <===> cmd5 -> outfile


### HERE_DOC


comming soon

* process image
* process controle block PCB
