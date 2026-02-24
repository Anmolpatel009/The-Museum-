# Smart Contracts Introduction

## What are Smart Contracts?

Smart contracts are self-executing programs stored on a blockchain that automatically enforce terms when predefined conditions are met. They are:
- **Self-executing**: Automatic when conditions are met
- **Trustless**: No intermediaries needed
- **Transparent**: Visible to all participants
- **Immutable**: Cannot be changed once deployed
- **Deterministic**: Same input = same output

```
┌─────────────────────────────────────────────────────────────┐
│               Smart Contract Concept                         │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Traditional Contract:           Smart Contract:            │
│  ┌─────────────────┐            ┌─────────────────┐       │
│  │ Lawyer          │            │ Code            │       │
│  │                 │            │                 │       │
│  │ "If X, then Y"  │            │ if (X) { Y }    │       │
│  │                 │            │                 │       │
│  │ Trust needed    │            │ Trust in code   │       │
│  │ Manual          │            │ Automatic       │       │
│  │ Slow            │            │ Fast            │       │
│  └─────────────────┘            └─────────────────┘       │
│                                                             │
│  Example: Escrow                                           │
│  If buyer confirms → release funds to seller              │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## How Smart Contracts Work

```
┌─────────────────────────────────────────────────────────────┐
│            Smart Contract Execution Flow                      │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. Write contract in code                                 │
│     (e.g., Solidity for Ethereum)                          │
│                                                             │
│  2. Deploy to blockchain                                   │
│     (pay gas fee for deployment)                           │
│                                                             │
│  3. Contract has address on chain                        │
│     (like an account, can hold funds)                     │
│                                                             │
│  4. Someone triggers a transaction                        │
│     (calls a function)                                     │
│                                                             │
│  5. Nodes validate and execute                             │
│     (EVM processes the code)                              │
│                                                             │
│  6. State is updated                                       │
│     (balances, data change)                                │
│                                                             │
│  7. All nodes see the result                              │
│     (transparent, verifiable)                              │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Smart Contract Example

### Simple Escrow Contract
```solidity
// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract Escrow {
    address public buyer;
    address public seller;
    address public arbiter;
    bool public released;
    
    // Funds held in contract
    uint256 public amount;
    
    constructor(address _seller, address _arbiter) {
        buyer = msg.sender;
        seller = _seller;
        arbiter = _arbiter;
        released = false;
    }
    
    // Buyer deposits funds
    function deposit() external payable {
        require(msg.sender == buyer, "Only buyer");
        amount = msg.value;
    }
    
    // Release funds to seller
    function release() external {
        require(msg.sender == arbiter, "Only arbiter");
        require(!released, "Already released");
        require(amount > 0, "No funds");
        
        released = true;
        payable(seller).transfer(amount);
    }
    
    // Refund to buyer
    function refund() external {
        require(msg.sender == arbiter, "Only arbiter");
        require(!released, "Already released");
        
        released = true;
        payable(buyer).transfer(amount);
    }
}
```

## Smart Contract Use Cases

### 1. Decentralized Finance (DeFi)
```
┌─────────────────────────────────────────────────────────────┐
│                  DeFi Use Cases                             │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  LENDING PROTOCOLS                                          │
│  - Users supply collateral                                 │
│  - Borrow against collateral                                │
│  - Interest rates algorithmically set                      │
│  - No credit checks                                         │
│                                                             │
│  DECENTRALIZED EXCHANGES (DEX)                             │
│  - Trade without intermediaries                            │
│  - Automated market makers (AMM)                          │
│  - Liquidity pools                                        │
│                                                             │
│  STABLECOINS                                               │
│  - Pegged to real-world assets                             │
│  - Algorithmically or collateralized                       │
│                                                             │
│  YIELD FARMING                                             │
│  - Maximize returns across protocols                       │
│  - Liquidity mining incentives                            │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### 2. NFTs (Non-Fungible Tokens)
```
Digital ownership of unique items:
─────────────────────────────────────────────────────────────
- Digital art
- In-game items
- Domain names
- Tickets
- Certificates
- Music/Video rights

Each NFT is unique - stored on chain with metadata
```

### 3. Supply Chain
```
Track products from origin to consumer:
─────────────────────────────────────────────────────────────
- Verify authenticity
- Track location
- Verify conditions (temperature, etc)
- Automated payments

Example: Tracking diamonds, food, pharmaceuticals
```

### 4. Gaming
```
Play-to-earn games:
─────────────────────────────────────────────────────────────
- Own in-game assets (NFTs)
- Trade on open markets
- Interoperable between games
- True ownership (not controlled by game company)
```

### 5. Insurance
```
Automated claims:
─────────────────────────────────────────────────────────────
- Flight delayed? Auto-refund
- Crop failed? Auto-payment
- Natural disaster? Instant payout

