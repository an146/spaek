/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "approximationmodel.h"
#include <QtCore/QVector>
#include <QtCore/QRandomGenerator>
#include <QtCore/QRect>
#include <QtGui/QColor>

ApproximationModel::ApproximationModel(QObject *parent) :
    QAbstractTableModel(parent), m_dataSet(), m_fit(&m_dataSet)
{
    m_fit.extractPeak();
}

int ApproximationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_dataSet.size());
}

int ApproximationModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant ApproximationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section == 0)
            return "x";
        else if (section == 1)
            return "y";
        else
            return "y'";
    } else {
        return QString("%1").arg(section + 1);
    }
}

QVariant ApproximationModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        size_t r = static_cast<size_t>(index.row());
        switch (index.column()) {
        case 0:
            return m_dataSet[r].first;
        case 1:
            return m_dataSet[r].second;
        default:
            return m_fit.render()[r];
        }
    } else if (role == Qt::BackgroundRole) {
        // cell not mapped return white color
        return QColor(Qt::white);
    }
    return QVariant();
}

bool ApproximationModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index)
    Q_UNUSED(value)
    Q_UNUSED(role)

    return false;
}

Qt::ItemFlags ApproximationModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index);
}
