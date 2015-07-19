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

    /**
     * @brief process permanence
     */
    void incPerm();
    void decPerm();

private:
    float   m_fPerm;

    /**
     * @brief m_bIsContributed
     * 是否同时处于connected并且接受到有效input
     */
    bool    m_bIsActivated;

    int     m_nId;

};

#endif // SYNAPSE_H