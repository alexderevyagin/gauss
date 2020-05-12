#ifndef GAUSS_H
#define GAUSS_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QStandardItem>
namespace Ui {
class Gauss;
}

class Gauss : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gauss(QWidget *parent = 0);
    ~Gauss();
    void readCSV(QString filename);
    void calculateGauss();
    QStandardItemModel *csvModel;
private slots:
    void on_LoadButton_clicked();

    void on_CalculateButton_clicked();

private:
    Ui::Gauss *ui;
};

#endif // GAUSS_H
