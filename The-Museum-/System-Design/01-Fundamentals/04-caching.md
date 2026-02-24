# Caching

## What is Caching?

Caching is the process of storing frequently accessed data in a fast storage layer to reduce latency and improve performance. The cache acts as a temporary storage between the client and the original data source.

```
Without Cache                    With Cache
┌──────────┐                    ┌──────────┐
│ Request  │                    │ Request  │
└────┬─────┘                    └────┬─────┘
     │                               │
     ▼                               ▼
┌──────────┐                   ┌──────────┐
│ Database │                   │  Cache   │
│ (Slow)   │                   │  (Fast)  │
└──────────┘                   └────┬─────┘
                                     │
                                     │ (Cache Miss)
                                     ▼
                              ┌──────────┐
                              │ Database │
                              └──────────┘
```

## Why Caching?

1. **Reduce Latency**: Cache access is 10-100x faster than database
2. **Reduce Load**: Decreases database queries
3. **Improve Throughput**: Handle more requests per second
4. **Reduce Costs**: Fewer database resources needed

## Types of Caches

### 1. Browser Cache
```
User's Browser
┌─────────────────────────────────┐
│ ┌─────────────────────────────┐ │
│ │  CSS, JS, Images            │ │
│ │  (Cached locally)           │ │
│ └─────────────────────────────┘ │
│ ┌─────────────────────────────┐ │
│ │  Local Storage              │ │
│ └─────────────────────────────┘ │
└─────────────────────────────────┘
```

- Stored on user's device
- For static assets (CSS, JS, images)
- Controlled by cache headers

### 2. CDN (Content Delivery Network)
```
                    ┌─────────────────┐
                    │    CDN Edge     │
                    │    Locations    │
                    └────────┬────────┘
                             │
        ┌────────────────────┼────────────────────┐
        │                    │                    │
        ▼                    ▼                    ▼
   ┌─────────┐         ┌─────────┐         ┌─────────┐
   │   US    │         │   EU    │         │  Asia   │
   │   Edge  │         │   Edge  │         │  Edge   │
   └─────────┘         └─────────┘         └─────────┘
```

- Distributed globally
- Caches static content
- Reduces latency for users

### 3. Application Cache (In-Memory)
```
    Application Server
    ┌─────────────────────┐
    │  ┌───────────────┐  │
    │  │   In-Memory   │  │
    │  │    Cache      │  │
    │  │  (Redis/      │  │
    │  │   Memcached)  │  │
    │  └───────────────┘  │
    └─────────────────────┘
```

- Stored in RAM
- Fastest access times
- Can be distributed

### 4. Database Query Cache
```
┌──────────────────┐
│  SQL Query       │
└────────┬─────────┘
         │
         ▼
┌──────────────────┐
│  Query Cache     │
│  (Results cached)│
└────────┬─────────┘
         │
         │ (Cache hit)
         ▼
┌──────────────────┐
│  Return Results  │
└──────────────────┘
```

- Caches query results
- Database-specific
- Limited effectiveness

## Cache Strategies

### 1. Cache-Aside (Lazy Loading)
```
┌─────────────────────────────────────────┐
│  Application                           │
│                                         │
│  1. Request data                       │
│  2. Check cache                        │
│     ├── Cache Hit ──► Return data      │
│     │                                    │
│     └── Cache Miss ──► Fetch from DB   │
│                            │            │
│                            ▼            │
│                    Store in cache       │
│                            │            │
│                            ▼            │
│                    Return data          │
└─────────────────────────────────────────┘
```

**Implementation**:
```python
def get_user(user_id):
    # Check cache first
    cached = cache.get(f"user:{user_id}")
    if cached:
        return cached
    
    # Cache miss - fetch from database
    user = db.query(f"SELECT * FROM users WHERE id = {user_id}")
    
    # Store in cache
    cache.set(f"user:{user_id}", user, expire=3600)
    
    return user
```

**Pros**:
- Cache only requested data
- No code changes to database
- Easy to implement

**Cons**:
- Cache miss on first request
- Stale data possible
- Need to handle cache population

### 2. Write-Through
```
┌─────────────────────────────────────────┐
│  Application                           │
│                                         │
│  Write data ──► Update DB              │
│       │                                │
│       └───────────────► Update cache   │
│                                         │
│  (DB and cache always in sync)         │
└─────────────────────────────────────────┘
```

**Implementation**:
```python
def create_user(user_data):
    # Write to database
    db.insert("users", user_data)
    
    # Write to cache
    cache.set(f"user:{user_data['id']}", user_data)
    
    return user_data
```

**Pros**:
- Data always fresh in cache
- Read-heavy workloads fast
- No cache miss on writes

**Cons**:
- Slower writes
- Cache may have unused data
- More storage used

### 3. Write-Behind
```
┌─────────────────────────────────────────┐
│  Application                           │
│                                         │
│  Write data ──► Update cache          │
│       │                                │
│       │ (async)                        │
│       └───────────────► Update DB     │
│                                         │
│  (Fast writes, eventual consistency)   │
└─────────────────────────────────────────┘
```

**Pros**:
- Fast writes
- Reduces database load
- Better throughput

**Cons**:
- Risk of data loss (if cache fails before DB)
- More complex
- Eventual consistency

