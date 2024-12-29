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
     *  main_layout - for all widget
     *
     */
    this->main_layout = new QVBoxLayout(this);

    /*  Initialize main widget label
     *
     *  app_label - IVoice
     *
     */

    this->app_label = new QLabel("IVoice", this);
    this->app_label->setAlignment(Qt::AlignCenter);
    this->app_label->setObjectName("AppLabel");

    /*  Initialize fields for entering user's data
     *
     *  login_field - field for entering user's name or user's email or user's phone number
     *  password_field - field for entering user's password
     *
     */

    this->login_field  = new QLineEdit(this);
    this->login_field->setPlaceholderText("Username/Email/Phone number");
    //this->login_field->setAlignment(Qt::AlignCenter);
    this->login_field->setObjectName("LoginWindowField");

    this->password_field  = new QLineEdit(this);
    this->password_field->setPlaceholderText("Password");
    //this->password_field->setAlignment(Qt::AlignCenter);
    this->password_field->setObjectName("LoginWindowField");

    /*  Initialize buttons for register window
     *
     *  login_button - button for login into the app
     *  no_account_button - if user haven't got an account
     *
     */
    this->login_button = new QPushButton("Login", this);
    this->login_button->setObjectName("LoginButton");
    connect(this->login_button, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked); // add signal for button

    this->no_account_button = new QPushButton("I don't have an account.", this);
    this->no_account_button->setObjectName("LoginButton");
    connect(this->no_account_button, &QPushButton::clicked, this, &LoginWindow::onNoAccountButtonClicked); // add signal for button
    /*
     *  Set layout for widget
     */
    setLayout(this->main_layout);

    /*
     *  Add components to layout
     */
    this->main_layout->addWidget(app_label);
    this->main_layout->addWidget(login_field);
    this->main_layout->addWidget(password_field);
    this->main_layout->addWidget(login_button);
    this->main_layout->addWidget(no_account_button);
}

void LoginWindow::onLoginButtonClicked()
{
    QString login = this->login_field->text();
    QString password = this->password_field->text();

    auto server = LibCore::Server::instance();
    server->authLogin(login, password);
}

void LoginWindow::onNoAccountButtonClicked()
{
    stackedWidget->setCurrentIndex(1);

    this->login_field->clear();
    this->password_field->clear();
}

void LoginWindow::onLoginSuccessful()
{
    QMessageBox::information(this, "Login", "Login was successful!");

    qDebug() << "call onLoginSuccessful";

    this->login_field->clear();
    this->password_field->clear();
}

void LoginWindow::onLoginUnsuccessful(const QString &errorMessage)
{
    //qDebug() << errorMessage;
    QMessageBox::critical(this, "Login", "Login was unsuccessful!\n" + errorMessage);

    qDebug() << "call onLoginUnsuccessful";

    this->login_field->clear();
    this->password_field->clear();
}
