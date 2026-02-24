# CAP Theorem

## What is CAP Theorem?

CAP Theorem states that a distributed database system can only provide two out of three guarantees simultaneously:

1. **Consistency** - All nodes see the same data at the same time
2. **Availability** - Every request gets a response (without guarantee of most recent data)
3. **Partition Tolerance** - System continues to operate despite network failures

```
                    ┌────────────────────────────── │         CAP THE┐
                   OREM           │
                    │                              │
                    │         CONSISTENCY          │
                    │             ▲               │
                    │            ╱│╲              │
                    │           ╱ │ ╲             │
                    │          ╱  │  ╲            │
                    │         ╱   │   ╲           │
                    │        ╱    │    ╲          │
                    │       ╱     │     ╲         │
                    │      ╱      │      ╲        │
                    │     ╱       │       ╲       │
                    │    ╱        │        ╲      │
                    │   ▼─────────┴─────────▼     │
                    │  AVAILABILITY    PARTITION  │
                    │                       TOLERANCE
                    │                              │
                    │   Pick any TWO               │
                    └──────────────────────────────┘
```

## Why Only Two?

When there's **no network partition**, you can have both consistency and availability. But when network partitions occur (and they WILL happen), you must choose:

```
SCENARIO: Network Partition Occurs

┌─────────────────────────────────────────────────────────────┐
│  Node A (US-East)                    Node B (US-West)       │
│  ┌─────────────────┐                ┌─────────────────┐   │
│  │  Balance: $100  │   PARTITION    │  Balance: $100  │   │
│  └─────────────────┘    ✗ ╳ ✗        └─────────────────┘   │
│         │                                     │            │
│         │          (Cannot communicate)       │            │
│         │                                     │            │
│         ▼                                     ▼            │
│  ┌─────────────────┐                ┌─────────────────┐   │
│  │ Write: $50      │                │ Write: $30      │   │
│  │ New: $50        │                │ New: $70        │   │
│  └─────────────────┘                └─────────────────┘   │
│                                                             │
│  NOW: A has $50, B has $70                                 │
│                                                             │
│  OPTION 1: Consistency (C)                                 │
│    - Make A unavailable until partition heals             │
│    - Or reject the write                                   │
│                                                             │
│  OPTION 2: Availability (A)                                 │
│    - Accept writes on both                                │
│    - Later reconcile (eventual consistency)               │
└─────────────────────────────────────────────────────────────┘
```

## The Three Trade-offs

### 1. CP (Consistency + Partition Tolerance)
```
┌─────────────────────────────────────────────────────────────┐
│              CP Systems                                      │
├─────────────────────────────────────────────────────────────┤
│ 牺牲 AVAILABILITY                                            │
│                                                             │
│  When partition occurs:                                    │
│  - Reject writes (or make read-only)                      │
│  - All nodes must agree before responding                  │
│  - System unavailable until partition resolves            │
│                                                             │
│  Use Cases:                                                 │
│  - Financial transactions                                  │
│  - Distributed locking systems                             │
│  - Coordination services (ZooKeeper, etcd)               │
│                                                             │
│  Examples:                                                  │
│  - ZooKeeper                                               │
│  - etcd                                                    │
│  - HBase                                                   │
│  - MongoDB (in certain configs)                            │
└─────────────────────────────────────────────────────────────┘
```

### 2. AP (Availability + Partition Tolerance)
```
┌─────────────────────────────────────────────────────────────┐
│              AP Systems                                      │
├─────────────────────────────────────────────────────────────┤
│ 牺牲 CONSISTENCY                                             │
│                                                             │
│  When partition occurs:                                     │
│  - Continue serving requests                              │
│  - Allow divergent data                                    │
│  - Resolve conflicts when partition heals                  │
│                                                             │
│  Use Cases:                                                 │
│  - Web caching                                              │
│  - Social media feeds                                       │
│  - Analytics/aggregation                                   │
│  - Shopping carts                                           │
│                                                             │
│  Examples:                                                  │
│  - Cassandra                                                │
│  - DynamoDB                                                 │
│  - CouchDB                                                  │
│  - DNS                                                      │
└─────────────────────────────────────────────────────────────┘
```

### 3. CA (Consistency + Availability)
```
┌─────────────────────────────────────────────────────────────┐
│              CA Systems                                      │
├─────────────────────────────────────────────────────────────┤
│ 牺牲 PARTITION TOLERANCE                                     │
│                                                             │
│  Note: Partition tolerance is NOT optional in              │
│  distributed systems - you MUST have it!                    │
│                                                             │
│  In practice, this means:                                  │
│  - Single-node databases                                   │
│  - Or systems that don't tolerate network failures         │
│                                                             │
│  Use Cases:                                                 │
│  - Single-server databases                                 │
│  - Testing/development environments                        │
│                                                             │
│  Examples:                                                  │
│  - Traditional RDBMS (MySQL, PostgreSQL)                   │
│  - (Without clustering/replication)                        │
└─────────────────────────────────────────────────────────────┘
```

## Consistency Models

### Strong Consistency
```
Timeline:
─────────────────────────────────────────────────────────────
T0: Write X=1 to Node A
    │
    │  Node A: X=1   Node B: X=0   Node C: X=0
    │      ▲
    │      │
    │      ▼
T1: Read from Node B ───► Returns ERROR or waits
                        (Must wait for sync)

    All nodes must agree before any read succeeds
```

