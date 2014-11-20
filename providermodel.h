#ifndef PROVIDERMODEL_H
#define PROVIDERMODEL_H

#include <QAbstractListModel>
#include <QUrl>

class Provider
{
public:
    Provider(const QString &name, const QUrl &url) :
        m_name(name),
        m_url(url),
        m_active(false)
    {
    }

    QString name() const
    {
        return m_name;
    }

    QUrl url() const
    {
        return m_url;
    }

    bool isActive() const
    {
        return m_active;
    }

    void setActive(bool active)
    {
        m_active = active;
    }

private:
    QString m_name;
    QUrl m_url;
    bool m_active;
};

class ProviderModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        Name = Qt::DisplayRole,
        Host = Qt::UserRole,
        Active
    };

    explicit ProviderModel(QObject *parent = 0);
    ~ProviderModel();
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &) const;
    void addProvider(const QString &name, const QUrl &url);

private:
    QList<Provider> m_providers;
};

#endif // PROVIDERMODEL_H

