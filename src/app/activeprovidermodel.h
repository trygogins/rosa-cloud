#ifndef ACTIVEPROVIDERMODEL_H
#define ACTIVEPROVIDERMODEL_H

#include <QSortFilterProxyModel>

class ActiveProviderModel : public QSortFilterProxyModel
{
public:
    ActiveProviderModel(QObject *parent = 0);
    ~ActiveProviderModel();

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};

#endif // ACTIVEPROVIDERMODEL_H

