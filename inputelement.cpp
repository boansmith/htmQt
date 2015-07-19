#include "inputelement.h"
#include "synapse.h"

InputElement::InputElement(bool value, QObject *parent) :
    QObject(parent)
{
    m_bValue = value;
}

void InputElement::setValue(bool b)
{
    m_bValue = b;
}

void InputElement::checkValue()
{
    if (m_bValue)
    {
        emit inputValid();
    }
}

void InputElement::fillSynapses(Synapse *s)
{
    m_listSynapses << s;
}


void InputElement::connectSynapses()
{
    Q_ASSERT(!m_listSynapses.empty());

    // disconnect at first, to cover the changes
    QList<Synapse*>::Iterator iter;
    for (iter = m_listSynapses.begin(); iter != m_listSynapses.end(); ++iter)
    {
        disconnect(this, SIGNAL(inputValid()), (*iter), SLOT(onRecv()));
    }

    // then connect
    for (iter = m_listSynapses.begin(); iter != m_listSynapses.end(); ++iter)
    {
        connect(this, SIGNAL(inputValid()), (*iter), SLOT(onRecv()));
    }
}
