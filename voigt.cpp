#include <cmath>
#include <complex>
#include <map>
#include <Faddeeva.hh>
#include "voigt.h"

using namespace std::complex_literals;

Voigt::Voigt(double _xpeak, double _sigma, double _gamma, double _height)
             : xpeak(_xpeak), sigma(_sigma), gamma(_gamma), height(_height)
{
}

static constexpr double pi = 3.14159265358979323846;

//memoized Faddeeva
static std::complex<double> w(std::complex<double> z)
{
    /*
    static std::map<std::pair<double, double>, std::pair<double, double>> memo({});
    auto i = memo.find(std::make_pair(z.real(), z.imag()));
    if (i == memo.end()) {
        std::complex<double> v = Faddeeva::w(z);
        memo.insert(std::make_pair(std::make_pair(z.real(), z.imag()), std::make_pair(v.real(), v.imag())));
        if (memo.size() > 7)
            memo.clear();
        return v;
    }
    return std::complex<double>(i->second.first, i->second.second);*/
    return Faddeeva::w(z);
}

//derivative of Faddeeva function
static std::complex<double> dw(std::complex<double> z)
{
    return -2. * z * w(z) + 2.i / std::sqrt(pi);
}

double Voigt::value(double x) const
{
    double s2s = std::sqrt(2.) * sigma;
    auto z = std::complex<double>(x - xpeak, gamma) / s2s;
    auto peakZ = std::complex<double>(0., gamma) / s2s;
    return height * w(z).real() / w(peakZ).real();
}

//derivatives
Voigt Voigt::grad(double x) const
{
    Voigt ret(0, 0, 0, 0);
    double s2s = std::sqrt(2.) * sigma;
    auto z = std::complex<double>(x - xpeak, gamma) / s2s;
    auto peakZ = std::complex<double>(0., gamma) / s2s;
    ret.xpeak = height * dw(z).real() / w(peakZ).real();

    auto z_sigma = -z / sigma;
    auto peakZ_sigma = -peakZ / sigma;
    auto wZ = w(z).real();
    auto wPeakZ = w(peakZ).real();
    auto dWZ_sigma = (dw(z) * z_sigma).real();
    auto dWPeakZ_sigma = (dw(peakZ) * peakZ_sigma).real();
    ret.sigma = height * ((dWZ_sigma * wPeakZ - wZ * dWPeakZ_sigma) / wPeakZ / wPeakZ);

    auto z_gamma = 1i / s2s;
    auto peakZ_gamma = 1i / s2s;
    auto dWZ_gamma = (dw(z) * z_gamma).real();
    auto dWPeakZ_gamma = (dw(peakZ) * peakZ_gamma).real();
    ret.gamma = height * ((dWZ_gamma * wPeakZ - wZ * dWPeakZ_gamma) / wPeakZ / wPeakZ);

    ret.height = wZ / wPeakZ;

    ret.xpeak = 0.;
    return ret;
}
