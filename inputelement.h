#ifndef INPUTELEMENT_H
#define INPUTELEMENT_H

#include <QObject>
#include <QList>

class Synapse;

class InputElement : public QObject
{
    Q_OBJECT
public:
    explicit InputElement(bool value, QObject *parent = 0);

    void setValue(bool b);

    // 等一个回合的所有输入完毕后， 再统一发射信号
    void checkValue();

    void fillSynapses(Synapse *s);

signals:
    void inputValid();

private:
    bool m_bValue;

    QList<Synapse*> m_listSynapses;

};

#endif // INPUTELEMENT_H
