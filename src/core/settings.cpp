#include "include/core.h"

namespace LibCore {

Settings* Settings::m_instance = nullptr;
QMutex Settings::mutex;

Settings::Settings()
    : QSettings("config/config.ini", QSettings::IniFormat)
{
}

Settings::~Settings()
{
}

Settings* Settings::instance()
{
    if (!m_instance)
    {
        QMutexLocker locker(&mutex);
        m_instance = new Settings();
    }
    return m_instance;
}

QVariant Settings::getSetting(const QString& key)
{
    return this->value(key);
}

void Settings::setSetting(const QString& key, const QVariant& value)
{
    this->setValue(key, value);
    this->sync();
}
} // namespace LibCore
