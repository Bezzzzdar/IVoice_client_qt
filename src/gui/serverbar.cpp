#include "serverbar.h"

ServerBar::ServerBar(QWidget *parent)
    : BaseWidget(parent)
{
    this->initialize();
}

ServerBar::~ServerBar()
{
    delete serversLayout;
    delete functionalLayout;
}

void ServerBar::initUI()
{
    this->setFixedWidth(50);
    this->setObjectName("ServerBar");

    /*  Initialize layouts for server bar
     *
     *  mainLayout - for all widget
     *  serversLayout - for servers and button for add server
     *  functionalLayout - for functional buttons: settingsButton and directMessagesButton
     *
     */
    this->mainLayout = new QVBoxLayout(this);

    this->serversLayout = new QVBoxLayout();
    this->serversLayout->setAlignment(Qt::AlignTop);

    this->functionalLayout = new QVBoxLayout();
    this->functionalLayout->setAlignment(Qt::AlignBottom);

    /*  Initialize buttons for server bar
     *
     *  addServerButton - button for adding new server
     *  settingsButton - button to view and change account settings
     *  directMessagesButton - button to go to users direct messages
     *
     */
    this->addServerButton = new QPushButton(this);
    this->addServerButton->setObjectName("ServerBarButton");
    this->addServerButton->setIcon(QIcon(":/resources/images/add_server_white.png"));
    this->addServerButton->setIconSize(QSize(40, 40));

    this->settingsButton = new QPushButton(this);
    this->settingsButton->setObjectName("ServerBarButton");
    this->settingsButton->setIcon(QIcon(":/resources/images/settings_white.png"));
    this->settingsButton->setIconSize(QSize(40, 40));
    connect(this->settingsButton, &QPushButton::clicked, this, &ServerBar::onSettingsButtonClicked);

    this->directMessagesButton = new QPushButton(this);
    this->directMessagesButton->setObjectName("ServerBarButton");
    this->directMessagesButton->setIcon(QIcon(":/resources/images/direct_messages_white.png"));
    this->directMessagesButton->setIconSize(QSize(40, 40));

    /*
     *  Add buttons to layouts
     */
    this->serversLayout->addWidget(this->addServerButton);

    this->functionalLayout->addWidget(this->directMessagesButton);
    this->functionalLayout->addWidget(this->settingsButton);

    /*
     *  Add sub-layouts to main layout
     */
    this->mainLayout->addLayout(this->serversLayout);
    this->mainLayout->addLayout(this->functionalLayout);

    /*
     *  Set layout for widget
     */
    setLayout(this->mainLayout);

    this->mainLayout->setContentsMargins(0,0,0,0);
    this->mainLayout->setSpacing(0);
}

void ServerBar::onSettingsButtonClicked()
{
    emit this->showSettingsWidget();
}

