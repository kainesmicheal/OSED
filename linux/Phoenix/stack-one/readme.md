
in this got a strcpy copy any amount of bytes we pass in to a buffer of size 64, we have update the 65,66,67,68 bytes to hardcoded value 0x496c5962

we get the ascii version of the hex value and send them after 64bytes to update the change me variable

python3 -c 'print(("A"*64)+"bYlI")'
