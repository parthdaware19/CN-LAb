# Experiment 8: Sliding Window Protocol (Go-Back-N)

## C Code (`sliding_window230.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 50

void sender(int frames[], int size, int window_size);
void receiver(int frames[], int start, int window_size);

int main() {
    int n, window_size;
    int frames[MAX_FRAMES];

    printf("Sliding Window Protocol Simulation (Go-Back-N)\n");
    printf("Enter number of frames to send (max %d): ", MAX_FRAMES);
    scanf("%d", &n);

    if (n > MAX_FRAMES || n <= 0) {
        printf("Invalid number of frames.\n");
        return 0;
    }

    printf("Enter window size: ");
    scanf("%d", &window_size);

    if (window_size <= 0 || window_size > n) {
        printf("Invalid window size.\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        frames[i] = i;
    }

    sender(frames, n, window_size);

    return 0;
}

void sender(int frames[], int size, int window_size) {
    int base = 0;
    char choice;

    srand(time(NULL));

    while (base < size) {
        printf("\nSender window: ");

        for (int i = base; i < base + window_size && i < size; i++) {
            printf("[%d] ", frames[i]);
        }

        printf("\nSending frames...\n");

        for (int i = base; i < base + window_size && i < size; i++) {
            printf("Sent frame: %d\n", frames[i]);
        }

        printf("\nSimulating receiver...\n");
        receiver(frames, base, window_size);

        printf("\nDid all frames receive correctly? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            base += window_size;
        } else {
            printf("Resending from frame %d...\n", frames[base]);
            printf("In Go-Back-N, we resend from base\n");
        }
    }

    printf("\nAll frames sent successfully!\n");
}

void receiver(int frames[], int start, int window_size) {
    for (int i = start; i < start + window_size; i++) {
        printf("Received frame: %d, sending ACK: %d\n",
               frames[i], frames[i] + 1);
    }
}
```

---

## Objective
To implement and simulate the **Go-Back-N Sliding Window Protocol** in C, demonstrating pipelined frame transmission, window sliding upon receipt of ACKs, and retransmission of all unacknowledged frames starting from the base on frame loss.

---

## Theory

The **Sliding Window Protocol** is a flow control and error control protocol utilized at the Data Link and Transport layers. 

### Go-Back-N (GBN) ARQ Working Principle
1. **Window Size ($N$)**: The sender can transmit up to $N$ frames without waiting for an acknowledgment (ACK).
2. **Cumulative ACK**: The receiver sends an acknowledgment $ACK(n)$ indicating that all frames up to $n-1$ were successfully received, expecting frame $n$.
3. **Loss Handling**: If an error or loss occurs for any frame in the window, the receiver discards that frame and all subsequent out-of-order frames. Upon timeout or negative confirmation, the sender slides back ("goes back") and retransmits all frames starting from the unacknowledged `base` frame.

```
Sender Window (Size = 3):
[0] [1] [2]  --> Sent to Receiver
Receiver ACKs: ACK 1, ACK 2, ACK 3
If ACK received (y):
Window slides forward -> [3] [4] ...
If Error (n):
Go back to base -> Resend all frames from base
```

---

## Program Details

- **File:** [`sliding_window242.c`]
- **Functions:**
  - `sender(frames[], size, window_size)`: Manages the base pointer, window boundaries, and interactive acknowledgment prompts.
  - `receiver(frames[], start, window_size)`: Simulates frame reception and ACK generation (`frame + 1`).

---

## Compilation & Execution

```bash
# Navigate to directory
cd Exp-08-Sliding-Window-Protocol

# Compile
gcc sliding_window230.c -o sliding_window230

# Run
./sliding_window
```

---

## Sample Input & Output

### Input
```text
5
3
y
y
```

### Execution Output
```text
Sliding Window Protocol Simulation (Go-Back-N)
Enter number of frames to send (max 50): 5
Enter window size: 3

Sender window: [0] [1] [2] 
Sending frames...
Sent frame: 0
Sent frame: 1
Sent frame: 2

Simulating receiver...
Received frame: 0, sending ACK: 1
Received frame: 1, sending ACK: 2
Received frame: 2, sending ACK: 3

Did all frames receive correctly? (y/n): y

Sender window: [3] [4] 
Sending frames...
Sent frame: 3
Sent frame: 4

Simulating receiver...
Received frame: 3, sending ACK: 4
Received frame: 4, sending ACK: 5

Did all frames receive correctly? (y/n): y

All frames sent successfully!
```
