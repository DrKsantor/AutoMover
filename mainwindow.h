#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QDir;
class QFile;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnFromPath_clicked();
    void on_btnToPath_clicked();
    void on_btnFilterPath_clicked();
    void on_linePrefix_editingFinished();
    void on_linePostfix_editingFinished();

    void on_btnMove_clicked();

private:
    void moveFiles();

    Ui::MainWindow *ui;

    QFile *m_filter;
    QDir *m_moveFrom;
    QDir *m_moveTo;
    QString m_prefix;
    QString m_postfix;
};
#endif // MAINWINDOW_H
