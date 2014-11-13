#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QTime>
#include <QTextStream>

#include "graph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    // menubar
    void on_actionAbout_EzTSPSolver_triggered();

    void on_actionTask_triggered();

    void on_actionSolution_triggered();

    void on_actionSolution_and_task_triggered();

    void on_actionLoad_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionSettings_triggered();

    // ######################################


    // combobox
    void on_comboBox_alghoritm_currentIndexChanged(const QString &arg1);
    // #####################################

    // spinbox
   // void on_spinBox_number_of_vertices_valueChanged(int arg1);
    // #####################################



    // buttons
    void on_pushButton_random_clicked();

    void on_pushButton_solve_clicked();



    void on_numOfVerticesSpinBox_editingFinished();

private:

    const int MIN_NUMBER_OF_VERTICES = 3;
    const int MAX_NUMBER_OF_VERTICES = 1000;
    const int MIN_LENGTH_OF_PATH = 1;
    const int MAX_LENGTH_OF_PATH = 100;
    Graph* graph;
    Ui::MainWindow *ui;
    QStandardItemModel* tableModel;  // pointer to data for TableView

    int get_random_number(const int& low, const int& high);

    void disable_editing_item(QStandardItem* item);

    void fill_new_rows_and_columns_with_zeros(QStandardItemModel* tableModel, const int &old_size);

    void fill_cities_with_randoms(QStandardItemModel* tableModel, const int& low, const int& high);

    void change_number_of_cities(QStandardItemModel* tableModel, const int& new_size);

    void save(const QString& name_of_file, const QStandardItemModel* data_to_save);

    void load(const QString& name_of_file, QStandardItemModel* receiver);



};

#endif // MAINWINDOW_H
