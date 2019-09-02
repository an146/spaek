#ifndef DATASET_H
#define DATASET_H

#include <utility>
#include <vector>
#include <QtCharts/QSplineSeries>

class DataSet : public std::vector<std::pair<double, double>>
{
public:
    DataSet();
    QtCharts::QSplineSeries *createSplineSeries() const;
};

#endif // DATASET_H
