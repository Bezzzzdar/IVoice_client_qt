#include "core.h"

namespace LibCore {

Server* Server::instance(const QString& serverAddress, const int serverPort)
{
    static Server server_instance(serverAddress, serverPort);
    return &server_instance;
}

Server::Server(const QString& serverAddress, const int serverPort, QObject* parent)
    : QObject(parent),
    domain("http://" + serverAddress + ":" + QString::number(serverPort)),
    networkManager(new QNetworkAccessManager(this)),
    timer(new QTimer(this))
{
    this->routes =
    {
        // auth
        {RequestTypeAuthRegister,                     qMakePair("POST", "/auth/register")},
        {RequestTypeAuthLogin,                        qMakePair("POST", "/auth/login")},
        {RequestTypeAuthLogout,                       qMakePair("POST", "/tokens/logout")},
        {RequestTypeAuthRefresh,                      qMakePair("POST", "/tokens/refresh")},

        // users
        {RequestTypeGetCurrentUser,                   qMakePair("GET", "/users/me")},
        {RequestTypeUpdateCurrentUser,                qMakePair("PATCH", "/users")},
        {RequestTypeDeleteCurrentUser,                qMakePair("DEL", "/users")},
        {RequestTypeGetCurrentUserDetails,            qMakePair("GET", "/users/details")},
        {RequestTypeUpdateCurrentUserDetails,         qMakePair("PATCH", "/users/details")},
        {RequestTypeDeleteCurrentUserDetails,         qMakePair("DEL", "/users/details")},
        {RequestTypeGetOtherUserInfo,                 qMakePair("GET", "/users/:user_id/details")}, // user_id ???
        {RequestTypeGetOtherUserDetails,              qMakePair("GET", "/users/:user_id/details")}, // user_id ???
        {RequestTypeUpdatePassword,                   qMakePair("POST", "/users/password")},

        // friends
        {RequestTypeGetFriendsList,                   qMakePair("GET", "/friends")},
        {RequestTypeSendFriendRequest,                qMakePair("POST", "/friends")},
        {RequestTypeHandleFriendRequest,              qMakePair("PATCH", "/friends/:requestId")}, // request_id ???
        {RequestTypeDeleteFriend,                     qMakePair("DEL", "/friends/:userId")}, // userId ???
        {RequestTypeGetUserFriends,                   qMakePair("GET", "/friends/:userId")}, // userId ???
    };

    /* connect signal for starting timer after login */
    QObject::connect(this, &LibCore::Server::loginSuccessful, this, &LibCore::Server::startTimer);

#ifdef GRPC
    // Создаем HTTP2-канал
    channel = std::make_shared<QGrpcHttp2Channel>(QUrl("http://91.122.46.91:50051")); // TODO: вынести в config!!!!

    // Инициализируем gRPC клиента
    authService = std::make_shared<auth::AuthService::Client>();
    authService->attachChannel(channel);
#endif // GRPC

}

Server::~Server()
{
    delete networkManager;
}

QUrl Server::createUrl(const requestType type) const
{
    QUrl url(this->domain + routes.value(type).second);
    return url;
}

void Server::startTimer()
{
    /* Set the timer for sending authRefresh() every 10 minutes*/
    QObject::connect(timer, &QTimer::timeout, this, &LibCore::Server::authRefresh);
    this->timer->start(DELAY_BETWEEN_REFRESH); // 10 minutes in milliseconds
}

void Server::authRegister(const QString& username, const QString& displayName,
                          const QString& email, const QString& password,
                          const QString& phoneNumber, const QString& birthDate)
{
    const QUrl url = this->createUrl(LibCore::Server::RequestTypeAuthRegister);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject data;
    data["user_name"]     = username;
    data["display_name"]  = displayName;
    data["email"]         = email;
    data["password"]      = password;
    data["phone_number"]  = phoneNumber;
    data["birth_date"]    = birthDate;

    const QJsonDocument jsonDoc(data);
    const QByteArray jsonBytes = jsonDoc.toJson();

    QNetworkReply *reply = networkManager->sendCustomRequest(request,
        this->routes.value(LibCore::Server::RequestTypeAuthRegister).first.toUtf8(), jsonBytes);

    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        const QByteArray responseData = reply->readAll();
        const QJsonDocument responseJsonDoc = QJsonDocument::fromJson(responseData);

        if (QJsonObject responseJsonObj = responseJsonDoc.object(); (reply->error() == QNetworkReply::NoError) &&
            (responseJsonObj["status"].toInt() == 0))
        {
            emit registerSuccessful();
            LOG(Info) << "Register user " << username << " successful\n";
        }
        else if ((reply->error() != QNetworkReply::NoError) && (responseJsonObj["status"].toInt() != 0))
        {
            emit registerUnsuccessful(responseJsonObj["error"].toString());
            LOG(Error) << "Register user " << username << " unsuccessful. " << "Error: " << responseJsonObj["error"].toString() << "\n";
        }
        reply->deleteLater();
    });
}

