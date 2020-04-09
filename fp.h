/*
 * fp.h
 *
 *  Created on: 12-Mar-2020
 *  	Author: Sagar
 */

#ifndef FP_H_
#define FP_H_

namespace std{

class fp{
	private:

		unsigned int sign, fpoint, exp, manti, sel;
		int ubias;

	public:
		fp(int, int, int, int, int);

		//	Defining all the Getters
		int get_fp();
		int get_sign();
		int get_exp();
		int get_manti();
		int get_ubias();
		int get_sel();
		void fp_burp();
	
		//	Defining all the Setters	
		void set_sign(unsigned int);
		void set_exp(unsigned int);
		void set_manti(unsigned int);
		void set_sel(unsigned int);
		void find_ubias();

		virtual ~fp();
};

}

#endif
