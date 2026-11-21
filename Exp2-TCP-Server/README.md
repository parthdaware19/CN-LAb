# Experiment 2: TCP Echo Server

## C Code (`server1230.c`)

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT (10000 + 242)
#define BUF_SIZE 1024

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUF_SIZE];
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 3);

    printf("TCP Echo Server listening on port %d...\n", PORT);

    new_socket = accept(
        server_fd,
        (struct sockaddr *)&address,
        (socklen_t *)&addrlen
    );

    while (1)
    {
        memset(buffer, 0, BUF_SIZE);

        int bytes = read(new_socket, buffer, BUF_SIZE);

        if (bytes <= 0)
            break;

        printf("Received: %s", buffer);

        send(new_socket, buffer, bytes, 0);
    }

    close(new_socket);
    close(server_fd);

    return 0;
}
```

---

## Objective
To implement a connection-oriented **TCP Echo Server** in C using Berkeley sockets that:
1. Creates a stream socket (`SOCK_STREAM`) and binds it to port `10242` (`10000 + 242`).
2. Listens for incoming connections and accepts a client connection.
3. Enters an iterative loop reading incoming text buffers from the client.
4. Prints the received text to standard output and immediately echoes it back to the client.
5. Closes the connection gracefully when the client terminates.

---

## Theory

**Transmission Control Protocol (TCP)** provides reliable, ordered, and error-checked delivery of a stream of bytes between applications over an IP network.

### Socket Lifecycle (TCP Server)
```
       socket()
          │
          ▼
        bind()
          │
          ▼
       listen()
          │
          ▼
       accept()  ◄── (Blocks until client connects)
          │
  ┌───────▼───────┐
  │ read() buffer │
  │ print buffer  │ (Loop until client disconnects)
  │ send() echo   │
  └───────┬───────┘
          ▼
        close()
```

1. **`socket(AF_INET, SOCK_STREAM, 0)`**: Initializes an IPv4 TCP stream socket descriptor.
2. **`bind(...)`**: Binds the socket to `INADDR_ANY` on port `10242` (`10000 + PRN`).
3. **`listen(server_fd, 3)`**: Puts the socket in passive listening mode with a connection backlog queue of 3.
4. **`accept(...)`**: Accepts the connection from the client, returning `new_socket`.
5. **`read(...)` & `send(...)`**: Reads client data into `buffer` and echoes it back.

---

## Compilation & Execution

### Prerequisites
- GCC Compiler (Linux / WSL / macOS)

### Steps
1. Navigate to this directory:
   ```bash
   cd Exp-02-TCP-Server
   ```

2. Compile the server program:
   ```bash
   gcc server1242.c -o server
   ```

3. Run the TCP Echo Server:
   ```bash
   ./server
   ```

> [!IMPORTANT]
> The server must be started **before** the TCP Echo client ([Exp-03-TCP-Client](../Exp-03-TCP-Client/client1242.c)).

---

## Sample Output

```text
TCP Echo Server listening on port 10242...
Received: Hello from Client!
Received: Computer Networks Lab
Received: Testing Echo Communication
```

---

## Related
- **Client Implementation:** [Exp-03-TCP-Client](../Exp-03-TCP-Client/)
