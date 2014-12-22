#include "delegate.h"


Delegate_validation::Delegate_validation(QObject *parent) :
    QItemDelegate(parent)
{
}

//QWidget *Delegate_validation::createEditor(QObject *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    QSpinBox* editor = new QSpinBox(parent);
//    editor->setMinimum(1);
//    editor->setMaximum(100);

//    return editor;
//}
