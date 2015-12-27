#include "Organiser.h"
#include "htmGlobal.h"
#include "cell.h"
#include "column.h"
#include "dendritesegment.h"
#include "inputelement.h"
#include "synapse.h"

Organiser::Organiser(QObject *parent) : QObject(parent)
{

}


void Organiser::buildSpatialPooler()
{
    buildInputElements();
    buildColumns();
    connectElements();
}

void Organiser::feedSpatialPooler(const QList<bool> &data)
{
    int nWidth  = HtmGlobal::m_nWidthInput;
    int nHeight = HtmGlobal::m_nHeightInput;
    Q_ASSERT(data.size() == nWidth*nHeight);

    for (int i=0; i<nHeight; ++i)
    {
        for (int j=0; j<nWidth; ++j)
        {
            if (data.at(nWidth*i+j))
            {
                m_listInputs.at(nWidth*i+j)->setValue(true);
            }
            else
            {
                m_listInputs.at(nWidth*i+j)->setValue(false);
            }
        }
    }

    // this is one way, check after set all the values,
    // the alternative is to check one by one only if the element's value is set, there will be just one double for
    // loop if so.
    for (int i=0; i<nHeight; ++i)
    {
        for (int j=0; j<nWidth; ++j)
        {
            m_listInputs.at(nWidth*i+j)->checkValue();
        }
    }
}


void Organiser::buildInputElements()
{
    int nWidth  = HtmGlobal::m_nWidthInput;
    int nHeight = HtmGlobal::m_nHeightInput;

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
 *        according to HtmGlobal, build the columns, set the proximal dendriteSegment
 *        in the Organiser's view, it can only see the column array and the proximal dendriteSegments
 *
 * @return
 */
void Organiser::buildColumns()
{
    int nWidth  = HtmGlobal::m_nWidthColumn;
    int nHeight = HtmGlobal::m_nHeightColumn;

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

    // first, link input elements with columns through synapses
    // every column should connect to a subset of input elements
    
    //float fWidthOverlap = 0.05;
    // this place need to be optimized
    float fWidthOverlap = 1.0/float(m_listColumns.size())+0.01;
    float fBeginRatio   = 0.0;
    float fEndRatio     = 0.0;
    
    for (int i=0; i<m_listInputs.size(); ++i)
    {
        fBeginRatio = float(i)/float(m_listInputs.size());
        fEndRatio   = fBeginRatio + fWidthOverlap;
        int nColSize = m_listColumns.size();
        int nUpper = nColSize*fEndRatio > nColSize ? nColSize : nColSize*fEndRatio;
        for (int j=nColSize*fBeginRatio; j<nUpper; ++j)
        {
            Synapse* sTmp = new Synapse(j);

            m_listInputs.at(i)->fillSynapses(sTmp);
            m_listColumns.at(j)->dendriteSegment()->fillSynapses(sTmp);
        }
    }

    return true;
}

