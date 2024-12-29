#include "include/widgets.h"

ServerBar::ServerBar(QWidget *parent)
    : BaseWidget(parent)
{
    this->initialize();
}

ServerBar::~ServerBar()
{
    delete servers_layout;
    delete functional_layout;
}

void ServerBar::initUI()
{
    this->setFixedWidth(50);
    this->setObjectName("ServerBar");

    /*  Initialize layouts for server bar
     *
     *  main_layout - for all widget
     *  servers_layout - for servers and button for add server
     *  functional_layout - for functional buttons: settings_button and direct_messages_button
     *
     */
    this->main_layout = new QVBoxLayout(this);

    this->servers_layout = new QVBoxLayout();
    this->servers_layout->setAlignment(Qt::AlignTop);

    this->functional_layout = new QVBoxLayout();
    this->functional_layout->setAlignment(Qt::AlignBottom);

    /*  Initialize buttons for server bar
     *
     *  add_server_button - button for adding new server
     *  settings_button - button to view and change account settings
     *  direct_messages_button - button to go to users direct messages
     *
     */
    this->add_server_button = new QPushButton(this);
    this->add_server_button->setObjectName("ServerBarButton");
    this->add_server_button->setIcon(QIcon(":/resources/images/add_server_white.png"));
    this->add_server_button->setIconSize(QSize(40, 40));

    this->settings_button = new QPushButton(this);
    this->settings_button->setObjectName("ServerBarButton");
    this->settings_button->setIcon(QIcon(":/resources/images/settings_white.png"));
    this->settings_button->setIconSize(QSize(40, 40));

    this->direct_messages_button = new QPushButton(this);
    this->direct_messages_button->setObjectName("ServerBarButton");
    this->direct_messages_button->setIcon(QIcon(":/resources/images/direct_messages_white.png"));
    this->direct_messages_button->setIconSize(QSize(40, 40));

    /*
     *  Add buttons to layouts
     */
    this->servers_layout->addWidget(this->add_server_button);

    this->functional_layout->addWidget(this->direct_messages_button);
    this->functional_layout->addWidget(this->settings_button);

    /*
     *  Add sub-layouts to main layout
     */
    this->main_layout->addLayout(this->servers_layout);
    this->main_layout->addLayout(this->functional_layout);

    /*
     *  Set layout for widget
     */
    setLayout(this->main_layout);

    this->main_layout->setContentsMargins(0,0,0,0);
    this->main_layout->setSpacing(0);
}

