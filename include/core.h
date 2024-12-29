#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QHash>
#include <QPair>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QDate>
#include <QSettings>

#ifndef CORE_H
#define CORE_H

#ifdef LIBCORE_EXPORTS
#  define LIBCORE_API Q_DECL_EXPORT
#else
#  define LIBCORE_API Q_DECL_IMPORT
#endif

namespace LibCore
{

class LIBCORE_API Server : public QObject
{
    Q_OBJECT

public:
    static Server* instance(const QString& server_address = "", int server_port = 0);

    Server(const Server&) = delete;
    Server& operator = (const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator = (Server&&) = delete;

    void authRegister(const QString& user_name, const QString& display_name,
                                  const QString& email, const QString& password, const QString& birth_date);
    void authLogin(const QString& login, const QString& password);
    // Q_INVOKABLE void authLogout();
    // Q_INVOKABLE void authRefresh();
    ~Server();

private:
    explicit Server(const QString& server_address, int server_port, QObject* parent = nullptr);

    static Server* m_instance;
    static QMutex mutex;

    QString domen;
    QNetworkAccessManager* networkManager;
    QHash<QString, QPair<QString, QString>> routes;

signals:
    void registerSucsessful();
    void registerUnsucsessful(const QString &errorMessage);
    void loginSuccessful();
    void loginUnsucsessful(const QString &errorMessage);
};


class LIBCORE_API User : public QObject
{
    Q_OBJECT

private:
    explicit User(QObject* parent = nullptr);

    User(const User&) = delete;
    User& operator = (const User&) = delete;
    User(User&&) = delete;
    User& operator = (User&&) = delete;

    static User* m_instance;
    static QMutex mutex;

    QString accessToken;
    QString refreshToken;
    QString username;
    QString display_name;
    QString email;
    QString phone_number;
    QString password;
    QDate birth_date;

public:
    static User* instance(QObject* parent = nullptr);
    virtual ~User();

    void setAccessToken(const QString& accessToken);
    void setRefreshToken(const QString& refreshToken);
    void setUsername(const QString& username);
    void setDisplayName(const QString& display_name);
    void setEmail(const QString& email);
    void setPhoneNumber(const QString& phone_number);
    void setPassword(const QString& password);
    void setBirthDate(QDate birth_date);

    QString getAccessToken();
    QString getRefreshToken();
    QString getUsername();
    QString getDisplayName();
    QString getEmail();
    QString getPhoneNumber();
    QString getPassword();
    QDate getBirthDate();
};

class LIBCORE_API Settings  : public QSettings
{
    Q_OBJECT

public:
    static Settings* instance();

    QVariant getSetting(const QString& key);
    void setSetting(const QString& key, const QVariant& value);
    virtual ~Settings();

    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
    Settings(Settings&&) = delete;
    Settings& operator=(Settings&&) = delete;

private:
    explicit Settings();

    const QString configFilePath;

    static Settings* m_instance;
    static QMutex mutex;
};

}   // namespace LibCore


#endif // CORE_H
