# API Design

## What is API Design?

API (Application Programming Interface) design involves creating interfaces that allow different software systems to communicate. Good APIs are intuitive, consistent, and well-documented.

```
┌─────────────────────────────────────────────────────────────┐
│                    API Architecture                         │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Client ──► API ──► Business Logic ──► Database           │
│               │                                             │
│               │ (API serves as contract)                    │
│               ▼                                             │
│          Documentation                                       │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Types of APIs

### 1. REST (Representational State Transfer)
```
HTTP Methods:
┌─────────────────────────────────────────────────────────────┐
│  Method   │  Description       │  Idempotent               │
├───────────┼───────────────────┼───────────────────────────┤
│  GET      │  Read resource    │  Yes                      │
│  POST     │  Create resource  │  No                       │
│  PUT      │  Update (full)    │  Yes                      │
│  PATCH    │  Update (partial) │  No                       │
│  DELETE   │  Delete resource │  Yes                      │
└─────────────────────────────────────────────────────────────┘

REST Example:
GET    /users              - Get all users
GET    /users/123          - Get user 123
POST   /users              - Create new user
PUT    /users/123          - Update user 123
DELETE /users/123          - Delete user 123
```

**Characteristics**:
- Resource-based URLs
- Stateless communication
- Standard HTTP methods
- JSON/XML responses
- Uses HTTP status codes

### 2. GraphQL
```
Query:
─────────────────────────────────────────────────────────────
query {
  user(id: "123") {
    name
    email
    posts {
      title
      comments {
        body
      }
    }
  }
}

Response:
─────────────────────────────────────────────────────────────
{
  "data": {
    "user": {
      "name": "Alice",
      "email": "alice@email.com",
      "posts": [
        {
          "title": "Hello World",
          "comments": [...]
        }
      ]
    }
  }
}
```

**Characteristics**:
- Single endpoint
- Client specifies fields needed
- Strongly typed schema
- No over-fetching or under-fetching
- Real-time with subscriptions

### 3. gRPC (Google Remote Procedure Call)
```
Protocol Buffers Schema:
─────────────────────────────────────────────────────────────
syntax = "proto3";

message User {
  string id = 1;
  string name = 2;
  string email = 3;
}

service UserService {
  rpc GetUser (GetUserRequest) returns (User);
  rpc CreateUser (CreateUserRequest) returns (User);
  rpc StreamUsers (StreamRequest) returns (stream User);
}
```

**Characteristics**:
- Binary protocol (Protocol Buffers)
- Highly efficient
- Strongly typed
- Supports streaming
- Service definition (proto files)

### 4. WebSocket
```
Connection:
─────────────────────────────────────────────────────────────
Client ──► WS Connection ──► Server
         ◄──────────────────
         
Bi-directional, real-time messaging
```

**Characteristics**:
- Full-duplex communication
- Persistent connection
- Low latency
- Real-time updates
- Server push capability

## REST API Best Practices

### 1. Resource Naming
```
Good:                              Bad:
─────────────────────────────────────────────────────────────
/users                             /getAllUsers
/users/123                         /getUserById
/users/123/orders                  /userOrders
/orders?status=pending            /getPendingOrders
POST /users                        POST /createUser
```

### 2. Use Plural Nouns
```
✓ /users
✓ /products
✓ /orders
✓ /order-items

✗ /user
✗ /product
```

### 3. Nested Resources
```
/users/123/orders              // Orders of user 123
/users/123/orders/456/items   // Items in order 456
/companies/123/departments    // Departments in company 123
```

### 4. Versioning
```
URL Versioning:
/api/v1/users
/api/v2/users

Header Versioning:
Accept: application/vnd.api.v1+json

Query Parameter:
/api/users?version=1
```

### 5. Pagination
```
GET /users?page=2&limit=20

Response:
{
  "data": [...],
  "pagination": {
    "currentPage": 2,
    "totalPages": 10,
    "totalCount": 200,
    "limit": 20
  }
}
```

### 6. Filtering, Sorting, Field Selection
```
Filtering:
GET /users?status=active&age=gt:25

Sorting:
GET /users?sort=created_at:desc

Field Selection:
GET /users?fields=id,name,email
```

## HTTP Status Codes

### Success Codes
```
┌─────────────────────────────────────────────────────────────┐
│  200 OK          │  Request succeeded                       │
│  201 Created    │  Resource created successfully           │
│  204 No Content │  Request succeeded, no content to return │
└─────────────────────────────────────────────────────────────┘
```

### Client Error Codes
```
┌─────────────────────────────────────────────────────────────┐
│  400 Bad Request   │  Invalid request syntax              │
│  401 Unauthorized  │  Authentication required              │
│  403 Forbidden     │  Access denied                        │
│  404 Not Found     │  Resource not found                   │
│  409 Conflict      │  Resource conflict                    │
│  422 Unprocessable │  Validation failed                     │
│  429 Too Many      │  Rate limit exceeded                  │
│                     │  Requests                             │
└─────────────────────────────────────────────────────────────┘
```

### Server Error Codes
```
┌─────────────────────────────────────────────────────────────┐
│  500 Internal Server Error │  Unexpected server error     │
│  502 Bad Gateway            │  Invalid response from upstream│
│  503 Service Unavailable    │  Server temporarily overloaded│
│  504 Gateway Timeout        │  Upstream timeout             │
└─────────────────────────────────────────────────────────────┘
```

## API Security

### 1. Authentication

#### API Keys
```
Request:
GET /api/data?api_key=your_api_key_here

