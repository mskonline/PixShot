#ifndef UNDOACTION_H
#define UNDOACTION_H

class UndoAction
{
    public:
        UndoAction();
        int action;
        QGraphicsItem *item;

        QVariant vt;
};

#endif // UNDOACTION_H
