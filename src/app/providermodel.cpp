#include "providermodel.h"
#include <QSettings>

ProviderModel::ProviderModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

ProviderModel::~ProviderModel()
{

}

bool ProviderModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    int row = index.row();
    if (row < 0 || row >= m_providers.size())
        return false;

    switch (role) {
    case Token:
        m_providers[row].setToken(value.toString());
        return true;
    }

    return false;
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

void ProviderModel::save()
{
    QSettings settings;
    settings.beginWriteArray("providers");
    for (int i = 0; i < m_providers.size(); i++) {
        settings.setArrayIndex(i);
        settings.setValue("name", m_providers.at(i).name());
        settings.setValue("token", m_providers.at(i).token());
    }
    settings.endArray();
}

void ProviderModel::load()
{
    QSettings settings;
    int size = settings.beginReadArray("providers");
    for (int i = 0; i < size; i++) {
        settings.setArrayIndex(i);
        QString name = settings.value("name").toString();
        QString token = settings.value("token").toString();
        QModelIndex index = firstMatch(Name, name);
        if (index.isValid())
            setData(index, token, Token);
    }
    settings.endArray();
}

QModelIndex ProviderModel::firstMatch(int role, const QVariant &value)
{
    QModelIndexList indecies = match(index(0, 0), role, value);
    return indecies.isEmpty() ? QModelIndex() : indecies.first();
}

