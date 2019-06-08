#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtGui>
#include <ctime>

static bool flag_Remove = 0;
static bool flag_Sort = 0;
static bool flag_width = 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Массивы");
    ui->tableWidget->horizontalHeader()->setVisible(true);
    ui->pushButton_Done_3->setVisible(false);
    ui->pushButton_Done_4->setVisible(false);
    ui->pushButton_Remove_Same->setVisible(false);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(0);
    ui->label_Find_Num->setText("");
    ui->pushButton_Find_Sort->setVisible(true);


    ui->textBrowser->setText("");
    ui->textBrowser->append("Номера ячеек:");


    flag_Sort = 0;

    this->window()->setMinimumHeight(110);
    this->window()->setMinimumWidth(290);
    this->window()->setMaximumHeight(110);
    this->window()->setMaximumWidth(290);
}

MainWindow::~MainWindow()
{
    int Count = ui->tableWidget->columnCount();
    for(int i = 0;i < Count;i++)
    {
        ui->tableWidget->item(0,i)->~QTableWidgetItem();
    }
    delete ui;
}

void MainWindow::on_pushButton_Done_clicked()
{
    ui->label_Find_Num->setText("");
    ui->pushButton_Remove_Same->setVisible(false);
    int Count = ui->spinBox_NArr->value();
    int Num = ui->comboBox->currentIndex();
    QString * Str_Rand = new QString;
    srand(time(0));
    ui->tableWidget->setColumnCount(Count);

    if(Count <= 5)
    {
        for(int i = 0;i < Count;i++)
        {
            ui->tableWidget->setColumnWidth(i,610/Count);
        }
    }
    else
    {
        for(int i = 0;i < Count;i++)
        {
            ui->tableWidget->setColumnWidth(i,122);
        }
    }


    switch(Num)
    {
    case 0:
        for(int i = 0;i < Count;i++)
        {

            if(ui->tableWidget->item(0,i) != nullptr)
            {
                ui->tableWidget->item(0,i)->~QTableWidgetItem();
                QTableWidgetItem * item = new QTableWidgetItem;
                item->setText("");
                ui->tableWidget->setItem(0, i, item);
            }
            else
            {
                QTableWidgetItem * item = new QTableWidgetItem;
                item->setText("");
                ui->tableWidget->setItem(0, i, item);
            }
        }
        flag_Sort = 0;
        break;
    case 1:
        for(int i = 0;i < Count;i++)
        {
            if(ui->tableWidget->item(0,i) != nullptr)
            {
                ui->tableWidget->item(0,i)->~QTableWidgetItem();
                QTableWidgetItem * item = new QTableWidgetItem;
                (*Str_Rand).setNum(-100 + rand() % 300);
                item->setText((*Str_Rand));
                ui->tableWidget->setItem(0, i, item);
            }
            else
            {
                QTableWidgetItem * item = new QTableWidgetItem;
                (*Str_Rand).setNum(-100 + rand() % 300);
                item->setText((*Str_Rand));
                ui->tableWidget->setItem(0, i, item);
            }
        }
        flag_Sort = 0;
        break;
    default:
        break;
    }

    delete Str_Rand;
    Str_Rand = nullptr;

    if(!flag_width)
    {
        this->window()->setMinimumHeight(371);
        this->window()->setMinimumWidth(659);
        this->window()->setMaximumHeight(371);
        this->window()->setMaximumWidth(659);
        ui->pushButton_Size->setText(">");
    }
    else
    {
        this->window()->setMinimumHeight(371);
        this->window()->setMinimumWidth(1280);
        this->window()->setMaximumHeight(371);
        this->window()->setMaximumWidth(1280);
        ui->pushButton_Size->setText("<");
    }
    ui->tableWidget->setVisible(true);
    ui->pushButton_Done->setVisible(false);
    ui->spinBox_NArr->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->pushButton_Done_3->setVisible(true);
    ui->pushButton_Done_4->setVisible(true);
}

