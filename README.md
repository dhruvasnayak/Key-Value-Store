# Distributed Key-Value Store - Phase 1

A simple in-memory key-value database accessible over TCP connection. Clients connect to the server and execute commands such as SET, GET, and DELETE.

## Features

- TCP server with single client connection handling
- In-memory key-value storage using hash table
- Text-based protocol with line-based commands
- O(1) average lookup, insertion, and deletion times
- Error handling and graceful client disconnect support

## Supported Commands

### SET Command
Store a key-value pair.

```
SET <key> <value>
```

**Response:** `OK` (on success) or `ERROR Invalid Command` (on invalid syntax)

**Example:**
```
SET name Dhruva
OK
```

### GET Command
Retrieve a value by key.

```
GET <key>
```

**Response:** 
- Value if key exists
- `NOT_FOUND` if key does not exist

**Example:**
```
GET name
Dhruva
```

### DELETE Command
Remove a key-value pair.

```
DELETE <key>
```

**Response:** 
- `DELETED` if key was removed
- `NOT_FOUND` if key does not exist

**Example:**
```
DELETE name
DELETED
```

### Error Responses

- `ERROR Invalid Command` - Malformed command syntax
- `ERROR Unknown Command` - Unsupported command

## Building

### Prerequisites
- CMake 3.10 or later
- C++17 compatible compiler (g++, clang++)
- Unix-like system (Linux, macOS)

### Build Steps

```bash
cd kv-store
mkdir build
cd build
cmake ..
make
```

The executable will be created as `kvserver`

## Running

### Start the Server

```bash
./kvserver 5000
```

Output:
```
Server started on port 5000
```

### Connect a Client

In another terminal, use `telnet` or `netcat`:

#### Using telnet:
```bash
telnet localhost 5000
```

#### Using netcat:
```bash
nc localhost 5000
```

### Example Session

```
SET name Dhruva
OK

GET name
Dhruva

SET city Mysore
OK

GET city
Mysore

DELETE name
DELETED

GET name
NOT_FOUND

HELLO
ERROR Unknown Command

DELETE xyz
NOT_FOUND
```

## Architecture

The project follows a modular design with the following components:

### TcpServer
- Manages socket creation, binding, and listening
- Accepts client connections
- Routes commands to the parser and executor

### Parser
- Converts raw text commands into Command objects
- Validates command syntax
- Supports SET, GET, DELETE, and error handling

### CommandExecutor
- Executes parsed commands
- Interacts with the storage engine
- Returns appropriate responses

### StorageEngine
- Manages in-memory key-value storage
- Uses `std::unordered_map<std::string, std::string>`
- Provides O(1) average access time

## Project Structure

```
kv-store/
├── src/
│   ├── main.cpp         # Entry point
│   ├── server.h/cpp     # TCP server implementation
│   ├── parser.h/cpp     # Command parser
│   ├── executor.h/cpp   # Command executor
│   ├── storage.h/cpp    # Storage engine
│   └── command.h/cpp    # Command data structure
├── tests/               # Test files (placeholder)
├── CMakeLists.txt       # Build configuration
└── README.md           # This file
```

## Non-Functional Requirements

### Performance
- O(1) average lookup time
- O(1) average insertion time
- O(1) average deletion time

### Reliability
- Graceful handling of invalid input
- Handles missing keys without crashing
- Manages unexpected client disconnects

### Capacity
- Supports at least 10,000 key-value pairs
- All keys stored entirely in memory

## Limitations (Phase 1)

The following features are intentionally excluded:
- Multithreading (single client at a time)
- Persistence to disk
- Replication
- Authentication and encryption
- Leader election and sharding
- Logging system
- Configuration files

These will be implemented in future phases.

## Testing

To test the key-value store:

1. Start the server: `./kvserver 5000`
2. Connect with `telnet localhost 5000` or `nc localhost 5000`
3. Execute commands as shown in the example session above
4. Test error cases (missing commands, invalid syntax, missing keys)

## License

This is a learning project for educational purposes.
# Key-Value-Store
