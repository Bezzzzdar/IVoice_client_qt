/*!
 * @file basewidget.h
 * @author Ivan Rastegaev
 * @brief Contains the definitions of abstract classes for custom widgets and dialogs.
 */

#ifndef BASEWIDGET_H
#define BASEWIDGET_H

/* Global headers */
#include <QWidget>
#include <QDialog>
#include <QIODevice>
#include <QPainter>
#include <QFile>
#include <QStyleOption>

/*!
 * @class BaseWidget
 * @brief Provides an abstract class for custom QWidget-based widgets (almost all widgets in app).
 *
 * This class serves as a foundation for creating custom widgets.
 * It includes functionality for initializing the widget and applying styles.
 */
class BaseWidget : public QWidget
{
    Q_OBJECT

public:

    /*!
     * @brief Сlass constructor.
     * @param parent Pointer to the parent widget. Defaults to nullptr.
     */
    explicit BaseWidget(QWidget *parent = nullptr);

    /*!
     * @brief Class destructor.
     */
    virtual ~BaseWidget();

    /*!
     * @brief Initializes the widget by calling necessary setup functions.
     */
    void initialize();

protected:

    /*!
     * @brief Initializes the user interface components.
     *
     * This method is pure virtual and must be implemented by derived classes
     * to set up the specific UI elements.
     */
    virtual void initUI() = 0;

    /*!
     * @brief Handles the paint event to customize widget rendering.
     * @param event Pointer to the QPaintEvent containing paint event details.
     */
    void paintEvent(QPaintEvent *event);

    /*!
     * @brief Applies the styles to the widget.
     */
    void applyStyles();
};


/*!
 * @class BaseDialog
 * @brief Provides an abstract class for custom QDialog-based dialogs (almost all dialogs in app).
 *
 * This class serves as a foundation for creating custom dialogs.
 * It includes functionality for initializing the dialog and applying styles.
 */
class BaseDialog : public QDialog
{
    Q_OBJECT

public:

    /*!
     * @brief Class constructor.
     * @param parent Pointer to the parent widget. Defaults to nullptr.
     */
    explicit BaseDialog(QWidget *parent = nullptr);

    /*!
     * @brief Class destructor.
     */
    virtual ~BaseDialog();

    /*!
     * @brief Initializes the dialog by calling necessary setup functions.
     */
    void initialize();

protected:

    /*!
     * @brief Initializes the user interface components.
     *
     * This method is pure virtual and must be implemented by derived classes
     * to set up the specific UI elements.
     */
    virtual void initUI() = 0;

    /*!
     * @brief Handles the paint event to customize dialog rendering.
     * @param event Pointer to the QPaintEvent containing paint event details.
     */
    void paintEvent(QPaintEvent *event);

    /*!
     * @brief Applies the styles to the dialog.
     */
    void applyStyles();

};

#endif // BASEWIDGET_H
