#ifndef COMPARISONTABLE_H_
#define COMPARISONTABLE_H_

#include "Formatter.hpp"
#include "ComparisonEntry.hpp"
#include "QStringList"
#include "QTableWidget"
#include <QtWidgets>


namespace file_sync_app::gui {
    
class ComparisonTable : public QTableWidget{
    private:
        enum class Column
        {
            Status = 0,
            File,
            Size,
            Date
        };
        static const QStringList TableHeaders;
    public:
        ComparisonTable();
        void setTableData(const std::vector<common::ComparisonEntry>& datas);
    private:
        void setTableItem(const common::ComparisonEntry& data, int column, QTableWidgetItem* item);

    };
} // namespace file_sync_app::gui

#endif  