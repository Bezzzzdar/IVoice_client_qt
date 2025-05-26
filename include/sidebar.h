/*!
 * @file sidebar.h
 * @author Ivan Rastegaev
 * @brief Declaration of the SideBar class, a widget providing user interface elements such as chats, search, and user controls.
 */

#ifndef SIDEBAR_H
#define SIDEBAR_H

/* Global headers */
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QString>
#include <QIcon>
#include <QSize>
#include <QAction>

/* Local headers */
#include "basewidget.h"

/*!
 * @class SideBar
 * @brief A custom widget that provides a sidebar with user controls, chat options, and a search box.
 *
 * This class extends @ref BaseWidget to offer a set of functional buttons,
 * such as for camera and microphone control, as well as a search box and user-related features.
 */
class SideBar final : public BaseWidget
{
    Q_OBJECT

public:

    /*!
     * @brief Class constructor.
     * @param parent Pointer to the parent widget. Defaults to `nullptr`.
     */
    explicit SideBar(QWidget *parent = nullptr);

    /*!
     * @brief Class destructor.
     */
    ~SideBar() override;

    /*!
     * @brief Sets the text of the user label button.
     * @param text The text to display on the user label button.
     */
    void setUserLabelButtonText(const QString& text) const;

private:
    QVBoxLayout *mainLayout;                    ///< Main vertical layout for the sidebar.
    QVBoxLayout *chatsLayout;                   ///< Layout for the chats section.
    QHBoxLayout *functionalLayout;              ///< Layout for functional buttons.
    QHBoxLayout *userLayout;                    ///< Layout for the user section.
    QLineEdit *searchBox;                       ///< Search box for the sidebar.
    QPushButton *cameraButton;                  ///< Button to turn on/off the camera.
    // display???
    QPushButton *displayButton;                 ///< Button to turn on/off streaming user's screen
    QPushButton *microphoneButton;              ///< Button to turn on/off the microphone.
    QPushButton *soundButton;                   ///< Button to turn on/off the sound.
    QPushButton *hungUpButton;                  ///< Button to hang up a call.
    QPushButton *userLabelButton;               ///< Button displaying info about user (username and online status)

protected:

    /*!
     * @brief Initializes the user interface components of the SideBar.
     *
     * This method overrides the pure virtual function @ref BaseWidget::initUI
     * to set up layouts, buttons, and other UI elements.
     */
    void initUI() override;
};

#endif // SIDEBAR_H
