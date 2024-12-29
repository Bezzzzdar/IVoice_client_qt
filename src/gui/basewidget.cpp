#include "include/widgets.h"

/**************************************************
 *
 *      Abstract class for any widget in app
 *
 *************************************************/
BaseWidget::BaseWidget(QWidget *parent)
    : QWidget(parent) {}

BaseWidget::~BaseWidget() {}

void BaseWidget::paintEvent(QPaintEvent *pe)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void BaseWidget::applyStyles()
{
    QFile style_file(":/resources/styles/styles.qss");
    if (style_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString style_sheet = style_file.readAll();

        this->setStyleSheet(style_sheet);

        style_file.close();
    }
}


/**************************************************
 *
 *      Abstract class for any dialog in app
 *
 *************************************************/
void BaseWidget::initialize()
{
    this->initUI();
    this->applyStyles();
}

BaseDialog::BaseDialog(QWidget *parent)
    : QDialog(parent) {}

BaseDialog::~BaseDialog() {}

void BaseDialog::paintEvent(QPaintEvent *pe)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void BaseDialog::applyStyles()
{
    QFile style_file(":/resources/styles/styles.qss");
    if (style_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString style_sheet = style_file.readAll();

        this->setStyleSheet(style_sheet);

        style_file.close();
    }
}

void BaseDialog::initialize()
{
    this->initUI();
    this->applyStyles();
}
