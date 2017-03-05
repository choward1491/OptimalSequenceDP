
#include "dp_optseq.hpp"

namespace dp {



	void optimal_sequence::setSequenceValueRange(unsigned int startval, unsigned int endval)
	{
		unsigned int Nv = (endval - startval + 1);
		if (seq_range.size() != Nv) { seq_range.resize(Nv); }
		for (unsigned int i = startval; i <= endval; ++i) {
			seq_range[i-startval] = i;
		}
	}

	void optimal_sequence::setSizeOfSequence(int Ns)
	{
		size_seq = Ns;
	}

	void optimal_sequence::init_optimal_structures()
	{
		V_opt.resize(size_seq+1);
		u_opt.resize(size_seq);
		unsigned int Nv = seq_range.size();
		const unsigned int lb = seq_range[0], ub = seq_range[Nv - 1];

		V_opt[0].resize(1,0);
		for (int i = 0; i < size_seq; ++i) {
			unsigned int size = (i + 1)*(ub - lb) + 1;
			V_opt[i+1].resize(size);
			for (unsigned int k = 0; k < size; ++k) { V_opt[i + 1][k] = (i + 1)*lb + k; }
			u_opt[i].resize(size,0);
		}

	}

}