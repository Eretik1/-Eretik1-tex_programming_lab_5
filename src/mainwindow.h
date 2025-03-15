#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <memory>
#include <QList>
#include "mylibrary.h"  

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDeviceSelected(QListWidgetItem *item);
    void onAddDeviceClicked();
    void onEditDeviceClicked();
    void onDeleteDeviceClicked();
    void onDeviceTypeSelected(const QString &type);

private:
    QListWidget *devicesList;
    QLabel *deviceInfoLabel;
    QPushButton *addDeviceButton;
    QPushButton *editDeviceButton;
    QPushButton *deleteDeviceButton;
    std::unique_ptr<IDeviceFactory> deviceFactory;
    QList<std::shared_ptr<Electrodevice>> devices;  

    void setupUI();
    void displayDeviceInfo(const std::shared_ptr<Electrodevice>& device);
    void createDevice(const QString &type);
    void editDevice(QListWidgetItem *item);
};

#endif 