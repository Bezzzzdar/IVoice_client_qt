#include "include/core.h"

namespace LibCore {

User* User::m_instance = nullptr;
QMutex User::mutex;

User::User(QObject* parent)
    :QObject(parent)
{

}

User::~User()
{

}

User* User::instance(QObject* parent)
{
    if (!m_instance)
    {
        QMutexLocker locker(&mutex);
        m_instance = new User(parent);
    }
    return m_instance;
}

/*************************************************************
 *
 *                          Setters
 *
 ************************************************************/
void User::setAccessToken(const QString& accessToken)
{
    this->accessToken = accessToken;
}

void User::setRefreshToken(const QString& refreshToken)
{
    this->refreshToken = refreshToken;
}

void User::setUsername(const QString& username)
{
    this->username = username;
}

void User::setDisplayName(const QString& display_name)
{
    this->display_name = display_name;
}

void User::setEmail(const QString& email)
{
    this->email = email;
}

void User::setPhoneNumber(const QString& phone_number)
{
    this->phone_number = phone_number;
}

void User::setPassword(const QString& password)
{
    this->password = password;
}

void User::setBirthDate(QDate birth_date)
{
    this->birth_date = birth_date;
}

/*************************************************************
 *
 *                          Getters
 *
 ************************************************************/
QString User::getAccessToken()
{
    return this->accessToken;
}

QString User::getRefreshToken()
{
    return this->refreshToken;
}

QString User::getUsername()
{
    return this->username;
}

QString User::getDisplayName()
{
    return this->display_name;
}

QString User::getEmail()
{
    return this->email;
}

QString User::getPhoneNumber()
{
    return this->phone_number;
}

QString User::getPassword()
{
    return this->password;
}

QDate User::getBirthDate()
{
    return this->birth_date;
}
} // namespace LibCore
