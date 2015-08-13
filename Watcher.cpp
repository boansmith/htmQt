#include "Watcher.h"
#include "Organiser.h"

Watcher::Watcher(QObject *parent) : QObject(parent)
{
    m_layer1 = new Organiser;
}

void Watcher::getActiveColumns()
{

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
}

