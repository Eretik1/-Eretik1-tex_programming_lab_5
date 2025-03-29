#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), deviceFactory(createDeviceFactory())
{
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    devicesList = new QListWidget(this);
    deviceInfoLabel = new QLabel("Выберите устройство для просмотра информации", this);

    addDeviceButton = new QPushButton("Добавить устройство", this);
    editDeviceButton = new QPushButton("Редактировать устройство", this);
    deleteDeviceButton = new QPushButton("Удалить устройство", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addDeviceButton);
    buttonLayout->addWidget(editDeviceButton);
    buttonLayout->addWidget(deleteDeviceButton);

    layout->addWidget(devicesList);
    layout->addWidget(deviceInfoLabel);
    layout->addLayout(buttonLayout);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(devicesList, &QListWidget::itemClicked, this, &MainWindow::onDeviceSelected);
    connect(addDeviceButton, &QPushButton::clicked, this, &MainWindow::onAddDeviceClicked);
    connect(editDeviceButton, &QPushButton::clicked, this, &MainWindow::onEditDeviceClicked);
    connect(deleteDeviceButton, &QPushButton::clicked, this, &MainWindow::onDeleteDeviceClicked);
}

void MainWindow::displayDeviceInfo(const std::shared_ptr<Electrodevice>& device)
{
    QString info = QString("Устройство: %1\nПотребление: %2 Вт\nСтатус: %3")
                       .arg(QString::fromStdString(device->getName()))
                       .arg(device->getConsumption())
                       .arg(device->getStatus() ? "Включено" : "Выключено");

    if (auto heatingElement = std::dynamic_pointer_cast<HeatingElement>(device)) {
        info += QString("\nТепловыделение: %1 Вт").arg(heatingElement->getHeatGeneration());
    }
    else if (auto electricMotor = std::dynamic_pointer_cast<ElectricMotor>(device)) {
        info += QString("\nМощность: %1 кВт").arg(electricMotor->getPower());
    }
    else if (auto electricDrill = std::dynamic_pointer_cast<ElectricDrill>(device)) {
        info += QString("\nПроизводитель: %1").arg(QString::fromStdString(electricDrill->getManufacturer()));
    }

    deviceInfoLabel->setText(info);
}

void MainWindow::onDeviceSelected(QListWidgetItem *item)
{
    int index = devicesList->row(item);
    if (index >= 0 && index < devices.size()) {
        displayDeviceInfo(devices[index]);
    }
}

void MainWindow::onAddDeviceClicked()
{
    QStringList deviceTypes = {"Electrodevice", "HeatingElement", "ElectricMotor", "ElectricDrill"};
    bool ok;
    QString type = QInputDialog::getItem(this, "Выберите тип устройства", "Тип устройства:", deviceTypes, 0, false, &ok);
    if (ok && !type.isEmpty()) {
        onDeviceTypeSelected(type);
    }
}

void MainWindow::onDeviceTypeSelected(const QString &type)
{
    bool ok;
    QString name = QInputDialog::getText(this, "Добавить устройство", "Введите название устройства:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    float consumption = QInputDialog::getDouble(this, "Добавить устройство", "Введите потребление (Вт):", 0, 0, 10000, 2, &ok);
    if (!ok) return;

    std::shared_ptr<Electrodevice> device;

    if (type == "Electrodevice") {
        device = deviceFactory->createElectrodevice(name.toStdString(), consumption);
    }
    else if (type == "HeatingElement") {
        float heatGeneration = QInputDialog::getDouble(this, "Добавить устройство", "Введите тепловыделение (Вт):", 0, 0, 10000, 2, &ok);
        if (!ok) return;
        device = deviceFactory->createHeatingElement(name.toStdString(), consumption, heatGeneration);
    }
    else if (type == "ElectricMotor") {
        float power = QInputDialog::getDouble(this, "Добавить устройство", "Введите мощность (кВт):", 0, 0, 1000, 2, &ok);
        if (!ok) return;
        device = deviceFactory->createElectricMotor(name.toStdString(), consumption, power);
    }
    else if (type == "ElectricDrill") {
        float power = QInputDialog::getDouble(this, "Добавить устройство", "Введите мощность (кВт):", 0, 0, 1000, 2, &ok);
        if (!ok) return;
        QString manufacturer = QInputDialog::getText(this, "Добавить устройство", "Введите производителя:", QLineEdit::Normal, "", &ok);
        if (!ok || manufacturer.isEmpty()) return;
        device = deviceFactory->createElectricDrill(name.toStdString(), consumption, power, manufacturer.toStdString());
    }

    if (device) {
        devices.append(device);  
        devicesList->addItem(QString::fromStdString(device->getName()));
        QMessageBox::information(this, "Успех", "Устройство добавлено!");
    }
}

void MainWindow::onEditDeviceClicked()
{
    QListWidgetItem *item = devicesList->currentItem();
    if (item) {
        editDevice(item);
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите устройство для редактирования.");
    }
}

void MainWindow::editDevice(QListWidgetItem *item)
{
    int index = devicesList->row(item);
    if (index < 0 || index >= devices.size()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось найти устройство для редактирования.");
        return;
    }

    std::shared_ptr<Electrodevice> device = devices[index];

    bool ok;
    QString newName = QInputDialog::getText(this, "Редактировать устройство", "Введите новое название устройства:", QLineEdit::Normal, QString::fromStdString(device->getName()), &ok);
    if (!ok || newName.isEmpty()) return;

    float newConsumption = QInputDialog::getDouble(this, "Редактировать устройство", "Введите новое потребление (Вт):", device->getConsumption(), 0, 10000, 2, &ok);
    if (!ok) return;

    device->setName(newName.toStdString());
    device->setConsumption(newConsumption);

    if (auto heatingElement = std::dynamic_pointer_cast<HeatingElement>(device)) {
        float newHeatGeneration = QInputDialog::getDouble(this, "Редактировать устройство", "Введите новое тепловыделение (Вт):", heatingElement->getHeatGeneration(), 0, 10000, 2, &ok);
        if (!ok) return;
        heatingElement->setHeatGeneration(newHeatGeneration);
    }
    else if (auto electricMotor = std::dynamic_pointer_cast<ElectricMotor>(device)) {
        float newPower = QInputDialog::getDouble(this, "Редактировать устройство", "Введите новую мощность (кВт):", electricMotor->getPower(), 0, 1000, 2, &ok);
        if (!ok) return;
        electricMotor->setPower(newPower);
    }
    else if (auto electricDrill = std::dynamic_pointer_cast<ElectricDrill>(device)) {
        QString newManufacturer = QInputDialog::getText(this, "Редактировать устройство", "Введите нового производителя:", QLineEdit::Normal, QString::fromStdString(electricDrill->getManufacturer()), &ok);
        if (!ok || newManufacturer.isEmpty()) return;
        electricDrill->setManufacturer(newManufacturer.toStdString());
    }

    item->setText(QString::fromStdString(device->getName()));
    QMessageBox::information(this, "Успех", "Устройство отредактировано!");
}

void MainWindow::onDeleteDeviceClicked()
{
    QListWidgetItem *item = devicesList->currentItem();
    if (1) { 
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Удалить устройство", "Вы уверены, что хотите удалить устройство?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            int index = devicesList->row(item);
            if (index < devices.size()) {//index >= 0 &&
                devices.removeAt(index);  
            }
            delete item;
            QMessageBox::information(this, "Успех", "Устройство удалено!");
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите устройство для удаления.");
    }
}