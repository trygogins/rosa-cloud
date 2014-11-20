#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QUrl>

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = 0);
    ~AuthDialog();

public slots:
    void open(const QModelIndex &index);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AuthDialog *ui;
    QUrl m_url;
};

#endif // AUTHDIALOG_H
