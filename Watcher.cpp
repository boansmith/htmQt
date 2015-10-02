#include "Watcher.h"
#include "Organiser.h"
#include "column.h"
#include "htmGlobal.h"
#include "dendritesegment.h"
#include "synapse.h"

Watcher::Watcher(QObject *parent) : QObject(parent)
{
    m_layer1 = new Organiser;
}

/**
 * @brief Watcher::getActiveColumns
 *        just simply sort the overlap and get the thresh, the kth overlap,
 *        then if a column's overlap is larger than the thresh, add this column to the activeList
 */
void Watcher::getActiveColumns()
{
    // first get the kth overlap, to do this, we need a list of overlaps
    QList<int> listOverlaps;

    QList<Column*> listCols = m_layer1->listColumns();
    QList<Column*>::iterator iter;

    for (iter=listCols.begin(); iter!=listCols.end(); ++iter)
    {
        listOverlaps << (*iter)->overlap();
    }

    // get the sorted list (from small to large)
    qSort(listOverlaps.begin(), listOverlaps.end());

    // get the threshold of being active
    int thresh = listOverlaps.at(int(listOverlaps.size()*(1.0-HtmGlobal::m_fDesiredActiveRatio)));


    // fill the activeColums, but clear first
    m_listActiveColumns.clear();
    for (iter=listCols.begin(); iter!=listCols.end(); ++iter)
    {
        if ((*iter)->overlap() >= thresh)
        {
            m_listActiveColumns << (*iter);
        }
    }
}

void Watcher::updateParamsOfActiveColumns()
{
    QList<Column*>::iterator iter;
    for (iter=m_listActiveColumns.begin(); iter!=m_listActiveColumns.end(); ++iter)
    {
        (*iter)->dendriteSegment()->updateSynapsesParams();
    }
}


// adjust columns' boost and synapses who were always failed
// to do this, we need to know the maximum activeTimes, i.e we need to do some
// statistic about the activeTimes first
void Watcher::adjustActivity()
{
    // get activeTimes of all the columns
    // get activeTimes of all synapses
    QList<int> listColumnActiveTimes;
    QList<int> listSynapsesActiveTimes;
    QList<Column*> listCols = m_layer1->listColumns();
    QList<Column*>::iterator iter;
    for (iter=listCols.begin(); iter!=listCols.end(); ++iter)
    {
        listColumnActiveTimes << (*iter)->activeTimes();

        QList<Synapse*> sTmp = (*iter)->dendriteSegment()->listSynapses();

        for (int i=0; i<sTmp.size(); ++i)
        {
            listSynapsesActiveTimes << sTmp.at(i)->activeTimes();
        }
    }

    // get the sorted list (from small to large)
    qSort(listColumnActiveTimes.begin(), listColumnActiveTimes.end());
    qSort(listSynapsesActiveTimes.begin(), listSynapsesActiveTimes.end());

    int minColumnActiveTimes = 0.01 * (*(listColumnActiveTimes.end()-1));
    int minSynapseActiveTimes = 0.01 * (*(listSynapsesActiveTimes.end()-1));

    // traverse all the columns and synapses,  update their params
    for (iter=listCols.begin(); iter!=listCols.end(); ++iter)
    {
            // need a boost function to update boost
        (*iter)->setBoost(HtmGlobal::boostFunc((*iter)->activeTimes(), minColumnActiveTimes));

        QList<Synapse*> sTmp = (*iter)->dendriteSegment()->listSynapses();

        for (int i=0; i<sTmp.size(); ++i)
        {
            if (sTmp.at(i)->activeTimes() < minSynapseActiveTimes)
            {
                sTmp.at(i)->incPerm();
            }
        }
    }



}

void Watcher::init()
{
    // build columns as default
    m_layer1->buildColumns();

    //need to give an input array
//    m_layer1->fillInputs(blabla);

    // connect elements of columns
    m_layer1->connectElements();

}

bool Watcher::start()
{
    // set the input to start the whole thing

    return true;
}

