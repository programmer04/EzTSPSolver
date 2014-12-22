#ifndef DELEGATE_H
#define DELEGATE_H


#include <QSpinBox>
#include <QItemDelegate>

class Delegate_validation : public QItemDelegate
{
    Q_OBJECT
public:
    explicit Delegate_validation(QObject *parent = 0);

//    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;






signals:

public slots:

};

#endif // DELEGATE_H
