# Experiment 1B: File Sharing Within an Organization Using IP Address

## Aim
To establish and verify peer-to-peer and client-server file sharing within a Local Area Network (LAN) using IP addressing and the Server Message Block (SMB/CIFS) protocol.

---

## Theory
In a local area network (LAN), computers communicate with one another using unique numeric identifiers called **IP (Internet Protocol)** addresses. File sharing within an enterprise or lab organization relies on the **Server Message Block (SMB)** / **Common Internet File System (CIFS)** protocol running over TCP/IP (port 445), which enables client applications to read, write, and execute files on a remote host server.

---

## Steps Executed in Theory & Practice

1. **Host Network Identification:**
   Retrieving the host machine's IP address and network adapter details.
   - Windows command: `ipconfig`
   - Ubuntu command: `ip addr show` or `hostname -I`

2. **Network Connectivity Verification:**
   Verifying ICMP reachability and measuring round-trip network latency between workstations:
   - Target Host: `10.17.106.178`
   - Command: `ping 10.17.106.178` (expect 0% packet loss).

3. **Directory Sharing Configuration:**
   - Designating a target shared folder (e.g., `sit doc` or `shared_lab`).
   - Assigning Read and Write permissions for authorized users.

4. **Remote Access via Universal Naming Convention (UNC) or Mount Point:**
   - Windows UNC: `\\10.17.106.178\sit doc`
   - Linux SMB Client / CIFS Mount: `smb://10.17.106.178/sit doc` or `mount -t cifs`

---

## Observation & Output
```text
Pinging 10.17.106.178 with 32 bytes of data:
Reply from 10.17.106.178: bytes=32 time<1ms TTL=128
Reply from 10.17.106.178: bytes=32 time<1ms TTL=128
Reply from 10.17.106.178: bytes=32 time<1ms TTL=128
Reply from 10.17.106.178: bytes=32 time<1ms TTL=128

Ping statistics for 10.17.106.178:
    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss)
Approximate round trip times in milli-seconds:
    Minimum = 0ms, Maximum = 0ms, Average = 0ms
```

---

## Conclusion
The network interface configurations were successfully retrieved, and IP connectivity was verified using the ICMP ping utility with a 0% packet loss rate. Cross-workstation file sharing was established and verified using the host IP address (`10.17.106.178`).

---

## How to Execute in Ubuntu Terminal

### 1. Host Network Identification
Check your IP address and network adapter details:
```bash
hostname -I
```
Or for detailed network interface details:
```bash
ip -4 addr show
```

### 2. Verify Connectivity (ICMP Ping)
Verify network reachability and measure round-trip latency to the target machine:
```bash
ping -c 4 10.17.106.178
```

### 3. Setting Up Samba Share (Host Machine)
To share a directory, create/edit the Samba configuration:
```bash
sudo gedit /etc/samba/smb.conf
```
Add the following configuration at the end:
```ini
[sit_doc]
   path = /home/user/sit_doc
   browseable = yes
   read only = no
   guest ok = yes
   create mask = 0777
   directory mask = 0777
```
Restart the Samba service:
```bash
sudo systemctl restart smbd
```

### 4. Accessing Shared Folder from Client Machine
List available shares on the remote host:
```bash
smbclient -L //10.17.106.178 -U guest -N
```
Mount the shared directory:
```bash
sudo mkdir -p /mnt/network_share
sudo mount -t cifs //10.17.106.178/sit_doc /mnt/network_share -o guest,uid=$(id -u),gid=$(id -g)

# Verify shared files
ls -la /mnt/network_share
```
To unmount when finished:
```bash
sudo umount /mnt/network_share
```
