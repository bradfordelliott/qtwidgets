#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>

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

    void on_m_new_folder_clicked();

    void on_m_new_file_clicked();

    void on_m_tree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_m_tree_itemChanged(QTreeWidgetItem *item, int column);

    void on_m_tree_itemActivated(QTreeWidgetItem *item, int column);

    void on_m_tree_itemPressed(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
