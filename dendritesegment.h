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

    void updateSynapsesParams();

    // ****   THIS IS AN IMPORTANT STEP ****
    // check if the valid connected synapses this time exceed the threshhold, if so, emit the activated signal
    // need to clear the m_nActivatedSynapses every time?
    void check();

    // clear the m_nActivatedSynapses
    void clearActivatedSynapses();

    bool isSequence() const;
    void setSequence(bool isSequence);

    QList<Synapse *> listSynapses() const;

    bool isLearning() const;
    void setLearning(bool isLearning);

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

    // 用于计算激活的次数
    int m_nActiveTimes;

    // synapses for receiving signal
    QList<Synapse*> m_listSynapses;

    // only for distal dendriteSegments
    // indicating if the distal dendriteSegments contribute to the cell's prediction
    bool m_bIsSequence;

    // learning switch
    bool m_bIsLearning;
};

#endif // DENDRITESEGMENT_H
