when we run a program, the shell will call execve() shell call with our executable

execve() will setup as stack for us, push argc, argv, envp into that stack

when everything is ready, control is handed to `_start()`

![[Pasted image 20220814091704.png]]


