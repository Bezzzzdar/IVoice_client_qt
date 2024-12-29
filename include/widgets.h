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
    void paintEvent(QPaintEvent *pe) override;
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
    void paintEvent(QPaintEvent *pe) override;
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
    QVBoxLayout *main_layout;
    QVBoxLayout *servers_layout;
    QVBoxLayout *functional_layout;
    QPushButton *add_server_button;
    QPushButton *settings_button;
    QPushButton *direct_messages_button;

    QVector<QPushButton> *server_list;
};

class SideBar : public BaseWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);
    ~SideBar();

private:
    QVBoxLayout *main_layout;
    QVBoxLayout *chats_layout;
    QHBoxLayout *functional_layout;
    QHBoxLayout *user_layout;
    QLineEdit *search_box;
    QPushButton *camera_button;
    QPushButton *display_button; // display???
    QPushButton *microphone_button;
    QPushButton *sound_button;
    QPushButton *hung_up_button;
    QPushButton *user_label_button;

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
    QHBoxLayout *main_layout;

protected:
    void initUI() override;
};

class RegisterWindow : public BaseWidget
{
    Q_OBJECT

private:
    QVBoxLayout *main_layout;
    QLabel *app_label;
    QLineEdit *email_field;
    QLineEdit *password_field;
    QLineEdit *username_field;
    QLineEdit *displayname_field; // for what ??? idk
    QLineEdit *birthdate_field;
    QPushButton *register_button;
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
    QVBoxLayout *main_layout;
    QLabel *app_label;
    QLineEdit *login_field;
    QLineEdit *password_field;
    QPushButton *login_button;
    QPushButton *no_account_button;
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
    QWidget *central_widget;
    QHBoxLayout *main_layout;
    ServerBar *server_bar;
    SideBar *side_bar;
    WorkSpace *workspace;
    LoginWindow *login_window;
    RegisterWindow *register_window;

    QStackedWidget *stackedWidget;

    void initUI();

private slots:
    void switchToMainUI();
};

#endif // WIDGETS_H
