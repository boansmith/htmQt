#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QVariantList>

/**
 *  对于一个 细胞  的描述
 *  先准备好需要的元素， 然后进行对这些元素的操作， 定义这些元素之间的关系
 *  一个细胞应该有的状态： 1. active 2.predictive 3.gray
 *  一个细胞应该有的行为:  1. 通过dendriteSegment搜集周围的细胞的active状态，以便使自己处于predictive
 *                       2. 当自己处于active状态时，告知周围的细胞（发射信号给其它细胞的 dendriteSegment）
 */

class DendriteSegment;
class Synapse;

class Cell : public QObject
{
    Q_OBJECT
public:
    explicit Cell(QObject *parent = 0);

    void fillDendriteSegments(DendriteSegment* d);
    void fillSynapses(Synapse* s);

    // to cover the changes, public these functions
    void connectSynapses();
    void connectDendriteSegments();


signals:
    void activated();
    void predicted();

public slots:
    void onRecvSegmentActivated();

private:

    bool m_bIsActive;
    bool m_bIsPredictive;


    /*
     * 由此cell发出去的 dendrite segment, 作用为搜集其它细胞的active状态， 以便使自己成为 predictive
     * dendrite segment 直接与其它细胞通过synapse进行连接
     * dendrite segment 包含 synapses
     * 但是怎样选择要连接的细胞呢？
    */
    QList<DendriteSegment*> m_listDendriteSegment;

    // synapses for sending signal
    QList<Synapse*> m_listSynapses;


public:
    void setActive();

    bool isActive();
    bool isPredictive();

};

#endif // CELL_H
