#include "include/widgets.h"
#include "include/core.h"

/***********************************************************************************
 *
 *      SettingsAccountWidget - class for widget with user account settings
 *
 ***********************************************************************************/

SettingsAccountWidget::SettingsAccountWidget(QWidget *parent, QStackedWidget *stack)
    :BaseWidget(parent), stackedWidget(stack)
{
    this->initialize();
}

SettingsAccountWidget::~SettingsAccountWidget()
{
    delete usernameLayout;
    delete displayNameLayout;
    delete emailLayout;
    delete phoneNumberLayout;
    delete birthDateLayout;
    delete statusLayout;
}

void SettingsAccountWidget::initUI()
{
    auto* user = LibCore::User::instance();

    this->setObjectName("SettingsAccountWidget");
    this->setContentsMargins(0, 0, 0, 0);

    /*  Initialize layouts for account settings widget
     *
     *  mainLayout - for all widget
     *  usernameLayout - for username
     *  displayNameLayout - for display name
     *  emailLayout - for user's email
     *  phoneNumberLayout - for user's phone number
     *  birthDateLayout - for user's birth date
     *  statusLayout - for user's status (online, offline, etc...)
     *
     */
    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->setAlignment(Qt::AlignTop);
    this->mainLayout->setContentsMargins(0, 0, 0, 0);

    this->usernameLayout = new QHBoxLayout();
    this->usernameLayout->setContentsMargins(0, 0, 0, 0);

    this->displayNameLayout = new QHBoxLayout();
    this->displayNameLayout->setContentsMargins(0, 0, 0, 0);

    this->emailLayout = new QHBoxLayout();
    this->emailLayout->setContentsMargins(0, 0, 0, 0);

    this->phoneNumberLayout = new QHBoxLayout();
    this->phoneNumberLayout->setContentsMargins(0, 0, 0, 0);

    this->birthDateLayout = new QHBoxLayout();
    this->birthDateLayout->setContentsMargins(0, 0, 0, 0);

    this->statusLayout = new QHBoxLayout();
    this->statusLayout->setContentsMargins(0, 0, 0, 0);

    /*  Initialize labels for account settings widget
     *
     *  mainLabel - for name of setting widget
     *  usernameLabel - for username
     *  displayNameLabel - for display name
     *  emailLabel - for user's email
     *  phoneNumberLabel - for user's phone number
     *  birthDateLabel - for user's birth date
     *  statusLabel - for user's status (online, offline, etc...)
     *
     */
    this->mainLabel = new QLabel("Account", this);
    this->mainLabel->setAlignment(Qt::AlignCenter);
    this->mainLabel->setObjectName("MainLabel");
    this->mainLabel->setContentsMargins(0, 0, 0, 0);

    this->usernameLabel = new QLabel("Username", this);

    this->displayNameLabel = new QLabel("Display name", this);

    this->emailLabel = new QLabel("Email", this);

    this->phoneNumberLabel = new QLabel("Phone number", this);

    this->birthDateLabel = new QLabel("Birth date", this);

    this->statusLabel = new QLabel("Status", this);

    /*  Initialize fields for account settings widget
     *
     *  usernameField - for username
     *  displayNameField - for display name
     *  emailField - for user's email
     *  phoneNumberField - for user's phone number
     *  birthDateField - for user's birth date
     *  statusField (QComboBox) - for user's status (online, offline, etc...)
     *
     */

    QSize fieldFixedSize(500, 40);
    this->usernameField = new QLineEdit(user->getUsername(), this);
    this->usernameField->setObjectName("SettingsWidgetField");
    this->usernameField->setFixedSize(fieldFixedSize);

    this->displayNameField = new QLineEdit(user->getDisplayName(), this);
    this->displayNameField->setObjectName("SettingsWidgetField");
    this->displayNameField->setFixedSize(fieldFixedSize);

    this->emailField = new QLineEdit(user->getEmail(), this);
    this->emailField->setObjectName("SettingsWidgetField");
    this->emailField->setFixedSize(fieldFixedSize);

    this->phoneNumberField = new QLineEdit(user->getPhoneNumber(), this);
    this->phoneNumberField->setObjectName("SettingsWidgetField");
    this->phoneNumberField->setFixedSize(fieldFixedSize);

    this->birthDateField = new QLineEdit(user->getBirthDate(), this);
    this->birthDateField->setObjectName("SettingsWidgetField");
    this->birthDateField->setFixedSize(fieldFixedSize);

    this->statusField = new QComboBox(this);
    this->statusField->setObjectName("SettingsWidgetStatusComboBox");
    this->statusField->setFixedSize(fieldFixedSize);
    QStringList statuses = {"Online", "Offline", "Do not disturb", "Invisible"};
    this->statusField->addItems(statuses);
    int index = statusField->findText("Online");
    if (index != -1)
    {
        statusField->setCurrentIndex(index);
    }

    /*
     *  Add components to layouts
     */
    this->usernameLayout->addWidget(this->usernameField);
    this->usernameLayout->addWidget(this->usernameLabel);

    this->displayNameLayout->addWidget(this->displayNameField);
    this->displayNameLayout->addWidget(this->displayNameLabel);

    this->emailLayout->addWidget(this->emailField);
    this->emailLayout->addWidget(this->emailLabel);

    this->phoneNumberLayout->addWidget(this->phoneNumberField);
    this->phoneNumberLayout->addWidget(this->phoneNumberLabel);

    this->birthDateLayout->addWidget(this->birthDateField);
    this->birthDateLayout->addWidget(this->birthDateLabel);

    this->statusLayout->addWidget(this->statusField);
    this->statusLayout->addWidget(this->statusLabel);

    /*
     *  Add sub-layouts to main layout
     */
    this->mainLayout->addWidget(this->mainLabel);
    this->mainLayout->addLayout(this->usernameLayout);
    this->mainLayout->addLayout(this->displayNameLayout);
    this->mainLayout->addLayout(this->emailLayout);
    this->mainLayout->addLayout(this->phoneNumberLayout);
    this->mainLayout->addLayout(this->birthDateLayout);
    this->mainLayout->addLayout(this->statusLayout);

    /*
     *  Set layout for widget
     */
    setLayout(this->mainLayout);
}


