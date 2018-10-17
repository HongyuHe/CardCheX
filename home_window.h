#ifndef HOME_WINDOW_H
#define HOME_WINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPixmap>

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void signalCheck();

public:
    explicit HomeWindow(QWidget *parent = 0);
    ~HomeWindow();

    void ShowCardPicture(QPixmap card_pix) const;
    void ShowCardType(QString card_type) const;
    void ShowNotice(QPixmap notice_pix) const;

    QString get_card_number_(void);

private slots:
    void on_pushButtonCheck_clicked();

    void on_lineEditCardNumber_textChanged(const QString &arg1);

    void on_actionSamples_triggered();

    void on_actionLuhnInfo_triggered();

    void on_actionAbout_CardCheX_triggered();

private:
    Ui::HomeWindow *ui;

    QString card_number_;
};

#endif // HOME_WINDOW_H
