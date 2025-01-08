#include "registerwindow.h"
#include "core.h"

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
     *  emailField - field for entering user's email address
     *  passwordField - field for entering user's password
     *  usernameField - field for entering user's name
     *  displayNameField - field for entering user's name witch will be displayed in the app
     *  birthDateField - field for entering user's birth date
     *
     */
    this->emailField  = new QLineEdit(this);
    this->emailField->setPlaceholderText("Email");
    //this->emailField->setAlignment(Qt::AlignCenter);
    this->emailField->setObjectName("RegisterWindowField");

    this->passwordField  = new QLineEdit(this);
    this->passwordField->setPlaceholderText("Password");
    //this->passwordField->setAlignment(Qt::AlignCenter);
    this->passwordField->setObjectName("RegisterWindowField");

    this->usernameField  = new QLineEdit(this);
    this->usernameField->setPlaceholderText("Username");
    //this->usernameField->setAlignment(Qt::AlignCenter);
    this->usernameField->setObjectName("RegisterWindowField");

    this->displayNameField  = new QLineEdit(this);
    this->displayNameField->setPlaceholderText("Display name");
    //this->displayNameField->setAlignment(Qt::AlignCenter);
    this->displayNameField->setObjectName("RegisterWindowField");

    this->birthDateField  = new QLineEdit(this);
    this->birthDateField->setPlaceholderText("Date of birth");
    //this->birthDateField->setAlignment(Qt::AlignCenter);
    this->birthDateField->setObjectName("RegisterWindowField");

    /*  Initialize buttons for register window
     *
     *  registerButton - button for creating an account in the app
     *
     */
    this->registerButton = new QPushButton("Create account", this);
    this->registerButton->setObjectName("RegisterButton");
    connect(this->registerButton, &QPushButton::clicked, this, &RegisterWindow::onRegisterButtonClicked); // add signal for button

    /*
     *  Set layout for widget
     */
    setLayout(this->mainLayout);

    /*
     *  Add components to layout
     */
    this->mainLayout->addWidget(appLabel);
    this->mainLayout->addWidget(emailField);
    this->mainLayout->addWidget(passwordField);
    this->mainLayout->addWidget(usernameField);
    this->mainLayout->addWidget(displayNameField);
    this->mainLayout->addWidget(birthDateField);
    this->mainLayout->addWidget(registerButton);
}

void RegisterWindow::onRegisterButtonClicked()
{
    QString email = this->emailField->text();
    QString password = this->passwordField->text();
    QString username = this->usernameField->text();
    QString displayName = this->displayNameField->text();
    QString birthDate = this->birthDateField->text();

    auto* server = LibCore::Server::instance();
    server->authRegister(username, displayName, email, password, birthDate);
}

void RegisterWindow::onRegisterSucsessful()
{
    QMessageBox::information(this, "Registration", "Registration was successful!");

    LOG(Info) << "call onRegisterSucsessful\n";

    stackedWidget->setCurrentIndex(0);
    this->emailField->clear();
    this->passwordField->clear();
    this->usernameField->clear();
    this->displayNameField->clear();
    this->birthDateField->clear();
}

void RegisterWindow::onRegisterUnsucsessful(const QString &errorMessage)
{
    QMessageBox::critical(this, "Registration", "Registration was unsuccessful!\n" + errorMessage);

    LOG(Info) << "call onRegisterUnsucsessful\n";

    this->emailField->clear();
    this->passwordField->clear();
    this->usernameField->clear();
    this->displayNameField->clear();
    this->birthDateField->clear();
}

