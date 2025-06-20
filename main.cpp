#include "blockchain.h"
#include "miner.h"

int main() {
	Blockchain blockchain;
	blockchain.create_genesis();

	for (size_t i = 0; i < 10; i++) {

		// Get latest block hash to link the new block
		std::string prev_hash = blockchain.get_latest_block().get_hash();


		// For now: empty txs
		Block block_to_mine(prev_hash, {});

		// Mine it
		Miner miner(block_to_mine, blockchain.get_difficulty(), "a850c3cac93f501419a2029e087995607368dfc99ba851b9735d1ba8a955a028");
		miner.mine(block_to_mine.get_block_header());

		// Validate and add
		if (blockchain.validate_block(block_to_mine)) {
			blockchain.add_block(block_to_mine);
			//std::cout << "[+] BLOCK MINED AND ADDED!\n";
		}
		else {
			//std::cout << "[x] INVALID BLOCK, SKIPPED.\n";
		}

	}

	blockchain.get_blocks_hash();

	std::cin.get();
	return 0;
}
 