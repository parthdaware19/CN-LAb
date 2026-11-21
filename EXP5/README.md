# Experiment 5: UDP Client

## C Code (`client_udp_230.c`)

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    char message[100], buffer[100];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        printf("Socket creation failed\n");
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    sendto(sockfd, message, strlen(message), 0,
           (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    addr_size = sizeof(serverAddr);
    int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr *)&serverAddr, &addr_size);

    buffer[n] = '\0';
    printf("Server Response: %s\n", buffer);

    close(sockfd);
    return 0;
}
```

---

## Objective
To implement a connectionless **UDP Client** in C using Berkeley sockets that:
1. Creates a UDP datagram socket (`SOCK_DGRAM`).
2. Configures the destination server address on `127.0.0.1:8080`.
3. Prompts the user to enter a message via `fgets()`.
4. Transmits the datagram directly to the server using `sendto()`.
5. Receives the server's reply via `recvfrom()` and displays it on the console.

---

## Theory

UDP does not establish a connection before data transmission. The client addresses the datagram directly to the destination IP and port with `sendto()` and waits for the incoming response using `recvfrom()`.

### Socket Lifecycle (UDP Client)
```
       socket(SOCK_DGRAM)
             │
             ▼
         sendto()   ──► (Sends message datagram to server)
             │
        recvfrom()  ◄── (Awaits server reply datagram)
             │
             ▼
          close()
```

---

## Compilation & Execution

### Prerequisites
- GCC Compiler (Linux / WSL / macOS)
- The UDP Server ([Exp-04-UDP-Server](../Exp-04-UDP-Server/)) must be running first.

### Steps
1. Navigate to this directory:
   ```bash
   cd Exp-05-UDP-Client
   ```

2. Compile the client program:
   ```bash
   gcc client_udp_230.c -o client
   ```

3. Run the UDP Client:
   ```bash
   ./client
   ```

---

## Sample Input & Output

```text
Enter message: hello
Server Response: Hello from UDP Server
```

---

## Related
- **Server Implementation:** [Exp-04-UDP-Server](../Exp-04-UDP-Server/)
