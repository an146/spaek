#ifndef FIT_H
#define FIT_H

#include <vector>
#include "dataset.h"
#include "voigt.h"

class Fit : protected std::vector<Voigt>
{
public:
    Fit(DataSet *);
    const std::vector<double> &render() const;
    bool learn();
    bool extractPeak();
    void setDirty() { m_dirty = true; }
private:
    DataSet *m_dataSet;
    bool m_dirty;
    std::vector<double> m_left;
    mutable std::vector<double> m_render;
};

#endif // FIT_H