/***********************************************************************************
 *
 *    SettingsAppearanceWidget - class for widget with app appearance settings
 *
 ***********************************************************************************/

SettingsAppearanceWidget::SettingsAppearanceWidget(QWidget *parent, QStackedWidget *stack)
    :BaseWidget(parent), stackedWidget(stack)
{
    this->initialize();
}

SettingsAppearanceWidget::~SettingsAppearanceWidget()
{
    delete themeLayout;
    delete languageLayout;
}

void SettingsAppearanceWidget::initUI()
{
    this->setObjectName("SettingsAppearanceWidget");

    /*  Initialize layouts for appearance settings widget
     *
     *  mainLayout - for all widget
     *  themeLayout - for theme
     *  languageLayout - for language
     *
     */
    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->setAlignment(Qt::AlignTop);
    this->mainLayout->setContentsMargins(0, 0, 0, 0);

    this->themeLayout = new QHBoxLayout();
    this->themeLayout->setContentsMargins(0, 0, 0, 0);

    this->languageLayout = new QHBoxLayout();
    this->languageLayout->setContentsMargins(0, 0, 0, 0);

    /*  Initialize labels for appearance settings widget
     *
     *  mainLabel - for name of setting widget
     *  themeLabel - for theme
     *  languageLabel - for language
     *
     */
    this->mainLabel = new QLabel("Appearance", this);
    this->mainLabel->setAlignment(Qt::AlignCenter);
    this->mainLabel->setObjectName("MainLabel");
    this->mainLabel->setContentsMargins(0, 0, 0, 0);

    this->themeLabel = new QLabel("Theme", this);

    this->languageLabel = new QLabel("Language", this);

    /*  Initialize checkboxes for appearance settings widget
     *
     *  darkThemeCheckBox - switch to dark theme
     *  lightThemeCheckBox - switch to light theme
     *  ruLanguageCheckBox - switch to russian language
     *  enLanguageCheckBox - switch to english language
     *
     */
    QSize checkBoxFixedSize(350, 40);
    this->darkThemeCheckBox = new QCheckBox("Dark", this);
    this->darkThemeCheckBox->setFixedSize(checkBoxFixedSize);
    this->darkThemeCheckBox->setObjectName("SettingsCheckBox");
    connect(this->darkThemeCheckBox, &QCheckBox::clicked,  this, &SettingsAppearanceWidget::onDarkThemeCheckBoxClicked);

    this->lightThemeCheckBox = new QCheckBox("Light", this);
    this->lightThemeCheckBox->setFixedSize(checkBoxFixedSize);
    this->lightThemeCheckBox->setObjectName("SettingsCheckBox");
    this->lightThemeCheckBox->setChecked(true);
    connect(this->lightThemeCheckBox, &QCheckBox::clicked, this, &SettingsAppearanceWidget::onLightThemeCheckBoxClicked);

    this->ruLanguageCheckBox = new QCheckBox("ru", this);
    this->ruLanguageCheckBox->setFixedSize(checkBoxFixedSize);
    this->ruLanguageCheckBox->setObjectName("SettingsCheckBox");
    connect(this->ruLanguageCheckBox, &QCheckBox::clicked, this, &SettingsAppearanceWidget::onRuLanguageCheckBoxClicked);

    this->enLanguageCheckBox = new QCheckBox("en", this);
    this->enLanguageCheckBox->setFixedSize(checkBoxFixedSize);
    this->enLanguageCheckBox->setObjectName("SettingsCheckBox");
    this->enLanguageCheckBox->setChecked(true);
    connect(this->enLanguageCheckBox, &QCheckBox::clicked, this, &SettingsAppearanceWidget::onEnLanguageCheckBoxClicked);

    /*
     *  Add components to layouts
     */
    this->themeLayout->addWidget(darkThemeCheckBox);
    this->themeLayout->addWidget(lightThemeCheckBox);
    this->themeLayout->addWidget(themeLabel);

    this->languageLayout->addWidget(ruLanguageCheckBox);
    this->languageLayout->addWidget(enLanguageCheckBox);
    this->languageLayout->addWidget(languageLabel);

    /*
     *  Add sub-layouts to main layout
     */
    this->mainLayout->addWidget(this->mainLabel);
    this->mainLayout->addLayout(this->themeLayout);
    this->mainLayout->addLayout(this->languageLayout);

    /*
     *  Set layout for widget
     */
    setLayout(this->mainLayout);
}

