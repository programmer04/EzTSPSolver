#include "mainwindow.h"
#include "ui_mainwindow.h"


const int MIN_NUMBER_OF_VERTICES = 3;
const int MAX_NUMBER_OF_VERTICES = 1000;
const int NUMBER_OF_LETTERS_IN_VERTICES = 8;




// usefull functions

// this function is only use to create plain new model in a constructor of mainwindow
void fill_cities_with_zeros(QStandardItemModel* model, const int& size)
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            QModelIndex index = model->index(i, j, QModelIndex());
            model->setData(index, 0);
        }
    }
}

void change_number_of_cities(QStandardItemModel* city_data, const int& size)
{

    // increase numbe of cities
    while (size > city_data->rowCount())   // it doesn't matter what I take, because number of rows == number of columns
    {
        city_data->insertRow(city_data->rowCount());
        city_data->insertColumn(city_data->columnCount());
    }


    while (size < city_data->rowCount())   // it doesn;t matter what I take number of rows == number of columns
    {
        city_data->removeRow(city_data->rowCount()-1);
        city_data->removeColumn(city_data->columnCount()-1);
    }


}


// ################################################################




// constructor end destructor

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create numbers of vertices in combo box
    for (int i = MIN_NUMBER_OF_VERTICES; i <= MAX_NUMBER_OF_VERTICES; ++i) {

        ui->comboBox_nuber_of_vertices->addItem(QString::number(i) + " vertices");

    }

    // create model to store length of paths beetwen cities
    city_data = new QStandardItemModel(MIN_NUMBER_OF_VERTICES, MIN_NUMBER_OF_VERTICES, this);
    fill_cities_with_zeros(city_data, MIN_NUMBER_OF_VERTICES);  // default value
    ui->tableView_task->setModel(city_data);





}



MainWindow::~MainWindow()
{
    delete ui;
}

// ################################################################



// slots, which take care of menubar

void MainWindow::on_actionAbout_EzTSPSolver_2_triggered()
{

    QMessageBox::information(this,"About EzTSPSolver ", "Version:\nRelease date:\nAuthors:\nLicencion:\n");
}


void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::on_actionSettings_triggered()
{

}


// save and load
void MainWindow::on_actionTask_triggered()
{
    QString name_of_file = QFileDialog::getSaveFileName(this, tr("Save input"), "Input", tr("Text files (*.txt);; Input files (*.io)"));
    ui->description_1->setText(name_of_file);

    if (!name_of_file.isNull())  // protect when client click cancel
    {
        // function to take carry of file
    }

}

void MainWindow::on_actionSolution_triggered()
{
    QString name_of_file = QFileDialog::getSaveFileName(this, tr("Save output"), "Output", tr("Text files (*.txt);; Input files (*.io)"));

    if (!name_of_file.isNull())  // protection in situation when client click cancel
    {
        // function to takecarry of file
    }
}


void MainWindow::on_actionSolution_and_task_triggered()
{
    QString name_of_file = QFileDialog::getSaveFileName(this, tr("Save input and output"), "Input_and_Output", tr("Text files (*.txt);; Input files (*.io)"));

    if (!name_of_file.isNull())  // protection in situation when client click cancel
    {
        // function to take carry of file
    }

}

void MainWindow::on_actionLoad_triggered()
{
    QString name_of_file = QFileDialog::getOpenFileName(this, tr("Open file"), "Input", tr("All files (*.txt *.io);; Text files (*.txt);; Input files (*.io)"));

    if (!name_of_file.isNull())  // protection in situation when client click cancel
    {
        // function to take carry of file
    }
}



// ##########################################################


// comboboxes

void MainWindow::on_comboBox_nuber_of_vertices_currentIndexChanged(const QString &arg1)
{
    // extract number of rows and column
    QString number_of_vertices = arg1;
    number_of_vertices.chop(NUMBER_OF_LETTERS_IN_VERTICES); // after this only number stay in string
    int size = number_of_vertices.toInt();


    //change size of TABLEVIEW
    /*
    city_data = new QStandardItemModel(size, size, this);
    fill_cities_with_zeros(city_data, size);
    ui->tableView_task->setModel(city_data);
    */
    if(size != MIN_NUMBER_OF_VERTICES)  // when I haven't this condition program was crashed
    {
        change_number_of_cities(city_data, size);   // only work for increase



    }

}


void MainWindow::on_comboBox_alghoritm_currentIndexChanged(const QString &arg1)
{

}



// ##########################################################


// buttons


void MainWindow::on_pushButton_random_clicked()
{

}



void MainWindow::on_pushButton_solve_clicked()
{

}
