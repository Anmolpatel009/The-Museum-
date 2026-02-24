# Distributed Systems Basics

## What is a Distributed System?

A distributed system is a collection of independent computers that appear to users as a single coherent system. Components located on networked computers communicate and coordinate their actions by passing messages.

```
┌─────────────────────────────────────────────────────────────┐
│              Distributed System Overview                     │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│     ┌──────────┐    ┌──────────┐    ┌──────────┐         │
│     │  Node 1  │    │  Node 2  │    │  Node 3  │         │
│     │          │    │          │    │          │         │
│     │  Server  │◄──►│  Server  │◄──►│  Server  │         │
│     │          │    │          │    │          │         │
│     └──────────┘    └──────────┘    └──────────┘         │
│           │                                    │           │
│           └──────────────┬─────────────────────┘           │
│                          │                                  │
│                          ▼                                  │
│                   ┌──────────┐                             │
│                   │  Client  │                             │
│                   │  (User)  │                             │
│                   └──────────┘                             │
│                                                             │
│  All nodes work together to provide a service              │
└─────────────────────────────────────────────────────────────┘
```

## Why Distributed Systems?

### Benefits
```
┌─────────────────────────────────────────────────────────────┐
│                    Benefits                                  │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. SCALABILITY                                             │
│     - Add more nodes to handle more load                   │
│     - Scale horizontally                                    │
│                                                             │
│  2. RELIABILITY / FAULT TOLERANCE                          │
│     - No single point of failure                           │
│     - Continue when some nodes fail                        │
│                                                             │
│  3. PERFORMANCE                                            │
│     - Parallel processing                                  │
│     - Geographic distribution for latency                  │
│                                                             │
│  4. COST EFFICIENCY                                        │
│     - Use commodity hardware                               │
│     - Pay as you grow                                      │
│                                                             │
│  5. AVAILABILITY                                           │
│     - 24/7 service availability                           │
│     - Redundancy                                           │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Challenges
```
┌─────────────────────────────────────────────────────────────┐
│                   Challenges                                 │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. NETWORK ISSUES                                          │
│     - Latency                                              │
│     - Partial failures                                     │
│     - Network partitions                                   │
│                                                             │
│  2. COMPLEXITY                                             │
│     - Distributed transactions                             │
│     - Concurrency control                                   │
│     - Consistency issues                                    │
│                                                             │
│  3. OBSERVABILITY                                           │
│     - Debugging across machines                            │
│     - Distributed tracing                                   │
│     - Logging aggregation                                   │
│                                                             │
│  4. SECURITY                                               │
│     - Authentication across services                        │
│     - Data encryption in transit                           │
│     - Access control                                       │
│                                                             │
│  5. DATA CONSISTENCY                                        │
│     - Maintaining consistency across nodes                │
│     - CAP theorem trade-offs                               │
│     - Conflict resolution                                   │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Key Concepts

### 1. Distributed Communication
```
Synchronous Communication:
─────────────────────────────────────────────────────────────
Client ──► Request ──► Server
         ◄── Response ◄──

- HTTP/REST calls
- gRPC
- Wait for response before continuing


Asynchronous Communication:
─────────────────────────────────────────────────────────────
Client ──► Message ──► Queue ──► Server
         ◄── Ack ◄────

- Message queues (Kafka, RabbitMQ)
- Event-driven architecture
- Fire and forget
```

### 2. Service Discovery
```
┌─────────────────────────────────────────────────────────────┐
│              Service Discovery                               │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Service A wants to call Service B:                        │
│                                                             │
│  1. Service A queries Service Registry                     │
│     /service-b/instances                                   │
│                                                             │
│  2. Registry returns available instances:                  │
│     [{"host": "10.0.0.1", "port": 8080},                   │
│      {"host": "10.0.0.2", "port": 8080}]                   │
│                                                             │
│  3. Service A chooses one (load balancing)                 │
│     and makes the call                                     │
│                                                             │
│  Popular tools: Consul, Eureka, etcd, ZooKeeper           │
└─────────────────────────────────────────────────────────────┘
```

