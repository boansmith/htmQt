#include "column.h"
#include "globalparams.h"
#include "cell.h"
#include "dendritesegment.h"

Column::Column(int nId, QObject *parent) :
    QObject(parent)
{
    m_nId               = nId;
    m_nOverlap          = 0;
    m_dendriteSegment   = NULL;
    m_nActiveTimes      = 0;
    m_fBoost            = 1.0;

    // fill each column with cells
    for (int iCell=0; iCell<GlobalParams::m_nCellsPerCol; ++iCell)
    {
        m_listCell << new Cell;
    }

}


// for reconstruction
void Column::fillCell(Cell *cell)
{
    m_listCell << cell;
}

void Column::setDendriteSegment(DendriteSegment *d)
{
    m_dendriteSegment = d;
}

DendriteSegment *Column::dendriteSegment()
{
    return m_dendriteSegment;
}

void Column::connectDendriteSegment()
{
    Q_ASSERT(m_dendriteSegment != NULL);

    connect(m_dendriteSegment, SIGNAL(activated(int)), this, SLOT(onRecv(int)));
}


// 如果有cell处于 predictive 状态， 则设定这些cell为active
// 如果没有一个cell处于 predictive 状态， 则所有的cell 均被设为 active
void Column::setActive()
{
    m_nActiveTimes++;

    bool hasOnePredictiveAtLeast = false;
    for (int i=0; i<m_listCell.size(); ++i)
    {
        if (m_listCell.at(i)->isPredictive())
        {
            m_listCell.at(i)->setActive();
            hasOnePredictiveAtLeast = true;
        }
    }

    if (!hasOnePredictiveAtLeast)
    {
        for (int i=0; i<m_listCell.size(); ++i)
        {
            m_listCell.at(i)->setActive();
        }
    }
}


// 当收到来自proximal dendriteSegment 的信号时
void Column::onRecv(int overlap)
{
    m_nOverlap = overlap;
}

int Column::id()
{
    return m_nId;
}

int Column::overlap()
{
    return m_nOverlap;
}

int Column::activeTimes() const
{
    return m_nActiveTimes;
}

float Column::boost() const
{
    return m_fBoost;
}

void Column::setBoost(float fBoost)
{
    m_fBoost = fBoost;
}



