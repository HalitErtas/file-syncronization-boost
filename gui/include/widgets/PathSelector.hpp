#ifndef PATHSELECTOR_H_
#define PATHSELECTOR_H_

#include <QtWidgets>


namespace file_sync_app::gui {
    
class PathSelector : public QGroupBox {
    private:
        QHBoxLayout* h_layout;
        QLineEdit* pathEdit;
        QPushButton* browseButton;
        public:
        PathSelector(const QString& title, const QString& buttonText = "Browse");
        QString path() const;
    private:
        void createWidgets(const QString& buttonText);
        void createLayout();
        void connectSignals();
        void openFileDialog();
    };
} // namespace file_sync_app::gui

#endif  