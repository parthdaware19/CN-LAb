# Experiment 7: DNS and HTTP Packet Analysis

## Objective
To capture, inspect, and analyze both **DNS (Domain Name System)** resolution and **HTTP (Hypertext Transfer Protocol)** request/response sessions using **Wireshark**.

---

## Theory

When a client web browser accesses an unencrypted URL such as `http://example.com`, two core protocol exchanges occur sequentially:
1. **DNS Resolution (UDP Port 53)**: The client resolves `example.com` into an IP address using recursive DNS queries.
2. **TCP 3-Way Handshake (Port 80)**: A connection is established between client and web server via `SYN -> SYN-ACK -> ACK`.
3. **HTTP Transaction (TCP Port 80)**:
   - **HTTP Request**: The client sends an `HTTP GET` request specifying resource paths and headers (`Host`, `User-Agent`, `Accept`).
   - **HTTP Response**: The server answers with an HTTP Status Code (`200 OK`) and returns payload data (`text/html`).
4. **TCP Connection Teardown**: Graceful teardown via `FIN-ACK`.

```
Client                                      DNS Server / Web Server
  │                                                    │
  │─── 1. DNS Query (A record for example.com) ───────►│ (UDP 53)
  │◄── 2. DNS Response (93.184.216.34) ────────────────│
  │                                                    │
  │─── 3. TCP SYN ────────────────────────────────────►│ (TCP 80)
  │◄── 4. TCP SYN-ACK ─────────────────────────────────│
  │─── 5. TCP ACK ────────────────────────────────────►│
  │                                                    │
  │─── 6. HTTP GET / HTTP/1.1 ────────────────────────►│
  │◄── 7. HTTP/1.1 200 OK (HTML Payload) ──────────────│
  │                                                    │
  │─── 8. TCP FIN-ACK ────────────────────────────────►│
  │◄── 9. TCP FIN-ACK ─────────────────────────────────│
```

---

## Commands & Step-by-Step Procedure

### 1. DNS Resolution Command
In Command Prompt / Terminal:
```cmd
nslookup www.google.com
```

### 2. HTTP Request Generation
Open a browser or terminal and navigate to plain HTTP:
```text
http://example.com
```
Or using `curl` in terminal:
```bash
curl -I http://example.com
```

---

## Wireshark Filters & Analysis

### Wireshark Display Filters

| Filter Purpose | Wireshark Display Filter |
| :--- | :--- |
| **Inspect DNS Only** | `dns` |
| **Inspect HTTP Only** | `http` |
| **Inspect Both Combined** | `dns || http` |
| **Inspect Specific Host** | `http.host == "example.com"` |
| **Inspect GET Requests** | `http.request.method == "GET"` |

---

## Key Packet Fields to Inspect

### Part A: DNS Query & Response
1. **DNS Query Packet:**
   - Transport: `User Datagram Protocol (UDP), Src Port: [Random], Dst Port: 53`
   - Transaction ID: Hex value (e.g., `0x1a2b`)
   - Query: `www.google.com: type A, class IN`
2. **DNS Response Packet:**
   - Same Transaction ID as Query
   - Flags: `Response: Message is a response`
   - Answers: List of resolved IPv4 addresses for `www.google.com`

### Part B: HTTP GET Request & 200 OK Response
1. **HTTP GET Request:**
   - Method: `GET`
   - Request URI: `/`
   - Request Version: `HTTP/1.1`
   - Host Header: `example.com`
   - User-Agent Header: Client browser identity
2. **HTTP 200 OK Response:**
   - Status Code: `200`
   - Response Phrase: `OK`
   - Content-Type: `text/html; charset=UTF-8`
   - Content-Length: Length of the response body
   - Line-based text data: Actual HTML payload

---

## Conclusion
By capturing both DNS and HTTP traffic, we observed the entire lifecycle of a web request: from name resolution over connectionless UDP port 53 to reliable HTTP delivery over a TCP port 80 stream.
