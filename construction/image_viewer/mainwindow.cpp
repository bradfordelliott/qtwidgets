#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QTimer>
#include <qmath.h>
#include <QGraphicsSceneMouseEvent>

QGraphicsScene* scene;
QTimer* timer;

class myItem : public QGraphicsItem
{
public:

    void setPixmap(QPixmap& pixmap)
    {
        pressed = false;
        this->pixmap = pixmap;
    }
    void setFullPixmap(QPixmap& pixmap)
    {
        pressed = false;
        this->full_pixmap = pixmap;
    }

    QRectF boundingRect() const
    {
        int x = this->x();
        int y = this->y();
        int width = this->pixmap.width();
        int height = this->pixmap.height();

        if(pressed)
        {
        x = 0;
        y = 0;
        width = this->full_pixmap.width();
        height = this->full_pixmap.height();
        }

        return QRectF(x,y,width,height);
    }

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget)
    {
        QRectF rect = boundingRect();

        if(pressed)
        {
            painter->drawPixmap(rect.toRect(),full_pixmap);
        }
        else
        {
            painter->drawPixmap(rect.toRect(),pixmap);
        }

        /*if(Pressed)
        { QPen pen(Qt::red, 3);
            painter->setPen(pen);
            painter->drawEllipse(rect);
        }
        else
        {
            QPen pen(Qt::black, 3);
            painter->setPen(pen);
            painter->drawRect(rect);
        }*/
    }

protected:
    bool pressed;

    void mousePressEvent(QGraphicsSceneMouseEvent* event)
    {
        QString data = this->data(Qt::UserRole).toString();
        pressed = true;
        qDebug() << "Clicking object " << data;
        update();
        QGraphicsItem::mousePressEvent(event);

        // To make sure the release event is called
        event->accept();
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        pressed = false;
        qDebug() << "Calling mouse release event";
        update();
        QGraphicsItem::mouseReleaseEvent(event);
    }

private:
    QPixmap pixmap;
    QPixmap full_pixmap;

};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this->ui->graphicsView);
    this->ui->graphicsView->setScene(scene);

    timer = new QTimer(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_show_clicked()
{
    scene->clear();
    QStringList images;
    images.append("M:\\gallery\\best\\ah007.jpg");
    images.append("M:\\gallery\\best\\bb012.jpg");
    images.append("M:\\gallery\\best\\ac004.jpg");
    images.append("M:\\gallery\\best\\l027.jpg");
    images.append("M:\\gallery\\best\\l057.jpg");
    images.append("M:\\gallery\\best\\l056.jpg");


    int count = images.count();
    int total_width = this->ui->graphicsView->width();
    int total_height = this->ui->graphicsView->height();

    int scaled_width = total_width/count;
    qDebug() << "Image count: " << count;
    qDebug() << "total.width: " << total_width;
    qDebug() << "scaled.width:" << scaled_width;

    int x = 0;
    int y = 0;
    int num_rows = qSqrt(count);
    int num_cols = count / num_rows;

    qDebug() << "num.rows: " << num_rows;
    int row_height = total_height/(1.0*num_rows);
    qDebug() << "row.height: " << row_height;

    int col_index = 0;

    for(int i = 0; i < images.count(); i++)
    {
        QPixmap pixmap;
        pixmap.load(images.at(i));
        int height = pixmap.height();
        int width  = pixmap.width();

        // First scale to fit the row
        width = width * row_height/(1.0*height);
        height = row_height;

        // Now make the image proportional
        int scaled_height = (height) * (scaled_width/(1.0*width));

        qDebug() << "scaled.height: " << scaled_height;
        qDebug() << "x: " << x;
        qDebug() << "y: " << y;
        QPixmap scaled = pixmap.scaled(scaled_width, scaled_height);
        //QGraphicsPixmapItem* item = scene->addPixmap(scaled);
        //scene->addPixmap(scaled);
        myItem* item = new myItem();
        item->setX(x);
        item->setY(y);
        item->setPixmap(scaled);
        item->setFullPixmap(pixmap);

        scene->addItem(item);
        item->setData(Qt::UserRole, images.at(i));

        //item->setX(x);
        //item->setY(y);
        x += scaled_width;

        col_index += 1;

        if(col_index >= num_cols)
        {
            y += row_height;
            x = 0;
            col_index = 0;
        }
    }
}
