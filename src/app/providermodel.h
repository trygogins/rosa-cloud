#ifndef PROVIDERMODEL_H
#define PROVIDERMODEL_H

#include <QAbstractListModel>
#include <QUrl>

class Provider
{
public:
    Provider(const QString &name, const QString &title, const QUrl &url) :
        m_name(name),
        m_title(title),
        m_url(url)
    {
    }

    QString name() const
    {
        return m_name;
    }

    QString title() const
    {
        return m_title;
    }

    QUrl url() const
    {
        return m_url;
    }

    bool isActive() const
    {
        return !m_token.isEmpty();
    }

    void setToken(const QString &token)
    {
        m_token = token;
    }

    QString token() const
    {
        return m_token;
    }

private:
    QString m_name;
    QString m_title;
    QUrl m_url;
    QString m_token;
};

class ProviderModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        Title = Qt::DisplayRole,
        Name = Qt::UserRole,
        Url,
        Active,
        Token
    };

    explicit ProviderModel(QObject *parent = 0);
    ~ProviderModel();
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &) const;
    void addProvider(const QString &name, const QString &title, const QUrl &url);
    void save();
    void load();

protected:
    QModelIndex firstMatch(int role, const QVariant &value);

private:
    QList<Provider> m_providers;
};

#endif // PROVIDERMODEL_H

