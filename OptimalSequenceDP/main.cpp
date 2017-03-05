#include "dp_optseq.hpp"

class Penalty {
public:
	typedef unsigned int num_type;
	num_type operator()(num_type n, num_type s, num_type u) const {
		num_type scale = 1;
		if (s < 2) { scale = 1; }
		else if (s < 6) { scale = 2; }
		else if (s < 11) { scale = 3; }
		else if( s < 20 ){ scale = 4; }
		else { scale = 4; }
		return u*scale;
	}
};

class FinalCost {
public:
	typedef unsigned int num_type;
	num_type operator()(num_type s) const {
		num_type gamma = 100;
		int ds = 20 - static_cast<int>(s);
		return gamma*static_cast<num_type>(ds*ds);
	}
};

int main(int argc, char** argv) {

	// define cost functors
	Penalty p;
	FinalCost fc;

	// define solver
	dp::optimal_sequence os;
	os.setSequenceValueRange(1, 5);
	os.setSizeOfSequence(6);

	// compute optimal result
	unsigned int best_cost;
	dp::vec sequence = os.solve(p, fc, best_cost);

	// print results
	printf("Best cost is: %u\n", best_cost);
	printf("Best sequence is: [ ");
	for (int i = 0; i < sequence.size(); ++i) {
		if (i != 0) { printf(", "); }
		printf("%u",sequence[i]);
	}
	printf("]\n");

	return 0;
}

