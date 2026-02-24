# Databases Overview

## What is a Database?

A database is an organized collection of structured data stored electronically. It provides mechanisms for storing, retrieving, updating, and managing data efficiently.

```
┌─────────────────────────────────────────────────────────────┐
│                      Database System                        │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌──────────────┐     ┌──────────────┐     ┌───────────┐  │
│  │   Client     │────►│   Database   │◄────│  Query    │  │
│  │  Applications│     │   Server     │     │  Parser   │  │
│  └──────────────┘     └──────────────┘     └───────────┘  │
│                              │                              │
│                              ▼                              │
│                       ┌───────────┐                        │
│                       │   Data    │                        │
│                       │  Storage  │                        │
│                       └───────────┘                        │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Types of Databases

### 1. Relational Databases (SQL)

Structured data with predefined schema using tables with rows and columns.

```
┌─────────────────────────────────────────┐
│  Users Table                            │
├─────────┬───────────┬──────────────────┤
│  id     │  name     │  email           │
├─────────┼───────────┼──────────────────┤
│  1      │  Alice    │  alice@email.com │
│  2      │  Bob      │  bob@email.com   │
│  3      │  Charlie  │  charlie@email   │
└─────────┴───────────┴──────────────────┘

┌─────────────────────────────────────────┐
│  Orders Table                           │
├─────────┬─────────┬────────────────────┤
│  id     │ user_id │  amount           │
├─────────┼─────────┼────────────────────┤
│  101    │    1    │     99.99         │
│  102    │    1    │    149.99         │
│  103    │    2    │     49.99         │
└─────────┴─────────┴────────────────────┘
         │
         │ (Foreign Key Relationship)
         ▼
    Relationships enforced by database
