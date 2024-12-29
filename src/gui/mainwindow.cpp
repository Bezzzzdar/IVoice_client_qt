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
    delete main_layout;
}

void MainWindow::initUI()
{
    this->resize(1400, 900);
    this->setMinimumSize(900, 600);

    this->central_widget = new QWidget(this);
    this->main_layout = new QHBoxLayout();
    central_widget->setLayout(main_layout);
    main_layout->setContentsMargins(0,0,0,0);
    main_layout->setSpacing(0);

    this->stackedWidget = new QStackedWidget(this);

    this->login_window = new LoginWindow(this, this->stackedWidget);
    this->register_window = new RegisterWindow(this, this->stackedWidget);

    this->stackedWidget->addWidget(login_window);
    this->stackedWidget->addWidget(register_window);
    this->stackedWidget->setCurrentWidget(login_window);

    main_layout->addWidget(this->stackedWidget, 0, Qt::AlignCenter);
    setCentralWidget(central_widget);
}

void MainWindow::switchToMainUI()
{
    if (this->stackedWidget)
    {
        this->stackedWidget->hide();
        this->stackedWidget->deleteLater();
        this->stackedWidget = nullptr;
    }

    this->server_bar = new ServerBar(this);
    this->side_bar = new SideBar(this);
    this->workspace = new WorkSpace(this);

    main_layout->addWidget(server_bar);
    main_layout->addWidget(side_bar);
    main_layout->addWidget(workspace);
}