void Server::authLogin(const QString& login, const QString& password)
{
    const QUrl url = this->createUrl(LibCore::Server::RequestTypeAuthLogin);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject data;
    data["login"]     = login;
    data["password"]  = password;

    const QJsonDocument jsonDoc(data);
    const QByteArray jsonBytes = jsonDoc.toJson();

    QNetworkReply *reply = networkManager->sendCustomRequest(request,
        this->routes.value(LibCore::Server::RequestTypeAuthLogin).first.toUtf8(), jsonBytes);

    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        const QByteArray responseData = reply->readAll();
        const QJsonDocument responseJsonDoc = QJsonDocument::fromJson(responseData);
        if (QJsonObject responseJsonObj = responseJsonDoc.object(); (reply->error() == QNetworkReply::NoError) &&
            (responseJsonObj["status"].toInt() == 0))
        {
            auto* user = LibCore::User::instance();
            user->setPassword(password);

            QJsonObject dataJsonObj = responseJsonObj["data"].toObject();
            QJsonObject tokenJsonObj = dataJsonObj["tokens"].toObject();
            user->setAccessToken(tokenJsonObj["accessToken"].toString());
            user->setRefreshToken(tokenJsonObj["refreshToken"].toString());

            this->getCurrentUserInfo();
            emit loginSuccessful();
            LOG(Info) << "Login user " << login << " successful\n";
        }
        else if ((reply->error() != QNetworkReply::NoError) && (responseJsonObj["status"].toInt() != 0))
        {
            emit loginUnsuccessful(responseJsonObj["error"].toString());
            LOG(Error) << "Login user " << login << " unsuccessful. " << "Error: " << responseJsonObj["error"].toString() << "\n";
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

    const QUrl url = this->createUrl(LibCore::Server::RequestTypeAuthRefresh);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject data;
    data["refresh_token"] = user->getRefreshToken();

    const QJsonDocument jsonDoc(data);
    const QByteArray jsonBytes = jsonDoc.toJson();

    QNetworkReply *reply = networkManager->sendCustomRequest(request,
        this->routes.value(LibCore::Server::RequestTypeAuthRefresh).first.toUtf8(), jsonBytes);

    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        const QByteArray responseData = reply->readAll();
        const QJsonDocument responseJsonDoc = QJsonDocument::fromJson(responseData);
        if (QJsonObject responseJsonObj = responseJsonDoc.object(); (reply->error() == QNetworkReply::NoError) &&
            (responseJsonObj["status"].toInt() == 0))
        {
            QJsonObject dataJsonObj = responseJsonObj["data"].toObject();
            QJsonObject tokenJsonObj = dataJsonObj["tokens"].toObject();
            user->setAccessToken(tokenJsonObj["accessToken"].toString());
            user->setRefreshToken(tokenJsonObj["refreshToken"].toString());

            LOG(Info) << "Refresh tokens successful\n";
        }
        else if ((reply->error() != QNetworkReply::NoError) && (responseJsonObj["status"].toInt() != 0))
        {
            LOG(Critical) << "Refresh tokens unsuccessful\n";
        }
        reply->deleteLater();
    });
}

