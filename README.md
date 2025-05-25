# FSSN_ZMQ_C

Implementing Various Communication Patterns with ZeroMQ

---

## OS

### Linux(Ubuntu)

Make sure that GCC is installed on your Ubuntu system.

install ZeroMQ library
```cmd
apt-get install libczmq-dev
```

Generate server and client executable files
```cmd
gcc -o {server filename} server.c -lzmq
gcc -o {client filename} client.c -lzmq
```
