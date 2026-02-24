# Load Balancing

## What is Load Balancing?

Load balancing is the process of distributing network traffic across multiple servers to ensure no single server bears too much load, improving responsiveness and availability of applications.

```
                    ┌──────────────────┐
                    │   Load Balancer  │
                    └────────┬─────────┘
                             │
        ┌────────────────────┼────────────────────┐
        │                    │                    │
        ▼                    ▼                    ▼
   ┌─────────┐         ┌─────────┐         ┌─────────┐
   │ Server 1│         │ Server 2│         │ Server 3│
   │ (User A)│         │ (User B)│         │ (User C)│
   └─────────┘         └─────────┘         └─────────┘
```

## Why Load Balancing?

1. **Scalability**: Distribute traffic across multiple servers
2. **High Availability**: Redirect traffic if servers fail
3. **Performance**: Optimize resource utilization
4. **Reliability**: Prevent single points of failure

## Types of Load Balancers

### 1. Hardware Load Balancers
- Physical devices
- Expensive but powerful
- Used in enterprise environments
- Examples: F5, Citrix ADC

### 2. Software Load Balancers
- Run on standard servers
- More flexible and cost-effective
- Examples: NGINX, HAProxy, Envoy

### 3. Cloud Load Balancers
- Managed by cloud providers
- Auto-scaling support
- Examples: AWS ELB, Google Cloud Load Balancing, Azure Load Balancer

## Load Balancing Algorithms

### 1. Round Robin
```
Requests: 1, 2, 3, 4, 5, 6

Server A: 1, 4
Server B: 2, 5  
Server C: 3, 6

Simple, but doesn't consider server load
```

**Use case**: Servers with similar specifications

### 2. Least Connections
```
Request comes in...
Server A: 5 active connections
Server B: 2 active connections  ◄── Send to this one (least)
Server C: 8 active connections
```

**Use case**: Long-lived connections

### 3. IP Hash
```
User IP Hash
    │
    ▼
Hash Value ──► Server Assignment

Same user always goes to same server (session persistence)
```

**Use case**: Stateful applications

### 4. Weighted Load Balancing
```
Server A: Weight 100 (powerful)
Server B: Weight 50 (weaker)
Server C: Weight 50 (weaker)

Requests distributed proportionally
```

**Use case**: Heterogeneous server pools

### 5. Least Response Time
```
Server A: 50ms response time
Server B: 20ms response time  ◄── Send to this one (fastest)
Server C: 100ms response time
```

**Use case**: Performance-critical applications

## Load Balancing in the OSI Model

```
┌────────────────────────────────────────────────────┐
│                  OSI Model Layers                   │
├────────────────────────────────────────────────────┤
│  Layer 7 (Application)   │  Content-based routing  │
│  Layer 6 (Presentation)  │                        │
│  Layer 5 (Session)       │                        │
├────────────────────────────────────────────────────┤
│  Layer 4 (Transport)     │  Port-based routing    │
│  Layer 3 (Network)       │                        │
│  Layer 2 (Data Link)     │                        │
│  Layer 1 (Physical)      │                        │
└────────────────────────────────────────────────────┘
```

