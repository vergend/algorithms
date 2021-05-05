#include <iostream>
#include <time.h>

using namespace std;

double MySqrt(int n) {
	if ( n < 0) { return -1; } // return error code for invalid input
	unsigned int p = 1,sqrtp=1; // unsigned int can store 1 higher power of 2 than int
	int count = 0; // p = 2^count, keeping track of the power
	while (p < n) { // at most 32 iterations
		p <<= 1; // shift the set bit in p to the left until we arrive at the first power of 2 larger than n
		count++; 
		if (count % 2 == 0) {
			sqrtp <<= 1; // shift the bit in sqrtp only every second shift, to get approximate square root of p
		}
	}
	double sqrt2 = 1.414213562373095; // In case the power "count" is odd, we will need the square root of 2
	double epsilonPowers[31];// we will sum 30 first summands of a Taylor expansion
	epsilonPowers[1] = ((double)(p - n)) / p; // deviation of p from n. By definition of p we have epsPowers[1]<=0.5
	for (int i = 2; i < 31; i++) {
		epsilonPowers[i] = epsilonPowers[i - 1] * epsilonPowers[1];
	}
	// considering that epsilonPowers[i] are powers of a number <=0.5 and int can store at most 10 significant digits
	// the following Taylor expansion to 30th power is guaranteed to be precise to 12 significant digits, which is enough
	double result = sqrtp * (1 - epsilonPowers[1] / 2. - epsilonPowers[2] / 8. - epsilonPowers[3] / 16. - (5. * epsilonPowers[4]) / 128. -
				(7. / 256.) * epsilonPowers[5] - (21. / 1024.) * epsilonPowers[6] - (33. / 2048.) * epsilonPowers[7] -
				(429. / 32768.) * epsilonPowers[8] - (715. / 65536.) * epsilonPowers[9] - (2431. / 262144.) * epsilonPowers[10] -
				(4199. / 524288.) * epsilonPowers[11] - (29393. / 4194304.) * epsilonPowers[12] -
				(52003. / 8388608.) * epsilonPowers[13] - (185725. / 33554432.) * epsilonPowers[14] -
				(334305. / 67108864.) * epsilonPowers[15] - (9694845. / 2147483648.) * epsilonPowers[16] -
				(17678835. / 4294967296.) * epsilonPowers[17] - (64822395. / 17179869184.) * epsilonPowers[18] -
				(119409675. / 34359738368.) * epsilonPowers[19] - (883631595. / 274877906944.) * epsilonPowers[20] -
				(1641030105. / 549755813888.) * epsilonPowers[21] - (6116566755. / 2199023255552.) * epsilonPowers[22] -
				(11435320455. / 4398046511104.) * epsilonPowers[23] - (171529806825. / 70368744177664.) * epsilonPowers[24] -
				(322476036831. / 140737488355328.) * epsilonPowers[25] - (1215486600363. / 562949953421312.) * epsilonPowers[26] -
				(2295919134019. / 1125899906842624.) * epsilonPowers[27] - (17383387729001. / 9007199254740992.) * epsilonPowers[28] -
				(32968493968795. / 18014398509481984.) * epsilonPowers[29] - (125280277081421. / 72057594037927936.) * epsilonPowers[30]);
	
	if (count % 2) {
		result *= sqrt2; // additional factor of sqrt(2) if the original power "count" is odd
	}
	return result;
}


int main()
{
	srand(time(NULL));
	int randomInt;
	for (int i = 0; i < 31; i++) {
		randomInt = pow(2,i)+rand()%100;
		cout << "number: " << randomInt << " , sqrt(number): " << sqrt(randomInt) << " MySqrt(number): " << MySqrt(randomInt) << endl;
	}
}

/* 
One example execution of the above code leads to:

number: 56 , sqrt(number): 7.48331 MySqrt(number): 7.48331
number: 51 , sqrt(number): 7.14143 MySqrt(number): 7.14143
number: 50 , sqrt(number): 7.07107 MySqrt(number): 7.07107
number: 48 , sqrt(number): 6.9282 MySqrt(number): 6.9282
number: 21 , sqrt(number): 4.58258 MySqrt(number): 4.58258
number: 92 , sqrt(number): 9.59166 MySqrt(number): 9.59166
number: 116 , sqrt(number): 10.7703 MySqrt(number): 10.7703
number: 174 , sqrt(number): 13.1909 MySqrt(number): 13.1909
number: 301 , sqrt(number): 17.3494 MySqrt(number): 17.3494
number: 598 , sqrt(number): 24.454 MySqrt(number): 24.454
number: 1097 , sqrt(number): 33.121 MySqrt(number): 33.121
number: 2085 , sqrt(number): 45.6618 MySqrt(number): 45.6618
number: 4165 , sqrt(number): 64.5368 MySqrt(number): 64.5368
number: 8288 , sqrt(number): 91.0385 MySqrt(number): 91.0385
number: 16446 , sqrt(number): 128.242 MySqrt(number): 128.242
number: 32789 , sqrt(number): 181.077 MySqrt(number): 181.077
number: 65596 , sqrt(number): 256.117 MySqrt(number): 256.117
number: 131159 , sqrt(number): 362.159 MySqrt(number): 362.159
number: 262210 , sqrt(number): 512.064 MySqrt(number): 512.064
number: 524302 , sqrt(number): 724.087 MySqrt(number): 724.087
number: 1048580 , sqrt(number): 1024 MySqrt(number): 1024
number: 2097249 , sqrt(number): 1448.19 MySqrt(number): 1448.19
number: 4194397 , sqrt(number): 2048.02 MySqrt(number): 2048.02
number: 8388702 , sqrt(number): 2896.33 MySqrt(number): 2896.33
number: 16777263 , sqrt(number): 4096.01 MySqrt(number): 4096.01
number: 33554517 , sqrt(number): 5792.63 MySqrt(number): 5792.63
number: 67108885 , sqrt(number): 8192 MySqrt(number): 8192
number: 134217817 , sqrt(number): 11585.2 MySqrt(number): 11585.2
number: 268435525 , sqrt(number): 16384 MySqrt(number): 16384
number: 536870999 , sqrt(number): 23170.5 MySqrt(number): 23170.5
number: 1073741867 , sqrt(number): 32768 MySqrt(number): 32768

At all relevant orders of magnitude we see that the square root is calculated correctly.
*/
