#ifndef FORMATTER_H_
#define FORMATTER_H_

#include "ComparisonStatus.hpp"
#include <QColor>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QTableWidget>
#include <QFileDialog>


namespace file_sync_app::gui {
    
class Formatter{
    private: 
        static const QStringList units;
    public:
        static QString formatFileSize(uintmax_t bytes);
        static QString formatDate(const std::filesystem::file_time_type& time);
        static QColor statusColor(common::ComparisonStatus status);
        static QString statusText(common::ComparisonStatus status);
    };
} // namespace file_sync_app::gui

#endif  