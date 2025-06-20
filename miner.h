#pragma once

#include "block.h"
#include "picosha2.h"
#include <chrono>


class Miner {

	uint64_t nonce;
	Block& block;
	int difficulty;
	std::string hash;
	uint64_t timestamp;
	std::string miner_address;
	Transaction coinbase_tx;
	std::vector<Transaction> transactions;
	//std::string block_header;

public:

	Miner(Block& block, int difficulty, const std::string& miner_address) : block(block), miner_address(miner_address), coinbase_tx(Transaction({}, std::vector<TX_OUT>{TX_OUT{"a850c3cac93f501419a2029e087995607368dfc99ba851b9735d1ba8a955a028", 25}})) {

		this->difficulty = difficulty;
		nonce = 0;
		auto now = std::chrono::high_resolution_clock::now();
		timestamp = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();

	}

	std::string mine(std::string block_header) {

		transactions.push_back(coinbase_tx);

		std::string base;
		while (true) {
			base = picosha2::hash256_hex_string(block_header + std::to_string(timestamp) + std::to_string(nonce));
			if (base.substr(0, difficulty) == std::string(difficulty, '0')) break;
			nonce++;
		}

		block.set_hash(base);
		block.set_nonce(nonce);
		block.set_timestamp(timestamp);
		block.set_transactions(transactions);

		return base;

	}

};