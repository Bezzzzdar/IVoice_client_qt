#include "include/widgets.h"
#include "include/core.h"

RegisterWindow::RegisterWindow(QWidget *parent, QStackedWidget *stack)
    : BaseWidget(parent), stackedWidget(stack)
{
    this->initialize();

    auto* server = LibCore::Server::instance();

    /* legacy Qt style. TODO: fix this shit */
    connect(server, SIGNAL(registerSucsessful()), this, SLOT(onRegisterSucsessful()));
    connect(server, SIGNAL(registerUnsucsessful(QString)),
            this, SLOT(onRegisterUnsucsessful(QString)));
}

RegisterWindow::~RegisterWindow()
{

}

void RegisterWindow::initUI()
{
    this->setFixedSize(400, 600);
    this->setObjectName("RegisterWindow");

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
     *  email_field - field for entering user's email address
     *  password_field - field for entering user's password
     *  username_field - field for entering user's name
     *  displayname_field - field for entering user's name witch will be displayed in the app
     *  birthdate_field - field for entering user's birth date
     *
     */
    this->email_field  = new QLineEdit(this);
    this->email_field->setPlaceholderText("Email");
    //this->email_field->setAlignment(Qt::AlignCenter);
    this->email_field->setObjectName("RegisterWindowField");

    this->password_field  = new QLineEdit(this);
    this->password_field->setPlaceholderText("Password");
    //this->password_field->setAlignment(Qt::AlignCenter);
    this->password_field->setObjectName("RegisterWindowField");

    this->username_field  = new QLineEdit(this);
    this->username_field->setPlaceholderText("Username");
    //this->username_field->setAlignment(Qt::AlignCenter);
    this->username_field->setObjectName("RegisterWindowField");

    this->displayname_field  = new QLineEdit(this);
    this->displayname_field->setPlaceholderText("Display name");
    //this->displayname_field->setAlignment(Qt::AlignCenter);
    this->displayname_field->setObjectName("RegisterWindowField");

    this->birthdate_field  = new QLineEdit(this);
    this->birthdate_field->setPlaceholderText("Date of birth");
    //this->birthdate_field->setAlignment(Qt::AlignCenter);
    this->birthdate_field->setObjectName("RegisterWindowField");

    /*  Initialize buttons for register window
     *
     *  register_button - button for creating an account in the app
     *
     */
    this->register_button = new QPushButton("Create account", this);
    this->register_button->setObjectName("RegisterButton");
    connect(this->register_button, &QPushButton::clicked, this, &RegisterWindow::onRegisterButtonClicked); // add signal for button

    /*
     *  Set layout for widget
     */
    setLayout(this->main_layout);

    /*
     *  Add components to layout
     */
    this->main_layout->addWidget(app_label);
    this->main_layout->addWidget(email_field);
    this->main_layout->addWidget(password_field);
    this->main_layout->addWidget(username_field);
    this->main_layout->addWidget(displayname_field);
    this->main_layout->addWidget(birthdate_field);
    this->main_layout->addWidget(register_button);
}

void RegisterWindow::onRegisterButtonClicked()
{
    QString email = this->email_field->text();
    QString password = this->password_field->text();
    QString username = this->username_field->text();
    QString displayname = this->displayname_field->text();
    QString birthdate = this->birthdate_field->text();

    auto* server = LibCore::Server::instance();
    server->authRegister(username, displayname, email, password, birthdate);
}

void RegisterWindow::onRegisterSucsessful()
{
    QMessageBox::information(this, "Registration", "Registration was successful!");

    qDebug() << "call onRegisterSucsessful";

    stackedWidget->setCurrentIndex(0);
    this->email_field->clear();
    this->password_field->clear();
    this->username_field->clear();
    this->displayname_field->clear();
    this->birthdate_field->clear();
}

void RegisterWindow::onRegisterUnsucsessful(const QString &errorMessage)
{
    //qDebug() << errorMessage;
    QMessageBox::critical(this, "Registration", "Registration was unsuccessful!\n" + errorMessage);

    qDebug() << "call onRegisterUnsucsessful";

    this->email_field->clear();
    this->password_field->clear();
    this->username_field->clear();
    this->displayname_field->clear();
    this->birthdate_field->clear();
}

