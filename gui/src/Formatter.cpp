#include "Formatter.hpp"

namespace file_sync_app::gui {
    const QStringList Formatter::units = {
        QString("B"),
        QString("KB"),
        QString("MB"),
        QString("GB"),
        QString("TB")
    };


    QString Formatter::formatFileSize(uintmax_t bytes){
        double size = bytes;
        
        int ind = 0;

        while(size >= 1024 && ind < units.size() - 1){
            size /= 1024;
            ind++;
        }
        QString unit = units[ind];
        return QString::number(size, 'g', 2) + " " + unit;
    }

    QString Formatter::formatDate(const std::filesystem::file_time_type& time)
    {

        const auto systemTime =
            std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                time - std::filesystem::file_time_type::clock::now()
                + std::chrono::system_clock::now());

        const std::time_t tt = std::chrono::system_clock::to_time_t(systemTime);

        return QDateTime::fromSecsSinceEpoch(tt)
            .toString("yyyy-MM-dd HH:mm:ss");
    }

    QColor Formatter::statusColor(common::ComparisonStatus status){
        switch (status) {
            case common::ComparisonStatus::Added:
                return QColor(Qt::darkGreen);
            case common::ComparisonStatus::Modified:
                return QColor(Qt::darkMagenta);
            case common::ComparisonStatus::Removed:
                return QColor(Qt::darkRed);
            case common::ComparisonStatus::Unchanged:
                return QColor(Qt::gray);
        }

        return QColor(Qt::gray);
    }

    QString Formatter::statusText(common::ComparisonStatus status){
        switch (status){
            case common::ComparisonStatus::Added:
                return QString("[Added]");
            case common::ComparisonStatus::Modified:
                return QString("[Modified]");
            case common::ComparisonStatus::Removed:
                return QString("[Removed]");
            case common::ComparisonStatus::Unchanged:
                return QString("[Unchanged]");
        }

        return QString("[Unknown");
    }
}