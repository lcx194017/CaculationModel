#include <iostream>
#include "Caculation.h"


int main()
{
	double array[] = { 1,2,3,4,5,7,8,9,10};
	//Caculation *caculation = new Caculation();
	cout << Caculation::maxValue(array) << endl;
	cout << Caculation::minValue(array) << endl;
	cout << Caculation::dcValue(array) << endl;
	cout << Caculation::caculateRMS(array) << endl;
	cout << Caculation::caculatePKtoPk(array) << endl;

	//´°¿ÚÉú³É²âÊÔ
	cout << "´°¿ÚÉú³É²âÊÔ£º" << endl;
	cout << "hanning window: ";
	int size = 5;
	double amp = 1.0;
	vector<double> hann = Caculation::hanning(size, amp);
	vector<double>::iterator it; 
	for (it = hann.begin(); it != hann.end(); it++)
		cout << *it << " ";
	cout << endl;
	cout << "hamming window: ";
	vector<double>hamm = Caculation::hamming(size, amp);
	for (it = hamm.begin(); it != hamm.end(); it++)
		cout << *it << " ";
	cout << endl;


	//FFT²âÊÔ
	cout << "FFT²âÊÔ£º" << endl;
	int len = 8;
	fftw_complex *din = NULL;
	fftw_complex *out = NULL;

	din = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * len);
	out = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * len);
	double dx = 1.0 / len;
	for (int i = 0; i < len; i++)
	{

		din[i][0] = sin(2 * M_PI* dx*i) + sin(4 * M_PI * dx*i);
		din[i][1] = 0;

	}

	Caculation::FFT(len, din, out);

	for (int i = 0; i < len; i++)
	{
		double len = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
		cout << len << endl;
	}

	fftw_free(din);
	fftw_free(out);


	system("pause");
	return 0;
}