void MainWindow::on_pushButton_Done_2_clicked()
{
    const int Count = ui->tableWidget->columnCount();
    QString Str, Str_i,Str_Num;
    QString Item;
    int *Arr = new int[Count];

    bool flag_int,flag_r = false;



    ui->label_Max_2->setText("");
    ui->label_Min_2->setText("");
    for(int i = 0;i < Count;i++)
    {
        ui->tableWidget->item(0,i)->setSelected(false);
    }

    for(int i = 0;i < Count;i++)
    {
        Str_i.setNum(i + 1);
        Str = ui->tableWidget->item(0,i)->text();
        Arr[i] = Str.toInt(&flag_int,10);
        if(!flag_int)
        {
            ui->tableWidget->item(0,i)->setSelected(true);
            QMessageBox::information(nullptr,"Ошибка","Содержание ячейки " + Str_i + " не корректно",QMessageBox::Ok);
            if(Count > 5)
            {
                ui->tableWidget->scrollToItem(ui->tableWidget->item(0,i));
            }
            flag_r = 0;
            break;
        }
        else
        {
            ui->label_Error->setText("");
            flag_r = 1;
        }

    }

    if(flag_r == 1)
    {
        if(Count > 1)
        {
            int Prom;
            for(int i = 0; i < Count - 1;i++)
            {
                for(int j = i + 1;j < Count;j++)
                {
                    if(Arr[i] > Arr[j])
                    {
                        Prom = Arr[i];
                        Arr[i] = Arr[j];
                        Arr[j] = Prom;
                    }
                }
            }

            ui->label_Error->setText("");
            ui->label_Max_2->setNum(Arr[Count - 1]);
            ui->label_Min_2->setNum(Arr[0]);


            ui->label_Max->setVisible(true);
            ui->label_Min->setVisible(true);
        }
        else if(Count == 1)
        {
            ui->label_Error->setText("");
            ui->label_Max_2->setNum(Arr[0]);
            ui->label_Min_2->setNum(Arr[0]);
        }
    }
    delete [] Arr;
    Arr = nullptr;
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if(ui->pushButton_Remove_Same->isVisible())
    {
        ui->pushButton_Remove_Same->setVisible(false);
    }
    flag_Sort = 0;
    flag_Remove = 0;
}

void MainWindow::on_pushButton_Done_3_clicked()
{
    int Count = ui->tableWidget->columnCount();
    for(int i = 0;i < Count;i++)
    {
        ui->tableWidget->item(0,i)->~QTableWidgetItem();
    }
    ui->tableWidget->setColumnCount(0);

    ui->tableWidget->setVisible(false);
    ui->pushButton_Done_3->setVisible(false);
    ui->pushButton_Done_4->setVisible(false);

    ui->pushButton_Done->setVisible(true);
    ui->comboBox->setVisible(true);
    ui->spinBox_NArr->setVisible(true);

    this->window()->setMinimumHeight(110);
    this->window()->setMinimumWidth(290);
    this->window()->setMaximumHeight(110);
    this->window()->setMaximumWidth(290);


}

void MainWindow::on_pushButton_Done_4_clicked()
{
    ui->pushButton_Remove_Same->setVisible(false);
    int Count = ui->tableWidget->columnCount();
    for(int i = 0;i < Count;i++)
    {
        ui->tableWidget->item(0,i)->setText("");
    }
}

