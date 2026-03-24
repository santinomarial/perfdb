# perfdb

## What is this?

perfdb is a disk-backed relational storage engine written in C++20. It is designed for OLTP-style workloads: high concurrency, low latency point lookups and range scans, and strict durability guarantees under memory constraints.

This is not a wrapper around an existing storage library. Every component is implemented from scratch: the buffer pool, B+ tree index, write-ahead log, crash recovery, and transaction layer.

## Why does this exist?

When a working set no longer fits in RAM, the engine must orchestrate **pages** on disk with a **buffer pool**: choosing what to keep in memory, when to evict, and how to honor consistency when many operations touch the same data. **Concurrent writers** add another layer of difficulty: without a disciplined locking or versioning scheme, schedules interleave in ways that break isolation and produce impossible reads. **Crash recovery** is equally subtle: a process can fail after persisting some intents but not others, so the system must be able to replay or roll back durable **log records** and reconcile in-memory and on-disk state—otherwise committed work is lost or torn pages appear committed.

## Architecture

```text
Client
  └── Query Executors (Insert / Delete / Update / Lookup / Scan)
        ├── B+ Tree Index  ──────────────────┐
        ├── Table Heap                        │
        ├── Lock Manager (2PL)                │
        └── Log Manager (WAL)           Buffer Pool Manager
                                             │
                                        Disk Manager
                                     (perfdb.db + perfdb.log)
```

- **Query executors** interpret client operations, acquire locks, and drive index and heap access in a consistent order.
- **B+ tree index** maps keys to record locations on disk-resident pages.
- **Table heap** stores tuple data in pages independent of the index structure.
- **Lock manager (2PL)** orders concurrent access so schedules remain serializable under the chosen policy.
- **Log manager (WAL)** records intended changes so they can be replayed after a crash.
- **Buffer pool manager** caches fixed-size pages, decides eviction, and issues reads and writes to the disk manager.
- **Disk manager** performs aligned page I/O against the database file and log file (`perfdb.db`, `perfdb.log`).

## Core Components

| Component           | Status      | Description                          |
|---------------------|-------------|--------------------------------------|
| Disk Manager        | 🔲 planned  | pread/pwrite page I/O                |
| Buffer Pool Manager | 🔲 planned  | Fixed-size page cache, Clock eviction |
| B+ Tree Index       | 🔲 planned  | Disk-backed, latch crabbing          |
| Write-Ahead Log     | 🔲 planned  | Durability, ARIES recovery           |
| Lock Manager        | 🔲 planned  | 2PL with deadlock detection          |
| Transaction Manager | 🔲 planned  | Begin/commit/abort with undo         |
| Query Executors     | 🔲 planned  | Insert/delete/update/lookup/scan     |

## Build

Requirements: CMake 3.20+, GCC 12+ or Clang 15+, Linux

```bash
git clone https://github.com/santinomarial/perfdb
cd perfdb
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

## Run Benchmarks

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/benchmarks/perfdb_bench
```

## Performance

Results will be posted here after the benchmarking milestone is complete.

## Design Decisions

Planned topics:

- Clock vs LRU-K for page eviction
- 2PL vs MVCC for concurrency control
- ARIES vs simpler recovery strategies
- B+ tree vs LSM-tree for the index structure

## Testing

The test suite covers:

- Unit tests for every component
- Concurrency tests with ThreadSanitizer
- Fault injection tests for crash recovery
- End-to-end integration tests
