#include "dendritesegment.h"
#include "globalparams.h"
#include "synapse.h"


DendriteSegment::DendriteSegment(int nId, QObject *parent)
    :QObject(parent)
{
    m_nActivatedSynapse = 0;
    m_nActiveTimes = 0;
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

void DendriteSegment::check()
{
    if (m_nActivatedSynapse >= GlobalParams::m_nActiveThreshHold)
    {
        m_nActiveTimes++;
        emit activated(m_nActivatedSynapse);
    }
}

void DendriteSegment::onRecv()
{
    m_nActivatedSynapse++;
}
