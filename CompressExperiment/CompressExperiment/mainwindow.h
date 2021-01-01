#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qprocess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QProcess process;
    QString FilePos;
    QString CompressPos;
    void OpenMessageBox(QString s);

public slots:
    void on_StartCompressBtn_clicked();
    void on_FileChooseBtn_clicked();
    void on_CompressPosBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
