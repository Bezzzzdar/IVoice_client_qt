#include "basewidget.h"

/**************************************************
 *
 *      Abstract class for any widget in app
 *
 *************************************************/
BaseWidget::BaseWidget(QWidget *parent)
    : QWidget(parent) {}

BaseWidget::~BaseWidget() = default;

void BaseWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption option;
    option.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void BaseWidget::applyStyles()
{
    if (QFile styleFile(":/resources/styles/styles.qss"); styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        const QString styleSheet = styleFile.readAll();

        this->setStyleSheet(styleSheet);

        styleFile.close();
    }
}

void BaseWidget::initialize()
{
    this->initUI();
    this->applyStyles();
}

/**************************************************
 *
 *      Abstract class for any dialog in app
 *
 *************************************************/

BaseDialog::BaseDialog(QWidget *parent)
    : QDialog(parent) {}

BaseDialog::~BaseDialog() = default;

void BaseDialog::paintEvent(QPaintEvent *event)
{
    QStyleOption option;
    option.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void BaseDialog::applyStyles()
{
    if (QFile styleFile(":/resources/styles/styles.qss"); styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        const QString styleSheet = styleFile.readAll();

        this->setStyleSheet(styleSheet);

        styleFile.close();
    }
}

void BaseDialog::initialize()
{
    this->initUI();
    this->applyStyles();
}
