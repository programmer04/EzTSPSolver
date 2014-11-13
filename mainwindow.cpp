#include "mainwindow.h"
#include "ui_mainwindow.h"




// private functions

// return random number from a specific range
int MainWindow::get_random_number(const int& low, const int& high)
{
    return qrand() % ((high + 1) - low) + low;
}


// disable edititing cell in QStandardItemModel (QTableView)
void MainWindow::disable_editing_item(QStandardItem* item)
{
    Qt::ItemFlags flags = item->flags();
    flags &= ~Qt::ItemIsEditable;   // putting mask (with nagation) on flags
    item->setFlags(flags);
}



void MainWindow::fill_new_rows_and_columns_with_zeros(QStandardItemModel* city_data, const int& old_size)
{

   int desired_size = city_data->rowCount();    // actual size of QStandardItemModel


    for(int row = 0; row < desired_size; ++row)
    {
        for (int column = 0; column < desired_size; ++column)

            if(!(row < old_size && column < old_size)){

             QModelIndex index = city_data->index(row, column, QModelIndex());
             city_data->setData(index, 0);

             if (column == row) // if on diagonal
                 disable_editing_item(city_data->itemFromIndex(index)); // disable editing diagonal

            }

    }



}


// slow for 1 000 of cells
void MainWindow::fill_cities_with_randoms(QStandardItemModel* city_data, const int& low, const int& high)
{
    // it doesn't matter what I take, because number of rows == number of columns
    int size = city_data->rowCount();

    for (int i = 0; i < size; ++i) {

        for (int j = 0; j < size; ++j) {


            QModelIndex index = city_data->index(i, j, QModelIndex());


            if (i == j) // if on diagonal
            {
               continue;    // because we've already zeros
            }


            city_data->setData(index, get_random_number(low, high));    // put randoms

        }
    }
}


void MainWindow::change_number_of_cities(QStandardItemModel* city_data, const int& new_size)
{

    // it doesn't matter what I take, because number of rows == number of columns
    int old_size = city_data->rowCount();


    int size_change = abs(old_size - new_size);


    if (new_size > old_size)   // increase number of cities
    {
        city_data->insertRows(old_size, size_change);
        city_data->insertColumns(old_size, size_change);

    }else if(new_size < old_size)  // decrease number of cities
    {
        city_data->removeRows(new_size, size_change);
        city_data->removeColumns(new_size, size_change);
    }

}


void MainWindow::save(const QString& name_of_file, const QStandardItemModel* data_to_save)
{
    QFile file(name_of_file);

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream output(&file);

        int size = data_to_save->rowCount();

        output << QString::number(size) << "\n";    // number of vertices

        //  graph's adjacency matrix
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
void MainWindow::load(const QString& name_of_file, QStandardItemModel* receiver)
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

    // create model to store length of paths beetwen cities
    tableModel = new QStandardItemModel(MIN_NUMBER_OF_VERTICES, MIN_NUMBER_OF_VERTICES, this);   // default size
    fill_new_rows_and_columns_with_zeros(tableModel, 0);    // fill new model with default value of zero


    // set the random number generator
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());


    // setings properties of ui
    ui->setupUi(this);
    ui->spinBox_number_of_vertices->setRange(MIN_NUMBER_OF_VERTICES, MAX_NUMBER_OF_VERTICES);    // set default and min/max values
    ui->tableView->setModel(tableModel);    // connect data with ModelView
    graph=new Graph(this);
    connect(tableModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),graph,SLOT(edgeWeightChanged(QModelIndex,QModelIndex)));
//    connect()
}



MainWindow::~MainWindow()
{
    delete ui;
    // delete city_data;   // probably it isn't necessary because Qt do it with deleting ui
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
        save(name_of_file, tableModel);
    }

}

void MainWindow::on_actionSolution_triggered()
{
    QString name_of_file = QFileDialog::getSaveFileName(this, tr("Save output"), "Output", tr("Text files (*.txt);; Input files (*.io)"));

    if (!name_of_file.isNull())  // protect when client click cancel
    {
       load(name_of_file, tableModel);
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
/*  change immediatelly
void MainWindow::on_spinBox_number_of_vertices_valueChanged(int arg1)
{

    int old_size = city_data->rowCount();

    change_number_of_cities(city_data, arg1);
    fill_new_rows_and_columns_with_zeros(city_data, old_size);

}
*/

// ##########################################################


// buttons

void MainWindow::on_pushButton_random_clicked()
{
    fill_cities_with_randoms(tableModel, MIN_LENGTH_OF_PATH, MAX_LENGTH_OF_PATH);
}



void MainWindow::on_pushButton_solve_clicked()
{

}

// spinbox
// you have to accept changes by pressing enter (avoid bug when decrease fill with randoms tab from 100 to 50)
// in other case it's change to size five and next to 50 so you have zeros in some rows and columns
void MainWindow::on_spinBox_number_of_vertices_editingFinished()
{
    int old_size = tableModel->rowCount();

    int new_size = ui->spinBox_number_of_vertices->value();

    change_number_of_cities(tableModel, new_size);
    fill_new_rows_and_columns_with_zeros(tableModel, old_size);
}
