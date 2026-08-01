#include "widgets/ComparisonTable.hpp"

namespace file_sync_app::gui {
    const QStringList ComparisonTable::TableHeaders = {
        "Status",
        "File",
        "Size",
        "Date"
    };

    ComparisonTable::ComparisonTable(){
        setColumnCount(TableHeaders.size());
        setHorizontalHeaderLabels(TableHeaders);
        horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        verticalHeader()->hide();
        setShowGrid(false);
        setAlternatingRowColors(true);
        setSelectionBehavior(QAbstractItemView::SelectRows);
        setSelectionMode(QAbstractItemView::SingleSelection);
        setSortingEnabled(true);
    };

    void ComparisonTable::setTableData(const std::vector<common::ComparisonEntry>& datas){
        this->clearContents();
        this->setRowCount(std::size(datas));

        for (size_t row = 0; row < datas.size(); ++row)
        {
            for (int column = 0; column < columnCount(); ++column)
            {
                auto* item = new QTableWidgetItem;
                setTableItem(datas[row], column, item);
                setItem(static_cast<int>(row), column, item);
            }
        }
    }

    void ComparisonTable::setTableItem(const common::ComparisonEntry& data, int column, QTableWidgetItem* item){
        switch (static_cast<Column>(column)) {
            case Column::Status:
                item->setText(Formatter::statusText(data.status));
                item->setForeground(Formatter::statusColor(data.status));
                break;
            case Column::File:
                item->setIcon(
                    data.info.isDirectory ? 
                        QApplication::style()->standardIcon(QStyle::SP_DirIcon) :
                        QApplication::style()->standardIcon(QStyle::SP_FileIcon));
                item->setText(QString::fromStdString(data.info.path));
                break;
            case Column::Size:
                item->setText(Formatter::formatFileSize(data.info.size));
                break;
            case Column::Date:
                item->setText(Formatter::formatDate(data.info.lastWriteTime));
                break;
            default:
                break;
        }
    }

}