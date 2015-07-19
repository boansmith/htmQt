#include "cell.h"
#include "dendritesegment.h"
#include "synapse.h"


Cell::Cell(QObject *parent) : QObject(parent)
{
    m_bIsActive = false;
    m_bIsPredictive = false;
}

void Cell::fillDendriteSegments(DendriteSegment *d)
{
    m_listDendriteSegment << d;
}

void Cell::fillSynapses(Synapse *s)
{
    m_listSynapses << s;
}

void Cell::connectSynapses()
{
    if (m_listSynapses.isEmpty())
    {
        return;
    }

    // disconnect at first, to cover the changes
    QList<Synapse*>::Iterator iter;
    for (iter = m_listSynapses.begin(); iter != m_listSynapses.end(); ++iter)
    {
        disconnect(this, SIGNAL(activated()), (*iter), SLOT(onRecv()));
    }

    // then connect
    for (iter = m_listSynapses.begin(); iter != m_listSynapses.end(); ++iter)
    {
        connect(this, SIGNAL(activated()), (*iter), SLOT(onRecv()));
    }
}

void Cell::connectDendriteSegments()
{
    if (m_listDendriteSegment.isEmpty())
    {
        return;
    }

    // disconnect at first, to cover the changes
    QList<DendriteSegment*>::Iterator iter;
    for (iter = m_listDendriteSegment.begin(); iter != m_listDendriteSegment.end(); ++iter)
    {
        disconnect((*iter), SIGNAL(activated()), this, SLOT(onRecvSegmentActivated()));
    }

    // then connect
    for (iter = m_listDendriteSegment.begin(); iter != m_listDendriteSegment.end(); ++iter)
    {
        connect((*iter), SIGNAL(activated()), this, SLOT(onRecvSegmentActivated()));
    }
}

void Cell::onRecvSegmentActivated()
{

    // set to be predictive only if the cell is NOT ACTIVE
    if (!m_bIsActive)
    {
        m_bIsPredictive = true;
    }
}

void Cell::setActive()
{
    m_bIsActive = true;

    // 如果cell变为active， 发送此cell变为active了的消息
    emit activated();
}


bool Cell::isActive()
{
    return m_bIsActive;
}

bool Cell::isPredictive()
{
    return m_bIsPredictive;
}

