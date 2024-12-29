#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
#include <QLineEdit>
#include <QVector>
#include <QLabel>
#include <QDialog>
#include <QStyleOption>
#include <QPainter>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QIcon>
#include <QSize>
#include <QAction>
#include <QStackedWidget>
#include <QDialog>
#include <QMessageBox>

#ifndef WIDGETS_H
#define WIDGETS_H

class BaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseWidget(QWidget *parent = nullptr);
    virtual ~BaseWidget();
    void initialize();

protected:
    virtual void initUI() = 0;
    void paintEvent(QPaintEvent *event);
    void applyStyles();
};

class BaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaseDialog(QWidget *parent = nullptr);
    virtual ~BaseDialog();
    void initialize();
protected:
    virtual void initUI() = 0;
    void paintEvent(QPaintEvent *event);
    void applyStyles();

};


class ServerBar : public BaseWidget
{
    Q_OBJECT

public:
    explicit ServerBar(QWidget *parent = nullptr);
    ~ServerBar();

protected:
    void initUI() override;

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *serversLayout;
    QVBoxLayout *functionalLayout;
    QPushButton *addServerButton;
    QPushButton *settingsButton;
    QPushButton *directMessagesButton;

    QVector<QPushButton> *serverList;
};

class SideBar : public BaseWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);
    ~SideBar();

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *chatsLayout;
    QHBoxLayout *functionalLayout;
    QHBoxLayout *userLayout;
    QLineEdit *searchBox;
    QPushButton *cameraButton;
    QPushButton *displayButton; // display???
    QPushButton *microphoneButton;
    QPushButton *soundButton;
    QPushButton *hungUpButton;
    QPushButton *userLabelButton;

protected:
    void initUI() override;
};

class WorkSpace : public BaseWidget
{
    Q_OBJECT

public:
    explicit WorkSpace(QWidget *parent = nullptr);
    ~WorkSpace();

private:
    QHBoxLayout *mainLayout;

protected:
    void initUI() override;
};

class RegisterWindow : public BaseWidget
{
    Q_OBJECT

private:
    QVBoxLayout *mainLayout;
    QLabel *appLabel;
    QLineEdit *emailField;
    QLineEdit *passwordField;
    QLineEdit *usernameField;
    QLineEdit *displayNameField; // for what ??? idk
    QLineEdit *birthDateField;
    QPushButton *registerButton;
    QStackedWidget *stackedWidget;

public:
    explicit RegisterWindow(QWidget *parent = nullptr, QStackedWidget *stack = nullptr);
    ~RegisterWindow();

protected:
    void initUI() override;

private slots:
    void onRegisterButtonClicked();
    void onRegisterSucsessful();
    void onRegisterUnsucsessful(const QString &errorMessage);
};

class LoginWindow : public BaseWidget
{
    Q_OBJECT

private:
    QVBoxLayout *mainLayout;
    QLabel *appLabel;
    QLineEdit *loginField;
    QLineEdit *passwordField;
    QPushButton *loginButton;
    QPushButton *noAccountButton;
    QStackedWidget *stackedWidget;

public:
    explicit LoginWindow(QWidget *parent = nullptr, QStackedWidget *stack = nullptr);
    ~LoginWindow();

protected:
    void initUI() override;

private slots:
    void onLoginButtonClicked();
    void onNoAccountButtonClicked();
    void onLoginSuccessful();
    void onLoginUnsuccessful(const QString &errorMessage);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget;
    QHBoxLayout *mainLayout;
    ServerBar *serverBar;
    SideBar *sideBar;
    WorkSpace *workspace;
    LoginWindow *loginWindow;
    RegisterWindow *registerWindow;

    QStackedWidget *stackedWidget;

    void initUI();

private slots:
    void switchToMainUI();
};

#endif // WIDGETS_H
