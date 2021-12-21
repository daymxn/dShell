<p align="center">
<img src="https://i.imgur.com/xhSqaLL.png" />
</p>

# dShell

Another toy shell that serves no true purpose beyond being an engineer's µarch baby.

Learn more about my journey in developing the initial release of this shell <a href="daymxn.com">on my website.</a>
*to be released
## Usage/Examples

### Builtins

Builtins are predefined commands built into the shell.
If the first argument of a `COMMAND` (otherwise known as the WORD) is equal to
any of the builtin functions, then said builtin functions will be called instead
of being executed. This is true regardless if you have a valid form of the program
on your PATH.

`help` - prints a list of all builtins

```custom
dShell $ > help
----- dShell -----
Builtin commands: 
~ cd
~ help
~ exit
```

`cd` - change the working directory

```custom
dShell $ > cd help
dShell $/help > 
```

`exit` - terminate the shell

```custom
dShell $ > exit

Process finished with exit code 0
```

### Logical Operators

Logical operators provide a way for simple commands to be followed by other
simple commands.
Logical operators can not be followed or superseded by other logical operators.

AND [`&&`] - following command will only execute if the exit status is `EXIT_SUCESS`

```custom
dShell $ > ls
Testing
dShell $ > mkdir Testing && cd Testing
mkdir: cannot create directory ‘TestDirectory’: File exists
dShell $ > mkdir Testing2 && cd Testing2
dShell $/Testing2 >
```

OR [`||`] - following command will only execute if the exit status is NOT `EXIT_SUCESS`

```custom
dShell $ > ls
Testing
dShell $ > mkdir Testing && cd Testing
mkdir: cannot create directory ‘TestDirectory’: File exists
dShell $/Testing > 
```


NOT [`!`] - flips the exit status of the following command

```custom
dShell $ > ls
Testing
dShell $ > ! mkdir Testing && cd Testing
mkdir: cannot create directory ‘TestDirectory’: File exists
dShell $/Testing > 
```

ENDCOMMAND [`;`] - separates commands from one another

```custom
dShell $ > ls pwd
ls: cannot access 'pwd': No such file or directory
dShell $ > ls;pwd
Testing
/home/daymon/dShell/cmake-build-debug
```

### Pipes

Pipes (labeled `PIPE` or `|`) push the STDOUT of one command to the STDIN of another.

```custom
dShell $ > tail test.txt | grep "Hello"
Hello World!
```

Pipes must be precceded and followed by a `COMMAND` or `SUBSHELL`.
Preceeding or following `PIPE` with anything else is undefined.

Pipes are good for a single `COMMAND`.
To continue the `PIPE`, follow the `COMMAND` with another `PIPE`


### Redirection

Redirection allows you to write the STDOUT of a `COMMAND` to a specified file.

```custom
dShell $ > tail test.txt >> test2.txt
dShell $ > tail test2.txt
Hello World!
```

Redirection comes in two forms: `REDIRECT_TO` [`>`] and `REDIRECT_TO_OVERWRITE` [`>>`]. Both are
identical in nature, except that one *appends* the input to the file, wheres the other
*overwrites* the file to contain the input.

Redirection does not make any straight assumptions about your input. If you provide a
complex command to a redirection, the redirection will evaluate the complex command and
utilize the first string streamed to STDOUT as the input (or output). What this means is that
you can do things like this:

```custom
dShell $ > tail test.txt > (cd ./testdirectory && ls && grep "test3")
```

You are not limited to programs either, you can provide either the input
or output as straight string literals.

```custom
dShell $ > "Hello world!" > test3.txt && "Goodbye world!" >> test3.txt
dShell $ > tail test3.txt
Hello world!
Goodbye world!
```

### Subshells

Subshells allow you to branch execution into a seperate process.

```
dShell $ > (cd Test && pwd)
/home/daymon/dShell/cmake-build-debug/Test
dShell $ > pwd
/home/daymon/dShell/cmake-build-debug
```

Initilized with a `SUBSHELL_START` [`(`] and ended with a `SUBSHELL_END` [`)`],
these two symbols create a `SUBSHELL`.

Subshells also support pipes!

```
dShell $ > (cd Test && tail test.txt) | grep "Hello"
Hello World!
```
## Roadmap

- Fix open issues

- Generate unit tests for everything

- Implement addition builtins

- Add support for pre-evaluated arguments


## Acknowledgements

- [Stephen Brennan's classic tutorial](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [Introduction to Systems Programming: a Hands-on Approach](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/)
- [The Linux Programming Interface: A Linux and UNIX System Programming Handbook](https://www.amazon.com/Linux-Programming-Interface-System-Handbook/dp/1593272200)
- [flex & bison: Text Processing Tools](https://www.amazon.com/flex-bison-Text-Processing-Tools/dp/0596155972)

## License

[Apache 2.0](https://github.com/daymxn/dShell/blob/main/LICENSE)


## Authors

- [@daymxn](https://www.github.com/daymxn)

