#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QFileDialog>

// we are on github, hell yea!!!

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
    void on_actionAbout_EzTSPSolver_2_triggered();

    void on_actionTask_triggered();

    void on_actionSolution_triggered();

    void on_actionSolution_and_task_triggered();

    void on_actionLoad_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionSettings_triggered();

    // ######################################


    // comboboxes
    void on_comboBox_nuber_of_vertices_currentIndexChanged(const QString &arg1);

    void on_comboBox_alghoritm_currentIndexChanged(const QString &arg1);

    // #####################################

    // buttons
    void on_pushButton_random_clicked();

    void on_pushButton_solve_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel* city_data;  // pointer to data for TableView

};

#endif // MAINWINDOW_H
