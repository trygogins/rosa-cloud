#include "providermodel.h"

ProviderModel::ProviderModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

ProviderModel::~ProviderModel()
{

}

QVariant ProviderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    if (row < 0 || row >= m_providers.size())
        return QVariant();

    const Provider &service = m_providers[row];
    switch (role) {
    case Name:
        return service.name();
    case Title:
        return service.title();
    case Url:
        return service.url();
    case Active:
        return service.isActive();
    case Token:
        return service.token();
    }

    return QVariant();
}

int ProviderModel::rowCount(const QModelIndex &) const
{
    return m_providers.size();
}

void ProviderModel::addProvider(const QString &name, const QString &title, const QUrl &url)
{
    int rows = m_providers.size();
    beginInsertRows(QModelIndex(), rows, rows);
    Provider provider(name, title, url);
    m_providers.append(provider);
    endInsertRows();
}