### 3. Fault Tolerance
```
┌─────────────────────────────────────────────────────────────┐
│              Fault Tolerance Patterns                        │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. RETRIES                                                 │
│     - Exponential backoff                                   │
│     - Jitter (random delay)                                │
│     - Max retry attempts                                   │
│                                                             │
│  2. CIRCUIT BREAKER                                         │
│     - Track failures                                       │
│     - Open circuit after threshold                        │
│     - Fallback response                                    │
│                                                             │
│  3. HEALTH CHECKS                                           │
│     - Monitor service health                               │
│     - Remove unhealthy instances                           │
│     - Re-add when healthy                                  │
│                                                             │
│  4. LOAD SHEDDING                                           │
│     - Reject non-critical requests                        │
│     - Prioritize essential traffic                        │
│                                                             │
│  5. REDUNDANCY                                              │
│     - Multiple copies of data                              │
│     - Multiple service instances                          │
│     - Multi-region deployment                              │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### 4. Consensus in Distributed Systems
```
The Consensus Problem:
─────────────────────────────────────────────────────────────
All nodes must agree on a single value
even if some nodes fail

Example: Which node should be master?

Node A: Vote for A    ──┐
Node B: Vote for A    ──┼──► Consensus: A is master
Node C: Vote for A    ──┘
```

### 5. Two-Phase Commit (2PC)
```
Phase 1: Prepare
─────────────────────────────────────────────────────────────
Coordinator ──► Prepare ──► All Nodes
                    │
                    ▼
              All Nodes say "YES"

Phase 2: Commit
─────────────────────────────────────────────────────────────
Coordinator ──► Commit ──► All Nodes
                    │
                    ▼
              All Nodes Commit
```

## Distributed Data Management

### Sharding (Horizontal Partitioning)
```
┌─────────────────────────────────────────────────────────────┐
│              Data Sharding                                   │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Shard Key: user_id                                        │
│                                                             │
│  Users 1-1000      ──► Shard 1                            │
│  Users 1001-2000   ──► Shard 2                            │
│  Users 2001-3000   ──► Shard 3                            │
│                                                             │
│  Benefits:                                                  │
│  - Distribute load across nodes                           │
│  - Scale write throughput                                 │
│                                                             │
│  Challenges:                                                │
│  - Cross-shard queries                                    │
│  - Rebalancing                                            │
│  - Choosing good shard key                                │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Replication
```
┌─────────────────────────────────────────────────────────────┐
│              Data Replication                                │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Master-Slave:                                              │
│  ┌───────┐    ┌───────┐    ┌───────┐                     │
│  │Master │───►│Slave  │───►│Slave  │                     │
│  │(Write)│    │(Read) │    │(Read) │                     │
│  └───────┘    └───────┘    └───────┘                     │
│       │                                                   │
│       └─────────── Async / Sync                           │
│                                                             │
│  Multi-Master:                                              │
│  ┌───────┐    ┌───────┐                                  │
│  │Master │◄──►│Master │                                  │
│  │       │    │       │                                  │
│  └───────┘    └───────┘                                  │
│                                                             │
│  Conflict resolution needed                                │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Distributed Transactions

### Saga Pattern
```
┌─────────────────────────────────────────────────────────────┐
│              Saga Pattern                                    │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Orchestrated Saga:                                         │
│                                                             │
│  Order Service                                              │
│      │                                                      │
│      ├──► Payment Service (compensate: refund)              │
│      │                                                      │
│      ├──► Inventory Service (compensate: release)          │
│      │                                                      │
│      └──► Shipping Service (compensate: cancel)            │
│                                                             │
│  Each step has a compensating transaction                  │
│  If any step fails, execute compensations in reverse       │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Common Distributed System Patterns

