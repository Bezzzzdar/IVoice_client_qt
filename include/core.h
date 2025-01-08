/*!
 * @file core.h
 * @author Ivan Rastegaev
 * @brief Contains the definitions of core functions.
 */

#ifndef CORE_H
#define CORE_H

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
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QFileInfo>
#include <QDir>

/*!
 * @def LIBCORE_API
 * @brief Macro for exporting/importing library symbols.
 *
 * This macro ensures the correct handling of symbol visibility depending on the build context:
 * - If `LIBCORE_EXPORTS` is defined, symbols are exported (`Q_DECL_EXPORT`).
 * - Otherwise, symbols are imported (`Q_DECL_IMPORT`).
 */
#ifdef LIBCORE_EXPORTS
#  define LIBCORE_API Q_DECL_EXPORT
#else
#  define LIBCORE_API Q_DECL_IMPORT
#endif


/*!
 * @def LOG()
 * @brief Macro for logging messages with automatic context information.
 *
 * This macro simplifies the process of logging by automatically including
 * the log level, file name, line number, and function name in the log message.
 *
 * Usage example:
 * @code
 * LOG(Info) << "Application started";
 * LOG(Error) << "An error occurred";
 * @endcode
 *
 * The resulting log message format:
 * @code
 * [2025-01-08 14:24:40] [INFO] /path/to/file.cpp:42 (functionName) - Your log message
 * @endcode
 *
 * @param level The log level, one of the @ref LibCore::Logger::logLevel values (e.g., Debug, Info, Warning, Error, Critical).
 *
 * @see LibCore::Logger
 */
#define LOG(level) (*LibCore::Logger::instance()) << LibCore::Logger::level << __FILE__ << ":" << __LINE__ << ":" << " (" << Q_FUNC_INFO << ") - "

namespace LibCore
{

/*!
 * @class Server
 * @brief Manages communication with the server, handling authentication and user information retrieval.
 *
 * This class is responsible for managing network interactions with the backend server,
 * such as user registration, login, and fetching current user information.
 * It follows the Singleton design pattern to ensure a single instance across the application.
 */
class LIBCORE_API Server : public QObject
{
    Q_OBJECT

public:

    Server(const Server&) = delete;
    Server& operator = (const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator = (Server&&) = delete;

    /*!
     * @brief Retrieves the single instance of the class.
     * @param serverAddress The server address. Defaults to empty string
     * @param serverPort The server port. Defaults to 0
     * @return The instance of the class.
     */
    static Server* instance(const QString& serverAddress = "", int serverPort = 0);

    /*!
     * @brief Class destructor.
     */
    ~Server();

    /*!
     * @brief Registers a new user on the server.
     * @param username The username for the new user.
     * @param displayName The display name for the new user.
     * @param email The email address for the new user.
     * @param password The password for the new user.
     * @param birthDate The birth date of the user.
     */
    void authRegister(const QString& username, const QString& displayName,
                      const QString& email, const QString& password,
                      const QString& birthDate);

    /*!
     * @brief Authenticates a user by logging them in.
     * @param login The username, email or phone number for login.
     * @param password The password for login.
     */
    void authLogin(const QString& login, const QString& password);
    // Q_INVOKABLE void authLogout();

    /*!
     * @brief Retrieves the current user's information from the server.
     */
    void getCurrentUserInfo();

private:
    explicit Server(const QString& serverAddress, int serverPort, QObject* parent = nullptr);

    static Server* m_instance;                              ///< The single instance of the class.
    static QMutex mutex;                                    ///< Mutex for thread safety.

    QString domen;                                          ///< The domain of the server.
    QNetworkAccessManager* networkManager;                  ///< The network manager for handling requests.
    QHash<QString, QPair<QString, QString>> routes;         ///< Hash-table of server routes.
    QTimer* timer;                                          ///< Timer for periodic tasks.

private slots:

    /*!
     * @brief [Slot] Refreshes the authentication token periodically.
     */
    void authRefresh();

signals:
    /*!
     * @brief [Signal] Emitted when user registration is successful.
     * @see RegisterWindow::onRegisterSucsessful
     */
    void registerSucsessful();

    /*!
     * @brief [Signal] Emitted when user registration fails.
     * @param errorMessage The error message describing the failure.
     * @see RegisterWindow::onRegisterUnsucsessful
     */
    void registerUnsucsessful(const QString &errorMessage);

    /*!
     * @brief [Signal] Emitted when user login is successful.
     * @see LoginWindow::onLoginSuccessful
     */
    void loginSuccessful();

    /*!
     * @brief [Signal] Emitted when user login fails.
     * @param errorMessage The error message describing the failure.
     * @see LoginWindow::onLoginUnsuccessful
     */
    void loginUnsucsessful(const QString &errorMessage);
};


/*!
 * @class User
 * @brief Stores and manages the current user information.
 *
 * This class is a Singleton responsible for storing and providing access to the
 * authenticated user's information, such as their access token, personal details, and status.
 */
class LIBCORE_API User : public QObject
{
    Q_OBJECT

public:

