#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qprocess>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QObject::connect(this->ui->FileChooseBtn, SIGNAL(clicked()), this, SLOT(on_FileChooseBtn_clicked()));
    //QObject::connect(this->ui->CompressPosBtn, SIGNAL(clicked()), this, SLOT(on_CompressPosBtn_clicked()));
    //QObject::connect(this->ui->StartCompressBtn, SIGNAL(clicked()), this, SLOT(on_StartCompressBtn_clicked()));

}


MainWindow::~MainWindow()
{
     process.close();
    delete ui;
}

void MainWindow::on_FileChooseBtn_clicked()
{
    FilePos = QFileDialog::getOpenFileName(this,
                                                       tr("选择需要压缩的文件"),
                                                       ".");
    this->ui->FileChooseText->setPlainText(FilePos);
//     qDebug()<<"filename : "<<fileName;
}

void MainWindow::on_CompressPosBtn_clicked()
{
    CompressPos = QFileDialog::getExistingDirectory (this,
                                                       tr("解压至") );
    this->ui->CompressPosText->setPlainText(CompressPos);
//     qDebug()<<"filename : "<<fileName;
}

void MainWindow::on_StartCompressBtn_clicked()
{
    FilePos = this->ui->FileChooseText->toPlainText();
    CompressPos = this->ui->CompressPosText->toPlainText();
    if(FilePos.isEmpty())
    {
        OpenMessageBox("请选择文件！");
        return;
    }
    if(CompressPos.isEmpty())
    {
        OpenMessageBox("请选择解压位置！");
        return;
    }
    process.start("D://CompressExperiment//CompressExperiment//hello.exe", {FilePos,CompressPos});
}

void MainWindow::OpenMessageBox(QString s)
{
    QMessageBox msg(this);
    msg.setWindowTitle("提示");
    msg.setText(s);
    msg.setIcon(QMessageBox::Warning);
    msg.setStandardButtons(QMessageBox::Ok);

    if(msg.exec() == QMessageBox::Ok)
    {
       msg.close();
    }
}
