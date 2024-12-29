#include "include/widgets.h"
#include "include/core.h"

LoginWindow::LoginWindow(QWidget *parent, QStackedWidget *stack)
    : BaseWidget(parent), stackedWidget(stack)
{
    this->initialize();

    auto* server = LibCore::Server::instance();
    connect(server, SIGNAL(loginSuccessful()), this, SLOT(onLoginSuccessful()));
    connect(server, SIGNAL(loginUnsucsessful(QString)), this, SLOT(onLoginUnsuccessful(QString)));
}

LoginWindow::~LoginWindow() {}

void LoginWindow::initUI()
{
    this->setFixedSize(400, 600);
    this->setObjectName("LoginWindow");

    /*  Initialize layouts for register window
     *
     *  mainLayout - for all widget
     *
     */
    this->mainLayout = new QVBoxLayout(this);

    /*  Initialize main widget label
     *
     *  appLabel - IVoice
     *
     */

    this->appLabel = new QLabel("IVoice", this);
    this->appLabel->setAlignment(Qt::AlignCenter);
    this->appLabel->setObjectName("AppLabel");

    /*  Initialize fields for entering user's data
     *
     *  loginField - field for entering user's name or user's email or user's phone number
     *  passwordField - field for entering user's password
     *
     */

    this->loginField  = new QLineEdit(this);
    this->loginField->setPlaceholderText("Username/Email/Phone number");
    //this->loginField->setAlignment(Qt::AlignCenter);
    this->loginField->setObjectName("LoginWindowField");

    this->passwordField  = new QLineEdit(this);
    this->passwordField->setPlaceholderText("Password");
    //this->passwordField->setAlignment(Qt::AlignCenter);
    this->passwordField->setObjectName("LoginWindowField");

    /*  Initialize buttons for register window
     *
     *  loginButton - button for login into the app
     *  noAccountButton - if user haven't got an account
     *
     */
    this->loginButton = new QPushButton("Login", this);
    this->loginButton->setObjectName("LoginButton");
    connect(this->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked); // add signal for button

    this->noAccountButton = new QPushButton("I don't have an account.", this);
    this->noAccountButton->setObjectName("LoginButton");
    connect(this->noAccountButton, &QPushButton::clicked, this, &LoginWindow::onNoAccountButtonClicked); // add signal for button
    /*
     *  Set layout for widget
     */
    setLayout(this->mainLayout);

    /*
     *  Add components to layout
     */
    this->mainLayout->addWidget(appLabel);
    this->mainLayout->addWidget(loginField);
    this->mainLayout->addWidget(passwordField);
    this->mainLayout->addWidget(loginButton);
    this->mainLayout->addWidget(noAccountButton);
}

void LoginWindow::onLoginButtonClicked()
{
    QString login = this->loginField->text();
    QString password = this->passwordField->text();

    auto* server = LibCore::Server::instance();
    server->authLogin(login, password);
}

void LoginWindow::onNoAccountButtonClicked()
{
    stackedWidget->setCurrentIndex(1);

    this->loginField->clear();
    this->passwordField->clear();
}

void LoginWindow::onLoginSuccessful()
{
    QMessageBox::information(this, "Login", "Login was successful!");

    qDebug() << "call onLoginSuccessful";

    this->loginField->clear();
    this->passwordField->clear();
}

void LoginWindow::onLoginUnsuccessful(const QString &errorMessage)
{
    QMessageBox::critical(this, "Login", "Login was unsuccessful!\n" + errorMessage);

    qDebug() << "call onLoginUnsuccessful";

    this->loginField->clear();
    this->passwordField->clear();
}
