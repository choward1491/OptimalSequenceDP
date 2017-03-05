#ifndef _dp_optseq_hpp_
#define _dp_optseq_hpp_

#include <vector>

namespace dp {

	typedef std::vector<unsigned int> vec;

	class optimal_sequence {
	public:

		void setSequenceValueRange(unsigned int startval, unsigned int endval);
		void setSizeOfSequence(int Ns);

		template<class Penalty, class FinalCost>
		vec solve(const Penalty & p, const FinalCost & c, unsigned int & best_cost);

	private:

		vec seq_range;
		int size_seq;
		std::vector<vec> V_opt;
		std::vector<vec> u_opt;

		// helper stuff
		void init_optimal_structures();

	};


	template<class Penalty, class FinalCost>
	inline vec optimal_sequence::solve(const Penalty & p, const FinalCost & c, unsigned int & best_cost)
	{
		init_optimal_structures();
		vec opt_seq(size_seq);

		{
			// compute helper variables
			unsigned int Nv = seq_range.size();
			const unsigned int lb = seq_range[0], ub = seq_range[Nv - 1];
			unsigned int lcost = 0, bcost = 0, best_u = 0;

			// compute final condition
			for (size_t i = 0; i < V_opt[size_seq].size(); ++i) {
				V_opt[size_seq][i] = c(size_seq*lb + i);
			}

			// recursively compute optimal cost and policy
			for (int n = size_seq - 1; n >= 0; --n) {

				// compute number of states at step n and helper vars
				size_t Ns = n*(ub - lb) + 1;
				size_t offset	= n*lb;
				size_t offset_n = (n + 1)*lb;

				// loop through states at sequence n
				for (size_t k = 0; k < Ns; ++k) {
					unsigned int s = offset + k; // set current state
					V_opt[n][k] = 0xFFFFFFFF; // init with max value
					

					// loop through possible sequence values
					for (size_t uidx = 0; uidx < Nv; ++uidx) {
						unsigned int u = seq_range[uidx]; // set current choice
						lcost = p(n, s, u) + V_opt[n + 1][s + u - offset_n];
						if (lcost < V_opt[n][k]) {
							V_opt[n][k]	= lcost;
							u_opt[n][k]	= u;
						}
					}// end for uidx
				}// end for k
			}// end for n
		}

		// compute optimal sequence
		best_cost = 0;
		unsigned int s = 0, Nv = seq_range.size();
		const unsigned int lb = seq_range[0], ub = seq_range[Nv - 1];
		for (size_t n = 0; n < size_seq; ++n) {
			unsigned int offset = n*lb;
			opt_seq[n] = u_opt[n][s - offset];
			best_cost += p(n, s, opt_seq[n]);
			s += opt_seq[n];
		}

		// return resulting sequence
		return opt_seq;
	}

}



#endif