### Layer 4 (Transport) Load Balancing
- Faster (doesn't inspect packet content)
- Routes based on IP and port
- Less intelligent
- Examples: HAProxy (TCP mode), AWS NLB

### Layer 7 (Application) Load Balancing
- Can inspect HTTP headers
- Path-based routing
- More flexible but slower
- Examples: NGINX, AWS ALB, HAProxy (HTTP mode)

## Load Balancing Strategies

### 1. Health Checks
```
              ┌──────────────┐
              │     LB       │
              └──────┬───────┘
                     │
        ┌────────────┼────────────┐
        │            │            │
        ▼            ▼            ▼
   ┌─────────┐  ┌─────────┐  ┌─────────┐
   │ Server 1│  │ Server 2│  │ Server 3│
   │ ✓ HEALTH│  │ ✗ DOWN  │  │ ✓ HEALTH│
   └─────────┘  └─────────┘  └─────────┘
                    │
                    └── Traffic NOT sent here
```

- Periodic checks (HTTP, TCP, ping)
- Remove unhealthy servers
- Re-add when healthy

### 2. Session Persistence (Sticky Sessions)
```
User 12345
    │
    │ (First request)
    ▼
   LB ──► Server A (creates session)
    │
    │ (Subsequent requests)
    ▼
   LB ──► Server A (always)
    │
    │ Session stored on Server A
```

**Methods**:
- Cookie-based (insert session cookie)
- IP-based (hash of client IP)
- Header-based (custom header)

### 3. SSL Termination
```
Client ──► LB (decrypts SSL) ──► Backend Server
         ◄── Plain HTTP ──────────────────
```

- Load balancer handles encryption
- Offloads SSL processing
- Reduces backend server load

### 4. Geographic Routing
```
User from US ──► US Data Center
User from EU ──► EU Data Center
User from Asia ──► Asia Data Center
```

- Route based on user location
- Reduces latency
- Used with CDN

## Load Balancer Architecture

### 1. Gateway Load Balancer
```
Internet
    │
    ▼
┌─────────────┐
│     GWLB    │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Security   │
│  Appliance  │
│  (Firewall) │
└─────────────┘
       │
       ▼
┌─────────────┐
│  Backend    │
│  Servers    │
└─────────────┘
```

### 2. Reverse Proxy Load Balancer
```
Internet
    │
    ▼
┌─────────────┐
│  Reverse    │
│  Proxy LB   │
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Backend    │
│  Servers    │
└─────────────┘
```

### 3. Distributed Load Balancing
```
Region 1          Region 2          Region 3
┌──────────┐    ┌──────────┐    ┌──────────┐
│  Local LB│    │  Local LB│    │  Local LB│
└────┬─────┘    └────┬─────┘    └────┬─────┘
     │               │               │
     └───────────────┼───────────────┘
                     │
                     ▼
              Global DNS LB
                     │
                     ▼
               (Route to nearest region)
```

## Failover and High Availability

### Active-Passive Failover
```
Master Server (Active)
        │
        │ (Heartbeat)
        ▼
   ┌──────────┐
   │  Shared  │
   │  Storage │
   └──────────┘
        │
        │ (Heartbeat)
        ▼
  Standby Server (Passive)
        │
        │ (On failure)
        ▼
   Becomes Active
```

- One active, one standby
- Failover when active fails
- Data loss possible if not replicated

### Active-Active Failover
```
         ┌──────────┐
         │  LB      │
         └────┬─────┘
              │
    ┌─────────┼─────────┐
    │         │         │
    ▼         ▼         ▼
┌───────┐ ┌───────┐ ┌───────┐
│Server1│ │Server2│ │Server3│
│Active │ │Active │ │Active │
└───────┘ └───────┘ └───────┘
```

- All servers active
- Better resource utilization
- More complex setup

## Real-World Examples

### Google Cloud Load Balancing
- Global load balancer
- Anycast IP addresses
- Automatic scaling
- Built-in DDoS protection

### AWS Elastic Load Balancing
- Application Load Balancer (Layer 7)
- Network Load Balancer (Layer 4)
- Gateway Load Balancer
- Classic Load Balancer

### NGINX
- Software load balancer
- Layer 7 routing
- Health checks
- Session persistence
- SSL termination

## Load Balancing Best Practices

1. **Health Checks**: Implement regular health checks
2. **Graceful Degradation**: Handle partial failures
3. **SSL/TLS Termination**: Offload encryption
4. **Session Persistence**: When needed, use it wisely
5. **Monitoring**: Track server health and load
6. **Auto-scaling**: Combine with scaling policies
7. **Geographic Distribution**: For global applications

## Interview Tips

1. **Know the algorithms** - Round Robin, Least Connections, IP Hash
2. **Understand Layer 4 vs Layer 7** - When to use each
3. **Be ready to discuss health checks** - Why they're important
4. **Understand sticky sessions** - Trade-offs
5. **Know about failover** - Active-passive vs active-active

## Summary

Load Balancing is essential for:
- Distributing traffic across servers
- Improving availability and reliability
- Enabling horizontal scaling
- Providing failover capability

Key decisions:
- **Algorithm choice** based on workload
- **Layer selection** (4 vs 7)
- **Health check frequency**
- **Session persistence needs**
- **HA configuration**
