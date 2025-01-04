#include "include/core.h"

namespace LibCore {

Server* Server::m_instance = nullptr;
QMutex Server::mutex;

Server* Server::instance(const QString& serverAddress, int serverPort)
{
    if (!m_instance)
    {
        QMutexLocker locker(&mutex);
        m_instance = new Server(serverAddress, serverPort);
    }
    return m_instance;
}

Server::Server(const QString& serverAddress, int serverPort, QObject* parent)
    : QObject(parent),
    domen("http://" + serverAddress + ":" + QString::number(serverPort)),
    networkManager(new QNetworkAccessManager(this)),
    timer(new QTimer(this))
{
    this->routes =
    {
        // auth
        {"auth_register",                   qMakePair("POST", "/auth/register")},
        {"auth_login",                      qMakePair("POST", "/auth/login")},
        {"auth_logout",                     qMakePair("POST", "/auth/logout")},
        {"auth_refresh",                    qMakePair("POST", "/auth/refresh")},

        // users
        {"get_current_user",                qMakePair("GET", "/users")},
        {"update_current_user",             qMakePair("PATCH", "/users")},
        {"delete_current_user",             qMakePair("DEL", "/users")},
        {"get_current_user_details",        qMakePair("GET", "/users/details")},
        {"update_current_user_details",     qMakePair("PATCH", "/users/details")},
        {"delete_current_user_details",     qMakePair("DEL", "/users/details")},
        {"get_other_user_info",             qMakePair("GET", "/users/:user_id/details")}, // user_id ???
        {"get_other_user_details",          qMakePair("GET", "/users/:user_id/details")}, // user_id ???
        {"update_password",                 qMakePair("POST", "/users/password")},

        // friends
        {"get_friends_list",                qMakePair("GET", "/friends")},
        {"send_friend_request",             qMakePair("POST", "/friends")},
        {"handle_friend_request",           qMakePair("PATCH", "/friends/:requesId")}, // request_id ???
        {"delete_friend",                   qMakePair("DEL", "/friends/:userId")}, // userId ???
        {"get_user_friends",                qMakePair("GET", "/friends/:userId")}, // userId ???
    };

    // отправлять запросы только после логина!!!!!!!!!
    /* Set timer for send authRefresh() every 10 minutes*/
    QObject::connect(timer, &QTimer::timeout, this, &Server::authRefresh);
    timer->start(10*60*1000); // 10 minutes in milliseconds
}

Server::~Server() {
    delete networkManager;
    //delete m_instance;
}

void Server::authRegister(const QString& username, const QString& displayName,
                          const QString& email, const QString& password, const QString& birthDate)
{
    QUrl url(this->domen + this->routes["auth_register"].second);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject data;
    data["user_name"]     = username;
    data["display_name"]  = displayName;
    data["email"]         = email;
    data["password"]      = password;
    data["birth_date"]    = birthDate;

    QJsonDocument jsonDoc(data);
    QByteArray jsonBytes = jsonDoc.toJson();

    QNetworkReply *reply = networkManager->sendCustomRequest(request, this->routes["auth_register"].first.toUtf8(), jsonBytes);

    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument responseJsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject responseJsonObj = responseJsonDoc.object();

        if ((reply->error() == QNetworkReply::NoError) && (responseJsonObj["status"].toInt() == 0))
        {
            emit registerSucsessful();
            qDebug() << "emit registerSucsessful";
        }
        else if ((reply->error() != QNetworkReply::NoError) && (responseJsonObj["status"].toInt() != 0))
        {
            emit registerUnsucsessful(responseJsonObj["error"].toString());
            qDebug() << "emit registerUnsucsessful";
        }
        reply->deleteLater();
    });
}

void Server::authLogin(const QString& login, const QString& password)
{
    auto* user = LibCore::User::instance();
    user->setPassword(password);

    QUrl url(this->domen + this->routes["auth_login"].second);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject data;
    data["login"]     = login;
    data["password"]  = password;

    QJsonDocument jsonDoc(data);
    QByteArray jsonBytes = jsonDoc.toJson();

    QNetworkReply *reply = networkManager->sendCustomRequest(request, this->routes["auth_login"].first.toUtf8(), jsonBytes);

    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument responseJsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject responseJsonObj = responseJsonDoc.object();

        if ((reply->error() == QNetworkReply::NoError) && (responseJsonObj["status"].toInt() == 0))
        {
            QJsonObject tokenJsonObj = responseJsonObj["tokens"].toObject();
            user->setAccessToken(tokenJsonObj["accessToken"].toString());
            user->setRefreshToken(tokenJsonObj["refreshToken"].toString());

            this->getCurrentUserInfo();
            emit loginSuccessful();
            qDebug() << "emit loginSuccessful";
        }
        else if ((reply->error() != QNetworkReply::NoError) && (responseJsonObj["status"].toInt() != 0))
        {
            emit loginUnsucsessful(responseJsonObj["error"].toString());
            qDebug() << "emit loginUnsucsessful";
        }
        reply->deleteLater();
    });
}

// void Server::authLogout()
// {

// }

void Server::authRefresh()
{
    auto* user = LibCore::User::instance();

    QUrl url(this->domen + this->routes["auth_refresh"].second);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject data;
    data["refreshToken"] = user->getRefreshToken();

    QJsonDocument jsonDoc(data);
    QByteArray jsonBytes = jsonDoc.toJson();

    QNetworkReply *reply = networkManager->sendCustomRequest(request, this->routes["auth_refresh"].first.toUtf8(), jsonBytes);

    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument responseJsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject responseJsonObj = responseJsonDoc.object();

        if ((reply->error() == QNetworkReply::NoError) && (responseJsonObj["status"].toInt() == 0))
        {
            QJsonObject tokenJsonObj = responseJsonObj["tokens"].toObject();
            user->setAccessToken(tokenJsonObj["accessToken"].toString());
            user->setRefreshToken(tokenJsonObj["refreshToken"].toString());
            qDebug() << "authRefresh sucsessful";
        }
        else if ((reply->error() != QNetworkReply::NoError) && (responseJsonObj["status"].toInt() != 0))
        {
            qDebug() << "authRefresh unsucsessful";
        }
        reply->deleteLater();
    });
}

void Server::getCurrentUserInfo()
{
    auto* user = LibCore::User::instance();

    QUrl url(this->domen + this->routes["get_current_user"].second);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + user->getAccessToken().toUtf8());
    QNetworkReply *reply = networkManager->sendCustomRequest(request, this->routes["get_current_user"].first.toUtf8());

    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        QByteArray responseData = reply->readAll();
        //qDebug() << responseData;
        QJsonDocument responseJsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject responseJsonObj = responseJsonDoc.object();

        if ((reply->error() == QNetworkReply::NoError) && (responseJsonObj["status"].toInt() == 0))
        {
            QJsonObject dataJsonObj = responseJsonObj["data"].toObject();

            user->setUserID(dataJsonObj["user_id"].toInt());
            user->setUsername(dataJsonObj["user_name"].toString());
            user->setDisplayName(dataJsonObj["display_name"].toString());
            user->setEmail(dataJsonObj["email"].toString());
            user->setBirthDate(dataJsonObj["birth_date"].toString());
            user->setPhoneNumber(dataJsonObj["phone_number"].toString());
        }
        else if ((reply->error() != QNetworkReply::NoError) && (responseJsonObj["status"].toInt() != 0))
        {
            qDebug() << "getCurrentUserInfo unsucsessful";
        }
    });
}


} // namespace LibCore


