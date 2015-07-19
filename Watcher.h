#ifndef WATCHER_H
#define WATCHER_H

#include <QObject>
#include <QList>

class Column;

/**
 * @brief The Watcher class
 * 观察者， 巡查者
 * 对组织者生成并组装形成的结构的运行情况进行监督
 * 以调整各个部件的参数，完成学习的功能
 */

class Watcher : public QObject
{
    Q_OBJECT
public:
    explicit Watcher(QObject *parent = 0);

    void getActiveColumns();

signals:

public slots:

private:
    QList<Column*> m_listActiveColumns;
};

#endif // WATCHER_H
