/*!
 * @file registerwindow.h
 * @author Ivan Rastegaev
 * @brief Declares the RegisterWindow class, which provides the user interface for the registration screen.
 */

#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

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
 * @class RegisterWindow
 * @brief A custom widget that provides a registration screen of the application.
 *
 * This class extends @ref BaseWidget to provide a user interface for registering new accounts.
 * It includes input fields for user details such as email, password, and display name,
 * as well as methods to handle registration events.
 */
class RegisterWindow : public BaseWidget
{
    Q_OBJECT

public:

    /*!
     * @brief Сlass constructor.
     * @param parent Pointer to the parent widget. Defaults to `nullptr`.
     * @param stack Pointer to the stacked widget for screen navigation. Defaults to `nullptr`.
     */
    explicit RegisterWindow(QWidget *parent = nullptr, QStackedWidget *stack = nullptr);

    /*!
     * @brief Class Destructor.
     */
    ~RegisterWindow();

private:
    QVBoxLayout *mainLayout;                ///< Main vertical layout for the register window
    QLabel *appLabel;                       ///< Label displaying the application name.
    QLineEdit *emailField;                  ///< Input field for entering the user's email address.
    QLineEdit *passwordField;               ///< Input field for entering the user's password.
    QLineEdit *usernameField;               ///< Input field for entering the user's username.
    QLineEdit *displayNameField;            ///< Input field for entering the user's display name.
    QLineEdit *birthDateField;              ///< Input field for entering the user's birth date.
    QPushButton *registerButton;            ///< Button to initiate the registration process.
    QStackedWidget *stackedWidget;          ///< Pointer to the stacked widget for screen navigation.

protected:

    /*!
     * @brief Initializes the user interface components of the RegisterWindow.
     *
     * This method overrides the pure virtual function @ref BaseWidget::initUI
     * to set up layouts, buttons, and other UI elements.
     */
    void initUI() override;

private slots:

    /*!
     * @brief [Slot] Handles the click event for the register button.
     */
    void onRegisterButtonClicked();

    /*!
     * @brief [Slot] Handles the event when the registration process is successful.
     */
    void onRegisterSucsessful();

    /*!
     * @brief [Slot] Handles the event when the registration process fails.
     * @param errorMessage The error message describing the reason for failure.
     */
    void onRegisterUnsucsessful(const QString &errorMessage);
};

#endif // REGISTERWINDOW_H
