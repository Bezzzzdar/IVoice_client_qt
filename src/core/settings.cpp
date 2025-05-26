#include "core.h"

namespace LibCore {

Settings::Settings()
    : QSettings("config/config.ini", QSettings::IniFormat)
{
}

Settings::~Settings()
{
}

Settings* Settings::instance()
{
    static Settings settings_instance;
    return &settings_instance;
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
