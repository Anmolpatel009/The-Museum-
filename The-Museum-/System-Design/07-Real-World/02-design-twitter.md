# Design Twitter

## Problem Statement

Design a system like Twitter where users can:
- Post tweets (up to 280 characters)
- Follow other users
- View their timeline (feed of tweets from followed users)
- Like, retweet, and reply to tweets

## Requirements Analysis

### Functional Requirements
```
┌─────────────────────────────────────────────────────────────┐
│              Functional Requirements                         │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. POST TWEET                                              │
│     - User posts tweet (text, media)                        │
│     - Max 280 characters                                   │
│     - Support images, videos                                │
│     - Timestamp                                            │
│                                                             │
│  2. TIMELINE                                                │
│     - Home timeline: tweets from followed users             │
│     - User timeline: user's own tweets                      │
│     - Chronological or ranked                               │
│                                                             │
│  3. FOLLOW SYSTEM                                           │
│     - Follow/unfollow users                                 │
│     - Follower/following counts                             │
│                                                             │
│  4. SOCIAL ACTIONS                                          │
│     - Like tweets                                           │
│     - Retweet                                               │
│     - Reply to tweets                                       │
│     - Quote tweet                                           │
│                                                             │
│  5. SEARCH & DISCOVERY                                      │
│     - Search tweets by keyword                              │
│     - Trending topics                                       │
│                                                             │
│  6. USER PROFILES                                           │
│     - Profile info, bio, location                          │
│     - Profile picture                                       │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Non-Functional Requirements
```
┌─────────────────────────────────────────────────────────────┐
│           Non-Functional Requirements                       │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  PERFORMANCE                                                │
│  - Timeline generation < 200ms                             │
│  - Tweet posting < 500ms                                   │
│  - Support 500M+ users                                     │
│                                                             │
│  AVAILABILITY                                               │
│  - 99.99% uptime                                           │
│  - Handle regional failures                                │
│                                                             │
│  SCALABILITY                                                │
│  - 150M+ daily active users                                │
│  - 500M+ tweets per day                                    │
│  - Handle peak traffic (events)                           │
│                                                             │
│  CONSISTENCY                                                │
│  - Eventual consistency for timeline                       │
│  - Strong consistency for user actions                     │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## High-Level Architecture

```
┌─────────────────────────────────────────────────────────────┐
│              Twitter High-Level Architecture                 │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│                      ┌──────────────┐                      │
│                      │   CDN        │                      │
│                      │ (Media)      │                      │
│                      └──────┬───────┘                      │
│                             │                               │
│         ┌───────────────────┼───────────────────┐           │
│         │                   │                   │           │
│         ▼                   ▼                   ▼           │
│  ┌─────────────┐    ┌─────────────┐    ┌─────────────┐     │
│  │   Web      │    │   Mobile   │    │   API      │     │
│  │   App      │    │   App      │    │   Gateway   │     │
│  └──────┬──────┘    └──────┬──────┘    └──────┬──────┘     │
│         │                  │                  │             │
│         └──────────────────┼──────────────────┘            │
│                            │                                │
│                            ▼                                │
│         ┌──────────────────────────────────────┐           │
│         │         Service Layer                 │           │
│         │  ┌──────────┐ ┌──────────┐ ┌───────┐ │           │
│         │  │  Tweet   │ │  User   │ │ Feed  │ │           │
│         │  │ Service  │ │ Service  │ │Service│ │           │
│         │  └──────────┘ └──────────┘ └───────┘ │           │
│         └──────────────────┬──────────────────────┘           │
│                            │                                │
│         ┌──────────────────┼──────────────────────┐         │
│         │                  │                      │         │
│         ▼                  ▼                      ▼         │
│  ┌─────────────┐    ┌─────────────┐    ┌─────────────┐    │
│  │   MySQL     │    │   Redis    │    │   Hadoop    │    │
│  │ (Primary)   │    │   Cache    │    │  (Analytics)│    │
│  └─────────────┘    └─────────────┘    └─────────────┘    │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Database Schema

### Users Table
```sql
CREATE TABLE users (
    id BIGINT PRIMARY KEY,
    username VARCHAR(15) UNIQUE,
    email VARCHAR(255) UNIQUE,
    password_hash VARCHAR(255),
    display_name VARCHAR(50),
    bio VARCHAR(160),
    location VARCHAR(100),
    profile_image_url VARCHAR(500),
    created_at TIMESTAMP,
    updated_at TIMESTAMP
);
```

### Tweets Table
```sql
CREATE TABLE tweets (
    id BIGINT PRIMARY KEY,
    user_id BIGINT REFERENCES users(id),
    text VARCHAR(280),
    media_urls JSON,
    in_reply_to_tweet_id BIGINT,
    in_reply_to_user_id BIGINT,
    retweet_of_tweet_id BIGINT,
    created_at TIMESTAMP,
    deleted_at TIMESTAMP
);

-- Index for timeline queries
CREATE INDEX idx_tweets_user_time 
    ON tweets(user_id, created_at DESC);
```

### Follows Table
```sql
CREATE TABLE follows (
    follower_id BIGINT REFERENCES users(id),
    followee_id BIGINT REFERENCES users(id),
    created_at TIMESTAMP,
    PRIMARY KEY (follower_id, followee_id)
);

-- Index for getting followers
CREATE INDEX idx_followers ON follows(followee_id);
CREATE INDEX idx_following ON follows(follower_id);
```

### Likes Table
```sql
CREATE TABLE likes (
    user_id BIGINT REFERENCES users(id),
    tweet_id BIGINT REFERENCES tweets(id),
    created_at TIMESTAMP,
    PRIMARY KEY (user_id, tweet_id)
);
```

## Key System Components

### 1. Tweet Service
```
Tweet Service:
─────────────────────────────────────────────────────────────
POST /tweet
  1. Validate tweet (length, content)
  2. Store in database
  3. Add to user's timeline cache
  4. Push to followers (async)
  5. Return tweet ID

