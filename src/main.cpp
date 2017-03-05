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

	FinalCost() :des_val(20) {}
	
	void setDesiredSumValue(int desv) { des_val = desv; }

	num_type operator()(num_type s) const {
		num_type gamma = 100;
		int ds = des_val - static_cast<int>(s);
		return gamma*static_cast<num_type>(ds*ds);
	}
private:
	int des_val;
};

int main(int argc, char** argv) {

	// define cost functors
	Penalty p;
	FinalCost fc;
	fc.setDesiredSumValue(20);

	// define solver
	dp::optimal_sequence os;
	os.setSequenceValueRange(1, 5);
	os.setSizeOfSequence(15);

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

	// test sequence - for validation of P(.) implementation
	unsigned int ts[6] = {1, 2, 3, 4, 5, 5};
	unsigned int s = 0;
	unsigned int cost = 0;

	for (int i = 0; i < 6; ++i) {
		cost += p(i, s, ts[i]);
		s += ts[i];
	}

	return 0;
}

