#ifndef COLUMN_H
#define COLUMN_H

#include <QObject>
#include <QVariantList>

class Cell;
class DendriteSegment;

class Column : public QObject
{
    Q_OBJECT
public:
    explicit Column(int nId, QObject *parent = 0);
    ~Column(){}

    void fillCell(Cell* cell);
    void setDendriteSegment(DendriteSegment* d);
    DendriteSegment* dendriteSegment();

    void connectDendriteSegment();

    void setActive();


signals:

public slots:
    // 对收到 proximal dendrite segment的信号的处理，当然这种信号都是 activated signal
    void onRecv(int overlap);

public:
    int id();
    int overlap();

    int activeTimes() const;

    float boost() const;

    // for Watcher, set the boost of this column
    void setBoost(float fBoost);

private:
    int m_nId;

    // 一般一个Column包含4个cell
    QList<Cell*> m_listCell;    // <Cell*>

    // 一个Column包含一个dendrite segment (proximal)
    DendriteSegment* m_dendriteSegment;

    int m_nOverlap;

    // activated times
    int m_nActiveTimes;

    // boost
    float m_fBoost;

};

#endif // COLUMN_H
