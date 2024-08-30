#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //没有右击转到槽，只能connect连接信号与槽
    connect(ui->newAction, &QAction::triggered, this, &MainWindow::newActionSlot);
    connect(ui->openAction, &QAction::triggered, this, &MainWindow::openActionSlot);
    connect(ui->saveAction, &QAction::triggered, this, &MainWindow::saveActionSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::newActionSlot()
{
    ui->textEdit->clear();
    this->setWindowTitle("新建文本文档.txt");
}

void MainWindow::openActionSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择一个文件",
                QCoreApplication::applicationFilePath(), "*.cpp"); // 打开窗口,Application能知道窗口在哪个位置，由哪个窗口接收消息
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "警告", "请选择一个文件");
    } else {
        // qDebug() << filename;
        QFile file(fileName); // 创建文件对象
        file.open(QIODevice::ReadOnly);
        QByteArray ba = file.readAll();
        ui->textEdit->setText(QString(ba));
        file.close();
    }
}

void MainWindow::saveActionSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this, "请选择一个文件",
                QCoreApplication::applicationFilePath());
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "警告", "请选择一个文件");
    } else {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QByteArray ba;
        ba.append(ui->textEdit->toPlainText().toUtf8()); //.toUtf8()解决.append()问题
        file.write(ba);
        file.close();
    }
}

// 键盘快捷键->事件QEvent 键盘事件,鼠标事件,拖放时间等等
// 任意的QObject对象都能处理QT事件能力
// bool event(QEvent *event)
// bool MyWidget::event(QEvent *event)
// {
//     if(event->type() == QEvent::MouseButtonPress)
//     {
//         qDebug() << "mouse press.";
//     }
//     return QWidget::event(event);
// }

void MainWindow::keyPressEvent(QKeyEvent *k) // 键盘事件,通过宏来完成,未能重写虚函数,可能是因为开头大写字母有影响
{
    if (k->modifiers() == Qt::ControlModifier && k->key() == Qt::Key_S) {
        saveActionSlot();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *m) // 鼠标事件
{
    QPoint pt = m->pos();
    qDebug() << pt;

    if (m->button() == Qt::LeftButton) {
        qDebug() << "左键被按下";
    } else if (m->button() == Qt::RightButton)  {
        qDebug() << "右键被按下";
    }
}
