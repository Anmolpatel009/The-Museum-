# HTTP/HTTPS Deep Dive

## What is HTTP?

HTTP (Hypertext Transfer Protocol) is the foundation of data communication on the World Wide Web. It defines how messages are formatted and transmitted between clients and servers.

```
┌─────────────────────────────────────────────────────────────┐
│                    HTTP Communication                        │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│    ┌─────────┐         HTTP Request         ┌─────────┐   │
│    │ Client  │ ───────────────────────────► │ Server  │   │
│    │(Browser)│ ◄─────────────────────────── │(Web)    │   │
│    └─────────┘         HTTP Response         └─────────┘   │
│                                                             │
│  Client: Makes request                                      │
│  Server: Responds with resources                           │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## HTTP Request Structure

```
┌─────────────────────────────────────────────────────────────┐
│                  HTTP Request Format                         │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌────────────────────────────────────────────────────────┐ │
│  │ METHOD /path HTTP/1.1                                  │ │
│  │ Host: example.com                                      │ │
│  │ User-Agent: Mozilla/5.0                                │ │
│  │ Accept: text/html                                      │ │
│  │ Accept-Language: en-US                                 │ │
│  │                                                       │ │
│  │ (request body for POST/PUT)                          │ │
│  └────────────────────────────────────────────────────────┘ │
│         │                │                │                   │
│         ▼                ▼                ▼                   │
│     Request Line     Headers        Optional Body            │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### HTTP Methods

| Method | Description | Idempotent |
|--------|------------|------------|
| GET | Retrieve resource | Yes |
| POST | Create resource | No |
| PUT | Update (replace) entire resource | Yes |
| PATCH | Partial update | No |
| DELETE | Remove resource | Yes |
| HEAD | Get headers only | Yes |
| OPTIONS | Get supported methods | Yes |

## HTTP Response Structure

```
┌─────────────────────────────────────────────────────────────┐
│                 HTTP Response Format                         │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌────────────────────────────────────────────────────────┐ │
│  │ HTTP/1.1 200 OK                                        │ │
│  │ Content-Type: text/html                               │ │
│  │ Content-Length: 1234                                  │ │
│  │ Server: Apache/2.4                                    │ │
│  │                                                       │ │
│  │ <html>...</html>                                      │ │
│  └────────────────────────────────────────────────────────┘ │
│         │                │                │                   │
│         ▼                ▼                ▼                   │
│     Status Line      Headers        Response Body             │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## HTTP Status Codes

### 1xx - Informational
```
100 Continue          - Client can continue with request
101 Switching Proto  - Server switching protocols
```

### 2xx - Success
```
200 OK               - Request succeeded
201 Created          - Resource created successfully
202 Accepted         - Request accepted for processing
204 No Content       - Success, no content to return
```

### 3xx - Redirection
```
301 Moved Permanently - Resource moved permanently
302 Found           - Resource temporarily elsewhere
304 Not Modified    - Use cached version
307 Temporary Redirect - Temporary, use same method
```

### 4xx - Client Errors
```
400 Bad Request     - Invalid syntax
401 Unauthorized    - Authentication required
403 Forbidden       - Access denied
404 Not Found       - Resource doesn't exist
405 Method Not Allowed - HTTP method not supported
429 Too Many Requests - Rate limit exceeded
```

### 5xx - Server Errors
```
500 Internal Server Error - Unexpected server error
502 Bad Gateway         - Invalid response from upstream
503 Service Unavailable - Server temporarily overloaded
504 Gateway Timeout     - Upstream timeout
```

## HTTP Headers

### Common Request Headers
```
Host: example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0)
Accept: text/html,application/json
Accept-Language: en-US,en;q=0.9
Accept-Encoding: gzip, deflate
Authorization: Bearer token123
Cookie: session_id=abc123
Referer: https://example.com/page
```

### Common Response Headers
```
Content-Type: text/html; charset=UTF-8
Content-Length: 12345
Content-Encoding: gzip
Cache-Control: max-age=3600
Set-Cookie: session=xyz; HttpOnly; Secure
ETag: "abc123"
Last-Modified: Wed, 21 Oct 2023 07:28:00 GMT
Server: Apache/2.4.41
```

### Custom Headers
```
X-Request-ID: abc-123-def
X-RateLimit-Limit: 100
X-RateLimit-Remaining: 95
X-Custom-Header: value
```

## HTTPS (HTTP Secure)

### How HTTPS Works
```
┌─────────────────────────────────────────────────────────────┐
│                  HTTPS Handshake                            │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. Client ──► Hello ──► Server                            │
│     (supported cipher suites)                              │
│                                                             │
│  2. Server ──► Certificate ──► Client                     │
│     (public key, signed by CA)                             │
│                                                             │
│  3. Client ──► Verify certificate                         │
│     (trusted CA list)                                      │
│                                                             │
│  4. Client ──► Pre-master secret (encrypted) ──► Server   │
│                                                             │
│  5. Both generate session keys                            │
│                                                             │
│  6. Encrypted communication begins                        │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### SSL/TLS Certificates
```
Certificate Chain:
─────────────────────────────────────────────────────────────
Root CA
    │
    ├──► Intermediate CA 1
    │       │
    │       └──► Intermediate CA 2
    │               │
    │               └──► Server Certificate
    │                        │
    │                        └──► example.com
```