- All reads see most recent write
- After update, all subsequent reads return new value
- Used in: Banking, inventory systems

### Eventual Consistency
```
Timeline:
─────────────────────────────────────────────────────────────
T0: Write X=1 to Node A
    │
    │  Node A: X=1   Node B: X=0   Node C: X=0
    │
    │  (Async replication)
    │       │              │              │
    │       ▼              ▼              ▼
    │  Node A: X=1   Node B: X=1   Node C: X=0
    │                                   │
    │                                   ▼
    │                          Node C: X=1
    │                                  
    │  Eventually all nodes converge to X=1
```

- Updates propagate asynchronously
- Temporary inconsistencies possible
- Used in: Social media, caching, CDNs

### Causal Consistency
```
Causal Relationship:
─────────────────────────────────────────────────────────────
User posts comment ──► Someone replies to that comment
      │                           │
      │ (Must happen first)       │
      │                           ▼
      │                    Can read original comment
      │                    before replying
      │
      ▼
No causal relationship:
─────────────────────────────────────────────────────────────
User posts photo A ──► User posts photo B
       │                           │
       │ (Can happen in any order) │
       │                           ▼
       │                    Either order is fine
       ▼
```

## PACELC Theorem

An extension of CAP that considers latency:

```
┌─────────────────────────────────────────────────────────────┐
│                   PACELC THEOREM                            │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  IF there's a Partition (P):                               │
│    THEN choose between Availability (A) or Consistency (C)│
│                                                             │
│  ELSE (E):                                                  │
│    THEN choose between Latency (L) or Consistency (C)     │
│                                                             │
│  This adds the latency dimension:                          │
│  - Even without partitions, you can't have both            │
│    low latency and strong consistency                      │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Real-World Examples

### Amazon DynamoDB (AP)
```
Characteristics:
- Highly available
- Eventual consistency by default
- Write idempotency
- Tunable consistency (per request)

Use Case: Shopping cart, session data
```

### Google Spanner (CP)
```
Characteristics:
- Strong consistency
- Globally distributed
- TrueTime (GPS + atomic clocks)
- 2-phase commit with Paxos

Use Case: Financial systems, AdWords
```

### MongoDB
```
Default Configuration: CP
- Write to primary (consistency)
- Read from primary by default
- Can configure for AP with secondary reads

Sharded Cluster: Eventual consistency
- Chunks move between shards
- Temporary inconsistencies possible
```

### Cassandra (AP)
```
Characteristics:
- Always writable (AP)
- Eventual consistency
- Tunable consistency
- Gossip protocol for coordination

Use Case: Time-series, IoT data, write-heavy workloads
```

## Choosing the Right Model

### Questions to Ask

| Question | If Yes → | If No → |
|----------|----------|---------|
| Need ACID transactions? | Choose CP | Consider AP |
| High availability critical? | Choose AP | Choose CP |
| Can tolerate temporary inconsistency? | Choose AP | Choose CP |
| Need complex queries? | SQL/CP | NoSQL/AP |
| Write-heavy workload? | AP (Cassandra) | CP (traditional DB) |

### Decision Matrix

```
Use CP when:
  ✓ Financial transactions
  ✓ Inventory management
  ✓ Distributed locking
  ✓ Leader election
  ✓ Strong consistency required

Use AP when:
  ✓ Social media feeds
  ✓ Analytics and reporting
  ✓ Shopping carts
  ✓ Session management
  ✓ High availability critical
  ✓ Temporary inconsistency acceptable
```

## Consistency Levels in Practice

### Cassandra Consistency Levels
```
┌─────────────────────────────────────────────┐
│  Consistency Level  │  Nodes Required      │
├─────────────────────┼──────────────────────│
│  ONE                │  1 node              │
│  QUORUM             │  N/2 + 1 nodes       │
│  ALL                │  All nodes           │
│  LOCAL_ONE          │  1 local node        │
│  LOCAL_QUORUM       │  Quorum in local DC  │
│  EACH_QUORUM        │  Quorum in ALL DCs   │
└─────────────────────────────────────────────┘
```

### DynamoDB Consistency
```
┌─────────────────────────────────────────────┐
│  Read Consistency    │  Behavior            │
├──────────────────────┼──────────────────────┤
│  Eventual (default)  │  Faster, may get     │
│                      │  stale data          │
├──────────────────────┼──────────────────────┤
│  Strongly Consistent │  Slower, always      │
│                      │  latest data         │
└──────────────────────┴──────────────────────┘
```

## Interview Tips

1. **Understand the theorem** - You can only have 2 of 3
2. **Know partition tolerance is mandatory** - Can't choose CA in distributed systems
3. **Be ready to explain real systems** - Cassandra (AP), MongoDB (CP), DynamoDB (AP)
4. **Understand consistency models** - Strong, eventual, causal
5. **Know PACELC** - Adds latency dimension

## Summary

CAP Theorem fundamental truth:
- **Partitions happen** - Network failures are inevitable
- **Must choose** - Consistency or Availability during partitions
- **No perfect solution** - Each has trade-offs

Modern approach:
- **Not all-or-nothing** - Tunable consistency
- **Application-specific** - Choose based on requirements
- **Multi-model** - Different systems for different needs
- **Compensating actions** - Handle eventual consistency in application
