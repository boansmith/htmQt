#include "Organiser.h"
#include "globalparams.h"
#include "cell.h"
#include "column.h"
#include "dendritesegment.h"
#include "inputelement.h"
#include "synapse.h"

Organiser::Organiser(QObject *parent) : QObject(parent)
{

}


// process binary inputs
void Organiser::fillInputs(const char *data)
{
    int nWidth  = GlobalParams::m_nWidthInput;
    int nHeight = GlobalParams::m_nHeightInput;

    for (int i=0; i<nHeight; ++i)
    {
        for (int j=0; j<nWidth; ++j)
        {
            m_listInputs << new InputElement(false);
        }
    }
}



/**
 * @brief Organiser::buildColumns
 *        according to GlobalParams, build the columns, set the proximal dendriteSegment
 *        in the Organiser's view, it can only see the column array and the proximal dendriteSegments
 *
 * @return
 */
void Organiser::buildColumns()
{
    int nWidth  = GlobalParams::m_nWidthColumn;
    int nHeight = GlobalParams::m_nHeightColumn;

    for (int i=0; i<nHeight; ++i)
    {
        for (int j=0; j<nWidth; ++j)
        {
            Column* columnTmp = new Column(i*nWidth+j);
            m_listColumns << columnTmp;

            // every column has only one proximal dendriteSegment
            columnTmp->setDendriteSegment(new DendriteSegment);
        }
    }
}


/**
 * @brief Organiser::buildColumns
 *        the same with above but need the width and height to be specified
 * @param nWidth
 * @param nHeight
 * @return
 */
void Organiser::buildColumns(int nWidth, int nHeight)
{
    for (int i=0; i<nHeight; ++i)
    {
        for (int j=0; j<nWidth; ++j)
        {
            Column* columnTmp = new Column(i*nWidth+j);
            m_listColumns << columnTmp;

            // every column has only one proximal dendriteSegment
            columnTmp->setDendriteSegment(new DendriteSegment);

        }
    }
}


QList<Column *> Organiser::listColumns() const
{
    return m_listColumns;
}



/**
 * @brief Organiser::connectElements
 *        connect input elements to columns' dendriteSegment with synapse
 * @return
 */
bool Organiser::connectElements()
{
    Q_ASSERT(!m_listColumns.isEmpty());
    Q_ASSERT(!m_listInputs.isEmpty());

    // first, link input elements with colums through synapses
    // every input element should just link to a subset of the columns
    // in general, the number of inputElement is (much) less than that of column
    int nTotalLink = m_listInputs.size()*1.5;
    int nNumOverlap = (nTotalLink-m_listInputs.size())/m_listColumns.size();
    
    float fWidthOverlap = 0.05;
    float fBeginRatio   = 0.0;
    float fEndRatio     = 0.0;
    
    for (int i=0; i<m_listInputs.size(); ++i)
    {
        fBeginRatio = float(i)/float(m_listInputs.size());
        fEndRatio   = fBeginRatio + fWidthOverlap;
        int nColSize = m_listColumns.size();
        for (int j=nColSize*fBeginRatio; j<(nColSize*fEndRatio > nColSize ? nColSize : nColSize*fEndRatio); ++j)
        {
            Synapse* sTmp = new Synapse(j);

            m_listInputs.at(i)->fillSynapses(sTmp);
            m_listColumns.at(j)->dendriteSegment()->fillSynapses(sTmp);
        }
    }

    // then, for every input element, connect their synapses
    QList<InputElement*>::Iterator iterInput;
    for (iterInput=m_listInputs.begin(); iterInput!=m_listInputs.end(); ++iterInput)
    {
        (*iterInput)->connectSynapses();
    }

    // then, for every column, connect its dendriteSegment
    // for every dendriteSegment of the column, connect its synapses
    QList<Column*>::iterator iterCol;
    for (iterCol=m_listColumns.begin(); iterCol!=m_listColumns.end(); ++iterCol)
    {
        (*iterCol)->connectDendriteSegment();
        (*iterCol)->dendriteSegment()->connectSynapses();
    }

    return true;
}

