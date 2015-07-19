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
            if (*(data+i*nWidth+j) == 0)
            {
                m_listInputs << new InputElement(false);
            }
            else
            {
                m_listInputs << new InputElement(true);
            }
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

            columnTmp->setDendriteSegment(new DendriteSegment);
        }
    }
}


/**
 * @brief Organiser::buildColumns
 *        the same with above but with the width and height specified
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

            //proximal dendriteSegment has the same id as the column it attached
            columnTmp->setDendriteSegment(new DendriteSegment);

        }
    }
}

bool Organiser::start()
{

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

    for (int i=0; i<m_listInputs.size(); ++i)
    {
        for (int j=0; j<m_listColumns.size(); ++i)
        {
            Synapse* sTmp = new Synapse(j);

            m_listInputs.at(i)->fillSynapses(sTmp);
            m_listColumns.at(j)->dendriteSegment()->fillSynapses(sTmp);
        }
    }

}

