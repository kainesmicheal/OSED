the main function calls a function called start_level() whihc has buffer of 64 bytes, which is copied with user input using a gets call

we can overwrite stuff, by overflowing the buffer


when a function is called using CALL somthing, the call instruction pushs the next instruction into the stack and jumps to the function, the new functions call stack starts next to the instruction, thus we can overwrite that address 

when our current function reaches the end, in leave instruction cleans up the stack frame leaving the pushed instruction on top of the stack, and ret just pops whats on top of the stack into RDI

python3 -c "print('A'*88 + '\x56\x11\x40')"

we just update the magic function address in the location, then it will poped to rdi


