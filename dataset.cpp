#include <cassert>
#include <fstream>
#include <iostream>
#include "dataset.h"

QT_CHARTS_USE_NAMESPACE

DataSet::DataSet()
{
    std::ifstream i("table.txt");
    std::string s;    //header strings
    i >> s;
    assert(s == "x");
    i >> s;
    assert(s == "y");

    double x, y;
    while (i >> x >> y)
        push_back(std::make_pair(x, y));
    std::cout << "read " << size() << " points" << std::endl;
}

QSplineSeries *DataSet::createSplineSeries() const {
    QSplineSeries *ret = new QSplineSeries();
    for (std::pair<double, double> point : *this)
        ret->append(point.first, point.second);
    return ret;
}
