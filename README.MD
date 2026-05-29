# Redstone

A Redis-inspired in-memory key-value store built from scratch in C — a learning project.

## What is Redstone?

Redstone is built to understand how Redis works under the hood: TCP networking, the RESP protocol, command dispatch, and an in-memory hashmap — all implemented from scratch in C.

Built to go beyond theoretical knowledge — if you can build it, you understand it.

## Why?

Most developers use Redis without understanding how it works. Redstone is an attempt to fix that by building it from the ground up at a low level.

## Getting Started

### Prerequisites

- GCC
- Linux
- Make

### Build

```bash
make
```

Produces two binaries:
- `./redstone` — the server
- `./redstone-client` — a minimal test client

### Run

```bash
./redstone
```

Redstone listens on port `6379`.

### Connect

```bash
redis-cli ping
redis-cli set foo bar
redis-cli get foo
```

## Project Structure

```
redstone/
├── src/
│   ├── server.c        # TCP accept loop, per-client request handling
│   ├── protocol.c      # RESP protocol parser and serializer
│   ├── commands.c      # Command dispatch and handlers (PING, SET, GET, ...)
│   ├── store.c         # In-memory key-value store (hashmap)
│   └── client.c        # Test client (development only)
├── include/
│   ├── methods.h       # Shared socket helpers (read_full, write_all, ...)
│   ├── protocol.h      # RESP types and function declarations
│   ├── commands.h      # Command handler declarations
│   └── store.h         # Store API declarations
├── Makefile
└── README.md
```

## Milestones

### Milestone 1 — redis-cli compatible PING / SET / GET
- [X] TCP server skeleton on port 6379
- [X] Module structure (protocol, commands, store)
- [X] RESP protocol parser and serializer
- [X] Command dispatch (PING, SET, GET)
- [X] In-memory string key-value store

### Milestone 2 — More commands + TTL
- [ ] DEL, EXISTS
- [ ] EXPIRE / TTL (passive expiry on access)
- [ ] Active expiry background sweep

### Milestone 3 — Non-blocking I/O
- [ ] Non-blocking sockets
- [ ] `epoll`-based event loop (multiple concurrent clients)

### Beyond
- [ ] Persistence (RDB/AOF style)
- [ ] Pub/Sub
- [ ] More value types — lists, sorted sets, sets

## License

MIT