void MainWindow::on_pushButton_Done_Puz_clicked()
{
    bool flag_R;
    if(flag_Remove == 1)
    {
        flag_R = 1;
    }
    else
    {
        flag_R = 0;
    }
    const int Count = ui->tableWidget->columnCount();
    QString Str, Str_i,Str_Puz;
    int *Arr = new int[Count];
    bool flag_int,flag_r = false;


    for(int i = 0;i < Count;i++)
    {
        ui->tableWidget->item(0,i)->setSelected(false);
    }

    for(int i = 0;i < Count;i++)
    {
        Str_i.setNum(i + 1);
        Str = ui->tableWidget->item(0,i)->text();
        Arr[i] = Str.toInt(&flag_int,10);
        if(!flag_int)
        {
            QMessageBox::information(nullptr,"Ошибка","Содержание ячейки " + Str_i + " не корректно",QMessageBox::Ok);
            ui->tableWidget->item(0,i)->setSelected(true);
            if(Count > 5)
            {
                ui->tableWidget->scrollToItem(ui->tableWidget->item(0,i));
            }
            flag_r = 0;
            break;
        }
        else
        {
            ui->label_Error->setText("");
            flag_r = 1;
        }

    }

    if(flag_r == 1)
    {
        int Prom;
        for(int i = 0; i < Count - 1;i++)
        {
            for(int j = i + 1;j < Count;j++)
            {
                if(Arr[i] > Arr[j])
                {
                    Prom = Arr[i];
                    Arr[i] = Arr[j];
                    Arr[j] = Prom;
                }
            }
        }

        for(int i = 0;i < Count;i++)
        {
            Str_Puz.setNum(Arr[i]);
            ui->tableWidget->item(0,i)->setText(Str_Puz);
        }

        if(flag_R == 0)
        {
            ui->pushButton_Remove_Same->setVisible(true);
        }

    }
    else
    {

    }

    delete [] Arr;
    Arr = nullptr;
    flag_Sort = 1;
    if(flag_R == 1)
    {
        flag_Remove = 1;
    }
}

void MainWindow::on_pushButton_Remove_Same_clicked()
{
    const int Count = ui->tableWidget->columnCount();
    QString Str, Str_i,Str_RSame;
    int *Arr = new int[Count];
    bool flag_int;

    for(int i = 0;i < Count;i++)
    {
        ui->tableWidget->item(0,i)->setSelected(false);
    }

    for(int i = 0;i < Count;i++)
    {
        Str_i.setNum(i + 1);
        Str = ui->tableWidget->item(0,i)->text();
        Arr[i] = Str.toInt(&flag_int,10);
        if(!flag_int)
        {
            QMessageBox::information(nullptr,"Ошибка","Содержание ячейки " + Str_i + " не корректно",QMessageBox::Ok);
            ui->tableWidget->item(0,i)->setSelected(true);
            if(Count > 5)
            {
                ui->tableWidget->scrollToItem(ui->tableWidget->item(0,i));
            }
            break;
        }
        else
        {
            ui->label_Error->setText("");
        }
    }

    int *Arr_RS = new int[1];

    Arr_RS[0] = Arr[0];
    int RS = 1;

    for(int i = 1;i < Count;i++)
    {
        if(Arr[i] != Arr_RS[RS - 1])
        {
            RS++;
            int *Arr_D = new int[RS];

            for(int j = 0; j < RS; j++)
            {
                Arr_D[j] = Arr_RS[j];
            }

            Arr_D[RS - 1] = Arr[i];

            delete [] Arr_RS;
            Arr_RS = Arr_D;
            Arr_D = nullptr;
        }
        Str_RSame.setNum(i);
        qDebug() << Str_RSame;
    }

    qDebug() << "ВЫХОД ИЗ ЦИКЛА УСПЕШНО ЗАВЕРШЕН";
    for(int i = 0;i < Count;i++)
    {
        ui->tableWidget->item(0,i)->~QTableWidgetItem();
    }
    ui->tableWidget->setColumnCount(RS);
    ui->spinBox_NArr->setValue(RS);
    if(RS <= 5)
    {
        for(int i = 0;i < RS;i++)
        {
            ui->tableWidget->setColumnWidth(i,610/RS);
        }
    }
    qDebug() << "НАЧИНАЮ РАБОТУ С ТАБЛИЦЕЙ";


    for(int i = 0;i < RS;i++)
    {

        if(ui->tableWidget->item(0,i) != nullptr)
        {
            ui->tableWidget->item(0,i)->~QTableWidgetItem();
            QTableWidgetItem * item = new QTableWidgetItem;
            Str_RSame.setNum(Arr_RS[i]);
            item->setText(Str_RSame);
            ui->tableWidget->setItem(0,i,item);
        }
        else
        {
            QTableWidgetItem * item = new QTableWidgetItem;
            Str_RSame.setNum(Arr_RS[i]);
            item->setText(Str_RSame);
            ui->tableWidget->setItem(0,i,item);
        }
    }
    qDebug() << "ЗАКОНЧИЛ РАБОТУ С ТАБЛИЦЕЙ";

    delete [] Arr;
    Arr = nullptr;
    delete [] Arr_RS;
    Arr_RS = nullptr;


    ui->pushButton_Remove_Same->setVisible(false);
    flag_Sort = 1;
    flag_Remove = 1;
}

