/*!
 * @file serverbar.h
 * @author Ivan Rastegaev
 * @brief Declaration of the ServerBar class for managing the server bar widget.
 */

#ifndef SERVERBAR_H
#define SERVERBAR_H

/* Global headers */
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include <QIcon>
#include <QSize>

/* Local headers */
#include "basewidget.h"

/*!
 * @class ServerBar
 * @brief A custom widget for managing and displaying a server bar.
 *
 * This class extends @ref BaseWidget for organizing server-related
 * functionality, such as adding servers, accessing settings, and managing direct messages.
 */
class ServerBar final : public BaseWidget
{
    Q_OBJECT

public:

    /*!
     * @brief Constructs a class.
     * @param parent Pointer to the parent widget. Defaults to `nullptr`.
     */
    explicit ServerBar(QWidget *parent = nullptr);

    /*!
     * @brief Destroys the class.
     */
    ~ServerBar() override;

protected:

    /*!
     * @brief Initializes the user interface components of the widget.
     *
     * This method overrides the pure virtual function @ref BaseWidget::initUI
     * to set up layouts, buttons, and other UI elements.
     */
    void initUI() override;

private:
    QVBoxLayout *mainLayout;            ///< The main vertical layout of the widget.
    QVBoxLayout *serversLayout;         ///< Layout for the list of servers.
    QVBoxLayout *functionalLayout;      ///< Layout for functional buttons like settings.
    QPushButton *addServerButton;       ///< Button to add a new server.
    QPushButton *settingsButton;        ///< Button to open settings.
    QPushButton *directMessagesButton;  ///< Button to manage direct messages.

    QVector<QPushButton> *serverList;   ///< A vector containing buttons with servers.

signals:

    /*!
     * @brief [Signal] Emitted when the settings button is clicked.
     */
    void showSettingsWidget() const;

private slots:

    /*!
     * @brief [Slot] Handles the settings button click event.
     */
    void onSettingsButtonClicked() const;
};

#endif // SERVERBAR_H
