# Experiment 3: TCP Echo Client

## C Code (`client1230.c`)

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
    int sock;
    struct sockaddr_in server;
    char buffer[BUF_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    while (1)
    {
        printf("Enter message: ");
        fgets(buffer, BUF_SIZE, stdin);

        send(sock, buffer, strlen(buffer), 0);

        memset(buffer, 0, BUF_SIZE);

        read(sock, buffer, BUF_SIZE);

        printf("Echo from server: %s", buffer);
    }

    close(sock);

    return 0;
}
```

---

## Objective
To implement a connection-oriented **TCP Echo Client** in C using Berkeley sockets that:
1. Creates a stream socket (`SOCK_STREAM`).
2. Configures the server address structure targeting port `10242` (`10000 + 242`).
3. Connects to the listening TCP Echo Server via `connect()`.
4. Prompts the user for messages from standard input in an interactive loop.
5. Sends each message to the server, reads back the echoed response, and displays it.

---

## Theory

The TCP client establishes a full-duplex connection to the server using the `connect()` system call, which executes the TCP 3-way handshake (SYN, SYN-ACK, ACK). Once connected, the client streams user input to the server and awaits the echoed response over the same socket.

### Socket Lifecycle (TCP Client)
```
       socket()
          │
          ▼
       connect()  ──► (Initiates TCP 3-way handshake with server)
          │
  ┌───────▼───────────────┐
  │ fgets() input message │
  │ send() to server      │ (Loop until user terminates)
  │ read() echoed reply   │
  │ printf() reply        │
  └───────┬───────────────┘
          ▼
        close()
```

---

## Compilation & Execution

### Prerequisites
- GCC Compiler (Linux / WSL / macOS)
- The TCP Echo Server ([Exp-02-TCP-Server](../Exp-02-TCP-Server/)) must already be running.

### Steps
1. Navigate to this directory:
   ```bash
   cd Exp-03-TCP-Client
   ```

2. Compile the client program:
   ```bash
   gcc client1242.c -o client
   ```

3. Run the TCP Echo Client:
   ```bash
   ./client
   ```

---

## Sample Input & Output

```text
Enter message: Hello from Client!
Echo from server: Hello from Client!
Enter message: Computer Networks Lab
Echo from server: Computer Networks Lab
Enter message: Testing Echo Communication
Echo from server: Testing Echo Communication
```

---

## Related
- **Server Implementation:** [Exp-02-TCP-Server](../Exp-02-TCP-Server/)