Flow:
User ──► API ──► Tweet Service ──► DB
                │
                └─► Fan-out Service ──► Timeline Cache
                                         │
                        Followers' Home Timelines
```

### 2. Timeline Service
```
Timeline Generation:
─────────────────────────────────────────────────────────────
Two approaches:

1. PULL (Fan-out on read)
   - Get list of followed users
   - Fetch tweets from each user
   - Merge and sort
   - +: Simple, real-time
   - -: Slow at read time

2. PUSH (Fan-out on write)
   - When user tweets, push to all followers
   - Store in cache
   - +: Fast read
   - -: Slow write, slower follower propagation

Hybrid Approach:
- Active users: Push (pre-compute timeline)
- Inactive users: Pull on read
```

### 3. Social Graph Service
```
Follow/Unfollow Flow:
─────────────────────────────────────────────────────────────
POST /follow
  1. Validate user exists
  2. Check not already following
  3. Add to follows table
  4. Update follower/following counts
  5. Trigger timeline fan-out

POST /unfollow
  1. Remove from follows table
  2. Update counts
  3. Remove from timeline cache
```

## Caching Strategy

```
Timeline Cache:
─────────────────────────────────────────────────────────────
Key: "timeline:user_id"
Value: List of tweet IDs (ordered)
Size: Last 1000 tweets per user

Cache Invalidation:
- When user posts tweet
- When user unfollows someone
- TTL: 24 hours

Read Cache:
─────────────────────────────────────────────────────────────
- User profiles (Redis)
- Tweet content (Redis - hot tweets)
- Follower/following counts
```

## Scalability Considerations

### Write Path (Fan-out)
```
For each follower:
1. Get follower's home timeline key
2. Prepend new tweet ID
3. Trim to max size (1000)
4. Set with TTL

If follower has 1M followers:
- Async processing
- Message queue
- Rate limiting on writes
```

### Read Path
```
Timeline Request:
1. Get user's cached timeline
2. If empty or stale, pull from DB
3. Paginate results
4. Fetch tweet content from cache
5. Return to user
```

## Handling High Traffic

### Trending Topics
```
Trending Service:
─────────────────────────────────────────────────────────────
1. Count mentions of hashtags/keywords
2. Time decay (recent tweets weighted more)
3. Store in Redis sorted sets
4. Update every 5 minutes
5. Serve from cache
```

### Media Handling
```
Media Upload:
─────────────────────────────────────────────────────────────
1. User uploads image/video
2. Upload to object storage (S3)
3. Store media URL in tweet
4. CDN for delivery
5. Generate multiple sizes for thumbnails
```

## API Design

```
REST Endpoints:
─────────────────────────────────────────────────────────────
POST   /tweets                    - Create tweet
GET    /tweets/:id                - Get tweet
DELETE /tweets/:id                - Delete tweet
POST   /tweets/:id/like           - Like tweet
DELETE /tweets/:id/like           - Unlike tweet
POST   /tweets/:id/retweet        - Retweet

GET    /users/:id/timeline        - User's tweets
GET    /users/:id/home_timeline   - Home timeline
GET    /users/:id/followers       - Get followers
GET    /users/:id/following       - Get following
POST   /users/:id/follow          - Follow user
DELETE /users/:id/follow          - Unfollow user

GET    /search?q=query            - Search tweets
```

## Trade-offs and Decisions

```
┌─────────────────────────────────────────────────────────────┐
│              Key Design Decisions                             │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. TIMELINE: PUSH vs PULL                                  │
│     Decision: Hybrid approach                               │
│     - Active users: Push                                    │
│     - Inactive users: Pull                                  │
│                                                             │
│  2. CONSISTENCY: Strong vs Eventual                         │
│     Decision: Eventual for timeline                        │
│     - Faster writes                                         │
│     - Accept delay in timeline                              │
│                                                             │
│  3. DATABASE: SQL vs NoSQL                                  │
│     Decision: Hybrid                                        │
│     - User data, tweets: MySQL (relational)                │
│     - Timeline cache: Redis                                 │
│     - Search: Elasticsearch                                 │
│                                                             │
│  4. MEDIA STORAGE                                          │
│     Decision: Object storage + CDN                          │
│     - S3 for storage                                        │
│     - CloudFront for delivery                               │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Interview Follow-up Questions

### 1. How would you handle 10x traffic spike?
- Auto-scaling groups
- Rate limiting
- Queue-based processing
- Degrade non-essential features

### 2. How would you implement search?
- Elasticsearch
- Index tweets asynchronously
- Rank by relevance and recency

### 3. How would you handle deleted tweets?
- Soft delete (mark as deleted)
- Keep in DB with deleted_at
- Remove from all timeline caches

### 4. How would you prevent spam?
- Rate limiting
- Content analysis
- User reporting
- Machine learning classifiers

## Summary

Twitter System Design Key Points:

| Component | Approach |
|-----------|----------|
| **Database** | MySQL for user/tweet data |
| **Caching** | Redis for timelines |
| **Timeline** | Hybrid push/pull |
| **Media** | S3 + CDN |
| **Search** | Elasticsearch |
| **Write Path** | Async fan-out via message queue |
| **Read Path** | Pre-computed timeline cache |

The design prioritizes:
- **Fast reads** through pre-computed timelines
- **Scalability** through asynchronous fan-out
- **Availability** through caching and redundancy
- **Consistency** trade-offs for better performance
