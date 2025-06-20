# Blockchain in C++

A minimal, educational blockchain implementation with Proof-of-Work mining
## This is a clean, easy-to-understand C++ blockchain implementation featuring:
- Proof-of-Work mining
- UTXO (Unspent Transaction Output) model
- Transaction validation
- Customizable mining difficulty

## Perfect for learning how blockchains work at a fundamental level!

Quick Start

- Clone & Compile
``` bash
git clone https://github.com/your-repo/simple-blockchain-cpp.git
cd simple-blockchain-cpp
g++ -std=c++17 main.cpp blockchain.cpp block.cpp transaction.cpp miner.cpp -o blockchain
```
- Run It!
``` bash

./blockchain


```
## Key Components

| File  | Purpose |
| ------------- | ------------- |
| blockchain.h/cpp  | Core chain logic (adding blocks, managing UTXOs) |
| block.h/cpp | Block structure (header + transactions) |
| transaction.h/cpp | Transactions (inputs/outputs) |
| miner.h/cpp | Proof-of-Work mining implementation |

## Example Usage

```bash
// 1. Create blockchain (difficulty = 2)
Blockchain blockchain(2);

// 2. Make genesis block
blockchain.createGenesisBlock();

// 3. Create transaction
Transaction tx = blockchain.createTransaction(
    "shaik_wallet", 
    "satoshi_wallet", 
    5
);

// 4. Mine block with transaction
Block newBlock(blockchain.getLatestBlock().getHash(), {tx});
Miner miner(newBlock, blockchain.getDifficulty(), "miner_wallet");
miner.mine(newBlock.getBlockHeader(), {tx});

// 5. Add to chain
blockchain.addBlock(newBlock);

```

## Customization
- Change Mining Difficulty
```bash
Blockchain blockchain(3); // Higher = harder to mine
```
## Limitations
- No real cryptography (addresses are just strings)
- Single-node only (no P2P networking)
- Basic error handling

## Why this exists
### I built this to:
  - Learn blockchain fundamentals
  - Have clean, readable reference code
  - Help others understand how blockchains work

_Everything by Marwaan, I jusy wanted to test my c++ skills, that's it_
