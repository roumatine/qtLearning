#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    picId = 2;

    QPixmap pix("D:\\record\\qt_pr0ject\\day2\\time\\objectTimer\\pic\\flow.PNG");
    ui->label->setPixmap(pix);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startButton_clicked()
{
    //开启定时器，返回定时器编号
    myTimerId = this->startTimer(TIMEOUT);
}

void Widget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != myTimerId) {
        return;
    }

    QString path("D:\\record\\qt_pr0ject\\day2\\time\\objectTimer\\pic");
    path += QString::number(picId);
    path += ".PNG";

    QPixmap pix(path);
    ui->label->setPixmap(pix);

    picId ++;
    if (picId == 6) {
        picId = 1;
    }
}


void Widget::on_stopButton_clicked()
{
    this->killTimer(myTimerId);
}