void MainWindow::QuickSort(int *Arr,int Left,int Right)
{
    int l = Left;
    int r = Right;
    int Index_Opor = (l + r)/2;
    int Prom;
    QString Str_QS;

    while(l <= r)
    {
        while(Arr[l] < Arr[Index_Opor])
        {
            l++;
        }
        while(Arr[r] > Arr[Index_Opor])
        {
            r--;
        }

        if(l <= r)
        {
            Prom = Arr[l];
            Arr[l] = Arr[r];
            Arr[r] = Prom;
            l++;
            r--;
        }



        if (Left < r)
        {
            QuickSort(Arr, Left, r);
        }
        if (l < Right)
        {
            QuickSort(Arr, l, Right);
        }
    }
}

void MainWindow::on_pushButton_Done_Quicksort_clicked()
{
    int Count = ui->tableWidget->columnCount();
    int flag_R;
    if(flag_Remove == 1)
    {
        flag_R = 1;
    }
    else
    {
        flag_R = 0;
    }

    QString Str, Str_i,Str_QS;
    int *Arr = new int[Count];
    bool flag_int,flag_QS = false;

    for(int i = 0;i < Count;i++)
    {
        ui->tableWidget->item(0,i)->setSelected(false);
    }

    for(int i = 0;i < Count;i++)
    {
        Str_i.setNum(i + 1);
        Str = ui->tableWidget->item(0,i)->text();
        Arr[i] = Str.toInt(&flag_int,10);
        if(!flag_int)
        {
            QMessageBox::information(nullptr,"Ошибка","Содержание ячейки " + Str_i + " не корректно",QMessageBox::Ok);
            ui->tableWidget->item(0,i)->setSelected(true);
            if(Count > 5)
            {
                ui->tableWidget->scrollToItem(ui->tableWidget->item(0,i));
            }
            flag_QS = 0;
            break;
        }
        else
        {
            ui->label_Error->setText("");
            flag_QS = 1;
        }
    }
    if(flag_QS == 1)
    {
        MainWindow::QuickSort(Arr,0,Count - 1);
        for(int i = 0; i < Count;i++)
        {
            Str_QS.setNum(Arr[i]);
            ui->tableWidget->item(0,i)->setText(Str_QS);
        }
        if(flag_R == 0)
        {
            ui->pushButton_Remove_Same->setVisible(true);
        }
    }

    delete [] Arr;
    Arr = nullptr;

    flag_Sort = 1;
    if(flag_R == 1)
    {
        flag_Remove = 1;
    }
}

