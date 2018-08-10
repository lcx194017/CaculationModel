
Caculation::Caculation()
{
}

Caculation::~Caculation()
{
}

/************************************************************************/
/*计算数组数据的最大值                                                  */
/************************************************************************/
template<typename T, int N>
T Caculation::maxValue(T(&data)[N])
{
	if (0 == N) return 0;
	T max = data[0];
	for (int i = 1; i < N; i++)
		if (max < data[i])
			max = data[i];
	return max;
}

/************************************************************************/
/*计算数组数据的最小值                                                  */
/************************************************************************/
template<typename T, int N>
T Caculation::minValue(T(&data)[N])
{
	if (0 == N) return 0;
	T min = data[0];
	for (int i = 1; i < N; i++)
		if (min > data[i])
			min = data[i];
	return min;
}

/************************************************************************/
/*计算数组数据的平均值                                                  */
/************************************************************************/
template<typename T, int N>
T Caculation::dcValue(T(&data)[N])
{
	if (0 == N) return 0;
	T sum = 0;
	for (int i = 0; i < N; i++)
		sum += data[i];
	return sum / N;
}


/************************************************************************/
/* 计算数组数据RMS                                                      */
/************************************************************************/
template<typename T, int N>
T Caculation::caculateRMS(T(&data)[N])
{
	if (0 == N) return 0;
	T fSum = 0;
	for (int i = 0; i < N; i++)
		fSum += data[i] * data[i];
	return sqrt(fSum / N);
}

/************************************************************************/
/* 计算数组数据峰峰值                                                     */
/************************************************************************/
template<typename T, int N>
T Caculation::caculatePKtoPk(T(&data)[N])
{
	if (0 == N) return 0;
	T min = data[0];
	T max = data[0];
	for (int i = 1; i < N; i++)
	{
		if (data[i] < min) min = data[i];
		if (data[i] > max) max = data[i];
	}
	return max - min;
}

/************************************************************************/
/* 计算数组数据0-pk                                                      */
/************************************************************************/
template<typename T, int N>
T Caculation::caculateZerotoPk(T(&data)[N])
{
	return caculatePKtoPk(data)/2;
}

/************************************************************************/
/* 计算数组数据Crest factor                                              */
/************************************************************************/
template<typename T, int N>
T Caculation::caculateCrestFactor(T(&data)[N])
{
	T RMS = caculateRMS(data);
	if (RMS != 0)
		return caculatePKtoPk(data) / RMS;
	else
		return (T)HUGE_VAL;
}

/************************************************************************/
/* 一维数据的快速傅里叶变换                                             */
/************************************************************************/
void Caculation::FFT(int n, fftw_complex* in, fftw_complex* out)
{
	if (in == NULL || out == NULL) return;
	fftw_plan p;
	p = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
	fftw_cleanup();
}

/************************************************************************/
/* 生成hanning窗口                                                      */
/************************************************************************/
template <typename T>                        
vector<T> Caculation::hanning(int N, T amp)
{
	vector<T> win(N);

	for (int i = 0; i < (N + 1) / 2; ++i)
	{
		win[i] = amp * T(0.5 - 0.5*cos(2 * M_PI*i / (N - 1)));
		win[N - 1 - i] = win[i];
	}

	return win;
}


/************************************************************************/
/* 生成hamming窗口                                                      */
/************************************************************************/
template <typename T>                    
vector<T> Caculation::hamming(int N, T amp)
{
	vector<T> win(N);

	for (int i = 0; i < (N + 1) / 2; ++i)
	{
		win[i] = amp * T(0.54 - 0.46*cos(2 * M_PI*i / (N - 1.0)));
		win[N - 1 - i] = win[i];
	}

	return win;
}