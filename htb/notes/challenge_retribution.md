
we have while loop that will continue as long as we enter wrong option

in the 2nd  option we overflow, but before that, it take some input and copies it to a buffer and print it

if we need to leak something, we will have to give empty input, that way it will print whatever that was in the stack at that point

this is a new trick, i didnt know about this 

to leak infor we just print the stack, without filling it with our data

this print happens right after read call, so the read libc function must have pushed some addresses that we can leak


leak address of our current instructions using local buffer print,

find pop rdi; ret; in our executable

[INFO] File: ./sp_retribution
0x0000000000000d33: pop rdi; ret; 

