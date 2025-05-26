/*!
 * @file settingswidget.h
 * @author Ivan Rastegaev
 * @brief Contains the declarations for the settings-related widgets in the application.
 */

#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

/* Global headers */
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QComboBox>
#include <QStringList>
#include <QCheckBox>
#include <QLineEdit>
#include <QSize>

/* Local headers */
#include "basewidget.h"

/*!
 * @class SettingsAccountWidget
 * @brief Represents the account settings widget.
 *
 * This class extends @ref BaseWidget to provide an interface for users to view and update their account information.
 */
class SettingsAccountWidget : public BaseWidget
{
    Q_OBJECT

public:

    /*!
     * @brief Constructs the class.
     * @param parent Pointer to the parent widget. Defaults to `nullptr`.
     * @param stack Pointer to the stacked widget for navigation. Defaults to `nullptr`.
     */
    SettingsAccountWidget(QWidget *parent = nullptr, QStackedWidget *stack = nullptr);

    /*!
     * @brief Destructor for the class.
     */
    ~SettingsAccountWidget();

private:
    QStackedWidget *stackedWidget;          ///< Pointer to the stacked widget for navigation.

    QVBoxLayout *mainLayout;                ///< Main vertical layout for settings widget.
    QHBoxLayout *usernameLayout;            ///< Layout for the username section.
    QHBoxLayout *displayNameLayout;         ///< Layout for the display name section.
    QHBoxLayout *emailLayout;               ///< Layout for the email section.
    QHBoxLayout *phoneNumberLayout;         ///< Layout for the phone number section.
    QHBoxLayout *birthDateLayout;           ///< Layout for the birth date section.
    QHBoxLayout *statusLayout;              ///< Layout for the online status section.

    QLabel *mainLabel;                      ///< Label for the main title.
    QLabel *usernameLabel;                  ///< Label for the username field.
    QLabel *displayNameLabel;               ///< Label for the display name field.
    QLabel *emailLabel;                     ///< Label for the email field.
    QLabel *phoneNumberLabel;               ///< Label for the phone number field.
    QLabel *birthDateLabel;                 ///< Label for the birth date field.
    QLabel *statusLabel;                    ///< Label for the status field.

    QLineEdit *usernameField;               ///< Input field for the username.
    QLineEdit *displayNameField;            ///< Input field for the display name.
    QLineEdit *emailField;                  ///< Input field for the email.
    QLineEdit *phoneNumberField;            ///< Input field for the phone number.
    QLineEdit *birthDateField;              ///< Input field for the birth date.
    QComboBox *statusField;                 ///< Combo box for selecting the user's online status.

protected:

    /*!
     * @brief Initializes the user interface components of the widget.
     *
     * This method overrides the pure virtual function @ref BaseWidget::initUI
     * to set up layouts, buttons, and other UI elements.
     */
    void initUI() override;
};

/*!
 * @class SettingsAppearanceWidget
 * @brief Represents the appearance settings widget.
 *
 * This class extends @ref BaseWidget to provide options for users to configure themes and language preferences.
 */
class SettingsAppearanceWidget : public BaseWidget
{
    Q_OBJECT

public:
    /*!
     * @brief Constructs the class.
     * @param parent Pointer to the parent widget. Defaults to `nullptr`.
     * @param stack Pointer to the stacked widget for screen navigation. Defaults to `nullptr`.
     */
    SettingsAppearanceWidget(QWidget *parent = nullptr, QStackedWidget *stack = nullptr);

    /*!
     * @brief Destructor for the class.
     */
    ~SettingsAppearanceWidget();

private:
    QStackedWidget *stackedWidget;          ///< Pointer to the stacked widget for navigation.

    QVBoxLayout *mainLayout;                ///< Main vertical layout for settings widget.
    QHBoxLayout *themeLayout;               ///< Layout for the theme section.
    QHBoxLayout *languageLayout;            ///< Layout for the language section.

    QLabel *mainLabel;                      ///< Label for the main title.
    QLabel *themeLabel;                     ///< Label for the theme selection.
    QLabel *languageLabel;                  ///< Label for the language selection.

    QCheckBox *darkThemeCheckBox;           ///< Checkbox for selecting the dark theme.
    QCheckBox *lightThemeCheckBox;          ///< Checkbox for selecting the light theme.
    QCheckBox *ruLanguageCheckBox;          ///< Checkbox for selecting Russian language.
    QCheckBox *enLanguageCheckBox;          ///< Checkbox for selecting English language.

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
     * @brief [Slot] Handles the dark theme checkbox click event.
     */
    void onDarkThemeCheckBoxClicked() const;

    /*!
     * @brief [Slot] Handles the light theme checkbox click event.
     */
    void onLightThemeCheckBoxClicked() const;

    /*!
     * @brief [Slot] Handles the Russian language checkbox click event.
     */
    void onRuLanguageCheckBoxClicked() const;

    /*!
     * @brief [Slot] Handles the English language checkbox click event.
     */
    void onEnLanguageCheckBoxClicked() const;
};


/*!
 * @class SettingsWidget
 * @brief Represents the main settings widget.
 *
 * This class extends @ref BaseWidget to combine account and appearance settings into a single interface with navigation.
 */
class SettingsWidget final : public BaseWidget
{
    Q_OBJECT

public:

    /*!
     * @brief Constructs the class.
     * @param parent Pointer to the parent widget. Defaults to `nullptr`.
     * @param stack Pointer to the stacked widget for screen navigation. Defaults to `nullptr`.
     */
    explicit SettingsWidget(QWidget *parent = nullptr, QStackedWidget *stack = nullptr);

    /*!
     * @brief Destructor for the class.
     */
    ~SettingsWidget() override;

private:
    QStackedWidget *stackedWidget;                              ///< Pointer to the stacked widget for navigation.
    QHBoxLayout *mainLayout;                                    ///< Main layout of the settings widget.
    QVBoxLayout *navigationBarLayout;                           ///< Layout for the navigation bar.
    QWidget *navigationBarContainer;                            ///< Container for the navigation bar.
    QHBoxLayout *editPanelLayout;                               ///< Layout for the edit panel.
    QWidget *editPanelContainer;                                ///< Container for the edit panel.
    QHBoxLayout *closePanelLayout;                              ///< Layout for the close panel.
    QWidget *closePanelContainer;                               ///< Container for the close panel.
    QPushButton *closeSettingsButton;                           ///< Button for closing the settings widget.
    QPushButton *userAccountButton;                             ///< Button for accessing account settings.
    QPushButton *appearanceButton;                              ///< Button for accessing appearance settings.
    SettingsAccountWidget *settingsAccountWidget;               ///< Instance of account settings widget.
    SettingsAppearanceWidget *settingsAppearanceWidget;         ///< Instance of appearance settings widget.


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
     * @brief [Slot] Handles the user account button click event.
     */
    void onUserAccountButtonClicked() const;

    /*!
     * @brief [Slot] Handles the user account button click event.
     */
    void onAppearanceButtonClicked() const;

    /*!
     * @brief [Slot] Handles the user account button click event.
     */
    void onCloseSettingsButtonClicked() const;

signals:

    /*!
     * @brief [Signal] Emitted when the settings widget is closed.
     */
    void closeSettings() const;
};

#endif // SETTINGSWIDGET_H