    User(const User&) = delete;
    User& operator = (const User&) = delete;
    User(User&&) = delete;
    User& operator = (User&&) = delete;

    /*!
     * @brief Retrieves the single instance of the class.
     * @param parent Pointer to the parent object. Defaults to `nullptr`.
     * @return The instance of the class.
     */
    static User* instance(QObject* parent = nullptr);

    /*!
     * @brief Class destructor.
     */
    ~User();

    /*!
     * @brief Sets the user's access token.
     * @param accessToken The access token.
     */
    void setAccessToken(const QString& accessToken);

    /*!
     * @brief Sets the user's refresh token.
     * @param refreshToken The refresh token.
     */
    void setRefreshToken(const QString& refreshToken);

    /*!
     * @brief Sets the user's ID.
     * @param userID The user's ID.
     */
    void setUserID(int userID);

    /*!
     * @brief Sets the user's username.
     * @param username The username.
     */
    void setUsername(const QString& username);

    /*!
     * @brief Sets the user's display name.
     * @param displayName The display name.
     */
    void setDisplayName(const QString& displayName);

    /*!
     * @brief Sets the user's email.
     * @param email The email.
     */
    void setEmail(const QString& email);

    /*!
     * @brief Sets the user's phone number.
     * @param phoneNumber The phone number.
     */
    void setPhoneNumber(const QString& phoneNumber);

    /*!
     * @brief Sets the user's password.
     * @param password The password.
     */
    void setPassword(const QString& password);

    /*!
     * @brief Sets the user's birth date.
     * @param birthDate The birth date.
     */
    void setBirthDate(const QString& birthDate);

    /*!
     * @brief Sets the user's status (online/offline).
     * @param status The status.
     */
    void setStatus(const QString& status);


    /*!
     * @brief Retrieves the user's access token.
     * @return The access token.
     */
    QString getAccessToken();

    /*!
     * @brief Retrieves the user's refresh token.
     * @return The refresh token.
     */
    QString getRefreshToken();

    /*!
     * @brief Retrieves the user's ID.
     * @return The user ID.
     */
    int getUserID();

    /*!
     * @brief Retrieves the user's username.
     * @return The username.
     */
    QString getUsername();

    /*!
     * @brief Retrieves the user's display name.
     * @return The display name.
     */
    QString getDisplayName();

    /*!
     * @brief Retrieves the user's email.
     * @return The email.
     */
    QString getEmail();

    /*!
     * @brief Retrieves the user's phone number.
     * @return The phone number.
     */
    QString getPhoneNumber();

    /*!
     * @brief Retrieves the user's password.
     * @return The password.
     */
    QString getPassword();

    /*!
     * @brief Retrieves the user's birth date.
     * @return The birth date.
     */
    QString getBirthDate();

    /*!
     * @brief Retrieves the user's status.
     * @return The status.
     */
    QString getStatus();

private:
    explicit User(QObject* parent = nullptr);

    static User* m_instance;            ///< The single instance of the class.
    static QMutex mutex;                ///< Mutex for thread safety.

