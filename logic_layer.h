#ifndef LOGIC_LAYER_H
#define LOGIC_LAYER_H

#include <QObject>

class WelcomeWidget;
class HomeWindow;

enum class CardType {
    UNKNOWN = 0,
    VISA,
    MASTER,
    AM_EXR,
    DISCOVER,
};

class LogicLayer: public QObject
{
    Q_OBJECT
public:
    explicit LogicLayer(QObject *parent = 0);
    ~LogicLayer();

    WelcomeWidget* get_welcome_(void);

    void Sleep (unsigned int msec);
    void ShowWelcome(void);
    void HideWelcome(void);
    void ShowHome(void);

    bool LuhnCheck(const QString card_number, int len);
    CardType CheckCardType(const QString card_number);

private:
    WelcomeWidget* welcome_;
    HomeWindow* home_;

public slots:
    void slotCheck();
};

#endif // LOGIC_LAYER_H
