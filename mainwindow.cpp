#include "mainwindow.h"
#include "ui_mainwindow.h"


const int MIN_NUMBER_OF_VERTICES = 3;
const int MAX_NUMBER_OF_VERTICES = 1000;
const int MIN_LENGTH_OF_PATH = 1;
const int MAX_LENGTH_OF_PATH = 100;

bool FIRST_USE_OF_SPINBOX = true;  // variable, which I have to use in spinbox (in other case program was crashed)

// usefull functions

// return random number from a specific range
int get_random_number(const int& low, const int& high)
{
    return qrand() % ((high + 1) - low) + low;
}


// this function is only use to put to each cell the same number
void fill_cities_with_number(QStandardItemModel* city_data, const int& number)
{
    // it doesn't matter what I take, because number of rows == number of columns
    int size = city_data->rowCount();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            QModelIndex index = city_data->index(i, j, QModelIndex());
            city_data->setData(index, number);
        }
    }
}

// TO DO (doesn't work)
void fill_new_rows_and_columns_with_zeros(QStandardItemModel* city_data, const int& size)
{
    int first_index = city_data->rowCount() + 1;
    int last_index = size - 1;

    int size_change = abs(city_data->rowCount() - size);

    //while (first_index != last_index) {

        for (int j = 0; j < size; ++j) {


             QModelIndex index = city_data->index(first_index, j, QModelIndex());
             city_data->setData(index, 0);

        }

      //  last_index--;
   //}


}

// slow for 1 000 of cells
void fill_cities_with_randoms(QStandardItemModel* city_data, const int& low, const int& high)
{
    // it doesn't matter what I take, because number of rows == number of columns
    int size = city_data->rowCount();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {

            QModelIndex index = city_data->index(i, j, QModelIndex());
            city_data->setData(index, get_random_number(low, high));
        }
    }
}




void change_number_of_cities(QStandardItemModel* city_data, const int& new_size)
{

    // it doesn't matter what I take, because number of rows == number of columns
    int old_size = city_data->rowCount();


    int size_change=abs(city_data->rowCount() - new_size);


    if (new_size > old_size)   // increase number of cities
    {
        city_data->insertRows(city_data->rowCount(), size_change);
        city_data->insertColumns(city_data->columnCount(), size_change);

    }else if(new_size < old_size)  // decrease number of cities
    {
        city_data->removeRows(new_size, size_change);
        city_data->removeColumns(new_size, size_change);
    }

}


void save(const QString& name_of_file, const QStandardItemModel* data_to_save)
{
    QFile file(name_of_file);

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream output(&file);

        int size = data_to_save->rowCount();

        // I haven't got smarter idea, but it's working
        for (int i = 0; i < size; ++i) {

            for (int j = 0; j < size; ++j) {

               output << data_to_save->item(i,j)->text();
               output << " ";
            }

            output << "\n";
       }

    }
    else    // when we can't open file for writing
    {
       return;
    }

    file.close();
}


// TO DO
void load(const QString& name_of_file, QStandardItemModel* receiver)
{
    QFile file(name_of_file);

    if(file.open(QIODevice::ReadOnly))
    {
       // TO DO
    }
    else    // when we can't open file for saving
    {
       return;
    }

    file.close();
}



// ################################################################




// constructor end destructor

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    // set default and min / max values
    ui->spinBox_number_of_vertices->setRange(3, MAX_NUMBER_OF_VERTICES);

    // create model to store length of paths beetwen cities
    city_data = new QStandardItemModel(MIN_NUMBER_OF_VERTICES, MIN_NUMBER_OF_VERTICES, this);   // default size

    fill_cities_with_number(city_data, 0); // default value zero
    ui->tableView_task->setModel(city_data);    // connect data with model view


    // set the random number generator
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());




}



MainWindow::~MainWindow()
{
    delete ui;
    delete city_data;   // probably it isn't necessary because Qt do it
}

// ################################################################



// menubar

void MainWindow::on_actionAbout_EzTSPSolver_triggered()
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

    if (!name_of_file.isNull())  // protect when client click cancel
    {
        save(name_of_file, city_data);
    }

}

void MainWindow::on_actionSolution_triggered()
{
    QString name_of_file = QFileDialog::getSaveFileName(this, tr("Save output"), "Output", tr("Text files (*.txt);; Input files (*.io)"));

    if (!name_of_file.isNull())  // protect when client click cancel
    {
       load(name_of_file, city_data);
    }
}


void MainWindow::on_actionSolution_and_task_triggered()
{
    QString name_of_file = QFileDialog::getSaveFileName(this, tr("Save input and output"), "Input_and_Output", tr("Text files (*.txt);; Input files (*.io)"));

    if (!name_of_file.isNull())  // protect when client click cancel
    {
        // function to take carry of file
    }

}

void MainWindow::on_actionLoad_triggered()
{
    QString name_of_file = QFileDialog::getOpenFileName(this, tr("Open file"), "Input", tr("All files (*.txt *.io);; Text files (*.txt);; Input files (*.io)"));

    if (!name_of_file.isNull())  // protect when client click cancel
    {
        // function to take carry of file
    }
}



// ##########################################################


// combobox
void MainWindow::on_comboBox_alghoritm_currentIndexChanged(const QString &arg1)
{

}

// ##########################################################


// spinbox
void MainWindow::on_spinBox_number_of_vertices_valueChanged(int arg1)
{


    if (!FIRST_USE_OF_SPINBOX) // without this condition program crashed
    {
    change_number_of_cities(city_data, arg1);
    fill_new_rows_and_columns_with_zeros(city_data, arg1);
    }



    FIRST_USE_OF_SPINBOX = false;  // set false, because we use this function after launch the program


}

// ##########################################################


// buttons

void MainWindow::on_pushButton_random_clicked()
{
    fill_cities_with_randoms(city_data, MIN_LENGTH_OF_PATH, MAX_LENGTH_OF_PATH);
}



void MainWindow::on_pushButton_solve_clicked()
{

}


