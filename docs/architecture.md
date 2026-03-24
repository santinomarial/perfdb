# perfdb Architecture

## Status

This document is a living design spec updated as each component is implemented.

## Problem Statement

perfdb targets **OLTP** workloads: many short transactions, fine-grained reads and writes, and strict expectations for correctness and durability. Datasets are assumed **large relative to memory**, so most pages live on disk and only a bounded **working set** resides in the buffer pool; every design choice must account for I/O cost, eviction, and visibility of updates across threads.

Solving that problem end-to-end requires more than fast data structures in isolation. **Disk I/O** must be batched at page granularity and made crash-safe with a **write-ahead log**. **Caching** must avoid unbounded memory use while preserving consistency when pages are evicted or reloaded. **Indexing** must keep probe and scan paths efficient on disk. **Concurrency** must serialize conflicting operations without killing throughput. **Recovery** must reconstruct a legal database state after arbitrary failure points. The sections below map these needs to concrete components.

## Component Overview

**DiskManager** owns the database and log files, exposes page-grained read and write primitives (e.g. `pread` / `pwrite`), and is the only layer that touches the block device semantics perfdb relies on for durability alignment.

**BufferPool** pins pages in memory, tracks which frames hold which page IDs, and coordinates with the replacer so the number of resident pages stays within a fixed budget while satisfying correctness (dirty flags, single-copy invariant per page in memory).

**ClockReplacer** implements the eviction policy for buffer frames (e.g. clock hand over reference bits), approximating recency and frequency of use without unbounded metadata so eviction stays cheap under load.

**BPlusTree** provides the primary disk-backed ordered index: internal and leaf pages linked by pointers, search and range scan with **latch crabbing** or equivalent to bound hold times and avoid deadlock-prone global locking.

**LogManager** appends WAL records before dirty data is considered durable, manages log buffer flushing and sync points, and hands stable LSNs to the transaction and recovery layers.

**RecoveryManager** runs at startup (and optionally after detected corruption): reads the log, performs **analysis**, **redo** to repeat history, and **undo** to remove effects of transactions that did not commit—matching the chosen protocol (e.g. ARIES).

**LockManager** implements **two-phase locking** (or the documented variant): grants locks on resources (tables, indexes, tuples as designed), detects or prevents deadlock, and interacts with the transaction manager for commit and abort ordering.

**TransactionManager** assigns transaction identifiers, tracks read/write sets, coordinates commit and abort, schedules undo for rollbacks, and ensures commit points align with log and lock release rules.

**Executors** (insert, delete, update, lookup, scan) translate client operations into a sequence of index, heap, lock, and log calls with a consistent order so all layers agree on what "done" means for a statement.

## Data Flow (stubs)

### Read Path

Client → PointLookupExecutor → BPlusTree → BufferPool → DiskManager

### Write Path

Client → InsertExecutor → LogManager → TableHeap → BPlusTree → BufferPool → DiskManager

### Recovery Path

Startup → RecoveryManager → LogManager → Analysis → Redo → Undo → Ready

## Page Format (to be documented later)

## WAL Protocol (to be documented later)

## ARIES Recovery (to be documented later)

## Latch Crabbing (to be documented later)