void Server::getCurrentUserInfo()
{
    auto* user = LibCore::User::instance();

    const QUrl url = this->createUrl(LibCore::Server::RequestTypeGetCurrentUser);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "Bearer " + user->getAccessToken().toUtf8());
    QNetworkReply *reply = networkManager->sendCustomRequest(request,
        this->routes.value(LibCore::Server::RequestTypeGetCurrentUser).first.toUtf8());

    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        const QByteArray responseData = reply->readAll();
        const QJsonDocument responseJsonDoc = QJsonDocument::fromJson(responseData);

        if (QJsonObject responseJsonObj = responseJsonDoc.object(); (reply->error() == QNetworkReply::NoError) &&
            (responseJsonObj["status"].toInt() == 0))
        {
            QJsonObject dataJsonObj = responseJsonObj["data"].toObject();

            user->setUserID(dataJsonObj["user_id"].toInt());
            user->setUsername(dataJsonObj["user_name"].toString());
            user->setDisplayName(dataJsonObj["display_name"].toString());
            user->setEmail(dataJsonObj["email"].toString());
            user->setPhoneNumber(dataJsonObj["phone_number"].toString());
            user->setBirthDate(dataJsonObj["birth_date"].toString());

            QJsonObject statusJsonObj = dataJsonObj["status"].toObject();

            user->setStatus(statusJsonObj["status"].toString());
            user->setLastActivity(statusJsonObj["last_activity"].toString());
            user->setLastOnline(statusJsonObj["last_online"].toString());

            LOG(Info) << "Get current user info successful\n";
        }
        else if ((reply->error() != QNetworkReply::NoError) && (responseJsonObj["status"].toInt() != 0))
        {
            LOG(Critical) << "Get current user info unsuccessful\n";
        }
    });
}

#ifdef GRPC
/*-------------------- gRPC functions --------------------*/

void Server::authLoginGrpc(const QString& login, const QString& password)
{
    auth::LoginRequest request;
    request.setLogin(login);
    request.setPassword(password);

    std::unique_ptr<QGrpcCallReply> reply = authService->Login(request);

    auto *replyPtr = reply.get();

    QObject::connect(replyPtr, &QGrpcCallReply::finished, this, [this, reply = std::move(reply), login, password](const QGrpcStatus &status)
    {
        if (!status.isOk())
        {
            LOG(Error) << "Couldn't login user " << login << ". Stream error(" << int(status.code()) << "): " << status.message() << "\n";
            emit loginUnsuccessful("Couldn't login due to internal server error");
            return;
        }

        auto response = reply.get()->read<auth::LoginResponse>();
        if (response->status() == 0)
        {
            auto* user = LibCore::User::instance();
            user->setPassword(password);

            auto userData = response->data().user();
            auto userTokens = response->data().tokens();

            user->setAccessToken(userTokens.accessToken());
            user->setRefreshToken(userTokens.refreshToken());

            user->setUserID(userData.userId());
            user->setUsername(userData.userName());
            user->setDisplayName(userData.displayName());
            user->setEmail(userData.email());
            user->setPhoneNumber(userData.phoneNumber());
            user->setBirthDate(userData.birthDate());

            emit loginSuccessful();
            LOG(Info) << "Sucsessful login user " << login << "\n";
        }
        else
        {
            emit loginUnsuccessful("Couldn't login due to internal server error");
            LOG(Error) << "Couldn't login user " << login << " due to internal server error\n";
        }
    });
}

void Server::authRegisterGrpc(const QString& username, const QString& displayName,
                              const QString& email, const QString& password, const QString& birthDate)
{
    auth::RegisterRequest request;
    request.setUserName(username);
    request.setDisplayName(displayName);
    request.setEmail(email);
    request.setPassword(password);
    request.setPhoneNumber("89818064354"); // TODO: fix this shit!
    request.setBirthDate(birthDate);

    std::unique_ptr<QGrpcCallReply> reply = authService->Register(request);

    auto *replyPtr = reply.get();

    QObject::connect(replyPtr, &QGrpcCallReply::finished, this, [this, reply = std::move(reply), username](const QGrpcStatus &status)
    {
        if (!status.isOk())
        {
            LOG(Error) << "Couldn't register user " << username << ". Stream error(" << int(status.code()) << "): " << status.message() << "\n";
            emit registerUnsuccessful("Couldn't register due to internal server error");
            return;
        }

        auto response = reply.get()->read<auth::RegisterResponse>();
        if (response->status() == 0)
        {
            emit registerSuccessful();
            LOG(Info) << "Sucsessful register user " << username << "\n";
        }
        else
        {
            emit registerUnsuccessful("Couldn't register due to internal server error");
            LOG(Error) << "Couldn't register user " << username << " due to internal server error\n";
        }
    });
}
#endif // GRPC

} // namespace LibCore


