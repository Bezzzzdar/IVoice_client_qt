#include "core.h"

namespace LibCore {
QMutex Logger::mutex;

Logger::Logger() {}

Logger::~Logger()
{
    if (this->logFile.isOpen())
    {
        this->logFile.close();
    }
}

Logger* Logger::instance()
{
    static Logger logger_instance;
    return &logger_instance;
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

QString Logger::logLevelToString(const logLevel level) {
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