    QString accessToken;                ///< The user's access token.
    QString refreshToken;               ///< The user's refresh token.
    int userID;                         ///< The user's ID.
    QString username;                   ///< The user's username.
    QString displayName;                ///< The user's display name.
    QString email;                      ///< The user's email.
    QString phoneNumber;                ///< The user's phone number.
    QString password;                   ///< The user's password.
    QString birthDate;                  ///< The user's birth date.
    QString status;                     ///< The user's status (e.g., online or offline).
};


/*!
 * @class Settings
 * @brief Manages user and application settings.
 *
 * This class is responsible for handling application settings, including
 * reading and writing to a configuration file. It follows the Singleton pattern.
 */
class LIBCORE_API Settings  : public QSettings
{
    Q_OBJECT

public:

    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
    Settings(Settings&&) = delete;
    Settings& operator=(Settings&&) = delete;

    /*!
     * @brief Retrieves the single instance of the class.
     * @return The instance of the class.
     */
    static Settings* instance();

    /*!
     * @brief Class destructor.
     */
    ~Settings();

    /*!
     * @brief Retrieves a setting value.
     * @param key The key for the setting.
     * @return The value associated with the key.
     */
    QVariant getSetting(const QString& key);

    /*!
     * @brief Sets a setting value.
     * @param key The key for the setting.
     * @param value The value to set.
     */
    void setSetting(const QString& key, const QVariant& value);

private:
    explicit Settings();

    const QString configFilePath;           ///< The path to the configuration file.

    static Settings* m_instance;            ///< The single instance of the class.
    static QMutex mutex;                    ///< Mutex for thread safety.
};


/**
 * @class Logger
 * @brief A singleton class for logging messages to a file.
 *
 * The Logger class provides functionality for writing log messages to a file.
 * It supports multiple log levels and ensures thread safety using a mutex.
 * The class is designed as a singleton to ensure only one instance manages logging.
 *
 */
class LIBCORE_API Logger : public QObject
{
    Q_OBJECT

public:

    /*!
     * @enum logLevel
     * @brief Represents the different levels of logging.
     *
     * The log levels indicate the severity or type of the log message.
     * - Debug: Detailed debugging information.
     * - Info: General informational messages.
     * - Warning: Indications of potential issues.
     * - Error: Error messages indicating failures.
     * - Critical: Critical errors requiring immediate attention.
     */
    enum logLevel
    {
        Debug,
        Info,
        Warning,
        Error,
        Critical
    };

    /*!
     * @brief Retrieves the single instance of the class.
     * @return The instance of the class.
     */
    static Logger* instance();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    /*!
     * @brief Sets the log file path.
     *
     * If the file already exists, it will be cleared. If necessary, intermediate
     * directories in the path will be created automatically.
     *
     * @param logFilePath The file path where log messages will be written.
     */
    void setLogFile(const QString& logFilePath);

    Logger& operator<<(logLevel level)
    {
        QMutexLocker locker(&mutex);

        this->buffer = QString("[%1] [%2] ")
                           .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                           .arg(logLevelToString(level));
        return *this;
    }

    Logger& operator<<(const QString& message)
    {
        QMutexLocker locker(&mutex);

        this->buffer += message;
        this->flush();
        return *this;
    }

    Logger& operator<<(const char* message)
    {
        return *this << QString(message);
    }

    Logger& operator<<(int value)
    {
        return *this << QString::number(value);
    }

    Logger& operator<<(double value)
    {
        return *this << QString::number(value);
    }

    /*!
     * @brief Class destructor.
     *
     * Closes the log file if it is open.
     */
    ~Logger();

private:
    explicit Logger();

    /*!
     * @brief Flushes the current log message to the file.
     *
     * Writes the current buffer to the log file and clears the buffer.
     */
    void flush();

    /*!
     * @brief Converts a log level enum value to its string representation.
     *
     * @param level The log level to convert.
     * @return A QString representing the log level.
     */
    QString logLevelToString(logLevel level) const;

    static Logger* m_instance;              ///< The single instance of the class.
    static QMutex mutex;                    ///< Mutex for thread safety.

    QFile logFile;                          ///< The file where log messages are written.
    QString buffer;                         ///< Buffer for the current log message.

};

}   // namespace LibCore
#endif // CORE_H
