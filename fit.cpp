#include "fit.h"

Fit::Fit(DataSet *dataSet)
    : m_dataSet(dataSet)
{
}

bool Fit::learn()
{
    return false;
}

bool Fit::extractPeak()
{
    return false;
}

const std::vector<double> &Fit::render() const
{
    m_render.clear();
    for (size_t i = 0; i < m_dataSet->size(); i++)
        m_render.push_back(.0);
    return m_render;
}
