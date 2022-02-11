#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_filter(new QFile),
    m_moveFrom(new QDir),
    m_moveTo(new QDir)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnFromPath_clicked()
{
    const auto path = QFileDialog::getExistingDirectory(this, QString(), ui->lineFolderFrom->text());

    if (path.isEmpty()) {
        return;
    } else {
        ui->lineFolderFrom->setText(QDir::toNativeSeparators(path));
        m_moveFrom->setPath(QDir::fromNativeSeparators(ui->lineFolderFrom->text()));
        qDebug() << "Move from:" << m_moveFrom->path();
    }
}


void MainWindow::on_btnToPath_clicked()
{
    const auto path = QFileDialog::getExistingDirectory(this, QString(), ui->lineFolderTo->text());

    if (path.isEmpty()) {
        return;
    } else {
        ui->lineFolderTo->setText(QDir::toNativeSeparators(path));
        m_moveTo->setPath(QDir::fromNativeSeparators(ui->lineFolderTo->text()));
        qDebug() << "Move to:" << m_moveTo->path();
    }
}


void MainWindow::on_btnFilterPath_clicked()
{
    const auto path = QFileDialog::getOpenFileName();

    if (path.isEmpty()) {
        return;
    } else {
        ui->lineFilterFile->setText(QDir::toNativeSeparators(path));
        m_filter->setFileName(QDir::fromNativeSeparators(ui->lineFilterFile->text()));
        qDebug() << "Filter file:" << m_filter->fileName();
    }
}

void MainWindow::on_linePrefix_editingFinished()
{
    m_prefix = ui->linePrefix->text();
}


void MainWindow::on_linePostfix_editingFinished()
{
    m_postfix = ui->linePostfix->text();
}

void MainWindow::on_btnMove_clicked()
{
    ui->lblstatusBar->setText("Moving files initiated!");
    moveFiles();
}

void MainWindow::moveFiles()
{

    auto ok = m_filter->open(QIODevice::ReadOnly);


    if(ok) {
        auto str = new QTextStream(m_filter);
        auto status = false;

        ui->lblstatusBar->setText("");

        while (!str->atEnd()) {
            auto filename = m_prefix + str->readLine() + m_postfix;   //hardcoded for now
            status = m_moveFrom->rename(filename, m_moveTo->path() + "/" + filename);

            qDebug() << status << filename;
            if(status) ui->lblstatusBar->setText(filename + " moved");
            else ui->lblstatusBar->setText(filename + " not moved");
        }
        m_filter->close();
    }
    else {
        ui->lblstatusBar->setText("Couldn't open filter file!");
    }
}
