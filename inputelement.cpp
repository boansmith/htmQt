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
    connect(this, SIGNAL(inputValid()), s, SLOT(onRecv()));
}


