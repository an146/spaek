#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include "fit.h"

Fit::Fit(DataSet *dataSet)
    : m_dataSet(dataSet)
    , m_dirty(true)
{
    for (auto p : *m_dataSet)
        m_left.push_back(p.second);
}

bool Fit::learn(double rate)
{
    auto backup = *this;
    auto e = error();
    for (auto i = begin(); i != end(); ++i) {
        std::vector<double> ref = m_left;
        for (size_t j = 0; j < m_dataSet->size(); j++) {
            auto x = m_dataSet->at(j).first;
            auto v = i->value(x);
            ref[j] += v;
            Voigt g = i->grad(x);
            i->xpeak += 2 * (ref[j] - v) * g.xpeak * rate;
            i->sigma += 2 * (ref[j] - v) * g.sigma * rate;
            i->gamma += 2 * (ref[j] - v) * g.gamma * rate;
            i->height += 2 * (ref[j] - v) * g.height * rate;
        }
    }
    handle_negative_coeffs();
    calc_left();
    status_prefix();
    if (error() < e) {
        std::cout << "Successful learn: " << error() << " < " << e << "\r" << std::flush;
        m_dirty = true;
        return true;
    } else {
        std::cout << "Failed learn: " << error() << " >= " << e << std::endl;
        swap(backup);
        calc_left();
        return false;
    }
}

bool Fit::extractPeak(bool force)
{
    assert(!m_left.empty());
    assert(m_dataSet->size() == m_left.size());
    auto mp = std::max_element(m_left.begin(), m_left.end());
    auto i = static_cast<size_t>(mp - m_left.begin());
    auto fG = 5.;
    auto fL = 5.;
    auto sigma = fG / (2. * std::sqrt(std::log(2.)));
    auto gamma = fL / 2.;
    push_back(Voigt(m_dataSet->at(i).first, sigma, gamma, *mp * 0.95));
    auto left_backup = m_left;
    auto e = error();
    calc_left();
    status_prefix();
    if (error() < e) {
        std::cout << "Successful fit at x=" << back().xpeak << ": " << error() << " < " << e << std::endl;
        m_dirty = true;
        return true;
    } else if (force) {
        std::cout << "Forced fit at x=" << back().xpeak << ": " << error() << " >= " << e << std::endl;
        m_dirty = true;
        return false;
    } else {
        std::cout << "Failed fit at x=" << back().xpeak << ": " << error() << " >= " << e << std::endl;
        pop_back();
        m_left.swap(left_backup);
        return false;
    }
}

void Fit::calc_left()
{
    m_left.clear();
    for (size_t i = 0; i < m_dataSet->size(); i++) {
        const std::pair<double, double> &p = (*m_dataSet)[i];
        m_left.push_back(p.second);
        for (auto v : *this)
            m_left.back() -= v.value(p.first);
    }
}

double Fit::error() const
{
    double ret = 0.;
    for (auto l : m_left)
        ret += l * l;
    return ret;
}

void Fit::load()
{
    std::ifstream i("fit.txt");
    std::string s;   //header
    i >> s;
    assert(s == "\"xpeak\"");
    i >> s;
    assert(s == "\"sigma\"");
    i >> s;
    assert(s == "\"gamma\"");
    i >> s;
    assert(s == "\"height\"");

    Voigt v(0, 0, 0, 0);
    while (i >> v.xpeak >> v.sigma >> v.gamma >> v.height)
        push_back(v);
    calc_left();
    m_dirty = true;
    status_prefix();
    std::cout << "loaded" << std::endl;
}

void Fit::save() const
{
    {
        std::ofstream o("fit.txt");
        o << "\"xpeak\" \"sigma\" \"gamma\" \"height\"" << std::endl;
        for (const auto &v : *this)
            o << v.xpeak << " " << v.sigma << " " << v.gamma << " " << v.height << std::endl;
    }
    {
        std::ofstream o("left.txt");
        o << "\"x\" \"y'\"" << std::endl;
        for (size_t i = 0; i < m_dataSet->size(); i++)
            o << m_dataSet->at(i).first << " " << m_left[i] << std::endl;
    }
    status_prefix();
    std::cout << "saved" << std::endl;
}

const std::vector<double> &Fit::render() const
{
    if (m_dirty) {
        m_render.clear();
        for (size_t i = 0; i < m_dataSet->size(); i++) {
            m_render.push_back((*m_dataSet)[i].second - m_left[i]);
        }
    }
    return m_render;
}

void Fit::status_prefix() const
{
    std::cout << "[" << size() << "] ";
}

void Fit::handle_negative_coeffs()
{
    for (auto i = begin(); i != end(); ++i)
        if (i->xpeak <= 0. || i->sigma <= .0 || i->gamma <= .0 || i->height <= .0) {
            erase(i);
            extractPeak(false);
            break;
        }
}
