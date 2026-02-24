# Monolithic vs Microservices Architecture

## What is Architecture?

Architecture defines how your application components are organized and interact. The choice between monolithic and microservices affects scalability, development speed, and operational complexity.

## Monolithic Architecture

A monolithic application is built as a single, self-contained unit where all components (UI, business logic, data access) are tightly coupled.

```
┌─────────────────────────────────────────────────────────────┐
│                  Monolithic Application                     │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌─────────────────────────────────────────────────────┐   │
│  │                    Frontend                          │   │
│  │  (Web UI, Mobile App)                               │   │
│  └───────────────────────┬─────────────────────────────┘   │
│                          │                                  │
│                          ▼                                  │
│  ┌─────────────────────────────────────────────────────┐   │
│  │                  Backend                            │   │
│  │ ┌───────────┐ ┌───────────┐ ┌───────────┐          │   │
│  │ │  User     │ │   Order   │ │   Product │   ...   │   │
│  │ │  Service  │ │  Service  │ │  Service  │          │   │
│  │ └───────────┘ └───────────┘ └───────────┘          │   │
│  │           │             │            │             │   │
│  │           └─────────────┼────────────┘             │   │
│  │                         │                          │   │
│  │                         ▼                          │   │
│  │              ┌───────────────────┐                │   │
│  │              │   Database        │                │   │
│  │              │  (Single DB)      │                │   │
│  │              └───────────────────┘                │   │
│  └─────────────────────────────────────────────────────┘   │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Characteristics

- Single codebase
- Single deployment unit
- Shared database
- Tightly coupled components
- Single technology stack

### Advantages

| Advantage | Description |
|-----------|-------------|
| **Simple Development** | One codebase, easy to understand |
| **Simple Deployment** | Single artifact to deploy |
| **Simple Testing** | End-to-end testing in one go |
| **Simple Debugging** | Call stacks are local |
| **Performance** | In-process calls are fast |
| **Transaction Support** | ACID transactions across all data |

### Disadvantages

| Disadvantage | Description |
|--------------|-------------|
| **Slow Development** | Large codebase slows teams |
| **Scaling** | Must scale entire application |
| **Reliability** | One bug crashes entire app |
| **Technology Lock-in** | Single tech stack |
| **Long-term Flexibility** | Hard to adopt new technologies |

### When to Use Monolith

1. **Small Teams** - 1-10 developers
2. **Simple Applications** - Limited functionality
3. **Fast MVP** - Quick time to market
4. **Low Traffic** - <10,000 users
5. **Budget Constraints** - Limited DevOps resources

## Microservices Architecture

Microservices decompose an application into small, independent services that communicate over well-defined APIs.

```
┌─────────────────────────────────────────────────────────────┐
│               Microservices Architecture                     │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌─────────────┐    ┌─────────────┐    ┌─────────────┐   │
│  │   User      │    │   Order     │    │  Product    │   │
│  │  Service    │    │  Service    │    │  Service    │   │
│  │             │    │             │    │             │   │
│  │  - Users    │    │  - Orders   │    │  - Products │   │
│  │  - Auth     │    │  - Cart     │    │  - Catalog  │   │
│  │  - Profile  │    │  - Payments │    │  - Search   │   │
│  └──────┬──────┘    └──────┬──────┘    └──────┬──────┘   │
│         │                  │                  │           │
│         │         API Gateway / Load Balancer  │           │
│         └──────────────────┬───────────────────┘           │
│                            │                                │
│         ┌──────────────────┼───────────────────┐            │
│         │                  │                   │            │
│         ▼                  ▼                   ▼            │
│  ┌─────────────┐    ┌─────────────┐    ┌─────────────┐   │
│  │   User DB   │    │  Order DB   │    │ Product DB  │   │
│  │  (Dedicated)│    │ (Dedicated) │    │(Dedicated)  │   │
│  └─────────────┘    └─────────────┘    └─────────────┘   │
│                                                             │
│  Each service:                                             │
│  ✓ Own codebase                                            │
│  ✓ Own database                                            │
│  ✓ Independent deployment                                  │
│  ✓ Own technology stack                                    │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Key Principles

1. **Single Responsibility** - Each service does one thing well
2. **Loose Coupling** - Services communicate via APIs
3. **High Cohesion** - Related functionality together
4. **Independence** - Services can be deployed separately
5. **Decentralized Data** - Each service owns its data

### Advantages

| Advantage | Description |
|-----------|-------------|
| **Independent Scaling** | Scale services individually |
| **Technology Flexibility** - | Different tech per service |
| **Fault Isolation** | One service failure doesn't crash all |
| **Faster Development** | Small teams, small codebases |
| **Faster Deployment** | Deploy services independently |
| **Team Autonomy** | Teams own their services |

### Disadvantages

| Disadvantage | Description |
|--------------|-------------|
| **Complexity** | Distributed systems are hard |
| **Data Consistency** | No ACID across services |
| **Operational Overhead** | Need monitoring, tracing |
| **Network Latency** | Inter-service calls add latency |
| **Testing** | End-to-end testing is complex |
| **Debugging** | Distributed tracing needed |

### Microservices Patterns