void SettingsAppearanceWidget::onDarkThemeCheckBoxClicked()
{
    if (this->lightThemeCheckBox->isChecked())
    {
        this->lightThemeCheckBox->setChecked(false);
    }
    else
    {
        this->darkThemeCheckBox->setChecked(true);
    }
}

void SettingsAppearanceWidget::onLightThemeCheckBoxClicked()
{
    if (this->darkThemeCheckBox->isChecked())
    {
        this->darkThemeCheckBox->setChecked(false);
    }
    else
    {
        this->lightThemeCheckBox->setChecked(true);
    }
}

void SettingsAppearanceWidget::onRuLanguageCheckBoxClicked()
{
    if (this->enLanguageCheckBox->isChecked())
    {
        this->enLanguageCheckBox->setChecked(false);
    }
    else
    {
        this->ruLanguageCheckBox->setChecked(true);
    }
}

void SettingsAppearanceWidget::onEnLanguageCheckBoxClicked()
{
    if (this->ruLanguageCheckBox->isChecked())
    {
        this->ruLanguageCheckBox->setChecked(false);
    }
    else
    {
        this->enLanguageCheckBox->setChecked(true);
    }
}


/***********************************************************************************
 *
 *          SettingsWidget - class for widget with all settings
 *
 ***********************************************************************************/
SettingsWidget::SettingsWidget(QWidget *parent, QStackedWidget *stack)
    :BaseWidget(parent), stackedWidget(stack)
{
    this->initialize();
}

SettingsWidget::~SettingsWidget()
{
    delete navigationBarLayout;
    delete editPanelLayout;
    delete closePanelLayout;
}

