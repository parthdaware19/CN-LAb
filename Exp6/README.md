# Experiment 6: DNS Packet Analysis (Windows)

## Objective
To capture, inspect, and analyze **Domain Name System (DNS)** queries and responses using `nslookup` and **Wireshark** on Windows.

---

## Theory

**DNS (Domain Name System)** is an application layer protocol operating primarily over **UDP port 53** (and TCP port 53 for zone transfers or large payloads > 512 bytes). It translates human-friendly domain names (e.g., `www.example.com`) into machine-routable IP addresses (e.g., `93.184.216.34`).

### DNS Message Structure
A DNS message consists of:
1. **Header**: 12 bytes containing Identification ID, Flags (QR, Opcode, AA, TC, RD, RA, RCODE), Question Count, Answer Count, Authority Count, and Additional Count.
2. **Question Section**: Domain name being queried and query type (`A`, `MX`, `PTR`, etc.).
3. **Answer Section**: Resource Records (RRs) satisfying the query.
4. **Authority Section**: RRs pointing to authoritative name servers.
5. **Additional Section**: Helpful RRs (e.g., IP addresses of authoritative servers).

```
+---------------------------------------------------+
|                  Identification (16 bits)         |
+---------------------------------------------------+
| QR | Opcode | AA | TC | RD | RA | Z | RCODE (16 bits)|
+---------------------------------------------------+
|             Total Questions (16 bits)             |
+---------------------------------------------------+
|              Total Answers (16 bits)              |
+---------------------------------------------------+
|             Authority Records (16 bits)           |
+---------------------------------------------------+
|            Additional Records (16 bits)           |
+---------------------------------------------------+
```

---

## Commands & Procedures

Open **Windows Command Prompt** (`cmd`) or **PowerShell**:

### 1. Standard Forward DNS Lookup (`A` Record)
Resolves a domain name to its IPv4 address:
```cmd
nslookup www.example.com
```

**Sample Output:**
```text
Server:  dns.google
Address:  8.8.8.8

Non-authoritative answer:
Name:    www.example.com
Addresses:  2606:2800:21f:cb07:6820:80da:af6b:8b2c
          93.184.216.34
```

---

### 2. Reverse DNS Lookup (`PTR` Record)
Resolves an IPv4 address to its associated hostname via in-addr.arpa:
```cmd
nslookup 93.184.216.34
```

**Sample Output:**
```text
Server:  dns.google
Address:  8.8.8.8

Name:    93.184.216.34
Address:  93.184.216.34
```

---

### 3. Mail Exchange (`MX` Record) Lookup
Queries the mail servers responsible for accepting incoming email for a domain:
```cmd
nslookup -query=MX example.com
```

**Sample Output:**
```text
Server:  dns.google
Address:  8.8.8.8

Non-authoritative answer:
example.com     MX preference = 0, mail exchanger = .
```

---

## Wireshark Capture Instructions

1. **Launch Wireshark** and select your active network interface (e.g., *Wi-Fi* or *Ethernet*).
2. **Apply Display Filter**:
   ```wireshark
   dns
   ```
3. **Start Packet Capture** (click the blue shark fin icon).
4. Run the commands above in Command Prompt.
5. **Stop Packet Capture** (red square icon).

---

## Key Packet Fields to Inspect in Wireshark

| Field | Description | Where to Find |
| :--- | :--- | :--- |
| **Transaction ID** | Matches query packet to response packet | `Domain Name System -> Transaction ID` |
| **Flags: QR** | `0` = Standard query, `1` = Response | `Domain Name System -> Flags -> Response: 0/1` |
| **Flags: RD** | Recursion Desired (client asks resolver to resolve fully) | `Domain Name System -> Flags -> Recursion desired: 1` |
| **Flags: RCODE** | Return Code (`0` = No Error, `3` = NXDOMAIN) | `Domain Name System -> Flags -> Reply code` |
| **Queries** | Domain requested, Type (`A`, `MX`, `PTR`), Class (`IN`) | `Domain Name System -> Queries` |
| **Answers** | Resolved IP address(es) and Time-to-Live (TTL) | `Domain Name System -> Answers` |

---

## Conclusion
Through Wireshark packet capture, we observed the complete request-response cycle of DNS over UDP port 53, verified how the 16-bit Transaction ID pairs queries with responses, and analyzed forward (`A`), reverse (`PTR`), and mail exchange (`MX`) records.
