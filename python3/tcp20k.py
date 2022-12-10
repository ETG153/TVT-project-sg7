import socket

host = "172.20.241.9"
port = 20000
outfile = "tcp20k.out"
data = []
with open(outfile, "w") as file:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        s.sendall(b"56\n")
        response = ""
        while True:
            response = s.recv(1024)
            if not response:
                break
            tempstr = str(response).replace("b'", "").replace("'", "").replace("\\n", "\n*").split("*")
            data.append(tempstr)
    for each in [item for sublist in data for item in sublist]:
        file.write(each)
print(data)
