#include "workspace.h"

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
     *  mainLayout - for all widget
     *  To be continued...
     *
     */
    this->mainLayout = new QHBoxLayout(this);

    /*
     *  Initialize default label
     */
    QLabel *defaultLabel = new QLabel("Select chat or server to start messaging", this);
    defaultLabel->setAlignment(Qt::AlignCenter);

    /*
     *  Add default label to layout
     */
    this->mainLayout->addWidget(defaultLabel);

    /*
     *  Set layout for widget
     */
    setLayout(this->mainLayout);

    this->mainLayout->setContentsMargins(0,0,0,0);
    this->mainLayout->setSpacing(0);
}