### 1. Leader-Follower
```
┌─────────────────────────────────────────────────────────────┐
│              Leader-Follower Pattern                          │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│      ┌──────────────┐                                      │
│      │   Leader     │                                      │
│      │  (Primary)   │                                      │
│      │   Handles    │                                      │
│      │    Writes    │                                      │
│      └──────┬───────┘                                      │
│             │                                               │
│             │ (Replicate)                                   │
│      ┌──────┼───────┐                                      │
│      │             │                                       │
│      ▼             ▼                                       │
│  ┌───────┐   ┌───────┐   ┌───────┐                        │
│  │Follow │   │Follow │   │Follow │                        │
│  │ ers   │   │ ers   │   │ ers   │                        │
│  │(Read) │   │(Read) │   │(Read) │                        │
│  └───────┘   └───────┘   └───────┘                        │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### 2. Sharded Database
```
┌─────────────────────────────────────────────────────────────┐
│              Sharded Database Pattern                        │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│         ┌──────────────────┐                              │
│         │   Application     │                              │
│         │   (Router)        │                              │
│         └────────┬─────────┘                              │
│                  │                                          │
│    ┌─────────────┼─────────────┐                          │
│    │             │             │                           │
│    ▼             ▼             ▼                           │
│ ┌──────┐   ┌──────────┐   ┌────────┐                      │
│ │Shard │   │  Shard   │   │ Shard  │                      │
│ │  1   │   │    2     │   │   3    │                      │
│ │ (A-F)│   │  (G-M)   │   │ (N-Z)  │                      │
│ └──────┘   └──────────┘   └────────┘                      │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### 3. Event Sourcing
```
┌─────────────────────────────────────────────────────────────┐
│              Event Sourcing                                  │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Instead of storing current state:                         │
│  Store all state changes as events                          │
│                                                             │
│  Traditional:                                               │
│  Account: balance = $100                                    │
│                                                             │
│  Event Sourcing:                                            │
│  Events:                                                    │
│  - AccountCreated                                          │
│  - Deposit($50)                                            │
│  - Withdraw($20)                                           │
│  - Deposit($70)                                           │
│                                                             │
│  Current State: $50 + $20 + $70 = $100                    │
│                                                             │
│  Benefits:                                                  │
│  - Complete audit trail                                    │
│  - Time travel (replay events)                             │
│  - Event-driven architecture                               │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Real-World Distributed Systems

### Examples
```
┌─────────────────────────────────────────────────────────────┐
│              Real-World Examples                             │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Google:                                                    │
│  - GFS (file system)                                       │
│  - MapReduce (computation)                                 │
│  - BigTable (database)                                     │
│  - Chubby (locking)                                        │
│                                                             │
│  Amazon:                                                   │
│  - Dynamo (key-value store)                                │
│  - S3 (storage)                                            │
│  - Cassandra (database)                                     │
│                                                             │
│  LinkedIn:                                                 │
│  - Kafka (messaging)                                       │
│  - Voldemort (key-value store)                             │
│  - Espresso (database)                                      │
│                                                             │
│  Netflix:                                                  │
│  - Eureka (service discovery)                             │
│  - Zuul (routing)                                          │
│  - Hystrix (circuit breaker)                               │
│  - Atlas (monitoring)                                      │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Interview Tips

1. **Understand CAP theorem** - Consistency, Availability, Partition tolerance
2. **Know distributed transaction patterns** - 2PC, Saga
3. **Be ready for fault tolerance** - Retries, circuit breakers
4. **Understand replication** - Sync vs async, master-slave vs multi-master
5. **Know about consensus** - Raft, Paxos basics
6. **Be ready for trade-off questions** - Consistency vs performance

## Summary

Distributed systems enable:
- **Horizontal scaling** across many machines
- **High availability** through redundancy
- **Geographic distribution** for latency
- **Fault tolerance** through replication

But they require:
- **Careful design** for consistency
- **Observability** for debugging
- **Robustness** to handle failures
- **Complex tooling** for management

Key principles:
- **Design for failure** - Assume components will fail
- **Simplicity** - Don't distribute unnecessarily
- **Trade-offs** - No perfect distributed system
- **Patterns** - Use proven solutions
