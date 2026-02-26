## Redstone
A fast, lightweight in-memory key-value store built from scratch in C, inspired by Redis internals.

What is Redstone?
Redstone is a Redis-inspired in-memory key-value store built from scratch in C. It implements core Redis functionality including the RESP protocol, a non-blocking event loop via epoll, and fundamental data structures.

Features
TCP server with non-blocking I/O
RESP protocol implementation
Core commands — GET, SET, DEL, EXPIRE
Event loop with epoll
In-memory hashmap storage
Why?
Built to deeply understand the internals of high performance in-memory databases and how networked systems work at a low level.

Building

bash
make
./redstone
Roadmap
 Persistence (RDB/AOF style)
 Pub/Sub
 More data structures (lists, sorted sets)
 Rust rewrite eventually
