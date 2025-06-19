#pragma once

#include "block.h"
#include "picosha2.h"

class Miner {

	uint64_t nonce;
	Block& block;
	int difficulty;
	std::string hash;
	//std::string block_header;

public:

	Miner(Block& block, int difficulty) : block(block) {
		this->difficulty = difficulty;
		nonce = 0;

	}

	std::string mine(std::string block_header) {

		std::cout << "BLOCK HEADER: " << block_header << "\n";

		std::string base;
		while (true) {
			base = picosha2::hash256_hex_string(block_header + std::to_string(nonce));
			if (base.substr(0, difficulty) == std::string(difficulty, '0')) break;
			nonce++;
		}

		block.set_hash(base);
		block.set_nonce(nonce);

		return base;

	}

};