### HTTPS Benefits
```
┌─────────────────────────────────────────────────────────────┐
│              HTTPS Benefits                                  │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. ENCRYPTION                                              │
│     - Data encrypted in transit                            │
│     - Cannot read intercepted data                         │
│                                                             │
│  2. AUTHENTICATION                                         │
│     - Verifies server identity                             │
│     - Prevents man-in-the-middle attacks                   │
│                                                             │
│  3. DATA INTEGRITY                                          │
│     - Detects tampering                                    │
│     - Ensures data not modified                            │
│                                                             │
│  4. SEO BENEFITS                                            │
│     - Google prefers HTTPS                                 │
│     - Better search rankings                               │
│                                                             │
│  5. TRUST                                                  │
│     - Browser shows secure indicator                       │
│     - Users trust HTTPS sites                              │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## HTTP/1.1 vs HTTP/2 vs HTTP/3

### HTTP/1.1
```
Characteristics:
─────────────────────────────────────────────────────────────
- Persistent connections (keep-alive)
- Pipelining (limited)
- Chunked transfer encoding
- Compression via headers only
- Text-based protocol

Problems:
- Head-of-line blocking
- Inefficient header compression
- No multiplexing
```

### HTTP/2
```
Improvements:
─────────────────────────────────────────────────────────────
- Multiplexing (multiple requests over single connection)
- Header compression (HPACK)
- Server push
- Binary protocol
- Stream prioritization

    ┌─────────────────────────────────────────────────────┐
    │         HTTP/1.1 vs HTTP/2                         │
    ├─────────────────────────────────────────────────────┤
    │                                                     │
    │ HTTP/1.1:                                          │
    │ ┌───┐ ┌───┐ ┌───┐ ┌───┐                          │
    │ │ R │ │ R │ │ R │ │ R │  (sequential)            │
    │ └───┘ └───┘ └───┘ └───┘                          │
    │                                                     │
    │ HTTP/2:                                            │
    │ ┌───────────────────────────────────────────────┐  │
    │ │ R │ R │ R │ R │  (parallel)                    │
    │ └───┴───┴───┴───┘                                │
    │                                                     │
    └─────────────────────────────────────────────────────┘
```

### HTTP/3
```
Major Change:
─────────────────────────────────────────────────────────────
- Uses QUIC instead of TCP
- Built on UDP
- Faster connection establishment
- No head-of-line blocking
- Better for mobile networks

Benefits:
- 0-RTT connection establishment
- Improved congestion control
- Connection migration
- Better packet loss handling
```

## Caching

### Cache-Control Headers
```
Cache-Control: max-age=3600           - Cache for 1 hour
Cache-Control: no-cache               - Must revalidate
Cache-Control: no-store                - Don't cache
Cache-Control: private                - Browser only
Cache-Control: public                  - Can be cached by proxies
Cache-Control: must-revalidate         - Must check stale
```

### ETag
```
Request:
GET /resource HTTP/1.1
If-None-Match: "abc123"

Response (unchanged):
304 Not Modified
ETag: "abc123"

Response (changed):
200 OK
ETag: "xyz789"
(body)
```

### Caching Flow
```
┌─────────────────────────────────────────────────────────────┐
│                  Caching Flow                                │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Client ──► Request ──► Cache?                            │
│                               │                            │
│              ┌────────────────┼────────────────┐           │
│              ▼                ▼                ▼           │
│          Fresh           Stale          Not in Cache       │
│              │                │                │            │
│              ▼                ▼                ▼            │
│          Return cached    Validate     Fetch from          │
│                           with server   server              │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## REST API Best Practices with HTTP

### URL Design
```
Good:                              Bad:
─────────────────────────────────────────────────────────────
GET  /users/123                   GET  /getUser?id=123
POST /users                       POST /createUser
PUT  /users/123                   POST /updateUser?id=123
DELETE /users/123                 POST /deleteUser?id=123
```

### Proper Status Codes
```
Create:         201 Created
Update:         200 OK or 204 No Content
Delete:         204 No Content
Not found:      404 Not Found
Auth failed:   401 Unauthorized
```

### Versioning
```
URL:     /api/v1/users
Header:  Accept: application/vnd.api.v1+json
Query:   /api/users?version=1
```

## Security Headers

```
┌─────────────────────────────────────────────────────────────┐
│               Security Headers                               │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Strict-Transport-Security: max-age=31536000              │
│  - Enforces HTTPS                                          │
│                                                             │
│  Content-Security-Policy: default-src 'self'              │
│  - Prevents XSS                                             │
│                                                             │
│  X-Content-Type-Options: nosniff                          │
│  - Prevents MIME sniffing                                  │
│                                                             │
│  X-Frame-Options: DENY                                     │
│  - Prevents clickjacking                                   │
│                                                             │
│  X-XSS-Protection: 1; mode=block                          │
│  - XSS filter (legacy browsers)                           │
│                                                             │
│  Referrer-Policy: strict-origin-when-cross-origin         │
│  - Controls referrer info                                  │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Interview Tips

1. **Know HTTP methods** - GET, POST, PUT, PATCH, DELETE
2. **Understand status codes** - 2xx, 3xx, 4xx, 5xx
3. **Know the difference between HTTP and HTTPS** - Encryption, TLS handshake
4. **Understand HTTP/2 improvements** - Multiplexing, header compression
5. **Know caching mechanisms** - Cache-Control, ETag, Last-Modified

## Summary

HTTP is the foundation of web communication:

- **Request/Response** model with methods and status codes
- **Stateless** protocol (each request independent)
- **HTTPS** adds security via TLS encryption
- **HTTP/2** adds multiplexing and header compression
- **HTTP/3** uses QUIC for better performance
- **Caching** improves performance significantly
- **Headers** control behavior and provide metadata
