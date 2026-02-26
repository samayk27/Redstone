# Redstone

A fast, lightweight in-memory key-value store built from scratch in C.

## What is Redstone?

Redstone is a Redis-inspired in-memory key-value store implemented from scratch in C. It covers the core internals of how a production-grade in-memory database works -including the RESP protocol, a non-blocking event loop via epoll, and fundamental data structures.

Built to go beyond theoretical knowledge — if you can build it, you understand it.

## Features

- TCP server with non-blocking I/O
- RESP protocol implementation
- Core commands — `GET`, `SET`, `DEL`, `EXPIRE`
- Event loop with `epoll`
- In-memory hashmap storage

## Why?

Most developers use Redis without understanding how it works under the hood. Redstone is an attempt to understand exactly that - how a high performance, networked, in-memory data store is built at a low level.

## Getting Started

### Prerequisites

- GCC or Clang
- Linux (epoll is Linux-specific)
- Make

### Build

```bash
git clone https://github.com/yourusername/redstone.git
cd redstone
make
```

### Run

```bash
./redstone
```

By default, Redstone listens on port `6379`.

### Connect

You can connect using the standard Redis CLI:

```bash
redis-cli ping
redis-cli set foo bar
redis-cli get foo
```

## Project Structure

```
redstone/
├── src/
│   ├── main.c          # Entry point
│   ├── server.c        # TCP server and event loop
│   ├── protocol.c      # RESP protocol parsing
│   ├── commands.c      # Command handlers
│   ├── hashmap.c       # Core data structure
│   └── util.c          # Helpers
├── include/
│   └── *.h
├── Makefile
└── README.md
```

## Roadmap

- [] TCP server with non-blocking I/O
- [] RESP protocol
- [] GET, SET, DEL, EXPIRE
- [ ] Persistence (RDB/AOF style)
- [ ] Pub/Sub
- [ ] More data structures — lists, sorted sets, sets
- [ ] TTL with background expiry
- [ ] Rust rewrite

## What I Learned

- How event loops and `epoll` work for handling concurrent connections
- How the RESP protocol encodes and decodes commands
- How to implement a hashmap from scratch in C
- How in-memory databases manage and expire keys
- Low level network programming in C

## License

MIT
