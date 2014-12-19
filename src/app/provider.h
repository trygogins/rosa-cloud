#ifndef PROVIDERMODEL_H
#define PROVIDERMODEL_H

#include <QAbstractListModel>
#include <QUrl>

class Provider : public QObject
{
    Q_OBJECT

public:
    Provider(const QString &name, const QString &title, const QUrl &url) :
        m_name(name),
        m_title(title),
        m_url(url),
        m_hasClient(false)
    {
    }

    Provider(const QString &name, const QString &title, const QUrl &url, const bool hasClient) :
        m_name(name),
        m_title(title),
        m_url(url),
        m_hasClient(hasClient)
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
        return m_isActive;
    }

    bool isMount() const
    {
        return m_isMount;
    }

    bool hasClient() const
    {
        return m_hasClient;
    }

    QString token() const
    {
        return m_token;
    }

    void setInstalled(bool mark)
    {
        if (mark != m_isActive) {
            m_isActive = mark;
        }
    }

    void setMount(bool mark)
    {
        if (mark != m_isMount) {
            m_isMount = mark;
            emit mount();
        }
    }

signals:
    void mount();

private:
    QString m_name;
    QString m_title;
    QUrl m_url;
    QString m_token;
    bool m_hasClient;
    bool m_isActive = false;
    bool m_isMount = false;
};

#endif // PROVIDERMODEL_H

