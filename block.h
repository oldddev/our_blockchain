#pragma once

#include <string>
#include <vector>
#include "transaction.h"

class Block {

	std::string prev_hash;
	std::string hash;
	std::vector<Transaction> transactions;
	uint64_t nonce;

public:

	Block(const std::string& prev_hash, const std::vector<Transaction>& txs) : prev_hash(prev_hash), transactions(txs) {
		nonce = 0;
	}

	void set_hash(const std::string& hash) {
		this->hash = hash;
	}

	void set_nonce(const uint64_t& nonce) {
		this->nonce = nonce;
	}

	std::string get_hash() const {
		return hash;
	}

	std::vector<Transaction> get_transactions() {
		return transactions;
	}

	std::string get_block_header() {
		std::string base = prev_hash;
		for (const auto& tx : transactions) {
			base += tx.get_transaction_hash();
		}
		return base;
	}

	std::string get_prev_hash() const {
		return prev_hash;
	}

	uint64_t get_nonce() const {
		return nonce;
	}
	
};