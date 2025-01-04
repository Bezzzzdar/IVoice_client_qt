#include "include/widgets.h"

SideBar::SideBar(QWidget *parent)
    :  BaseWidget(parent)
{
    this->initialize();
}

SideBar::~SideBar()
{
    delete chatsLayout;
    delete functionalLayout;
    delete userLayout;
}

void SideBar::initUI()
{
    this->setFixedWidth(200);
    this->setObjectName("SideBar");

    /*  Initialize layouts for side bar
     *
     *  mainLayout - for all widget
     *  chatsLayout - for chats
     *  functionalLayout - for functional buttons: cameraButton, displayButton, microphoneButton, soundButton, hungUpButton
     *  userLayout - for info about user: username and avatar
     *
     */
    this->mainLayout = new QVBoxLayout(this);

    this->chatsLayout = new QVBoxLayout();
    this->chatsLayout->setAlignment(Qt::AlignTop);

    this->functionalLayout = new QHBoxLayout();
    this->functionalLayout->setAlignment(Qt::AlignBottom);

    this->userLayout = new QHBoxLayout();
    this->userLayout->setAlignment(Qt::AlignBottom);

    /*  Initialize buttons for side bar
     *
     *  cameraButton - for turn on/off the user's camera
     *  displayButton - for turn on/off ща demonstration user's screen
     *  microphoneButton - for turn on/off user's microphone
     *  soundButton - for turn on/off user's sound
     *  hungUpButton - for end the call
     *  userLabelButton - label with username and avatar which can send to user's settings
     *
     */
    this->cameraButton = new QPushButton(this);
    this->cameraButton->setObjectName("SideBarButton");
    this->cameraButton->setIcon(QIcon(":/resources/images/camera.png"));
    this->cameraButton->setIconSize(QSize(30, 30));

    this->displayButton= new QPushButton(this);
    this->displayButton->setObjectName("SideBarButton");
    this->displayButton->setIcon(QIcon(":/resources/images/display.png"));
    this->displayButton->setIconSize(QSize(30, 30));

    this->microphoneButton = new QPushButton(this);
    this->microphoneButton->setObjectName("SideBarButton");
    this->microphoneButton->setIcon(QIcon(":/resources/images/microphone.png"));
    this->microphoneButton->setIconSize(QSize(30, 30));

    this->soundButton = new QPushButton(this);
    this->soundButton->setObjectName("SideBarButton");
    this->soundButton->setIcon(QIcon(":/resources/images/sound.png"));
    this->soundButton->setIconSize(QSize(30, 30));

    this->hungUpButton = new QPushButton(this);
    this->hungUpButton->setObjectName("SideBarButton");
    this->hungUpButton->setIcon(QIcon(":/resources/images/hung_up.png"));
    this->hungUpButton->setIconSize(QSize(30, 30));

    this->userLabelButton = new QPushButton(this);
    this->userLabelButton->setObjectName("UserLabelButton");
    this->userLabelButton->setIcon(QIcon(":/resources/images/default_user.png"));
    this->userLabelButton->setIconSize(QSize(40, 40));

    /*
     *  Initialize search box for side bar
     */
    this->searchBox = new QLineEdit(this);
    this->searchBox->setObjectName("SideBarSearchBox");
    QAction *iconAction = new QAction(QIcon(":/resources/images/search_box_icon.png"), "", searchBox);
    this->searchBox->addAction(iconAction, QLineEdit::TrailingPosition);

    /*
     *  Add buttons to layouts
     */
    this->chatsLayout->addWidget(searchBox);

    this->functionalLayout->addWidget(this->cameraButton);
    this->functionalLayout->addWidget(this->displayButton);
    this->functionalLayout->addWidget(this->microphoneButton);
    this->functionalLayout->addWidget(this->soundButton);
    this->functionalLayout->addWidget(this->hungUpButton);

    /*TODO: fix this shit*/
    this->userLayout->addWidget(this->userLabelButton);

    /*
     *  Add sub-layouts to main layout
     */
    this->mainLayout->addLayout(this->chatsLayout);
    this->mainLayout->addStretch();
    this->mainLayout->addLayout(this->functionalLayout);
    this->mainLayout->addLayout(this->userLayout);

    /*
     *  Set layout for widget
     */
    setLayout(this->mainLayout);

    //this->mainLayout->setContentsMargins(0,0,0,0);
    this->mainLayout->setSpacing(0);
}

void SideBar::setUserLabelButtonText(const QString& text)
{
    this->userLabelButton->setText(text);
}
