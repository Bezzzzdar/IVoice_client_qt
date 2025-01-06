/*!
 * @file mainwindow.h
 * @author Ivan Rastegaev
 * @brief Declares the MainWindow class, the central window of the application.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* Global headers */
#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
#include <QLineEdit>
#include <QVector>
#include <QLabel>
#include <QString>
#include <QIcon>
#include <QSize>
#include <QAction>
#include <QStackedWidget>
#include <QMessageBox>
#include <QComboBox>
#include <QStringList>
#include <QCheckBox>

/* Local headers */
#include "serverbar.h"
#include "sidebar.h"
#include "workspace.h"
#include "registerwindow.h"
#include "loginwindow.h"
#include "settingswidget.h"


/*!
 * @class MainWindow
 * @brief Represents the main window of the application.
 *
 * The MainWindow class is responsible for initializing and managing the primary
 * UI components, including the server bar, sidebar, workspace, login and register windows,
 * and settings widget. It provides navigation between these components and serves as the
 * central interface of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*!
     * @brief Class constructor.
     * @param parent Pointer to the parent widget. Defaults to `nullptr`.
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * @brief Destructor for the class.
     */
    ~MainWindow();

private:
    QWidget *centralWidget;                 ///< The central widget of the main window.
    QHBoxLayout *mainLayout;                ///< The main layout of the application.
    ServerBar *serverBar;                   ///< Pointer to the ServerBar component.
    SideBar *sideBar;                       ///< Pointer to the SideBar component.
    WorkSpace *workspace;                   ///< Pointer to the WorkSpace component.
    LoginWindow *loginWindow;               ///< Pointer to the LoginWindow component.
    RegisterWindow *registerWindow;         ///< Pointer to the RegisterWindow component.
    SettingsWidget *settingsWidget;         ///< Pointer to the SettingsWidget component.

    QStackedWidget *mainStackedWidget;      ///< Stacked widget for managing multiple views.

    /*!
     * @brief Initializes the user interface components of the MainWindow.
     */
    void initUI();

private slots:
    /*!
     * @brief [Slot] Switches the view to the main user interface.
     */
    void switchToMainUI();

    /*!
     * @brief [Slot] Switches the view to the settings widget.
     */
    void switchToSettingsWidget();
};

#endif // MAINWINDOW_H
