#pragma once

#include <string>
#include <vector>
#include "picosha2.h"

struct TX_IN {
	std::string transaction_id;
	int output_index;

	TX_IN(const std::string transaction_id, int output_id) {
		this->transaction_id = transaction_id;
		this->output_index = output_id;
	}

	std::string get_once() const {
		return transaction_id + std::to_string(output_index);
	}
};

struct TX_OUT {
	std::string owner;
	uint64_t amount = 0;  // TEMP

	std::string get_once() const {
		return owner + std::to_string(amount);
	}
};

class Transaction {

	std::vector<TX_IN> inputs;
	std::vector<TX_OUT> outputs;
	std::string transaction_hash;

public:

	Transaction(std::vector<TX_IN>& in,const std::vector<TX_OUT>& out) {

		this->inputs = in;
		this->outputs = out;

		std::string base;
		for (const auto& in : inputs) base += in.get_once();
		for (const auto& out : outputs) base += out.get_once();

		transaction_hash = picosha2::hash256_hex_string(base);

	}

	std::string get_transaction_hash() const {
		return transaction_hash;
	}

	std::vector<TX_IN> get_inputs() const {
		return inputs;
	}
	std::vector<TX_OUT> get_outputs() const {
		return outputs;
	}

};