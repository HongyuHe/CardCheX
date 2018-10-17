#include "welcome_widget.h"
#include "ui_welcome_widget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);      //去除边框；
//    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明
    this->setWindowIcon(QIcon(":/Cards/CCX.png"));
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}
