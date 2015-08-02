#include "synapse.h"
#include "globalparams.h"
#include <QTime>
#include <QDebug>


// 用于从文件载入时
Synapse::Synapse(int nId, float perm, QObject *parent) :
    QObject(parent)
{
    m_nId   = nId;
    m_fPerm = perm;
}

Synapse::Synapse(int nId, QObject *parent) :
    QObject(parent)
{
    m_nId = nId;

    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec() + time.second()*1000);
    float delta = (qrand()%20- 10)*0.01;

    qDebug() << "random delta: " << delta << "\n";

    m_fPerm = GlobalParams::m_fPermConnected + delta;
}


// 此处是 receive valid input时作出的反应
// 当然只有 input 是 valid， input 才会发出信号来激活此 slot
void Synapse::onRecv()
{
    if (m_fPerm >= GlobalParams::m_fPermConnected)
    {
        m_bIsActivated = true;
        emit activated();
    }
    else
    {
        m_bIsActivated = false;
    }
}

bool Synapse::isConnected()
{
    return (m_fPerm >= GlobalParams::m_fPermConnected);
}

// activated 是指收到valid input，同时synapse 处于 connected状态
bool Synapse::isActivated()
{
    return m_bIsActivated;
}

void Synapse::incPerm()
{


    m_fPerm += m_fPermTmprlDelta;
    m_fPermTmprlDelta = 0;
}

void Synapse::decPerm()
{

    m_fPerm -= m_fPermTmprlDelta;
    m_fPermTmprlDelta = 0;
}

void Synapse::incPermTemporal()
{
    m_fPermTmprlDelta += GlobalParams::m_fDeltaPermInc;
}

void Synapse::decPermTemporal()
{
    m_fPermTmprlDelta += GlobalParams::m_fDeltaPermDec;
}
