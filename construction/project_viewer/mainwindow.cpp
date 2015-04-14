#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

class tree_node_info
{
public:
    bool is_folder;
    QString path;
};

void MainWindow::on_m_new_folder_clicked()
{
    QTreeWidgetItem* selected = this->ui->m_tree->currentItem();
    QStringList strings;
    tree_node_info* node = new tree_node_info;
    node->is_folder = true;
    node->path = "New Folder";
    strings.append(node->path);

    QTreeWidgetItem* child = new QTreeWidgetItem(strings);

    QVariant data = qVariantFromValue((void *)node);
    child->setData(0, Qt::UserRole, data);

    if(selected)
    {
        tree_node_info* node = (tree_node_info *) selected->data(0, Qt::UserRole).value<void *>();
        if(node->is_folder)
        {
            selected->addChild(child);
            selected->setExpanded(true);
        }
        else
        {
            this->ui->m_tree->addTopLevelItem(child);
            child->setExpanded(true);
        }
    }
    else
    {
        this->ui->m_tree->addTopLevelItem(child);
        child->setExpanded(true);
    }
}

void MainWindow::on_m_new_file_clicked()
{
    QTreeWidgetItem* item = this->ui->m_tree->currentItem();

    if(item)
    {
        tree_node_info* node = new tree_node_info;
        node->is_folder = false;
        node->path = "New File";

        QStringList strings;
        strings.append(node->path);

        QTreeWidgetItem* child = new QTreeWidgetItem(strings);

        QVariant data = qVariantFromValue((void *)node);
        child->setData(0, Qt::UserRole, data);

        item->addChild(child);
        item->setExpanded(true);
    }
}

#include <QInputDialog>
void MainWindow::on_m_tree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QString text = QInputDialog::getText(this, "Re-name", "Enter a new name", QLineEdit::Normal, item->text(column));
    if(!text.isNull())
    {
        item->setText(column, text);
    }

    item->setExpanded(true);
}

void MainWindow::on_m_tree_itemChanged(QTreeWidgetItem *item, int column)
{

}

void MainWindow::on_m_tree_itemActivated(QTreeWidgetItem *item, int column)
{

}

void MainWindow::on_m_tree_itemPressed(QTreeWidgetItem *item, int column)
{
    tree_node_info* node = (tree_node_info *) item->data(column, Qt::UserRole).value<void *>();
    this->ui->m_new_file->setDisabled(true);
    //this->ui->m_new_folder->setDisabled(true);

    if(node->is_folder)
    {
        this->ui->m_new_file->setDisabled(false);
    }
    else
    {
        this->ui->m_new_file->setDisabled(true);
    }
}
