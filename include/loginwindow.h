/*!
 * @file loginwindow.h
 * @author Ivan Rastegaev
 * @brief Declares the LoginWindow class, which provides the user interface for the login screen.
 */

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

/* Global headers */
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include <QString>
#include <QMessageBox>

/* Local headers */
#include "basewidget.h"


/*!
 * @class LoginWindow
 * @brief A custom widget that provides a login screen of the application.
 *
 * This class extends @ref BaseWidget to create a user interface for logging into the application.
 * It provides input fields for credentials, buttons for user actions, and handles login events.
 */
class LoginWindow final : public BaseWidget
{
    Q_OBJECT

public:
    /*!
     * @brief Class constructor.
     * @param parent Pointer to the parent widget. Defaults to `nullptr`.
     * @param stack Pointer to the stacked widget for screen navigation. Defaults to `nullptr`.
     */

    explicit LoginWindow(QWidget *parent = nullptr, QStackedWidget *stack = nullptr);

    /*!
     * @brief Class destructor.
     */
    ~LoginWindow() override;

private:
    QVBoxLayout *mainLayout;            ///< Main vertical layout for login window.
    QLabel *appLabel;                   ///< Label displaying the application name.
    QLineEdit *loginField;              ///< Input field for entering the login.
    QLineEdit *passwordField;           ///< Input field for entering the password.
    QPushButton *loginButton;           ///< Button to initiate the login process.
    QPushButton *noAccountButton;       ///< Button to navigate to the registration screen.
    QStackedWidget *stackedWidget;      ///< Pointer to the stacked widget for screen navigation.

protected:

    /*!
     * @brief Initializes the user interface components of the widget.
     *
     * This method overrides the pure virtual function @ref BaseWidget::initUI
     * to set up layouts, buttons, and other UI elements.
     */
    void initUI() override;

private slots:

    /*!
     * @brief [Slot] Handles the click event for the login button.
     */
    void onLoginButtonClicked() const;

    /*!
     * @brief [Slot] Handles the click event for the no account button.
     */
    void onNoAccountButtonClicked() const;

    /*!
     * @brief [Slot] Handles the event when the login process is successful.
     */
    void onLoginSuccessful();

    /*!
     * @brief [Slot] Handles the event when the login process fails.
     * @param errorMessage The error message describing the reason for failure.
     */
    void onLoginUnsuccessful(const QString &errorMessage);
};

#endif // LOGINWINDOW_H
