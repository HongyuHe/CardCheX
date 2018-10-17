#include "home_window.h"
#include "ui_home_window.h"

#include <QRegExp>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QFont>

HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeWindow)
{
    ui->setupUi(this);

    QFont font ( "Microsoft YaHei", 20, 75);
    ui->labelCardType->setFont(font);
    ui->labelCardType->setText("CardCheX");

    QFile css(":/qss/lightblue.css");

    if (!css.open(QIODevice::ReadOnly))
    {
        qFatal("Could Not Open the theme !");
    }else
    {
        QTextStream data(&css);    //将文件与文本流绑定；
        QString theme = data.readAll();       //从文件中读取数据存入content；

        css.close();
        qApp->setStyleSheet(theme);
    }

    this->setWindowIcon(QIcon(":/Cards/CCX.png"));
    this->setWindowTitle("CardCheX 2018");
    ui->labelCardPicture->setPixmap(QPixmap(":/Cards/credit59.png").scaled(512, 450));
    ui->lineEditCardNumber->clear();
    ui->lineEditCardNumber->setContextMenuPolicy(Qt::DefaultContextMenu);
    card_number_.clear();

    //限制文本框输入数字：
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEditCardNumber );
    ui->lineEditCardNumber->setValidator(validator);
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::ShowCardPicture(QPixmap card_pix) const {
    ui->labelCardPicture->setPixmap(card_pix);
    ui->labelCardPicture->show();
}

void HomeWindow::ShowCardType(QString card_type) const {
    ui->labelCardType->setText(card_type);
}

void HomeWindow::ShowNotice(QPixmap notice_pix) const {
    ui->labelNotice->setPixmap(notice_pix);
}

QString HomeWindow::get_card_number_(void) {
    return card_number_;
}
/////////////////////////////////////// private slots //////////////////////////////////////////////////
void HomeWindow::on_pushButtonCheck_clicked() {
    card_number_ = ui->lineEditCardNumber->text();

    if (card_number_.isEmpty()) {
        ui->labelNotice->setText(tr("*No Number Entered!"));
    }  else if (card_number_.size() < 13 || card_number_.size() > 16) {
        ui->labelNotice->setText(tr("*Card number should be 13 ～ 16 digits!"));
    } else {
        ui->labelNotice->clear();
        emit signalCheck();
    }
}

void HomeWindow::on_lineEditCardNumber_textChanged(const QString &arg1) {
    ui->labelNotice->clear();
    ui->labelCardType->setText("CardCheX");
    ui->labelCardPicture->setPixmap(QPixmap(":/Cards/credit59.png").scaled(512, 450));
    if (arg1 == ""){};  //delete Warning;
}

void HomeWindow::on_actionSamples_triggered()
{
    QPixmap icon = QPixmap(":/Cards/Samples.png");

    QMessageBox msgBox;
    msgBox.resize(800, 800);
    msgBox.setWindowTitle(tr("Samples..."));
    msgBox.setWindowIcon(QIcon(":/Cards/CCX.png"));

    msgBox.setText("<h1>Valid Credit Card Number</h1>"
                            "<h3>"
                              "<ul>"
                             "<li> VISA:         420403413513514 </li>"
                             "<li> MASTER:    520403413513513 </li>"
                            "<li> DISCOVER:   620403413513512 </li>"
                            "<li> AM_EXR：   370403413513514 </li>"
                            "<li> UNKNOWN: 	220403413513516 </li>"
                              "</ul>"
                          "</h3>");
    msgBox.setTextInteractionFlags(Qt::TextSelectableByMouse);
    msgBox.setStandardButtons(QMessageBox::Ok);
//    QPushButton *tryButton = msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);
    msgBox.setIconPixmap(icon);
    int ret = msgBox.exec();
    switch (ret) {}
}

void HomeWindow::on_actionLuhnInfo_triggered()
{
    QPixmap icon = QPixmap(":/Cards/LuhnInfo.jfif");

    QMessageBox msgBox;
    msgBox.resize(800, 800);
    msgBox.setWindowTitle(tr("Luhn Algorithm"));
    msgBox.setWindowIcon(QIcon(":/Cards/CCX.png"));

    msgBox.setText("<h1>Luhn Algorithm</h1>"
                            "<div>"
                              "<ol>"
                             "<li> Double every second digit, from the rightmost </li>"
                             "<li> Sum all the individual digits (digits in parentheses are the products from Step 1) </li>"
                            "<li> If the sum is a multiple of 10, the account number is possibly valid. </li>"
//                            "<li> AM_EXR：   370403413513514 </li>"
//                            "<li> UNKNOWN: 	220403413513516 </li>"
                              "</ol>"
                          "</div>");
    msgBox.setTextInteractionFlags(Qt::TextSelectableByMouse);
    msgBox.setStandardButtons(QMessageBox::Ok);
//    QPushButton *tryButton = msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);
    msgBox.setIconPixmap(icon);
    int ret = msgBox.exec();
    switch (ret) {}
}

void HomeWindow::on_actionAbout_CardCheX_triggered()
{
    QPixmap icon = QPixmap(":/Cards/CCX.png");

    QMessageBox msgBox;
    msgBox.resize(800, 800);
    msgBox.setWindowTitle(tr("About CardCheX"));
    msgBox.setWindowIcon(QIcon(":/Cards/CCX.png"));

    msgBox.setText("<h1>CardChex 2018</h1>"
                   "<h2>【Function】Check if the credit card number is valid and check the card's type.</h2>"
                            "<h3>"
                              "<div>Copyright (C) 2018 Hongyu He (Ray). All rights reserved.</div>"

                   "</h3>");
    msgBox.setInformativeText("<sub>My GitHub：<a href=https://github.com/HongyuHe style='color:blue'>github.com/HongyuHe></sub>");
    msgBox.setTextInteractionFlags(Qt::TextSelectableByMouse);
//    msgBox.setStandardButtons(QMessageBox::Ok);
    QPushButton *tryButton = msgBox.addButton(tr("Close"), QMessageBox::ActionRole);
    if (tryButton) {}
    msgBox.setIconPixmap(icon);
    int ret = msgBox.exec();
    switch (ret) {}
}
