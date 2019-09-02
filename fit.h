#ifndef FIT_H
#define FIT_H

#include <vector>
#include "dataset.h"
#include "voigt.h"

class Fit : public std::vector<Voigt>
{
public:
    Fit(DataSet *);
    const std::vector<double> &render() const;
    bool learn();
    bool extractPeak();
private:
    DataSet *m_dataSet;
    mutable std::vector<double> m_render;
};

#endif // FIT_H
