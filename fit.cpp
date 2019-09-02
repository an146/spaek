#include <iostream>
#include "fit.h"

Fit::Fit(DataSet *dataSet)
    : m_dataSet(dataSet)
    , m_dirty(true)
{
}

bool Fit::learn()
{
    return false;
}

bool Fit::extractPeak()
{
    /* test code
    Voigt v(50, 2, 3, 150);
    {
        Voigt v_(50 + 1e-10, 2, 3, 150);
        std::cout << (v.value(300) - v.value(300)) / 1e-10 << std::endl;
        std::cout << v.d_xpeak(300) << std::endl;
    }
    {
        Voigt v_(50, 2 + 1e-10, 3, 150);
        std::cout << (v_.value(300) - v.value(300)) / 1e-10 << std::endl;
        std::cout << v.d_sigma(300) << std::endl;
    }
    {
        Voigt v_(50, 2, 3 + 1e-10, 150);
        std::cout << (v_.value(300) - v.value(300)) / 1e-10 << std::endl;
        std::cout << v.d_gamma(300) << std::endl;
    }
    {
        Voigt v_(50, 2, 3, 150 + 1e-10);
        std::cout << (v_.value(300) - v.value(300)) / 1e-10 << std::endl;
        std::cout << v.d_height(300) << std::endl;
    }
    */
    return false;
}

const std::vector<double> &Fit::render() const
{
    if (m_dirty) {
        m_render.clear();
        for (size_t i = 0; i < m_dataSet->size(); i++)
            m_render.push_back(.0);
    }
    return m_render;
}
