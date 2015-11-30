#ifndef SYNAPSE_H
#define SYNAPSE_H

#include <QObject>

class Synapse : public QObject
{
    Q_OBJECT
public:
    explicit Synapse(int nId, float perm, QObject *parent = 0);
    explicit Synapse(int nId, QObject *parent=0);

signals:
    /**
     * @brief synapseActivated
     *  当input为1， 而且与它连接的synapse处于connected状态时， 发送此信号
     */
    void activated();



public slots:
    /**
     * @brief onRecv
     * 接收input的槽， 起衔接作用
     * 只有input为1， input单元才会发送信号
     */
    void onRecv();

public:
    bool isConnected();
    bool isActivated();

    int activeTimes();

    /**
     * @brief process permanence
     *        process permanently
     */
    void incPerm();
    void decPerm();

    /**
     * @brief incPermTemporal
     *        process temporally
     */
    void incPermTemporal();
    void decPermTemporal();

private:
    float   m_fPerm;

    // 是一个 temporal 的增量，
    // every time when a perm has been processed( inc or dec ), m_fPermTmprDelta will be cleared.
    float   m_fPermTmpDelta;

    /**
     * @brief m_bIsContributed
     * 是否同时处于connected并且接受到有效input
     */
    bool    m_bIsActivated;

    int     m_nId;

    int     m_nActiveTimes;

};

#endif // SYNAPSE_H
