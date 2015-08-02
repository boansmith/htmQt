#ifndef ORGANISER_H
#define ORGANISER_H

#include <QObject>
#include <QList>


class Column;
class InputElement;


/**
 * @brief The Organiser class
 * 组织者
 * 用于将各个部件组装在一起，并记录组装的方式
 * 各个部件在这里生成
 * 每一层， 只要处理好自己看到的事情就好。
 * 每一层做好自己的事情，则整个系统自然能很好的工作
 */

class Organiser : public QObject
{
    Q_OBJECT
public:
    explicit Organiser(QObject *parent = 0);

    // process binary inputs
    void fillInputs(const char* data);

    // not only build columns, but also build what inside it.
    void buildColumns();
    void buildColumns(int nWidth, int nHeight);

    // connect various elements
    bool connectElements();

    // start to process
    bool start();

    // for Watcher
    QList<Column *> listColumns() const;

signals:

public slots:

private:

    // various resources stored here,
    // it's definitely a pool
    // mainly used for rebuilding from JSON
    // Through every elemnt's ### ID ###(need an protocol) to tell which PARENT they belong to.
    QList<InputElement*>    m_listInputs;
    QList<Column*>          m_listColumns;
};

#endif // ORGANISER_H
