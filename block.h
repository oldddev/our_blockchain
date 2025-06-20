#pragma once

#include <string>
#include <vector>
#include <chrono>
#include "transaction.h"

class Block {

	std::string prev_hash;
	std::string hash;
	uint64_t timestamp;
	std::vector<Transaction> transactions;
	uint64_t nonce;

public:

	Block(const std::string& prev_hash, const std::vector<Transaction>& txs) : prev_hash(prev_hash), transactions(txs) {

		nonce = 0;
		auto now = std::chrono::high_resolution_clock::now();
		timestamp = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
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

	void set_transactions(const std::vector<Transaction>& txs) {
		transactions = txs;
	}

	std::string get_block_header() {
		std::string base = prev_hash;
		return base;
	}

	std::string get_prev_hash() const {
		return prev_hash;
	}

	uint64_t get_nonce() const {
		return nonce;
	}

	void set_timestamp(uint64_t& time) {
		timestamp = time;
	}
	uint64_t get_timestamp() const {
		return timestamp;
	}
	
};