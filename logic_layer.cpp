#include "logic_layer.h"
#include "welcome_widget.h"
#include "home_window.h"

#include <QDebug>
#include <QTime>
#include <QCoreApplication>
#include <QMessageBox>
#include <QPixmap>

LogicLayer::LogicLayer(QObject *parent) :
    QObject(parent)
{
    welcome_ = new WelcomeWidget();
    home_ = new HomeWindow();

    QObject::connect(home_, SIGNAL(signalCheck()),
                                 this, SLOT(slotCheck()));
}

LogicLayer::~LogicLayer() {
    delete welcome_;
    delete home_;
}

void LogicLayer::ShowWelcome() {
    welcome_->show();
}
void LogicLayer::HideWelcome() {
    welcome_->hide();
}
void LogicLayer::ShowHome(){
    home_->show();
}
WelcomeWidget* LogicLayer::get_welcome_(void) {
    return welcome_;
}

///////////////////////////////////////////// 核心算法 ///////////////////////////////////////////
void LogicLayer::slotCheck() {
    QPixmap card_pix;
    QString card_type;
    QPixmap notice_pix(":/Icons/sign-check-icon.png");
    QString card_number = home_->get_card_number_();

    if (LuhnCheck(card_number, card_number.size())) {
        switch (CheckCardType(card_number)) {
        case CardType::VISA:
            card_pix.load(":/Cards/V7.png");
            card_type = QString("VISA card");
            break;
        case CardType::MASTER:
           card_pix.load(":/Cards/mastercard_512.png");
           card_type = QString("Master card");
            break;
        case CardType::AM_EXR:
            card_pix.load(":/Cards/american-express.png");
            card_type = QString("American Express card");
            break;
        case CardType::DISCOVER:
            card_pix.load(":/Cards/discover.png");
            card_type = QString("Discover card");
            break;
        default:
            card_pix.load(":/Cards/credit_card.png");
            card_type = QString("Unknown Type???");
            notice_pix.load(":/Icons/sign-question-icon.png");
            break;
        }
        home_->ShowCardType(card_type);
        home_->ShowCardPicture(card_pix.scaled(512, 512));
        home_->ShowNotice(notice_pix.scaled(60, 60));
    } else {
        QPixmap notice_pix(":/Icons/sign-error-icon.png");
        home_->ShowNotice(notice_pix.scaled(60, 60));
        home_->ShowCardPicture(QPixmap(":/Icons/cancel_red.png"));

        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Invalidate credit card number"));
        msgBox.setWindowIcon(QIcon(":/Cards/CCX.png"));

        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("<h1>Not a Valid Credit Card Number!</h1>");
        msgBox.setInformativeText("<h2><b>It cannot pass \"LuhnCheck\"!</b></h2>");
//        msgBox.setStandardButtons(QMessageBox::Ok);
        QPushButton *tryButton = msgBox.addButton(tr("Try Again"), QMessageBox::ActionRole);
        if (tryButton == tryButton){}
        int ret = msgBox.exec();
        switch (ret) {}

        qDebug() << "inValidate";
    }
}

bool LogicLayer::LuhnCheck(const QString card_number, int len) {
    int digit = 0;
    int sum = 0;
    int parity = len % 2;

    for (int i = 0; i <= len - 2; i++) {
        digit = card_number[i].digitValue();

        if (parity == i % 2) {
            digit *= 2;
            if (digit > 9) {
                digit = digit / 10 + digit % 10;
            }
        }
        sum += digit;
    }
    sum += card_number[len - 1].digitValue();

    return !(sum % 10);
}

CardType LogicLayer::CheckCardType(const QString card_number) {
    if (card_number.startsWith("4")) {
        return CardType::VISA;
    } else if (card_number.startsWith("5")) {
        return CardType::MASTER;
    } else if (card_number.startsWith("37")) {
        return CardType::AM_EXR;
    } else if (card_number.startsWith("6")) {
        return CardType::DISCOVER;
    } else {
        return CardType::UNKNOWN;
    }
}

//////////////////////////////////////////////////延时//////////////////////////////////////////////
void LogicLayer::Sleep (unsigned int msec) {
    QTime timer = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < timer )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}