void SettingsWidget::initUI()
{
    this->setObjectName("SettingsWidget");

    /*  Initialize layouts for settings widget
     *
     *  mainLayout - for all widget
     *  navigationBarLayout - for navigation bar
     *  editPanelLayout - for edit panel
     *  closePanelLayout - for close button
     *
     */
    this->mainLayout = new QHBoxLayout(this);
    this->mainLayout->setContentsMargins(0, 0, 0, 0);
    this->mainLayout->setSpacing(0);

    this->navigationBarLayout = new QVBoxLayout();
    this->navigationBarLayout->setAlignment(Qt::AlignTop);
    this->navigationBarContainer = new QWidget(this);
    this->navigationBarContainer->setLayout(this->navigationBarLayout);
    this->navigationBarContainer->setObjectName("NavigationBar");

    this->editPanelLayout = new QHBoxLayout();
    this->editPanelLayout->setAlignment(Qt::AlignTop);
    this->editPanelContainer = new QWidget(this);
    this->editPanelContainer->setLayout(this->editPanelLayout);
    this->editPanelContainer->setObjectName("EditPanel");

    this->closePanelLayout = new QHBoxLayout();
    this->closePanelLayout->setAlignment(Qt::AlignTop);
    this->closePanelContainer = new QWidget(this);
    this->closePanelContainer->setLayout(this->closePanelLayout);
    this->closePanelContainer->setObjectName("NavigationBar");

    /*  Initialize buttons for navigationBarLayout
     *
     *  userAccountButton - go to user settings
     *  appearanceButton - go to appearance settings
     *  closeSettingsButton - go back to main screen
     *  to be continued....
     *
     */

    this->userAccountButton = new QPushButton("Account", this);
    this->userAccountButton->setObjectName("SettingsNavigationBarButton");
    connect(this->userAccountButton, &QPushButton::clicked, this, &SettingsWidget::onUserAccountButtonClicked);

    this->appearanceButton = new QPushButton("Appearance", this);
    this->appearanceButton->setObjectName("SettingsNavigationBarButton");
    connect(this->appearanceButton, &QPushButton::clicked, this, &SettingsWidget::onAppearanceButtonClicked);

    this->closeSettingsButton = new QPushButton("close", this);
    this->closeSettingsButton->setObjectName("SettingsNavigationBarButton");
    connect(this->closeSettingsButton, &QPushButton::clicked, this, &SettingsWidget::onCloseSettingsButtonClicked);

    /*  Initialize widgets for editPanelLayout
     *
     *  stackedWidget - for storing all widgets in editPanelLayout
     *  SettingsAccountWidget - for user settings
     *  SettingsAppearanceWidget - for appearance settings
     *  to be continued....
     *
     */

    this->stackedWidget = new QStackedWidget(this);
    this->settingsAccountWidget = new SettingsAccountWidget(this, this->stackedWidget);
    this->settingsAppearanceWidget = new SettingsAppearanceWidget(this, this->stackedWidget);
    // to be continued....

    this->stackedWidget->addWidget(settingsAccountWidget);
    this->stackedWidget->addWidget(settingsAppearanceWidget);
    this->stackedWidget->setCurrentWidget(settingsAccountWidget);

    /*
     *  Add components to layouts
     */
    this->navigationBarLayout->addWidget(this->userAccountButton);
    this->navigationBarLayout->addWidget(this->appearanceButton);
    this->editPanelLayout->addWidget(this->stackedWidget);
    this->closePanelLayout->addWidget(this->closeSettingsButton);

    /*
     *  Add sub-layouts to main layout
     */
    this->mainLayout->addWidget(this->navigationBarContainer);
    this->mainLayout->addWidget(this->editPanelContainer);
    this->mainLayout->addWidget(this->closePanelContainer);

    /*
     *  Set layout for widget
     */
    setLayout(this->mainLayout);
}

void SettingsWidget::onUserAccountButtonClicked()
{
    this->stackedWidget->setCurrentWidget(this->settingsAccountWidget);
}

void SettingsWidget::onAppearanceButtonClicked()
{
    this->stackedWidget->setCurrentWidget(this->settingsAppearanceWidget);
}

void SettingsWidget::onCloseSettingsButtonClicked()
{
    emit this->closeSettings();
}
