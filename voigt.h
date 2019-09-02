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
    Voigt grad(double) const;
};

#endif // VOIGT_H
