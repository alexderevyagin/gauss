#include "gauss.h"
#include "ui_gauss.h"

Gauss::Gauss(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gauss)
{
    ui->setupUi(this);
}

Gauss::~Gauss()
{
    delete ui;
}
void Gauss::calculateGauss(){ //Процедура преобразования данных из TableView в массив типа Float
    int n=csvModel->rowCount(); //и дальнейший рассчет Методом Гаусса c выводом в TextBrowser
    int m=csvModel->columnCount();
    int i=0;
    int j=0;
    float  tmp;
    int k;
    float *xx = new float [m];
    float **matrix = new float *[n];
    for (i = 0; i<n; i++)
        matrix[i] = new float[m];
    for (i = 0; i<n; i++)
        for (j = 0; j<m; j++)
            matrix[i][j]=csvModel->item(i,j)->text().toFloat();
    ui->statusBar->showMessage("Рассчет начат");

    for (i = 0; i<n; i++) //Прямой ход, приведение к треугольному виду
    {
        tmp = matrix[i][i];
        for (j = n; j >= i; j--)
            matrix[i][j] /= tmp;
        for (j = i + 1; j<n; j++)
        {
            tmp = matrix[j][i];
            for (k = n; k >= i; k--)
                matrix[j][k] -= tmp*matrix[i][k];
        }
    }
    xx[n - 1] = matrix[n - 1][n]; //обратный ход
    for (i = n - 2; i >= 0; i--)
    {
        xx[i] = matrix[i][n];
        for (j = i + 1; j<n; j++) xx[i] -= matrix[i][j] * xx[j];
    }
    ui->statusBar->showMessage("Рассчет завершен");
    for (i = 0; i<n; i++) //Вывод решений
        ui->textBrowser->append(QString("x%1 = %2").arg(i).arg(xx[i]));
    delete[] matrix;
}
void Gauss::readCSV(QString filename){ //Процедура парсинга CSV файла и заполнения TableView
    QStringList matrixStr;             //значениями из него
    int n=0;
    int m=0;
    int i,j;
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    while (!in.atEnd()){
        QString line=in.readLine();
        if (!line.isNull()){
            n++;
            matrixStr.append(line);
        }
    }
    file.close();
    ui->statusBar->showMessage("Файл считан");
    m=n+1;
    QString lineStr;
    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(m);
    ui->tableView->setModel(csvModel);
    for (i = 0; i<n; i++){
        lineStr=matrixStr.at(i);
        QList<QStandardItem *> standardItemsList;
        for (j = 0; j<m; j++){
            QString item=lineStr.split(",").at(j);
            standardItemsList.append(new QStandardItem(item));}
        csvModel->insertRow(csvModel->rowCount(), standardItemsList);
    }
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->statusBar->showMessage("Готов к рассчету");
}
void Gauss::on_LoadButton_clicked() //Обработчик клика по кнопке "Загрузить матрицу из файла"
{
    QString filename=QFileDialog::getOpenFileName(this,"Выберите файл",".",("*.csv"),0,0);
    if (!filename.isNull())
        readCSV(filename);
}

void Gauss::on_CalculateButton_clicked() //Обработчик клика по кнопке "Рассчитать"
{
    calculateGauss();
}