```

**Characteristics**:
- Predefined schema
- ACID transactions
- SQL as query language
- Table-based structure
- Supports joins

**Popular SQL Databases**:
- PostgreSQL
- MySQL
- Oracle
- Microsoft SQL Server
- MariaDB

**Best For**:
- Financial transactions
- Complex queries
- Structured data
- Data integrity requirements
- Applications requiring ACID

### 2. NoSQL Databases

Non-relational databases designed for flexibility, scalability, and performance with various data models.

#### a) Document Databases
```
┌─────────────────────────────────────────┐
│  Document (JSON/BSON)                  │
│  {                                      │
│    "_id": "user123",                   │
│    "name": "Alice",                    │
│    "age": 30,                          │
│    "address": {                        │
│      "city": "NYC",                    │
│      "country": "USA"                 │
│    },                                  │
│    "orders": [                         │
│      {"id": 101, "amount": 99.99},    │
│      {"id": 102, "amount": 149.99}    │
│    ]                                                                        │
└──────────────────────────────── │
│  }─────────┘
```

**Examples**: MongoDB, CouchDB, Amazon DocumentDB

#### b) Key-Value Stores
```
┌─────────────────────────────────────────┐
│  Key-Value Pairs                        │
│                                         │
│  "user:1"     ──► {"name": "Alice"}   │
│  "user:2"     ──► {"name": "Bob"}     │
│  "session:abc" ──► {"logged_in": true}│
│  "cart:123"   ──► [{item1}, {item2}] │
│                                         │
└─────────────────────────────────────────┘
```

**Examples**: Redis, DynamoDB, etcd

#### c) Column-Family Stores
```
┌─────────────────────────────────────────┐
│  Wide Column Format                     │
│                                         │
│  Row Key: user1                        │
│  ┌────────────────────────────────────┐ │
│  │ Column Family: Profile             │ │
│  │   name: "Alice"                   │ │
│  │   email: "alice@email"            │ │
│  │ Column Family: Orders              │ │
│  │   order:101: 99.99                │ │
│  │   order:102: 149.99               │ │
│  └────────────────────────────────────┘ │
└─────────────────────────────────────────┘
```

**Examples**: Cassandra, HBase, Amazon Keyspaces

#### d) Graph Databases
```
┌─────────────────────────────────────────┐
│  Graph Structure                        │
│                                         │
│        Alice ──►follows──► Bob          │
│        │                    │          │
│        │                    ▼          │
│        │              follows          │
│        │                    │          │
│        ▼                    ▼          │
│      Carol ◄────────────── David        │
│                                         │
│  Nodes: Users, Posts, Comments          │
│  Edges: follows, likes, commented       │
└─────────────────────────────────────────┘
```

**Examples**: Neo4j, Amazon Neptune, ArangoDB

## SQL vs NoSQL Comparison

| Aspect | SQL (Relational) | NoSQL (Non-Relational) |
|--------|------------------|------------------------|
| Schema | Fixed | Flexible |
| Transactions | ACID | Eventually Consistent |
| Query Language | SQL | Varies (API) |
| Scalability | Vertical | Horizontal |
| Data Model | Tables | Documents/Key-Value/Graph |
| Relationships | Strong (joins) | Weak (denormalized) |
| Learning Curve | Moderate | Varies |
| Use Cases | Financial, Analytics | Real-time, Unstructured |

## When to Use SQL

1. **Complex Queries**: Need JOINs, aggregations
2. **Transaction Integrity**: ACID compliance required
3. **Structured Data**: Fixed schema fits well
4. **Reporting/Analytics**: Complex queries
5. **Data Relationships**: Complex relationships between entities

## When to Use NoSQL

1. **Rapid Development**: Schema flexibility
2. **High Write Throughput**: Massive writes
3. **Unstructured Data**: JSON, logs, events
4. **Horizontal Scaling**: Need distributed database
5. **Specific Data Models**: Documents, graphs, key-value

## Database Architecture

### 1. Single Node
```
┌─────────────────────────────────────────┐
│          Single Server                   │
│                                         │
│  ┌─────────────────────────────────┐   │
│  │     Application Layer           │   │
│  └─────────────────────────────────┘   │
│                 │                        │
│                 ▼                        │
│  ┌─────────────────────────────────┐   │
│  │     Database Server             │   │
│  │  ┌───────────────────────────┐  │   │
│  │  │   Query Processor         │  │   │
│  │  │   Transaction Manager      │  │   │
│  │  │   Storage Engine           │  │   │
│  │  └───────────────────────────┘  │   │
│  └─────────────────────────────────┘   │
│                 │                        │
│                 ▼                        │
│  ┌─────────────────────────────────┐   │
│  │     Data Files                  │   │
│  └─────────────────────────────────┘   │
└─────────────────────────────────────────┘
```

### 2. Primary-Replica
```
┌─────────────────────────────────────────┐
│      Primary-Replica Architecture       │
│                                         │
│              ┌─────────────┐           │
│              │ Load Balancer│           │
│              └──────┬───────┘           │
│                     │                    │
│       ┌────────────┼────────────┐      │
│       │            │            │        │
│       ▼            │            ▼        │
│  ┌─────────┐      │      ┌─────────┐   │
│  │Primary  │      │      │Replica  │   │
│  │(Writes) │◄─────┼─────►│(Reads)  │   │
│  └─────────┘      │      └─────────┘   │
│                   │            │        │
│                   │            ▼        │
│                   │      ┌─────────┐   │
│                   └─────►│Replica  │   │
│                          │(Reads)   │   │
│                          └─────────┘   │
│                                       │
│  Replication: Async/Sync              │
└─────────────────────────────────────────┘
```

### 3. Sharded Database
```
┌─────────────────────────────────────────┐
│        Sharded Architecture             │
│                                         │
│         Application Layer               │
│    ┌─────────────────────────────┐      │
│    │    Sharding Router           │      │
│    └──────────────┬──────────────┘      │
│                   │                       │
│    ┌──────────────┼──────────────┐       │
│    │              │              │       │
│    ▼              ▼              ▼       │
│ ┌──────┐    ┌──────────┐   ┌────────┐  │
│ │Shard │    │  Shard   │   │ Shard  │  │
│ │  1   │    │    2     │   │   3    │  │
│ │(A-G) │    │  (H-N)   │   │ (O-Z)  │  │
│ └──────┘    └──────────┘   └────────┘  │
│                                        │
│  Shard Key: user_id, region, etc.     │
└─────────────────────────────────────────┘
```

## Database Indexing

### Without Index
```
Search for "Alice" in Users table (1M rows):
┌─────────────────────────────────────────┐
│  Full Table Scan                        │
│                                         │
│  Row 1: "Bob"     ✗                    │
│  Row 2: "Charlie" ✗                    │
│  Row 3: "David"   ✗                    │
│  ...                                    │
│  Row 500,000: "Alice" ✓ FOUND!         │
│                                         │
│  Time: O(n) - Scanned 500,000 rows     │
└─────────────────────────────────────────┘
```

### With Index
```
Search for "Alice" using B-Tree Index:
┌─────────────────────────────────────────┐
│  B-Tree Index                          │
│                                         │
│           [D-M]                        │
│          /      \                       │
│      [A-C]        [N-Z]                │
│      /   \       /    \                │
│   [A]   [C]   [N]    [P-Z]            │
│   │            │       │               │
│   ▼            ▼       ▼               │
│  ...         Alice   ...               │
│                                         │
│  Time: O(log n) - ~20 steps            │
└─────────────────────────────────────────┘
```

## ACID Properties

### Atomicity
```
Transaction: Transfer $100 from Account A to B
┌─────────────────────────────────────────┐
│  Start: A=$500, B=$200                  │
│                                         │
│  Step 1: Deduct $100 from A ──► A=$400 │
│  Step 2: Add $100 to B ──► B=$300      │
│                                         │
│  IF Step 2 fails:                       │
│    Rollback to initial state            │
│    A=$500, B=$200 (unchanged)           │
│                                         │
│  Either ALL succeed or ALL fail         │
└─────────────────────────────────────────┘
```

### Consistency
```
Before Transaction: Account A = $500
                    Constraint: Balance >= 0