void MainWindow::on_pushButton_Find_Sort_clicked()
{
    const int Count = ui->tableWidget->columnCount();
    QString Str, Str_i,Str_FS;

    int *Arr = new int[Count];

    int *Arr_2 = new int[Count];

    bool flag_int,flag_FS = false;
    int Index_Num = 0;

    for(int i = 0;i < Count;i++)
    {
        ui->tableWidget->item(0,i)->setSelected(false);
    }

    for(int i = 0;i < Count;i++)
    {
        Str_i.setNum(i + 1);
        Str = ui->tableWidget->item(0,i)->text();
        Arr[i] = Str.toInt(&flag_int,10);
        if(!flag_int)
        {
            QMessageBox::information(nullptr,"Ошибка","Содержание ячейки " + Str_i + " не корректно",QMessageBox::Ok);
            ui->tableWidget->item(0,i)->setSelected(true);
            if(Count > 5)
            {
                ui->tableWidget->scrollToItem(ui->tableWidget->item(0,i));
            }
            flag_FS = 0;
            break;
        }
        else
        {
            ui->label_Error->setText("");
            flag_FS = 1;
        }
    }

    if(flag_FS == 1)
    {
        int Num_Find = ui->spinBox_Find->value();

        int j = 0;
        QString j_str;
        for(int i = 0;i < Count;i++)
        {

            if(Arr[i] == Num_Find)
            {
                Index_Num++;
                Arr_2[j] = i;
                j++;
            }
            if(Arr[i] > Num_Find && flag_Sort == 1)
            {
                qDebug() << "SORT";
                break;
            }
        }

        if(j == 0)
        {
            ui->textBrowser->setText("");
            ui->textBrowser->append("Номера ячеек:");
            ui->label_Find_Num->setText("0");
        }
        else
        {

            ui->label_Find->setVisible(true);
            ui->label_Find_Num->setVisible(true);
            ui->label->setVisible(true);
            ui->spinBox_Find->setVisible(true);
            ui->textBrowser->setVisible(true);
            j_str.setNum(j);
            ui->label_Find_Num->setText(j_str);
            ui->textBrowser->setText("");
            ui->textBrowser->append("Номера ячеек:");
            for(int i = 0; i < j;i++)
            {
                ui->textBrowser->append(Str_FS.setNum(Arr_2[i] + 1));
                ui->tableWidget->item(0,Arr_2[i])->setSelected(true);
            }
        }
    }

    delete [] Arr;
    Arr = nullptr;
    delete [] Arr_2;
    Arr_2 = nullptr;

}

