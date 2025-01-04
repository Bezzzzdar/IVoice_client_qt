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
#include <QTimer>

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
    static Server* instance(const QString& serverAddress = "", int serverPort = 0);

    void authRegister(const QString& username, const QString& displayName,
                      const QString& email, const QString& password,
                      const QString& birthDate);
    void authLogin(const QString& login, const QString& password);
    // Q_INVOKABLE void authLogout();
    void getCurrentUserInfo();
    ~Server();

private slots:
    void authRefresh();

private:
    explicit Server(const QString& serverAddress, int serverPort, QObject* parent = nullptr);

    Server(const Server&) = delete;
    Server& operator = (const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator = (Server&&) = delete;

    static Server* m_instance;
    static QMutex mutex;

    QString domen;
    QNetworkAccessManager* networkManager;
    QHash<QString, QPair<QString, QString>> routes;
    QTimer* timer;

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
    int userID;
    QString username;
    QString displayName;
    QString email;
    QString phoneNumber;
    QString password;
    QString birthDate;
    QString status; // online/offline

public:
    static User* instance(QObject* parent = nullptr);
    ~User();

    void setAccessToken(const QString& accessToken);
    void setRefreshToken(const QString& refreshToken);
    void setUserID(int userID);
    void setUsername(const QString& username);
    void setDisplayName(const QString& displayName);
    void setEmail(const QString& email);
    void setPhoneNumber(const QString& phoneNumber);
    void setPassword(const QString& password);
    void setBirthDate(const QString& birthDate);
    void setStatus(const QString& status);

    QString getAccessToken();
    QString getRefreshToken();
    int getUserID();
    QString getUsername();
    QString getDisplayName();
    QString getEmail();
    QString getPhoneNumber();
    QString getPassword();
    QString getBirthDate();
    QString getStatus();
};

class LIBCORE_API Settings  : public QSettings
{
    Q_OBJECT

public:
    static Settings* instance();

    QVariant getSetting(const QString& key);
    void setSetting(const QString& key, const QVariant& value);
    ~Settings();

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
