#ifndef DENDRITESEGMENT_H
#define DENDRITESEGMENT_H

#include <QObject>

class Synapse;

class DendriteSegment : public QObject
{
    Q_OBJECT
public:
    explicit DendriteSegment(QObject *parent = 0);

    void fillSynapses(Synapse *s);

    // to cover the changes, public these functions
    void connectSynapses();

    void check();

signals:
    /**
     * @brief activated
     *  当一个 dendrite segment的有效连接数 >= m_nActiveThreshHold 时， 发射此信号,向column（proximal)
     *  或者 cell(distal) 发送
     */
    void activated(int);

public slots:
    // 对收到的 synapse 的activated信号进行处理
    void onRecv();

private:

    // 用于计算 activated synapse 的连接数
    int m_nActivatedSynapse;

    // 用于计算没有激活的次数
    int m_nActiveTimes;

    // synapses for receiving signal
    QList<Synapse*> m_listSynapses;


};

#endif // DENDRITESEGMENT_H
