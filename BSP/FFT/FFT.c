#include "stdio.h"
#include "arm_math.h"
#include "arm_const_structs.h"
#include "main.h"
extern float fft_inputbuf[FFT_LENGTH * 2];  
extern float fft_outputbuf[FFT_LENGTH];


// 频率=数组下标*(采样率/FFT计算的点数)
// 栅栏效应取附近频率5个点平方和开根号为幅度
void perform_fft(float32_t* input, int length) 
{
    // Perform the FFT operation.
    for (int i = 0; i < length; i++) {
        fft_inputbuf[i * 2] = input[i];
        fft_inputbuf[i * 2 + 1] = 0;
    }

    arm_cfft_f32(&arm_cfft_sR_f32_len1024, fft_inputbuf, 0, 1);
    arm_cmplx_mag_f32(fft_inputbuf, fft_outputbuf, length);

    fft_outputbuf[0] /= 1024;
    for (int i = 1; i < length; i++) 
    {
        fft_outputbuf[i] /= 512;
    }
}


// 设采样频率10K 9.765625 fft_outputbuf[5]为48.828125HZ幅值 [4] 39.0625 [6] 58.59375
double GetTHD(void)
{
    static  double  U0=0.0,UN=0.0,THD=0.0;
    static  double thd_numerator = 0.0;
    for(int i=4;i<=6;i++)
    {
        U0+=(fft_outputbuf[i]*fft_outputbuf[i]);
    }
    U0=sqrt(U0);
    // Sum the squares of the amplitudes of the harmonics
    for (int harmonic = 2; harmonic <= 5; harmonic++) 
    {
        for(int i=4;i<=6;i++)
        {
            thd_numerator=(fft_outputbuf[i * harmonic]);
            UN += thd_numerator * thd_numerator;
        } 
    }
    UN=sqrt(UN);
    THD=UN/U0*100;
    return THD;
}














// https://blog.csdn.net/u010058695/article/details/112665306#:~:text=DSP%E5%BA%93%E6%94%AF%E6%8C%81%E7%9A%84%E8%AE%A1%E7%AE%97%E7%B1%BB%E5%88%AB%E5%8C%85%E6%8B%AC%EF%BC%9A%20%E5%9F%BA%E6%9C%AC%E6%95%B0%E5%AD%A6%E5%87%BD%E6%95%B0%EF%BC%8C%E5%8C%85%E6%8B%AC%EF%BC%9A%E5%90%91%E9%87%8F%E7%9A%84%E7%BB%9D%E5%AF%B9%E5%80%BC%EF%BC%8C%E5%8A%A0%E5%87%8F%E4%B9%98%E9%99%A4%EF%BC%8C%E4%BD%8D%E4%B8%8E%EF%BC%8C%E7%82%B9%E4%B9%98%EF%BC%8C%E6%88%96%EF%BC%8C%E5%BC%82%E6%88%96%E7%AD%89%20%E5%BF%AB%E9%80%9F%E6%95%B0%E5%AD%A6%E5%87%BD%E6%95%B0%EF%BC%8C%E5%8C%85%E6%8B%AC%EF%BC%9A%E5%B9%B3%E6%96%B9%E6%A0%B9%EF%BC%8C%E4%BD%99%E5%BC%A6%EF%BC%8C%E6%AD%A3%E5%BC%A6%20%E5%A4%8D%E6%9D%82%E7%9A%84%E6%95%B0%E5%AD%A6%E5%87%BD%E6%95%B0%EF%BC%8C%E5%8C%85%E6%8B%AC%EF%BC%9A%E5%85%B1%E8%BD%AD%EF%BC%8C%E7%82%B9%E4%B9%98%EF%BC%8C%E5%A4%8D%E6%95%B0%EF%BC%8C%E5%A4%8D%E6%95%B0%E5%B9%B3%E6%96%B9%EF%BC%8C%E4%B9%98%E6%96%B9%EF%BC%8C%E5%AE%9E%E6%95%B0%E4%B9%98%E6%B3%95,%E6%BB%A4%E6%B3%A2%E5%8A%9F%E8%83%BD%EF%BC%8C%E5%8C%85%E6%8B%AC%EF%BC%9AFIR%20IIR%20LMS%20%E7%AD%89
