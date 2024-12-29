#include "include/widgets.h"

WorkSpace::WorkSpace(QWidget *parent)
    : BaseWidget(parent)
{
    this->initialize();
}

WorkSpace::~WorkSpace() {}

void WorkSpace::initUI()
{
    this->setObjectName("WorkSpace");
    /*  Initialize layouts for workspace
     *
     *  main_layout - for all widget
     *  To be continued...
     *
     */
    this->main_layout = new QHBoxLayout(this);

    /*
     *  Initialize default label
     */
    QLabel *default_label = new QLabel("Select chat or server to start messaging", this);
    default_label->setAlignment(Qt::AlignCenter);

    /*
     *  Add default label to layout
     */
    this->main_layout->addWidget(default_label);

    /*
     *  Set layout for widget
     */
    setLayout(this->main_layout);

    this->main_layout->setContentsMargins(0,0,0,0);
    this->main_layout->setSpacing(0);

    QFile style_file(":/resources/styles/styles.qss");
    if (style_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString style_sheet = style_file.readAll();

        this->setStyleSheet(style_sheet);

        style_file.close();
    }
}
