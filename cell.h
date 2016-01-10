#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QVariantList>

/**
 *  对于一个 细胞  的描述
 *  先准备好需要的元素， 然后进行对这些元素的操作， 定义这些元素之间的关系
 *  一个细胞应该有的状态： 1. active 2.predictive 3.gray(not active and not predictive)
 *  一个细胞应该有的行为:  1. 通过dendriteSegment搜集周围的细胞的active状态，以便使自己处于predictive
 *                       2. 当自己处于active状态时，告知周围的细胞（发射信号给其它细胞的 dendriteSegment, 通过synapse）
 *                          to make other cells be predictive
 */


class DendriteSegment;
class Synapse;

class Cell : public QObject
{
    Q_OBJECT
public:
    explicit Cell(int nId, QObject *parent = 0);

    // dendriteSegments in a cell are used to collect other cell's active state
    // to make THIS cell be predictive
    // when fill, connect them BTW
    void fillDendriteSegments(DendriteSegment* d);

    // synapses in a cell are used to send THIS cell's active state to other cells' dendriteSegments
    // to notify other cells
    // when fill, connect them BTW
    void fillSynapses(Synapse* s);

    // reset THIS cell's states
    void resetButPredictive();
    void resetAll();

    // id of this cell
    int id();


signals:
    // when THIS cell becomes active, an activated signal should be sent
    void activated();

    // when THIS cell becomes predicted, a predicted signal should be sent
    void predicted();

public slots:
    // do sth when receive the dendriteSegments' output
    void onRecvSegmentActivated();

private:

    /*
     * 由此cell发出去的 dendrite segment, 作用为搜集其它细胞的active状态， 以便使自己成为 predictive
     * dendrite segment 直接与其它细胞通过synapse进行连接
     * dendrite segment includes synapses
     * But how to choose the cell to connect？
     * should follow the rules below,maybe:
     * the immediately prior active cell should "PREDICT" the cell which is active now
    */
    QList<DendriteSegment*> m_listDendriteSegment;

    // synapses for sending signal
    QList<Synapse*> m_listSynapses;


public:
    void setActive(bool b);
    void setPredictive(bool b);
    void setChosen(bool b);
    void setLearning(bool b);

    bool isActive();
    bool isPredictive();
    bool isChosen();
    bool isLearning();
    // to tell if the cell WAS active the immediately prior
    // if the cell WAS active, after get the status, set it to false
    // i.e. the "wasActive" should be only used for once
    bool wasActive();

private:

    bool m_bWasActive;
    bool m_bIsActive;
    bool m_bIsPredictive;

    bool m_bIsChosen;
    bool m_bIsLearning;

    int m_nId;
};

#endif // CELL_H
