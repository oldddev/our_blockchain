#pragma once

#include <vector>
#include <iostream>
#include <unordered_map>
#include "block.h"
#include "miner.h"
#include "transaction.h"

class Blockchain {

	std::vector<Block> blocks;
	std::unordered_map<std::string, TX_OUT> utxo;
	int diffculty = 2;

	std::string name = "SHAIKALI";

	std::string my_addr = picosha2::hash256_hex_string(name);

	// Genesis block creation
public:

	void create_genesis() {
		std::cout << my_addr << "\n";
		std::vector<TX_IN> txin{};
		Transaction coinbase_tx(txin, {TX_OUT{my_addr, 1000}});
		Block genesis_block("0", {coinbase_tx});
		Miner miner(genesis_block, diffculty);
		miner.mine(genesis_block.get_block_header());
		if (validate_block(genesis_block)) {
			std::cout << "[DEBUG] VALID BLOCK\n";
			blocks.push_back(genesis_block);
				update_utxo(coinbase_tx);
		}
		else {
			std::cout << "[DEBUG] NOT-VALID BLOCK\n";
		}
		std::cout << "[DEBUG] GENESIS BLOCK CREATED: " << genesis_block.get_hash() << std::endl;

	}
	bool add_block(Block& block) {
		if (!validate_block(block)) {
			std::cout << "[DEBUG] BLOCK VALIDATION FAILED!\n";
			return false;
		}

		// Check previous hash matches latest block
		if (block.get_prev_hash() != blocks.back().get_hash()) {
			std::cout << "[DEBUG] PREVIOUS HASH DON'T MATCH!\n";
			std::cout << "[DEBUG] Expected: " << blocks.back().get_hash() << " Got: " << block.get_prev_hash() << "\n";
			return false;
		}

		// Verify the block's hash is correct
		std::string calculated_hash = picosha2::hash256_hex_string(
			block.get_block_header() + std::to_string(block.get_nonce()));

		if (calculated_hash != block.get_hash()) {
			std::cout << "[DEBUG] INVALID BLOCK HASH!\n";
			std::cout << "[DEBUG] Expected: " << calculated_hash
				<< " Got: " << block.get_hash() << "\n";
			return false;
		}

		blocks.push_back(block);

		// Update UTXO for all transactions in the block
		for (auto& tx : block.get_transactions()) {
			update_utxo(tx);
		}

		std::cout << "[DEBUG] BLOCK ADDED SUCCESSFULLY!\n";
		return true;
	}
	bool validate_block(Block& block) {
		// Check if block hash meets difficulty requirement
		std::string block_hash = block.get_hash();
		if (block_hash.substr(0, diffculty) != std::string(diffculty, '0')) {
			std::cout << "[DEBUG] BLOCK HASH DOESN'T MEET DIFFICULTY REQUIREMENT\n";
			return false;
		}

		// Validate all transactions
		for (auto& tx : block.get_transactions()) {
			if (!validate_transaction(tx)) {
				std::cout << "[DEBUG] TRANSACTION VALIDATION FAILED\n";
				return false;
			}
		}

		// Remove the blocks.push_back(block) that was here before
		return true;
	}

	bool validate_transaction(Transaction& tx) {

		uint64_t input_sum = 0;
		uint64_t output_sum = 0;

		if (tx.get_inputs().empty()) return true;

		for (auto& in : tx.get_inputs()) {
			std::string utxo_key = in.transaction_id + ":" + std::to_string(in.output_index);

			if (utxo.find(utxo_key) == utxo.end()) {
				std::cout << "INAVLID UTXO KEY RECEIVED: " << utxo_key << std::endl;
				return false;
			}

			input_sum += utxo[utxo_key].amount;
		}

		for (auto& out : tx.get_outputs()) {
			output_sum += out.amount;
		}

		if (input_sum < output_sum) return false;

		return true;
	}

	void update_utxo(Transaction& tx) {

		// Removed Spent Unspents

		for (auto& in : tx.get_inputs()) {
			utxo.erase(in.get_once());
		}

		// Add New Unspents

		for (size_t i = 0; i < tx.get_outputs().size(); i++) {
			std::string key = tx.get_transaction_hash() + ":" + std::to_string(i);
			utxo[key] = tx.get_outputs()[i];
		}
	}

	Block& get_latest_block() {
		return blocks.back();
	}
	int get_difficulty() const {
		return diffculty;
	}

};