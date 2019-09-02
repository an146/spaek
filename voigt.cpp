#include <cmath>
#include <complex>
#include <Faddeeva.hh>
#include "voigt.h"

using namespace std::complex_literals;

Voigt::Voigt(double _xpeak, double _sigma, double _gamma, double _height)
             : xpeak(_xpeak), sigma(_sigma), gamma(_gamma), height(_height)
{
}

static constexpr double pi = 3.14159265358979323846;

//derivative of Faddeeva function
static std::complex<double> dw(std::complex<double> z)
{
    return -2. * z * Faddeeva::w(z) + 2.i / std::sqrt(pi);
}

double Voigt::value(double x) const
{
    double s2s = std::sqrt(2.) * sigma;
    auto z = std::complex<double>(x - xpeak, gamma) / s2s;
    auto peakZ = std::complex<double>(0., gamma) / s2s;
    return height * Faddeeva::w(z).real() / Faddeeva::w(peakZ).real();
}

//derivatives
double Voigt::d_xpeak(double x) const
{
    double s2s = std::sqrt(2.) * sigma;
    auto z = std::complex<double>(x - xpeak, gamma) / s2s;
    auto peakZ = std::complex<double>(0., gamma) / s2s;
    return height * dw(z).real() / Faddeeva::w(peakZ).real();
}

double Voigt::d_sigma(double x) const
{
    double s2s = std::sqrt(2.) * sigma;
    auto z = std::complex<double>(x - xpeak, gamma) / s2s;
    auto z_ = -z / sigma;
    auto peakZ = std::complex<double>(0., gamma) / s2s;
    auto peakZ_ = -peakZ / sigma;
    auto wZ = Faddeeva::w(z).real();
    auto dWZ = (dw(z) * z_).real();
    auto wPeakZ = Faddeeva::w(peakZ).real();
    auto dWPeakZ = (dw(peakZ) * peakZ_).real();
    return height * ((dWZ * wPeakZ - wZ * dWPeakZ) / wPeakZ / wPeakZ);
}

double Voigt::d_gamma(double x) const
{
    double s2s = std::sqrt(2.) * sigma;
    auto z = std::complex<double>(x - xpeak, gamma) / s2s;
    auto z_ = 1i / s2s;
    auto peakZ = std::complex<double>(0., gamma) / s2s;
    auto peakZ_ = 1i / s2s;
    auto wZ = Faddeeva::w(z).real();
    auto dWZ = (dw(z) * z_).real();
    auto wPeakZ = Faddeeva::w(peakZ).real();
    auto dWPeakZ = (dw(peakZ) * peakZ_).real();
    return height * ((dWZ * wPeakZ - wZ * dWPeakZ) / wPeakZ / wPeakZ);
}

double Voigt::d_height(double x) const
{
    double s2s = std::sqrt(2.) * sigma;
    auto z = std::complex<double>(x - xpeak, gamma) / s2s;
    auto peakZ = std::complex<double>(0., gamma) / s2s;
    return Faddeeva::w(z).real() / Faddeeva::w(peakZ).real();
}
