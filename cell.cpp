#include "cell.h"
#include "dendritesegment.h"
#include "synapse.h"


Cell::Cell(QObject *parent) : QObject(parent)
{
    m_bIsActive = false;
    m_bIsPredictive = false;
    m_bIsChosen = false;
    m_bIsLearning = false;
    m_bWasActive = false;
}

void Cell::fillDendriteSegments(DendriteSegment *d)
{
    m_listDendriteSegment << d;
    connect(d, SIGNAL(activated()), this, SLOT(onRecvSegmentActivated()));
}

void Cell::fillSynapses(Synapse *s)
{
    m_listSynapses << s;
    connect(this, SIGNAL(activated()), s, SLOT(onRecv()));
}

void Cell::resetButPredictive()
{
    m_bWasActive =
    m_bIsActive =
    m_bIsChosen =
    m_bIsLearning = false;
}

void Cell::resetAll()
{
    m_bWasActive =
    m_bIsActive =
    m_bIsChosen =
    m_bIsLearning =
    m_bIsPredictive = false;
}

void Cell::onRecvSegmentActivated()
{
    // set to be predictive only if the cell is NOT ACTIVE
    if (!m_bIsActive)
    {
        m_bIsPredictive = true;
    }
}

void Cell::setActive(bool b)
{
    m_bIsActive = b;

    if (b)
    {
        // if the cell becomes active, send 'active' signal
        emit activated();
    }
}

void Cell::setPredictive(bool b)
{
    m_bIsPredictive = b;
}

void Cell::setChosen(bool b)
{
    m_bIsChosen = b;
}

void Cell::setLearning(bool b)
{
    m_bIsLearning = b;
}


bool Cell::isActive()
{
    return m_bIsActive;
}

bool Cell::isPredictive()
{
    return m_bIsPredictive;
}

bool Cell::isChosen()
{
    return m_bIsChosen;
}

bool Cell::isLearning()
{
    return m_bIsLearning;
}

bool Cell::wasActive()
{
    if (m_bWasActive)
    {
        m_bWasActive = false;
        return true;
    }

    return false;
}

