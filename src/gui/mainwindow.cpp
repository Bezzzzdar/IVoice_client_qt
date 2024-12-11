#include "include/widgets.h"
//#include "include/styles.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->initUI();
}

MainWindow::~MainWindow() {}

void MainWindow::initUI()
{
    this->resize(1400, 900);
    this->setMinimumSize(900, 600);

    QWidget *central_widget = new QWidget(this);
    QHBoxLayout *main_layout = new QHBoxLayout();
    central_widget->setLayout(main_layout);
    main_layout->setContentsMargins(0,0,0,0);
    main_layout->setSpacing(0);

    ServerBar *server_bar = new ServerBar();
    SideBar *side_bar = new SideBar();
    WorkSpace *workspace = new WorkSpace();

    main_layout->addWidget(server_bar);
    main_layout->addWidget(side_bar);
    main_layout->addWidget(workspace);
    setCentralWidget(central_widget);
}
