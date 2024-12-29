#include "include/widgets.h"

SideBar::SideBar(QWidget *parent)
    :  BaseWidget(parent)
{
    this->initialize();
}

SideBar::~SideBar()
{
    delete chats_layout;
    delete functional_layout;
    delete user_layout;
}

void SideBar::initUI()
{
    this->setFixedWidth(200);
    this->setObjectName("SideBar");

    /*  Initialize layouts for side bar
     *
     *  main_layout - for all widget
     *  chats_layout - for chats
     *  functional_layout - for functional buttons: camera_button, display_button, microphone_button, sound_button, hung_up_button
     *  user_layout - for info about user: username and avatar
     *
     */
    this->main_layout = new QVBoxLayout(this);

    this->chats_layout = new QVBoxLayout();
    this->chats_layout->setAlignment(Qt::AlignTop);

    this->functional_layout = new QHBoxLayout();
    this->functional_layout->setAlignment(Qt::AlignBottom);

    this->user_layout = new QHBoxLayout();
    this->user_layout->setAlignment(Qt::AlignBottom);

    /*  Initialize buttons for side bar
     *
     *  camera_button - for turn on/off the user's camera
     *  display_button - for turn on/off ща demonstration user's screen
     *  microphone_button - for turn on/off user's microphone
     *  sound_button - for turn on/off user's sound
     *  hung_up_button - for end the call
     *  user_label_button - label with username and avatar which can send to user's settings
     *
     */
    this->camera_button = new QPushButton(this);
    this->camera_button->setObjectName("SideBarButton");
    this->camera_button->setIcon(QIcon(":/resources/images/camera.png"));
    this->camera_button->setIconSize(QSize(30, 30));

    this->display_button= new QPushButton(this);
    this->display_button->setObjectName("SideBarButton");
    this->display_button->setIcon(QIcon(":/resources/images/display.png"));
    this->display_button->setIconSize(QSize(30, 30));

    this->microphone_button = new QPushButton(this);
    this->microphone_button->setObjectName("SideBarButton");
    this->microphone_button->setIcon(QIcon(":/resources/images/microphone.png"));
    this->microphone_button->setIconSize(QSize(30, 30));

    this->sound_button = new QPushButton(this);
    this->sound_button->setObjectName("SideBarButton");
    this->sound_button->setIcon(QIcon(":/resources/images/sound.png"));
    this->sound_button->setIconSize(QSize(30, 30));

    this->hung_up_button = new QPushButton(this);
    this->hung_up_button->setObjectName("SideBarButton");
    this->hung_up_button->setIcon(QIcon(":/resources/images/hung_up.png"));
    this->hung_up_button->setIconSize(QSize(30, 30));

    this->user_label_button = new QPushButton("Username\nonline", this); /* TODO: fix online status and username */
    this->user_label_button->setObjectName("UserLabelButton");
    this->user_label_button->setIcon(QIcon(":/resources/images/default_user.png"));
    this->user_label_button->setIconSize(QSize(40, 40));

    /*
     *  Initialize search box for side bar
     */
    this->search_box = new QLineEdit(this);
    this->search_box->setObjectName("SideBarSearchBox");
    QAction *icon_action = new QAction(QIcon(":/resources/images/search_box_icon.png"), "", search_box);
    this->search_box->addAction(icon_action, QLineEdit::TrailingPosition);

    /*
     *  Add buttons to layouts
     */
    this->chats_layout->addWidget(search_box);

    this->functional_layout->addWidget(this->camera_button);
    this->functional_layout->addWidget(this->display_button);
    this->functional_layout->addWidget(this->microphone_button);
    this->functional_layout->addWidget(this->sound_button);
    this->functional_layout->addWidget(this->hung_up_button);

    /*TODO: fix this shit*/
    this->user_layout->addWidget(this->user_label_button);

    /*
     *  Add sub-layouts to main layout
     */
    this->main_layout->addLayout(this->chats_layout);
    this->main_layout->addStretch();
    this->main_layout->addLayout(this->functional_layout);
    this->main_layout->addLayout(this->user_layout);

    /*
     *  Set layout for widget
     */
    setLayout(this->main_layout);

    //this->main_layout->setContentsMargins(0,0,0,0);
    this->main_layout->setSpacing(0);
}

