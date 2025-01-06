#include "mainwindow.h"
#include "core.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->initUI();

    auto* server = LibCore::Server::instance();

    connect(server, SIGNAL(loginSuccessful()), this, SLOT(switchToMainUI()));
}

MainWindow::~MainWindow() {}

void MainWindow::initUI()
{
    this->resize(1400, 900);
    this->setMinimumSize(900, 600);
    this->centralWidget = nullptr;

    this->mainStackedWidget = new QStackedWidget(this);

    QWidget* loginContainer = new QWidget(this);
    QVBoxLayout* loginLayout = new QVBoxLayout(loginContainer);
    this->loginWindow = new LoginWindow(this, mainStackedWidget);
    loginLayout->addWidget(loginWindow, 0, Qt::AlignCenter);
    loginContainer->setLayout(loginLayout);

    QWidget* registerContainer = new QWidget(this);
    QVBoxLayout* registerLayout = new QVBoxLayout(registerContainer);
    this->registerWindow = new RegisterWindow(this, mainStackedWidget);
    registerLayout->addWidget(registerWindow, 0, Qt::AlignCenter);
    registerContainer->setLayout(registerLayout);

    this->mainStackedWidget->addWidget(loginContainer);
    this->mainStackedWidget->addWidget(registerContainer);

    this->mainStackedWidget->setCurrentWidget(loginContainer);

    setCentralWidget(mainStackedWidget);
}

void MainWindow::switchToMainUI()
{
    if (!this->centralWidget) {
        this->centralWidget = new QWidget(this);
        QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        this->serverBar = new ServerBar(this);
        this->sideBar = new SideBar(this);
        this->workspace = new WorkSpace(this);

        mainLayout->addWidget(this->serverBar);
        mainLayout->addWidget(this->sideBar);
        mainLayout->addWidget(this->workspace);

        this->mainStackedWidget->addWidget(centralWidget);

        this->settingsWidget = new SettingsWidget(this, mainStackedWidget);
        this->mainStackedWidget->addWidget(settingsWidget);

        connect(this->serverBar, &ServerBar::showSettingsWidget, this, &MainWindow::switchToSettingsWidget);
        connect(this->settingsWidget, &SettingsWidget::closeSettings, this, &MainWindow::switchToMainUI);
    }

    this->mainStackedWidget->setCurrentWidget(this->centralWidget);

    auto* user = LibCore::User::instance();
    this->sideBar->setUserLabelButtonText(user->getUsername() + "\nonline");
}

void MainWindow::switchToSettingsWidget()
{
    this->mainStackedWidget->setCurrentWidget(this->settingsWidget);
}
