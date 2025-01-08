#include "core.h"

namespace LibCore {

Logger* Logger::m_instance = nullptr;
QMutex Logger::mutex;

Logger::Logger() {}

Logger::~Logger()
{
    if (this->logFile.isOpen())
    {
        this->logFile.close();
    }

    delete m_instance;
    m_instance = nullptr;
}

Logger* Logger::instance()
{
    if (m_instance == nullptr)
    {
        QMutexLocker locker(&mutex);
        m_instance = new Logger();
    }
    return m_instance;

}

void Logger::setLogFile(const QString& logFilePath)
{
    QMutexLocker locker(&mutex);

    if (QFile::exists(logFilePath))
    {
        if (this->logFile.isOpen())
        {
            this->logFile.close();
        }

        QFile::remove(logFilePath);
    }

    QFileInfo fileInfo(logFilePath);
    QDir dir = fileInfo.absoluteDir();
    if (!dir.exists())
    {
        dir.mkpath(".");
    }

    this->logFile.setFileName(logFilePath);
    this->logFile.open(QIODevice::Append | QIODevice::Text);
}

void Logger::flush()
{
    if (!this->buffer.isEmpty() && this->logFile.isOpen())
    {
        QTextStream out(&this->logFile);
        out << this->buffer;
        out.flush();
        this->buffer.clear();
    }
}

QString Logger::logLevelToString(logLevel level) const
{
    switch (level)
    {
        case Debug: return "DEBUG";
        case Info: return "INFO";
        case Warning: return "WARNING";
        case Error: return "ERROR";
        case Critical: return "CRITICAL";
    }

    return "UNKNOWN";
}

}
