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
    QMutexLocker locker(&mutex);
    this->accessToken = accessToken;
}

void User::setRefreshToken(const QString& refreshToken)
{
    QMutexLocker locker(&mutex);
    this->refreshToken = refreshToken;
}

void User::setUserID(int userID)
{
    QMutexLocker locker(&mutex);
    this->userID = userID;
}

void User::setUsername(const QString& username)
{
    QMutexLocker locker(&mutex);
    this->username = username;
}

void User::setDisplayName(const QString& displayName)
{
    QMutexLocker locker(&mutex);
    this->displayName = displayName;
}

void User::setEmail(const QString& email)
{
    QMutexLocker locker(&mutex);
    this->email = email;
}

void User::setPhoneNumber(const QString& phoneNumber)
{
    QMutexLocker locker(&mutex);
    this->phoneNumber = phoneNumber;
}

void User::setPassword(const QString& password)
{
    QMutexLocker locker(&mutex);
    this->password = password;
}

void User::setBirthDate(const QString& birthDate)
{
    QMutexLocker locker(&mutex);
    this->birthDate = birthDate;
}
void User::setStatus(const QString& status)
{
    QMutexLocker locker(&mutex);
    this->status = status;
}

/*************************************************************
 *
 *                          Getters
 *
 ************************************************************/
QString User::getAccessToken()
{
    QMutexLocker locker(&mutex);
    return this->accessToken;
}

QString User::getRefreshToken()
{
    QMutexLocker locker(&mutex);
    return this->refreshToken;
}

int User::getUserID()
{
    QMutexLocker locker(&mutex);
    return this->userID;
}

QString User::getUsername()
{
    QMutexLocker locker(&mutex);
    return this->username;
}

QString User::getDisplayName()
{
    QMutexLocker locker(&mutex);
    return this->displayName;
}

QString User::getEmail()
{
    QMutexLocker locker(&mutex);
    return this->email;
}

QString User::getPhoneNumber()
{
    QMutexLocker locker(&mutex);
    return this->phoneNumber;
}

QString User::getPassword()
{
    QMutexLocker locker(&mutex);
    return this->password;
}

QString User::getBirthDate()
{
    QMutexLocker locker(&mutex);
    return this->birthDate;
}

QString User::getStatus()
{
    QMutexLocker locker(&mutex);
    return this->status;
}

} // namespace LibCore
