#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

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
    void on_pushButton_Done_clicked();

    void on_pushButton_Done_2_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_pushButton_Done_3_clicked();

    void on_pushButton_Done_4_clicked();

    void on_pushButton_Done_Puz_clicked();

    void on_pushButton_Remove_Same_clicked();

    void on_pushButton_Done_Quicksort_clicked();

    void QuickSort(int *Arr,int Left,int Right);

    void on_pushButton_Find_Sort_clicked();

    void on_pushButton_Import_clicked();

    void on_pushButton_Export_clicked();

    void on_pushButton_Size_clicked();

    void on_pushButton_Import_2_clicked();

    void on_pushButton_Export_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
;
