/*!
 * @file workspace.h
 * @author Ivan Rastegaev
 * @brief Declares the WorkSpace class, representing the main workspace widget.
 */

#ifndef WORKSPACE_H
#define WORKSPACE_H

/* Global headers */
#include <QHBoxLayout>
#include <QLabel>

/* Local headers */
#include "basewidget.h"

/*!
 * @class WorkSpace
 * @brief Represents the main workspace widget for the application.
 *
 * This class extends @ref BaseWidget to provide the main workspace.
 * It serves as a container for application-specific content and manages its user interface.
 */
class WorkSpace final : public BaseWidget
{
    Q_OBJECT

public:

    /*!
     * @brief Class constructor.
     * @param parent Pointer to the parent widget. Defaults to `nullptr`.
     */
    explicit WorkSpace(QWidget *parent = nullptr);

    /*!
     * @brief Class destructor.
     */
    ~WorkSpace() override;

private:
    QHBoxLayout *mainLayout;        ///< The main horizontal layout for the workspace.

protected:

    /*!
     * @brief Initializes the user interface components of the WorkSpace.
     *
     * This method overrides the pure virtual function @ref BaseWidget::initUI
     * to set up layouts, buttons, and other UI elements.
     */
    void initUI() override;
};

#endif // WORKSPACE_H
