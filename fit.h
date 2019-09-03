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
    bool learn(double rate);
    bool extractPeak(bool force);
    void setDirty() { m_dirty = true; }
    void calc_left();
    double error() const;
    using std::vector<Voigt>::size;
    void save() const;
    void status_prefix() const;
private:
    DataSet *m_dataSet;
    bool m_dirty;  //when need to recompute render
    std::vector<double> m_left;   //always valid
    mutable std::vector<double> m_render;
};

#endif // FIT_H
