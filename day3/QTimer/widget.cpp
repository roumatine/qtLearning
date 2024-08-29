#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    timer = new QTimer;
    picId = 2;

    //显示图片
    QImage img;
    img.load("D:\\record\\qt_pr0ject\\day3\\QTimer\\pic\\1.jpg");
    ui->label->setPixmap(QPixmap::fromImage(img));

    //定时器时间到，发出timeout信号
    connect(timer, &QTimer::timeout, this, &Widget::timeoutSlot);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startButton_clicked()
{
    timer->start(TIMEOUT);
}

void Widget::timeoutSlot(){
    QString path("D:\\record\\qt_pr0ject\\day3\\QTimer\\pic\\");
    path += QString::number(picId);
    path += ".jpg";

    QImage img;
    img.load(path);
    ui->label->setPixmap(QPixmap::fromImage(img));

    picId ++;
    if (5 == picId) {
        picId = 1;
    }
}

void Widget::on_stopButton_clicked()
{
    timer->stop();
}


void Widget::on_singleButton_clicked()
{
    QTimer::singleShot(TIMEOUT, this, SLOT(timeoutSlot()));
}

