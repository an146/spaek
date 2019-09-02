#ifndef VOIGT_H
#define VOIGT_H

struct Voigt
{
public:
    Voigt(double _xpeak, double _sigma, double _gamma, double _height);
    double xpeak;
    double sigma;
    double gamma;
    double height;

    //actual value
    double value(double) const;
    //derivatives
    double d_xpeak(double) const;
    double d_sigma(double) const;
    double d_gamma(double) const;
    double d_height(double) const;
};

#endif // VOIGT_H