Pros: Simple
Cons: Less secure, no user identification
```

#### JWT (JSON Web Tokens)
```
Header.Payload.Signature

Header: {"alg": "HS256", "typ": "JWT"}
Payload: {"sub": "123", "exp": 1234567890}
Signature: HMACSHA256(base64UrlEncode(header) + "." + 
              base64UrlEncode(payload), secret)
```

#### OAuth 2.0
```
Flow:
1. User clicks "Login with Google"
2. Redirect to Google OAuth
3. User grants permission
4. Callback with auth code
5. Exchange code for token
6. Use token for API calls
```

### 2. Rate Limiting
```
X-RateLimit-Limit: 1000
X-RateLimit-Remaining: 999
X-RateLimit-Reset: 1609459200
```

### 3. HTTPS
```
Always use HTTPS for:
- Encryption in transit
- Authentication
- Data integrity
```

### 4. Input Validation
```
Always validate:
- Request body
- Query parameters
- Headers
- File uploads
```

## API Documentation

### OpenAPI (Swagger) Example
```yaml
openapi: 3.0.0
info:
  title: User API
  version: 1.0.0
paths:
  /users:
    get:
      summary: Get all users
      parameters:
        - name: page
          in: query
          schema:
            type: integer
            default: 1
      responses:
        '200':
          description: Successful response
          content:
            application/json:
              schema:
                type: array
                items:
                  $ref: '#/components/schemas/User'
```

### Documentation Tools
- Swagger UI
- ReDoc
- Postman
- Slate
- Redocly

## API Gateway

```
┌─────────────────────────────────────────────────────────────┐
│                    API Gateway                               │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌─────────────────────────────────────────────────────┐ │
│  │                    API Gateway                        │ │
│  │                                                      │ │
│  │  ✓ Authentication                                    │ │
│  │  ✓ Rate Limiting                                     │ │
│  │  ✓ Request Routing                                   │ │
│  │  ✓ Protocol Translation                              │ │
│  │  ✓ Response Caching                                   │ │
│  │  ✓ Logging & Monitoring                              │ │
│  │  ✓ SSL Termination                                   │ │
│  └─────────────────────────────────────────────────────┘ │
│                           │                                 │
│         ┌─────────────────┼─────────────────┐              │
│         │                 │                 │              │
│         ▼                 ▼                 ▼              │
│   ┌─────────┐       ┌─────────┐       ┌─────────┐        │
│   │Service A│       │Service B│       │Service C│        │
│   └─────────┘       └─────────┘       └─────────┘        │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

Popular API Gateways:
- Kong
- AWS API Gateway
- Google Cloud Endpoints
- NGINX
- Apigee

## Versioning Strategies

### URL Path Versioning
```
/api/v1/users
/api/v2/users
```

### Header Versioning
```
Accept: application/vnd.myapp.v2+json
```

### Query Parameter
```
/api/users?version=2
```

### When to Version
- Breaking changes to response format
- Removing endpoints
- Changing field types
- Changing validation rules

## Error Handling

### Good Error Response
```json
{
  "error": {
    "code": "VALIDATION_ERROR",
    "message": "Invalid input data",
    "details": [
      {
        "field": "email",
        "message": "Invalid email format"
      },
      {
        "field": "password",
        "message": "Password must be at least 8 characters"
      }
    ],
    "requestId": "abc-123-def"
  }
}
```

## Interview Tips

1. **Know REST fundamentals** - Methods, status codes, best practices
2. **Understand when to use each API type** - REST, GraphQL, gRPC
3. **Be ready for security questions** - Auth, rate limiting
4. **Know versioning strategies** - URL, header, query
5. **Understand API Gateway role** - Why and when to use

## Summary

Key API Design Principles:

| Principle | Description |
|-----------|-------------|
| **Consistency** | Follow conventions |
| **Simplicity** | Keep APIs simple |
| **Discoverability** | Make it easy to explore |
| **Documentation** | Document everything |
| **Versioning** | Plan for changes |
| **Security** | Auth, rate limit, validate |
| **Error Handling** | Clear, consistent errors |
| **Performance** | Pagination, filtering, caching |
