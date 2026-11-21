# Experiment 9: Traffic Shaping Algorithms

## C Code — Part A: Leaky Bucket (`exp9_230.c`)

```c
#include <stdio.h>

int main() {
    int bucket_size, n, i, incoming, outgoing, stored = 0;

    printf("Leaky Bucket Algorithm Simulation\n");

    printf("Enter bucket size (capacity): ");
    scanf("%d", &bucket_size);

    printf("Enter outgoing rate: ");
    scanf("%d", &outgoing);

    printf("Enter number of packets (time units): ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nTime unit %d:\n", i + 1);

        printf("Enter number of incoming packets: ");
        scanf("%d", &incoming);

        if (incoming + stored > bucket_size) {
            printf("Bucket overflow! Packet loss: %d\n",
                   incoming + stored - bucket_size);
            stored = bucket_size;
        } else {
            stored += incoming;
        }

        if (stored <= outgoing) {
            printf("Packets sent: %d\n", stored);
            stored = 0;
        } else {
            printf("Packets sent: %d\n", outgoing);
            stored -= outgoing;
        }

        printf("Packets remaining in bucket: %d\n", stored);
    }

    while (stored > 0) {
        printf("\nHandling remaining packets...\n");

        if (stored <= outgoing) {
            printf("Packets sent: %d\n", stored);
            stored = 0;
        } else {
            printf("Packets sent: %d\n", outgoing);
            stored -= outgoing;
        }

        printf("Packets left in bucket: %d\n", stored);
    }

    printf("\nSimulation complete.\n");

    return 0;
}
```

---


```c
#include <stdio.h>

int main() {
    int bucket_size, n, rate, tokens = 0, incoming, i;

    printf("Token Bucket Algorithm Simulation\n");

    printf("Enter bucket size (capacity): ");
    scanf("%d", &bucket_size);

    printf("Enter token generation rate: ");
    scanf("%d", &rate);

    printf("Enter number of packets (time units): ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nTime unit %d:\n", i + 1);

        tokens += rate;

        if (tokens > bucket_size) {
            tokens = bucket_size;
        }

        printf("Enter number of packets to send: ");
        scanf("%d", &incoming);

        if (tokens >= incoming) {
            printf("Packets sent: %d\n", incoming);
            tokens -= incoming;
        } else {
            printf("Only %d tokens available, packets sent: %d, packets dropped: %d\n",
                   tokens, tokens, incoming - tokens);
            tokens = 0;
        }

        printf("Tokens left: %d\n", tokens);
    }

    printf("\nSimulation complete.\n");

    return 0;
}
```

---

## Objective
To simulate and analyze network traffic shaping and congestion control algorithms in C:
1. **Part A — Leaky Bucket Algorithm** ))

---

## Theory

Traffic shaping regulates the average rate and burstiness of packets admitted into a computer network to prevent buffer overflow and congestion.

### Comparison: Leaky Bucket vs. Token Bucket

| Parameter | Leaky Bucket | Token Bucket |
| :--- | :--- | :--- |
| **Output Rate** | Constant / Fixed rate strictly enforced | Allows bursty output up to bucket capacity |
| **Storage Unit** | Packets stored in queue | Tokens generated and stored |
| **Packet Loss** | Packets dropped if bucket overflows | Packets dropped/delayed if tokens are insufficient |
| **Burst Handling** | Smooths out bursts completely | Accommodates short traffic bursts |

---

## Part A: Leaky Bucket Algorithm

### Description
The bucket has a finite capacity (`bucket_size`). Incoming packets enter the bucket. If incoming packets exceed remaining capacity, the overflow packets are dropped. Regardless of the arrival rate, packets leak out at a constant `outgoing` rate. After the arrival sequence completes, remaining stored packets continue to drain until the bucket is empty.

### Compilation & Execution
```bash
gcc exp9_230.c -o exp9_230
./exp9_230
```

### Sample Input
```text
10
3
3
4
3
1
```
*(Bucket size = 10, Outgoing rate = 3, Time units = 3, Incoming packets = 4, 3, 1)*

### Sample Output
```text
Leaky Bucket Algorithm Simulation
Enter bucket size (capacity): 10
Enter outgoing rate: 3
Enter number of packets (time units): 3

Time unit 1:
Enter number of incoming packets: 4
Packets sent: 3
Packets remaining in bucket: 1

Time unit 2:
Enter number of incoming packets: 3
Packets sent: 3
Packets remaining in bucket: 1

Time unit 3:
Enter number of incoming packets: 1
Packets sent: 2
Packets remaining in bucket: 0

Simulation complete.
```

---

## Part B: Token Bucket Algorithm

### Description
Tokens are added to the bucket at a constant `rate` per time unit up to `bucket_size`. When packets arrive, each packet consumes one token. If sufficient tokens exist, all packets are transmitted immediately (allowing bursts). If tokens are insufficient, only packets with matching tokens are transmitted, and excess packets are dropped or delayed.

### Compilation & Execution
```bash
gcc exp9_2_230.c -o exp9_2_230
./exp9_2_230
```

### Sample Input
```text
10
4
3
3
3
9
```
*(Bucket size = 10, Token generation rate = 4, Time units = 3, Incoming packets = 3, 3, 9)*

### Sample Output
```text
Token Bucket Algorithm Simulation
Enter bucket size (capacity): 10
Enter token generation rate: 4
Enter number of packets (time units): 3

Time unit 1:
Enter number of packets to send: 3
Packets sent: 3
Tokens left: 1

Time unit 2:
Enter number of packets to send: 3
Packets sent: 3
Tokens left: 2

Time unit 3:
Enter number of packets to send: 9
Only 6 tokens available, packets sent: 6, packets dropped: 3
Tokens left: 0

Simulation complete.
```