### 4. Refresh-Ahead
```
┌─────────────────────────────────────────┐
│  Cache with TTL                         │
│                                         │
│  Entry has:                             │
│  - Data                                 │
│  - TTL (time to live)                   │
│                                         │
│  Background refresh before expiry       │
└─────────────────────────────────────────┘
```

**Pros**:
- Reduces cache misses
- Better user experience
- Predictable refresh

**Cons**:
- More complex
- Memory used for stale entries

## Cache Invalidation

### Types of Invalidation

1. **TTL (Time To Live)**
```
cache.set("key", value, ttl=300)  # 5 minutes
```

2. **Manual Invalidation**
```python
cache.delete("user:123")
```

3. **Event-Based Invalidation**
```
Database Update ──► Message Queue ──► Cache Invalidation
```

### Invalidation Strategies

| Strategy | Description | Use Case |
|----------|-------------|----------|
| TTL | Expire after time | Simple, acceptable staleness |
| LRU | Evict least recently used | Memory limited |
| LFU | Evict least frequently used | Popular items |
| FIFO | Evict oldest first | Time-sensitive |

## Caching Patterns

### 1. Cache Warming
```
┌─────────────────────────────────────────┐
│  Cache Warming                         │
│                                         │
│  On startup:                           │
│  1. Load popular data into cache       │
│  2. Pre-populate expensive queries     │
│                                         │
│  Result: No cold start cache misses    │
└─────────────────────────────────────────┘
```

### 2. Cache Partitioning
```
┌─────────────────────────────────────────┐
│  Distributed Cache                      │
│                                         │
│  Shard 1: Keys A-G                     │
│  Shard 2: Keys H-N                     │
│  Shard 3: Keys O-U                     │
│  Shard 4: Keys V-Z                     │
└─────────────────────────────────────────┘
```

### 3. Multi-Layer Caching
```
┌─────────────────────────────────────────┐
│  L1 Cache (Local)      - Fast, small   │
│  L2 Cache (Distributed) - Slower, big  │
│  Database                - Slowest      │
└─────────────────────────────────────────┘
```

## Cache Technologies

### Redis
```
┌─────────────────────────────────────────┐
│  Redis                                  │
│                                         │
│  ✓ In-memory data store                │
│  ✓ Multiple data structures            │
│  ✓ Persistence option                  │
│  ✓ Clustering support                  │
│  ✓ Pub/Sub messaging                   │
│  ✓ Lua scripting                       │
└─────────────────────────────────────────┘
```

**Data Types**:
- Strings
- Lists
- Sets
- Sorted Sets
- Hashes
- Bitmaps
- HyperLogLogs
- Geospatial

### Memcached
```
┌─────────────────────────────────────────┐
│  Memcached                              │
│                                         │
│  ✓ Simple key-value store              │
│  ✓ Multi-threaded                       │
│  ✓ No persistence                       │
│  ✓ No clustering (by default)          │
│  ✓ Lower memory overhead               │
└─────────────────────────────────────────┘
```

### Comparison

| Feature | Redis | Memcached |
|---------|-------|-----------|
| Data Types | Rich | Simple |
| Persistence | Yes | No |
| Clustering | Yes | Limited |
| Speed | Very Fast | Very Fast |
| Memory | Higher | Lower |
| Use Case | Complex data | Simple cache |

## Cache Problems

### 1. Cache Miss
```
First request ──► Cache miss ──► Database ──► Slow response
```

**Solution**: Cache warming, appropriate TTL

### 2. Cache Stampede (Thundering Herd)
```
Many requests ──► All miss cache ──► All hit database ──► Crash
```

**Solution**:
- Random jitter on TTL
- Request coalescing
- Semaphore-based population

### 3. Stale Data
```
Data updated in DB ──► Cache still has old value ──► Wrong data
```

**Solution**:
- TTL (eventual consistency)
- Write-through (immediate)
- Event-based invalidation

### 4. Hot Keys (Celebrity Problem)
```
Many requests ──► Same key ──► One cache server overloaded
```

**Solution**:
- Key spreading (hash with salt)
- Local cache
- Replica sets

## Real-World Examples

### Facebook
- Multiple cache layers
- TAO (distributed graph cache)
- Memcached clusters
- Thousands of servers

### Twitter
- Redis for timelines
- Memcached for fragments
- CDN for media

### Amazon
- DynamoDB DAX (cache)
- ElastiCache (Redis/Memcached)
- CloudFront CDN

## Best Practices

1. **Measure first** - Don't cache without reason
2. **Choose right strategy** - Read-heavy vs write-heavy
3. **Set appropriate TTL** - Balance freshness vs hit rate
4. **Handle failures gracefully** - Cache can fail
5. **Monitor cache metrics** - Hit rate, memory usage
6. **Plan for cold start** - Cache warming strategies
7. **Secure your cache** - Authentication, encryption

## Interview Tips

1. **Know cache strategies** - Cache-aside, write-through, etc.
2. **Understand when to use each** - Trade-offs
3. **Be ready for cache problems** - Stampede, hot keys
4. **Know Redis vs Memcached** - When to use each
5. **Understand invalidation** - TTL, event-based

## Summary

Caching is essential for:
- Reducing latency
- Improving throughput
- Reducing database load
- Cost optimization

Key decisions:
- **Cache strategy** based on read/write patterns
- **Technology choice** (Redis vs Memcached)
- **TTL values** based on data freshness needs
- **Invalidation strategy** for consistency
- **Scaling approach** for distributed caches