void MainWindow::on_pushButton_Import_clicked()
{
    QString File_Name = QFileDialog::getOpenFileName(this, "Открыть", "../Lesson_6/");
    QFile file(File_Name);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int PreCount = ui->tableWidget->columnCount();

        int ArrIndex = 0;
        QString Str_Name = "";
        QString Str_Text = file.readAll();
        const int Count = Str_Text.length();
        int ArrCount = 1;

        char *Text = new char[Count];


        int * Arr_Int = new int[200];

        bool flag_S = false, flag_E = false, flag_int;
        int Start = 0, End = 0;
        QString *Arr = new QString[Count];
        file.flush();
        file.close();

        if(Count <= 11200)
        {

            strcpy(Text, Str_Text.toLatin1().constData());

            for(int i = 0; i < 21;i++)                                     //В начале файла должна стоять запись - [lesson_6_array-list]
            {
                Str_Name.append(Text[i]);
            }

            if(Str_Name == "[lesson_6_array-list]")                        //Проверка на наличине обязательной записи
            {
                qDebug() << "flag_Name = 1";
                for(int i = 20; i < Count;i++)                             //Выполняем поиск [start] - Начало поиска
                {
                    Str_Name = "";
                    for(int j = i; j < i + 7;j++)
                    {
                        Str_Name.append(Text[j]);
                    }
                    qDebug() << Str_Name;
                    if(Str_Name == "[start]")
                    {
                        flag_S = 1;
                        Start = i + 6;
                        qDebug() << "[start] успешно найдено.";
                        break;
                    }
                    else
                    {
                        flag_S = 0;
                    }
                }                                                          //Выполняем поиск [start] - Конец поиска

                for(int i = Start+1; i < Count;i++)                             //Выполняем поиск [end] - Начало поиска
                {
                    Str_Name = "";
                    for(int j = i; j < i + 5;j++)
                    {
                        Str_Name.append(Text[j]);
                    }

                    qDebug() << Str_Name;
                    if(Str_Name == "[end]")
                    {
                        flag_E = 1;
                        End = i;
                        qDebug() <<"[end] успешно найдено.";
                        break;
                    }
                    else
                    {
                        flag_E = 0;
                    }
                }                                                           //Выполняем поиск [end] - Конец поиска


                if(flag_S == 1 && flag_E == 1)
                {
                    qDebug() << "flag_S и flag_E = 1";
                    Str_Name = "";
                    Str_Name.append(Text[Start]);
                    for(int i = Start; i < End;i++)                        //Идем до начала первого значения
                    {
                        if(Text[i] == '\n')
                        {
                            Start = i + 1;
                            break;
                        }
                    }
                    if(Text[Start] == '[')
                    {
                        QMessageBox::information(this,"", "Знаечния отсутствуют.\nИмпорт массива невозможен.",QMessageBox::Yes); //Если начало первого значения равно - '[', то выдаем ошибка т.к. значения отсутсвуют.
                    }
                    else
                    {
                        for(int i = 0;i < PreCount;i++)
                        {
                            ui->tableWidget->item(0,i)->~QTableWidgetItem();
                        }

                        qDebug() << "УДАЛЕНИЕ ЯЧЕЕК УСПЕШНО";
                        for(int i = 0; i < Count;i++)
                        {
                            Arr[i] = "";
                        }
                        for(int i = Start;i < End - 1;i++)              //Выполняем поиск значений + подсчет элементов.
                        {
                            if(Text[i] != '\n')
                            {
                                Arr[ArrIndex].append(Text[i]);
                            }
                            else
                            {
                                ArrCount++;
                                ArrIndex++;
                            }
                        }
                        qDebug() << "ПОСЧИТАЛ УСПЕШНО";                                       //Конец поиска значений + подсчета элементов.



                        ui->spinBox_NArr->setValue(ArrCount);
                        ui->tableWidget->setColumnCount(ArrCount);

                        qDebug() << "СДЕЛАЛ ТАБЛИЦУ НОВУЮ";
                        if(ArrCount <= 5)                                //Настраиваем ширину ячеек в таблице
                        {
                            for(int i = 0;i < ArrCount;i++)
                            {
                                ui->tableWidget->setColumnWidth(i,610/(ArrCount));
                            }
                        }
                        else
                        {
                            for(int i = 0;i < ArrCount;i++)
                            {
                                ui->tableWidget->setColumnWidth(i,122);
                            }
                        }
                        qDebug() << "ШИРИНА ФИГИНА";


                        for(int i = 0;i < ArrCount;i++)                     //Заносим знаечния в таблицу
                        {

                            if(ui->tableWidget->item(0,i) != nullptr)
                            {
                                ui->tableWidget->item(0,i)->~QTableWidgetItem();
                                QTableWidgetItem * item = new QTableWidgetItem;
                                Str_Name = "";
                                Str_Name.append(Arr[i]);
                                item->setText(Str_Name);
                                ui->tableWidget->setItem(0,i,item);
                            }
                            else
                            {
                                QTableWidgetItem * item = new QTableWidgetItem;
                                Str_Name = "";
                                Str_Name.append(Arr[i]);
                                item->setText(Str_Name);
                                ui->tableWidget->setItem(0,i,item);
                            }
                        }

                        qDebug() << "СДЕЛАЛ НОВЫЕ АЙТЕМЫ";

                        for(int i = 0;i < ArrCount;i++)                     //Проверка значений в таблице на Int
                        {
                            Str_Name.setNum(i + 1);
                            Str_Text = ui->tableWidget->item(0,i)->text();
                            Arr_Int[i] = Str_Text.toInt(&flag_int,10);
                            if(!flag_int)
                            {
                                QMessageBox::information(nullptr,"Ошибка","Содержание ячейки " + Str_Text + " не корректно",QMessageBox::Ok);
                                ui->tableWidget->item(0,i)->setSelected(true);
                                if(Count > 5)
                                {
                                    ui->tableWidget->scrollToItem(ui->tableWidget->item(0,i));
                                }
                                break;
                            }
                            else
                            {
                                ui->label_Error->setText("");
                            }
                        }
                        qDebug() << "ЫЫЫЫЫ";

                    }
                }
                else
                {
                    if(!flag_S && !flag_E)
                        QMessageBox::information(this,"Ошибка", "[start] и [end] не найдены",QMessageBox::Yes);
                    if(!flag_S && flag_E)
                        QMessageBox::information(this,"Ошибка", "[start] не найден",QMessageBox::Yes);
                    if(flag_S && !flag_E)
                        QMessageBox::information(this,"Ошибка", "[end] не найден",QMessageBox::Yes);
                }
            }
            else
            {
                QMessageBox::information(this,"", "flag_Name = 0",QMessageBox::Yes);
            }

        }
        else
        {
            QMessageBox::information(this,"Ошибка", "Большой размер файла.",QMessageBox::Yes);
        }
        delete [] Arr_Int;
        Arr_Int = nullptr;

        delete [] Arr;
        Arr = nullptr;

        delete [] Text;
        Text = nullptr;
        flag_Sort = 0;

    }

}

