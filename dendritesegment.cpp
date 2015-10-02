#include "dendritesegment.h"
#include "htmGlobal.h"
#include "synapse.h"


DendriteSegment::DendriteSegment(QObject *parent)
    :QObject(parent)
{
    m_nActivatedSynapse = 0;
    m_nActiveTimes = 0;
    m_bIsSequence = false;
    m_bIsLearning = false;
}

void DendriteSegment::fillSynapses(Synapse *s)
{
    m_listSynapses << s;
}

void DendriteSegment::connectSynapses()
{
    if (m_listSynapses.isEmpty())
    {
        return;
    }

    // disconnect at first, to cover the changes
    QList<Synapse*>::Iterator iter;
    for (iter = m_listSynapses.begin(); iter != m_listSynapses.end(); ++iter)
    {
        disconnect((*iter), SIGNAL(activated()), this, SLOT(onRecv()));
    }

    // then connect
    for (iter = m_listSynapses.begin(); iter != m_listSynapses.end(); ++iter)
    {
        connect((*iter), SIGNAL(activated()), this, SLOT(onRecv()));
    }
}

void DendriteSegment::updateSynapsesParams()
{
    QList<Synapse*>::iterator iter;
    for (iter=m_listSynapses.begin(); iter!=m_listSynapses.end(); ++iter)
    {
        if ((*iter)->isActivated())
        {
            (*iter)->incPerm();
        }
        else
        {
            (*iter)->decPerm();
        }
    }
}

void DendriteSegment::check()
{
    if (m_nActivatedSynapse >= HtmGlobal::m_nActiveThreshHold)
    {
        m_nActiveTimes++;
        emit activated(m_nActivatedSynapse);
    }
}

void DendriteSegment::clearActivatedSynapses()
{
    m_nActivatedSynapse = 0;
}

void DendriteSegment::onRecv()
{
    m_nActivatedSynapse++;
}
QList<Synapse *> DendriteSegment::listSynapses() const
{
    return m_listSynapses;
}

bool DendriteSegment::isSequence() const
{
    return m_bIsSequence;
}

void DendriteSegment::setSequence(bool bIsSequence)
{
    m_bIsSequence = bIsSequence;
}

