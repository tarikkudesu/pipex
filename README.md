# PIPEX 42

the project is all about discovering the UNIX mechanism : pipe

the main functions you are going to use are :

* pipe()
* fork()
* access()
* execve
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

the parsing part is very easy, all i did was open the files (input and output) and store their file descriptors in a structure, along side with the paths that i got from the environ variables. the first command and the second command splited with ft_split and stored in an array, and the last thing to is a two integer array that will be used with pipe().

the main idea is to create two child processes using the function fork(), and have them execute the command using execv(), and the first child has to pass it's output to the second child using a pipe.

Keep in mind the execve() function replaces the current process with a new process, that is the command to be executed, normally each process has it's own stdin, stdout and stderr. but in our case we need to read and write from and to files or pipes. so we should redirect the input and output accordingly. to do just that we will use the function dup2();

### Redirecting the input :
the first child has to read from the infile and write in the writeend pipe[1] of the pipe.
the second child has to read from the readend pipe[0] of the pipe and write in the outfile.

in order for us to redirect the input we will use the function dup2() to do the following changes :
* child 1 : infile -> stdin, pipe[1] -> stdout
* child 2 : pipe[0] -> stdin, outfile -> stdout

all unused file descriptor must be closed. 
* child 1 : close(outfile), close(pipe[0])
* child 1 : close(infile), close(pipe[1])
* parent : close(infile), close(outfile, close(pipe[0]), close(pipe[1])

The parent has to wait for the two childs to execute after forking both children (! it should not wait after forking the first child and wait again creat the second child and wait for it)
The reason for this is that if you execute
```
sleep 4 | sleep 8
```
it will wait 4 + 8 seconds
but in terminal it will wait 8 seconds, that is the biggest value



Parent :

		|
		|pipe()
		|
		|fork()
		|
		|__________ child 1 ____________
		|				|
		|				|close()
		|fork()				|dup2()
		|				|execve()
		|_____ child 2 _________
		|			|
		|			|close()
		|			|dup2()
		|			|execve()
		|
		|waitpid()
		|closefds()
		|exit()

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

it is quit challenging at first. it will make sence at end ;)




### HERE_DOC




process image
process controle block PCB