void MainWindow::on_pushButton_Export_clicked()
{
    const int Count = ui->tableWidget->columnCount();
    QString * Str = new QString;
    QString * Str_i = new QString;
    int *Arr = new int[Count];

    bool flag_FS = false;
    bool flag_int = false;
    for(int i = 0;i < Count;i++)
    {
        ui->tableWidget->item(0,i)->setSelected(false);
    }
    for(int i = 0;i < Count;i++)
    {
        (*Str_i).setNum(i + 1);
        (*Str) = ui->tableWidget->item(0,i)->text();
        Arr[i] = (*Str).toInt(&flag_int,10);
        if(!flag_int)
        {
            QMessageBox::information(nullptr,"Ошибка","Содержание ячейки " + *Str + " не корректно",QMessageBox::Ok);
            ui->tableWidget->item(0,i)->setSelected(true);
            if(Count > 5)
            {
                ui->tableWidget->scrollToItem(ui->tableWidget->item(0,i));
            }
            flag_FS = 0;
            break;
        }
        else
        {
            ui->label_Error->setText("");
            flag_FS = 1;
        }
    }


    if(flag_FS == 1)
    {
        QString * File_Name = new QString;
        QFileDialog Dialog;
        *File_Name = (Dialog.getSaveFileName(nullptr,"Сохранить как","../Lesson_6/","*.txt"));
        QFile file(*File_Name);

        delete File_Name;
        File_Name = nullptr;

        if(file.open(QFile::WriteOnly | QFile::Text))
        {
            for(int i = 0;i < Count;i++)
            {
                ui->tableWidget->item(0,i)->setSelected(false);
            }

            (*Str) = "[lesson_6_array-list]\n\nКаждая новая строка - новый элемент массива.\nЭлементы заполнять строго под [ start ] и над [ end ].\n\n[start]\n";
            (*Str_i) = "";
            for(int i = 0;i < Count; i++)
            {
                (*Str).append((*Str_i).setNum(Arr[i]) + "\n");
            }
            (*Str).append("[end]");
            file.write((*Str).toUtf8());
            file.flush();
            file.close();

            delete File_Name;
            File_Name = nullptr;
        }
    }

    delete Str;
    Str = nullptr;
    delete Str_i;
    Str_i = nullptr;
    delete [] Arr;
    Arr = nullptr;
    flag_Sort = 0;
}

void MainWindow::on_pushButton_Size_clicked()
{
    if(flag_width)
    {
        flag_width = false;
        this->window()->setMinimumHeight(371);
        this->window()->setMinimumWidth(659);
        this->window()->setMaximumHeight(371);
        this->window()->setMaximumWidth(659);
        ui->pushButton_Size->setText(">");
    }
    else
    {
        flag_width = true;
        this->window()->setMinimumHeight(371);
        this->window()->setMinimumWidth(1280);
        this->window()->setMaximumHeight(371);
        this->window()->setMaximumWidth(1280);
        ui->pushButton_Size->setText("<");
    }
}

