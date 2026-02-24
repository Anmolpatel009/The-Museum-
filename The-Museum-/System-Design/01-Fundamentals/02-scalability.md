# Scalability

## What is Scalability?

Scalability is a system's ability to handle growing amounts of work by adding resources. A scalable system can accommodate increased load without performance degradation or system failure.

## Types of Scaling

### 1. Vertical Scaling (Scale Up)

Adding more power to your existing machine:
- More CPU cores
- More RAM
- More storage
- Better network bandwidth

```
BEFORE                      AFTER
┌─────────────┐            ┌─────────────┐
│  Server     │            │  Server     │
│  4 CPU      │   ──────►  │  32 CPU     │
│  16 GB RAM  │            │  128 GB RAM │
│  500 GB SSD │            │  2 TB SSD   │
└─────────────┘            └─────────────┘
```

**Advantages:**
- Simple to implement
- No code changes needed
- Single point of management

**Disadvantages:**
- Hardware limits (can't add infinite resources)
- Single point of failure
- Expensive high-end hardware
- Downtime during upgrades

**When to use:**
- Small to medium workloads
- When simplicity is priority
- Development/testing environments

### 2. Horizontal Scaling (Scale Out)

Adding more machines to handle load:

```
BEFORE                      AFTER
┌─────────────┐            ┌─────────────┐
│  Server 1  │            │  Server 1  │
└─────────────┘            └─────────────┘
                             
                              ┌─────────────┐
                              │  Server 2  │
                              └─────────────┘
                             
                              ┌─────────────┐
                              │  Server 3  │
                              └─────────────┘
```

**Advantages:**
- No hardware limits
- Better fault tolerance
- Cost-effective (use commodity hardware)
- Better handling of high traffic

**Disadvantages:**
- More complex architecture
- Requires load balancing
- Data consistency challenges
- Network overhead

**When to use:**
- Large scale applications
- High availability requirements
- Unpredictable traffic patterns

## Scalability Dimensions

### 1. Load Scaling

Ability to handle increased user traffic:

```
User Traffic
    │
    │    ┌──────────────────────────┐
    │    │                          │
    │    │    Scalable System       │
    │    │                          │
    │    └──────────────────────────┘
    │              │
    ▼              ▼
   100        1,000,000
  Users         Users
   (Same response time)
```

### 2. Data Scaling

Ability to handle growing data volumes:
- Database sharding
- Data partitioning
- Archive old data
- Use appropriate data stores

### 3. Computational Scaling

Ability to handle complex computations:
- Distributed computing (MapReduce, Spark)
- Parallel processing
- GPU acceleration
- Async processing

## Scaling Strategies

### Database Scaling

#### Read Replicas
```
                    ┌──────────────┐
                    │  Load       │
                    │  Balancer   │
                    └──────┬───────┘
                           │
         ┌─────────────────┼─────────────────┐
         │                 │                 │
         ▼                 ▼                 ▼
   ┌───────────┐    ┌───────────┐    ┌───────────┐
   │  Master   │    │  Replica │    │  Replica │
   │  DB       │───►│  1        │───►│  2        │
   │ (Write)   │    │  (Read)   │    │  (Read)  │
   └───────────┘    └───────────┘    └───────────┘
```

- Master handles writes
- Replicas handle reads
- Asynchronous replication
- Improves read throughput

#### Database Sharding
```
                    ┌──────────────┐
                    │  Application │
                    │    Layer     │
                    └──────┬───────┘
                           │
         ┌─────────────────┼─────────────────┐
         │                 │                 │
         ▼                 ▼                 ▼
   ┌───────────┐    ┌───────────┐    ┌───────────┐
   │  Shard 1  │    │  Shard 2  │    │  Shard 3  │
   │ (Users     │    │ (Users     │    │ (Users     │
   │  A-M)      │    │  N-Z)      │    │  Admin)   │
   └───────────┘    └───────────┘    └───────────┘
```

- Horizontal partitioning
- Each shard contains subset of data
- Allows scaling write throughput
- More complex queries

### Application Scaling

#### Stateless Applications
```
┌─────────────┐
│  Load       │
│  Balancer   │
└──────┬──────┘
       │
 ┌─────┴─────┬─────┬─────┐
 ▼           ▼     ▼     ▼
Srv1        Srv2  Srv3  Srv4
(Any can handle any request)
```

- No session data on server
- Easy to add/remove servers
- Use external session store if needed

#### Stateful Applications
```
┌─────────────┐
│  Load       │
│  Balancer   │
└──────┬──────┘
       │
 ┌─────┴─────┬─────┬─────┐
 ▼           ▼     ▼     ▼
Srv1        Srv2  Srv3  Srv4
(User1)     (User2)(User3)(User4)
(Must route to same server)
```

- Session maintained on server
- More complex scaling
- Sticky sessions needed

## Scaling Patterns

### 1. Horizontal Auto-scaling
```
                    ┌──────────────────┐
                    │  Auto-scaler     │
                    │  (Monitors CPU)  │
                    └────────┬─────────┘
                             │
         ┌───────────────────┼───────────────────┐
         │                   │                   │
         ▼                   ▼                   ▼
    ┌─────────┐        ┌─────────┐        ┌─────────┐
    │ Server 1│        │ Server 2│        │ Server 3│
    │ (25% CPU)       │ (80% CPU)        │ (90% CPU)
    └─────────┘        └─────────┘        └─────────┘
                             │
                             ▼
                    Add 2 more servers
                    (CPU > 75% threshold)
```

### 2. Database Connection Pooling
```
    Application Server
    ┌─────────────────────┐
    │ ┌─────┐ ┌─────┐    │
    │ │Pool │ │Pool │    │
    │ │     │ │     │    │
    │ └─────┘ └─────┘    │
    └──────────┬──────────┘
               │
               ▼
    ┌─────────────────────┐
    │   Database Server   │
    │   (100 max conn)    │
    └─────────────────────┘
```

### 3. Caching Layer
```
    Request ──► Cache (Hit) ──► Response
                   │
                  Miss
                   │
                   ▼
              Database ──► Response + Cache
```

## Scalability Metrics

### Key Metrics to Track

| Metric | Description | Target |
|--------|-------------|--------|
| Response Time | Time to process request | < 200ms |
| Throughput | Requests per second | Depends on system |
| CPU Usage | Processor utilization | < 70% average |
| Memory Usage | RAM utilization | < 80% |
| Error Rate | Failed requests % | < 0.1% |
| Availability | Uptime percentage | > 99.9% |

### Measuring Scalability

**Linear Scalability**: Doubling resources doubles throughput
**Sub-linear Scalability**: More resources give diminishing returns
**Super-linear Scalability**: Better than expected (rare)

```
Throughput
    │
    │    ● Linear (Ideal)
    │   ╱
    │  ╱  ●● Sub-linear
    │ ╱   ╱
    │╱   ╱
    └──────────────► Resources
```

## Common Scalability Bottlenecks

### 1. Database Bottlenecks
- Slow queries
- Lock contention
- Connection limits
- Index inefficiencies

### 2. Network Bottlenecks
- Bandwidth limits
- Latency
- DNS lookups
- SSL/TLS overhead

### 3. Application Bottlenecks
- Single-threaded processing
- Synchronous I/O
- Memory leaks
- Poor code efficiency

### 4. Infrastructure Bottlenecks
- Limited server resources
- Load balancer capacity
- Firewall limits

## Real-World Examples

### Netflix
- Serves 200+ million subscribers
- Auto-scaling based on demand
- Content Delivery Network (CDN)
- Microservices architecture
- Processes billions of view hours daily

### Uber
- Handles millions of rides daily
- Real-time matching of drivers and riders
- Geo-spatial data processing
- Surge pricing calculations

### Amazon
- Millions of products
- Millions of concurrent users
- Sub-second page loads
- 99.99% availability target

## Interview Tips

1. **Know the difference** between vertical and horizontal scaling
2. **Understand when to use each** - small vs large scale
3. **Be ready to discuss** database scaling strategies
4. **Know about auto-scaling** - triggers and metrics
5. **Understand trade-offs** - complexity vs scalability

## Summary

Scalability is about designing systems that can grow:
- **Start with vertical scaling** for simplicity
- **Move to horizontal** for scale and availability
- **Use multiple strategies** - caching, read replicas, sharding
- **Monitor and measure** to understand when to scale
- **Automate** scaling for responsiveness
- **Plan for failure** - distribute across machines
