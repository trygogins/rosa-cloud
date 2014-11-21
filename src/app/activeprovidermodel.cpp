#include "activeprovidermodel.h"
#include "providermodel.h"

ActiveProviderModel::ActiveProviderModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

ActiveProviderModel::~ActiveProviderModel()
{
}

bool ActiveProviderModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0);
    if (!index.isValid())
        return false;
    return index.data(ProviderModel::Active).toBool();
}

