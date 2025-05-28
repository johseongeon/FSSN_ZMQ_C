# FSSN_ZMQ_C

FullStack Service Networking 2023-1 term-project

Implementing Various Communication Patterns with ZeroMQ

Official ZeroMQ Documentation https://zguide.zeromq.org/docs/chapter2/

---

## OS

### Linux(Ubuntu)

Make sure that GCC is installed on your Ubuntu system.

install ZeroMQ library
```cmd
apt-get install libczmq-dev
```

How to generate server and client executable files
```cmd
gcc -o {server filename} server.c -lzmq
gcc -o {client filename} client.c -lzmq
```
---
## test in cli

start server first
```cmd
./{server filename} [arguments]
```

run client cli and test
```cmd
./{client filename} [arguments]
```

Arguments serve as the username in the client and as the number of threads in the server.

for example) In Dealer-Router Pattern. The server runs 4 threads, and the client's username is A.

```cmd
cd ZMQ_DEALER_ROUTER
gcc -o server dealer_router_server.c -lzmq
gcc -o client dealer_router_client.c -lzmq
```

run with arguments
```cmd
./server 4
```
```cmd
./client A
```
