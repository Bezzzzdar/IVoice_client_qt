#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
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

class ServerBar : public QWidget
{
    Q_OBJECT

public:
    ServerBar(QWidget *parent = nullptr);
    virtual ~ServerBar();

private:
    QVBoxLayout *main_layout = new QVBoxLayout();
    QVBoxLayout *servers_layout = new QVBoxLayout();
    QVBoxLayout *functional_layout = new QVBoxLayout();
    QPushButton *add_server_button = new QPushButton(this);
    QPushButton *settings_button = new QPushButton(this);
    QPushButton *direct_messages_button = new QPushButton(this);

    QVector<QPushButton> *server_list;

    void initUI();
    void paintEvent(QPaintEvent *pe);
};

class SideBar : public QWidget
{
    Q_OBJECT

public:
    SideBar(QWidget *parent = nullptr);
    virtual ~SideBar();

private:
    QVBoxLayout *main_layout = new QVBoxLayout();
    QVBoxLayout *chats_layout = new QVBoxLayout();
    QHBoxLayout *functional_layout = new QHBoxLayout();
    QHBoxLayout *user_layout = new QHBoxLayout();
    QLineEdit *search_box = new QLineEdit();
    QPushButton *camera_button = new QPushButton(this);
    QPushButton *display_button= new QPushButton(this); // display???
    QPushButton *microphone_button = new QPushButton(this);
    QPushButton *sound_button = new QPushButton(this);
    QPushButton *hung_up_button = new QPushButton(this);
    QPushButton *user_label_button = new QPushButton("Username\nonline", this); /* TODO: fix online status and username */

    void initUI();
    void paintEvent(QPaintEvent *pe);
};

class WorkSpace : public QWidget
{
    Q_OBJECT

public:
    WorkSpace(QWidget *parent = nullptr);
    virtual ~WorkSpace();

private:
    QHBoxLayout *main_layout = new QHBoxLayout();

    void initUI();
    void paintEvent(QPaintEvent *pe);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private:
    QWidget *central_widget;
    QHBoxLayout *main_layout;
    ServerBar *server_bar;
    SideBar *side_bar;
    void initUI();
};