Oracle data feeds trigger smart contracts
```

### 6. Voting
```
Transparent, verifiable voting:
─────────────────────────────────────────────────────────────
- Anonymity preserved
- Results publicly verifiable
- No voter fraud possible
- Instant tallying
```

## Smart Contract Platforms

### Ethereum
```
First and most popular:
─────────────────────────────────────────────────────────────
- Turing complete
- Large ecosystem
- EVM (Ethereum Virtual Machine)
- Solidity programming language

Other EVM chains:
- Polygon
- BSC
- Avalanche
- Arbitrum
- Optimism
```

### Other Platforms
```
Solana: High speed, lower cost
─────────────────────────────────────────────────────────────
- Rust programming language
- PoH consensus
- 65k TPS theoretical

Cardano: Research-based
─────────────────────────────────────────────────────────────
- Haskell/Plutus
- Academic peer-reviewed
- Slow but rigorous

Near: Developer friendly
─────────────────────────────────────────────────────────────
- Rust/AssemblyScript
- sharding (Nightshade)
- Easy to learn
```

## Gas and Fees

### What is Gas?
```
┌─────────────────────────────────────────────────────────────┐
│                  Gas Concept                                 │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  Gas = computational work unit                             │
│                                                             │
│  Each operation costs gas:                                 │
│  - Storage write: ~20,000 gas                              │
│  - Storage read: ~200 gas                                  │
│  - Simple addition: ~3 gas                                │
│  - Function call: varies                                   │
│                                                             │
│  Total Fee = Gas Used × Gas Price                          │
│                                                             │
│  Gas Price = Base Fee + Priority Fee                       │
│  (Base fee burns, priority goes to validator)             │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Gas Optimization
```
Common optimizations:
─────────────────────────────────────────────────────────────
- Use mappings instead of arrays
- Delete unused variables
- Batch storage writes
- Use events instead of storage for logging
- Short-circuit boolean expressions
- Cache storage reads
```

## Smart Contract Limitations

```
┌─────────────────────────────────────────────────────────────┐
│                   Limitations                                │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ✗ IMPUTABILITY                                            │
│     Bugs can't be fixed                                    │
│     Must migrate to new contract                            │
│                                                             │
│  ✗ ORACLE PROBLEM                                          │
│     Smart contracts can't access off-chain data            │
│     Need oracles (Chainlink, Band)                         │
│                                                             │
│  ✗ SCALABILITY                                             │
│     Limited by blockchain TPS                              │
│     Layer 2 helps                                          │
│                                                             │
│  ✗ COMPLEXITY                                              │
│     Writing secure contracts is hard                       │
│     Audit costs money                                      │
│                                                             │
│  ✗ LEGAL RECOGNITION                                       │
│     Not legally binding in most countries                  │
│     Smart contracts ≠ legal contracts                      │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## Security Considerations

### Common Vulnerabilities
```
1. REENTRANCY
   - Calling external contract before state update
   - TheDAO hack ($60M)
   
2. OVERFLOW/UNDERFLOW
   - Integer overflow in Solidity < 0.8
   
3. ACCESS CONTROL
   - Missing modifiers, weak ownership
   
4. FRONT-RUNNING
   - Transactions visible in mempool
   
5. ORACLE MANIPULATION
   - Manipulating price feeds
```

### Security Best Practices
```
✓ Use SafeMath (older Solidity)
✓ Check-Effects-Interactions pattern
✓ Use ReentrancyGuard
✓ Proper access control
✓ Comprehensive testing
✓ Professional audits
✓ Timelocks for admin actions
✓ Upgradeable contracts (with care)
```

## Interview Tips

1. **Know what smart contracts are** - Self-executing code on chain
2. **Understand use cases** - DeFi, NFTs, supply chain
3. **Know about gas** - How fees work
4. **Understand limitations** - Oracle problem, immutability
5. **Know common vulnerabilities** - Reentrancy, overflow
6. **Be ready to write simple contract** - In Solidity

## Summary

Smart contracts enable:
- **Trustless agreements** - No intermediaries
- **Automation** - Automatic execution
- **Transparency** - Visible to all
- **Programmable money** - DeFi revolution

Key platforms:
- **Ethereum** - Most popular, largest ecosystem
- **Solana** - Fast, cheap
- **Polygon** - Ethereum Layer 2

Challenges:
- **Security** - Bugs are permanent
- **Oracles** - Need off-chain data
- **Scalability** - Limited by blockchain
- **Legal** - Not recognized as legal contracts
