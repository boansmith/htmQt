#include "Watcher.h"
#include "Organiser.h"
#include "column.h"
#include "globalparams.h"

Watcher::Watcher(QObject *parent) : QObject(parent)
{
    m_layer1 = new Organiser;
}

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
    int thresh = listOverlaps.at(listOverlaps.size()*(1.0-GlobalParams::m_fActiveRatio));


    // fill the activeColums
    for (iter=listCols.begin(); iter!=listCols.end(); ++iter)
    {
        if ((*iter)->overlap() >= thresh)
        {
            m_listActiveColumns << (*iter);
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