void MainWindow::on_pushButton_Import_2_clicked()
{
    QString input;
    QString File_Name = QFileDialog::getOpenFileName(this, "Открыть", "../Lesson_6/");
    if (File_Name.toLower().endsWith(".bin"))
    {
        QFile file(File_Name);
        file.open(QIODevice::ReadOnly);
        if((file.size() % 4 == 0) && (file.size() > 3))
        {
            int NUM;
            int ACount = 0;
            int Count = file.size()/4;
            QString ARR[Count];

            int size = sizeof(int);
            char bytes[size];
            int ii = 0;
            while(ACount < file.size())
            {
                file.read(bytes, size);
                memcpy (&NUM, &bytes, size);
                ACount = ACount + size;
                ARR[ii] = QString::number(NUM, 10);
                qDebug() << ARR[ii];
                ii++;
            }

            QString Str_Name, Str_Text;
            int Arr_Int[Count];
            bool flag_int = false;

            for(int i = 0;i < ui->spinBox_Find->value();i++)
            {
                ui->tableWidget->item(0,i)->~QTableWidgetItem();
            }

            ui->spinBox_NArr->setValue(Count);
            ui->tableWidget->setColumnCount(Count);

            if(Count <= 5)                                //Настраиваем ширину ячеек в таблице
            {
                for(int i = 0;i < Count;i++)
                {
                    ui->tableWidget->setColumnWidth(i,610/(Count));
                }
            }
            else
            {
                for(int i = 0;i < Count;i++)
                {
                    ui->tableWidget->setColumnWidth(i,122);
                }
            }


            for(int i = 0;i < Count;i++)                     //Заносим знаечния в таблицу
            {
                QTableWidgetItem * item = new QTableWidgetItem;
                Str_Name = "";
                Str_Name.append(ARR[i]);
                item->setText(Str_Name);
                ui->tableWidget->setItem(0,i,item);
            }


            for(int i = 0;i < Count;i++)                     //Проверка значений в таблице на Int
            {
                Str_Name.setNum(i + 1);
                Str_Text = ui->tableWidget->item(0,i)->text();
                Arr_Int[i] = Str_Text.toInt(&flag_int,10);
                if(!flag_int)
                {
                    QMessageBox::information(nullptr,"Ошибка","Содержание ячейки " + Str_Text + " не корректно",QMessageBox::Ok);
                    ui->tableWidget->item(0,i)->setSelected(true);
                    if(Count > 5)
                    {
                        ui->tableWidget->scrollToItem(ui->tableWidget->item(0,i));
                    }
                    break;
                }
                else
                {
                    ui->label_Error->setText("");
                }
            }
        }
        else
        {
            QMessageBox::information(nullptr,"Ошибка","Я не буду смотреть этот файл",QMessageBox::Ok);
        }
        file.close();
    }
    else
    {
        QMessageBox::information(nullptr,"Ошибка","Неверный формат файла",QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_Export_2_clicked()
{
    const int Count = ui->tableWidget->columnCount();
    QString * Str = new QString;
    QString * Str_i = new QString;
    int *Arr = new int[Count];

    bool flag_FS = false;
    bool flag_int = false;
    for(int i = 0;i < Count;i++)
    {
        ui->tableWidget->item(0,i)->setSelected(false);
    }
    for(int i = 0;i < Count;i++)
    {
        (*Str_i).setNum(i + 1);
        (*Str) = ui->tableWidget->item(0,i)->text();
        Arr[i] = (*Str).toInt(&flag_int,10);
        if(!flag_int)
        {
            QMessageBox::information(nullptr,"Ошибка","Содержание ячейки " + *Str + " не корректно",QMessageBox::Ok);
            ui->tableWidget->item(0,i)->setSelected(true);
            if(Count > 5)
            {
                ui->tableWidget->scrollToItem(ui->tableWidget->item(0,i));
            }
            flag_FS = 0;
            break;
        }
        else
        {
            ui->label_Error->setText("");
            flag_FS = 1;
        }
    }


    if(flag_FS == 1)
    {
        QString File_Name;
        QString TEXT;
        QFileDialog Dialog;
        int DATACount = 0;
        char * DATA = new char[DATACount];
        File_Name = (Dialog.getSaveFileName(nullptr,"Сохранить как","../Lesson_6/","*.bin"));

            if (!File_Name.endsWith (".bin"))
            {
                File_Name += ".bin";
            }

            QFile file(File_Name);

            file.open(QIODevice::WriteOnly);

            int size = sizeof(int);
            char cache[size];

            for (int i = 0; i < Count; i++)
            {
                memcpy(&cache,&(Arr[i]),size);
                if(file.write(cache,size) < size)
                {
                    QMessageBox::information(nullptr,"Ошибка","При записи в файл произошла ошибка",QMessageBox::Ok);
                }
            }
            file.close ();
    }

    delete Str;
    Str = nullptr;
    delete Str_i;
    Str_i = nullptr;
    delete [] Arr;
    Arr = nullptr;
    flag_Sort = 0;
}
