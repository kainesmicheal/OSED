
cases:

- using format string bug to local local instruction address or libc function address
- if a stack buffer is getting printed, and you dont fill it, it will print whatever that was there before, which could leak address (arbirtary read)