Transaction: Withdraw $600

┌─────────────────────────────────────────┐
│  Validation: $600 > $500                │
│  Result: REJECTED (violates constraint)│
│                                         │
│  Database remains in valid state        │
└─────────────────────────────────────────┘
```

### Isolation
```
Transaction 1: Read balance ──► $500
Transaction 2: Read balance ──► $500
Transaction 1: Add $100 ──► $600
Transaction 2: Add $50 ──► $550
                                         
Isolation Levels:
• Read Uncommitted: $550 (dirty read)
• Read Committed: $500 then $600
• Repeatable Read: $500 throughout
• Serializable: Strict ordering
```

### Durability
```
Transaction: Transfer $100 complete
───────────────────────────────────────────
✓ Transaction committed to database
✓ Written to disk
✓ Even if system crashes, transaction persists
```

## Popular Database Solutions

### Cloud Databases
- Amazon RDS (MySQL, PostgreSQL, Oracle)
- Amazon DynamoDB (NoSQL)
- Google Cloud SQL
- Google Cloud Firestore
- Azure SQL Database
- Azure Cosmos DB

### Open Source
- PostgreSQL
- MySQL/MariaDB
- MongoDB
- Redis
- Cassandra

## Interview Tips

1. **Know SQL vs NoSQL** - When to use each
2. **Understand ACID** - What each property means
3. **Know indexing** - How it improves performance
4. **Be ready for normalization vs denormalization** - Trade-offs
5. **Understand replication** - Master-slave, sharding

## Summary

Database selection depends on:
- **Data structure** - Fixed vs flexible schema
- **Query complexity** - Simple vs complex joins
- **Scale requirements** - Vertical vs horizontal
- **Consistency needs** - ACID vs eventual consistency
- **Development speed** - Schema migration frequency

Modern applications often use:
- **Polyglot persistence** - Different databases for different needs
- **SQL for business logic** - Transactions, relationships
- **NoSQL for performance** - High throughput, flexible schema
- **Caching layers** - Redis, Memcached
