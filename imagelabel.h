// imagelabel.h
#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>

class ImageLabel : public QLabel
{
    Q_OBJECT

public:
    ImageLabel(const QPixmap& pixmap, const QPoint& position, const QString& imageId, QWidget* parent = nullptr);

    QString getImageId() const { return imageId; }

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    QString imageId;
};

#endif // IMAGELABEL_H
