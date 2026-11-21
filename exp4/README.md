# Experiment 4: UDP Server

## C Code (`server_udp1230.c`)

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main()
{
    int server_socket;
    char buffer[1024];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0)
    {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        return 1;
    }

    printf("UDP Server is running on port %d...\n", PORT);

    int n = recvfrom(server_socket, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr *)&client_addr, &client_len);

    if (n < 0)
    {
        perror("Receive failed");
        close(server_socket);
        return 1;
    }

    buffer[n] = '\0';
    printf("Message from Client: %s\n", buffer);

    char *response = "Hello from UDP Server";
    sendto(server_socket, response, strlen(response), 0,
           (struct sockaddr *)&client_addr, client_len);

    close(server_socket);
    return 0;
}
```

---

## Objective
To implement a connectionless **UDP Server** in C using Berkeley sockets that:
1. Creates a UDP datagram socket (`SOCK_DGRAM`) and binds it to port `8080`.
2. Awaits incoming datagrams from clients without establishing a handshake connection.
3. Receives a client string message using `recvfrom()`.
4. Displays the client message on the server console.
5. Sends back the acknowledgment response `"Hello from UDP Server"` using `sendto()`.

---

## Theory

**User Datagram Protocol (UDP)** is a connectionless, unreliable transport layer protocol that provides low latency and minimal overhead by avoiding handshakes and state maintenance.

### Socket Lifecycle (UDP Server)
```
       socket(SOCK_DGRAM)
             │
             ▼
           bind()
             │
             ▼
        recvfrom()  ◄── (Waits for incoming datagram from client)
             │
         sendto()   ──► (Sends response string back to client)
             │
             ▼
          close()
```

---

## Compilation & Execution

### Prerequisites
- GCC Compiler (Linux / WSL / macOS)

### Steps
1. Navigate to this directory:
   ```bash
   cd Exp-04-UDP-Server
   ```

2. Compile the server program:
   ```bash
   gcc server_udp230.c -o server
   ```

3. Run the UDP Server:
   ```bash
   ./server
   ```

> [!NOTE]
> Run Experiment 4 (server) first, then Experiment 5 (client). The server handles one message and exits.

---

## Sample Output

```text
UDP Server is running on port 8080...
Message from Client: hello
```

---

## Related
- **Client Implementation:** [Exp-05-UDP-Client](../Exp-05-UDP-Client/)