#### API Gateway Pattern
```
┌─────────────────────────────────────────┐
│         API Gateway                     │
│                                         │
│  Client ──► /api/users ──► User Service │
│         ──► /api/orders ──► Order      │
│         ──► /api/products ──► Product   │
│                                         │
│  ✓ Single entry point                   │
│  ✓ Authentication                       │
│  ✓ Request routing                     │
│  ✓ Rate limiting                        │
└─────────────────────────────────────────┘
```

#### Service Discovery
```
┌─────────────────────────────────────────┐
│      Service Discovery                  │
│                                         │
│  Service A ──► Registry ──► Find        │
│                 │              │        │
│                 │              ▼        │
│                 │         Service B     │
│                 │              │        │
│                 │              │        │
│                 │         Register       │
│                 │              │        │
│                 └──────────────┘        │
│                                         │
│  Examples: Consul, Eureka, etcd        │
└─────────────────────────────────────────┘
```

#### Circuit Breaker
```
┌─────────────────────────────────────────┐
│      Circuit Breaker Pattern            │
│                                         │
│  Normal:                                │
│  Request ──► Service A ──► Response    │
│                                         │
│  Failure Threshold Reached:            │
│  Request ──► [OPEN] ──► Fail Fast     │
│                                         │
│  After Timeout:                        │
│  Request ──► [HALF-OPEN] ──► Try      │
│                                         │
│  If Success:                           │
│  Request ──► [CLOSED] ──► Normal      │
└─────────────────────────────────────────┘
```

## Comparison

| Aspect | Monolith | Microservices |
|--------|----------|---------------|
| **Development Speed** | Slow (large codebase) | Fast (small teams) |
| **Scaling** | Scale entire app | Scale individually |
| **Deployment** | All or nothing | Independent |
| **Fault Tolerance** | Single point of failure | Isolated failures |
| **Data** | Single DB | Polyglot persistence |
| **Tech Stack** | Single | Multiple |
| **Testing** | Simple E2E | Complex distributed |
| **Debugging** | Simple | Distributed tracing |
| **Team Structure** | Single team | Feature teams |
| **Infrastructure** | Simple | Complex (DevOps) |

## Migration Strategies

### Strangler Fig Pattern
```
Phase 1: Monolith                          Phase 2: Begin Extraction
┌──────────────┐                          ┌──────────────┐
│  Monolith    │                          │  Monolith   │
│              │                          │  ┌────────┐ │
│  ┌────────┐  │                          │  │ Remains│ │
│  │ All    │  │                          │  └────────┘ │
│  │ Features│  │                          │     │      │
│  └────────┘  │                          │  New Service│
└──────────────┘                          └──────┬───────┘
                                                │
Phase 3: Complete Migration                  Phase 4:
┌──────────────┐                              ┌──────────────┐
│  Monolith   │                              │ New Services │
│  ┌────────┐ │                              │ ┌──────────┐ │
│  │Decom-  │ │                              │ │User, Ord,│ │
│  │missioned│ │                              │ │Product   │ │
│  └────────┘ │                              │ └──────────┘ │
└──────────────┘                              └──────────────┘
```

### Branch by Abstraction
```
Step 1: Create Abstraction
┌─────────────────────────────────────────┐
│  interface PaymentService               │
│    processPayment()                     │
│                                         │
│  class LegacyPayment implements ...      │
│  class NewPayment implements ...        │
└─────────────────────────────────────────┘

Step 2: Redirect Traffic
┌─────────────────────────────────────────┐
│  Router: If (featureFlag)               │
│    use NewPayment                      │
│  else                                  │
│    use LegacyPayment                    │
└─────────────────────────────────────────┘

Step 3: Remove Legacy
```

## Real-World Examples

### Netflix
```
Microservices Journey:
- Started as monolithic DVD rental
- Now 1000+ microservices
-Zuul (API Gateway)
-Eureka (Service Discovery)
-Hystrix (Circuit Breaker)
```

### Amazon
```
Architecture:
- 200+ microservices
- Each handles specific business function
- APIs for inter-service communication
```

### Uber
```
Evolution:
- Monolith (Python) ──► Node.js ──► Go microservices
- 1000+ microservices
- Different services for rider, driver, pricing
```

## When to Choose Microservices

### Good Candidates
- Large applications (>100k lines)
- Multiple teams (>10 developers)
- High scale requirements
- Complex domain (multiple bounded contexts)
- Need for technology flexibility
- Frequent independent deployments

### Bad Candidates
- Small applications
- Small teams
- Limited DevOps maturity
- Tight budget
- Simple domain

## Interview Tips

1. **Know both approaches** - Trade-offs of each
2. **Understand when to use each** - Not microservices everywhere
3. **Know patterns** - API Gateway, Service Discovery, Circuit Breaker
4. **Be ready for challenges** - Distributed systems are complex
5. **Know migration strategies** - How to move from monolith

## Summary

The choice depends on:

| Factor | Monolith | Microservices |
|--------|----------|---------------|
| Team Size | Small | Large |
| App Complexity | Simple | Complex |
| Scale Needs | Low | High |
| DevOps Maturity | Low | High |
| Time to Market | Fast (initially) | Slower initially, faster later |
| Budget | Limited | Adequate |

**Modern Best Practice**: Start with monolith, evolve to microservices as needed. Premature microservices is an anti-pattern.
