#include "include/widgets.h"
#include "include/core.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->initUI();

    auto* server = LibCore::Server::instance();

    connect(server, SIGNAL(loginSuccessful()), this, SLOT(switchToMainUI()));
}

MainWindow::~MainWindow()
{
    delete mainLayout;
}

void MainWindow::initUI()
{
    this->resize(1400, 900);
    this->setMinimumSize(900, 600);

    this->centralWidget = new QWidget(this);
    this->mainLayout = new QHBoxLayout();
    centralWidget->setLayout(mainLayout);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    this->stackedWidget = new QStackedWidget(this);

    this->loginWindow = new LoginWindow(this, this->stackedWidget);
    this->registerWindow = new RegisterWindow(this, this->stackedWidget);

    this->stackedWidget->addWidget(loginWindow);
    this->stackedWidget->addWidget(registerWindow);
    this->stackedWidget->setCurrentWidget(loginWindow);

    mainLayout->addWidget(this->stackedWidget, 0, Qt::AlignCenter);
    setCentralWidget(centralWidget);
}

void MainWindow::switchToMainUI()
{
    if (this->stackedWidget)
    {
        this->stackedWidget->hide();
        this->stackedWidget->deleteLater();
        this->stackedWidget = nullptr;
    }

    this->serverBar = new ServerBar(this);
    this->sideBar = new SideBar(this);
    this->workspace = new WorkSpace(this);

    mainLayout->addWidget(serverBar);
    mainLayout->addWidget(sideBar);
    mainLayout->addWidget(workspace);
}
