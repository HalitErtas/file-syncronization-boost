#include "DirectoryComparer.hpp"
#include "FileScanner.hpp"
#include "MainWindow.hpp"
#include "ComparisonEntry.hpp"
#include "ComparisonStatus.hpp"
#include "FileType.hpp"

#include <filesystem>
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    file_sync_app::core::FileScanner scanner;
    auto source = std::filesystem::current_path() / "test-files/source";
    auto target = std::filesystem::current_path() / "test-files/target";

    auto type = file_sync_app::common::FileType::ALL;
    
    auto sourceFiles = scanner.scan(source, type);
    auto targetFiles = scanner.scan(target, type);

    std::cout << "SOURCE" << std::endl;
    for(const auto& file : sourceFiles){
        std::cout << file.path << std::endl;
    }

    std::cout << "TARGET" << std::endl;
    for(const auto& file : targetFiles){
        std::cout << file.path << std::endl;
    }

    file_sync_app::core::DirectoryComparer comparer;

    // auto denemeSource = std::filesystem::current_path() / "test-files/source/docs/readme.md";
    // auto denemeTarget = std::filesystem::current_path() / "test-files/target/docs/readme.md";

    // auto res = comparer.computeSHA256(denemeSource);
    // auto res1 = comparer.computeSHA256(denemeTarget);
    // std::cout << res << std::endl;
    // std::cout << res1 << std::endl;


    // auto result = comparer.compare(sourceFiles, targetFiles);
    // auto type = file_sync_app::common::FileType::ALL;
    
    // std::vector<file_sync_app::common::FileInfo> files = scanner.scan(path, type);

    // for(const auto& entry : result){
    //     std::cout <<
    //         (entry.status == file_sync_app::common::ComparisonStatus::Added ? "[ADDED]" : 
    //             entry.status == file_sync_app::common::ComparisonStatus::Unchanged ? "[UNCHANGED]" :
    //             entry.status == file_sync_app::common::ComparisonStatus::Removed ? "[REMOVED]" : (
    //             entry.status == file_sync_app::common::ComparisonStatus::Modified ? "[MODIFIED]" : ""))
    //         << std::setw(20) <<  entry.info.path <<  std::setw(20)  << (entry.info.isDirectory ? "Directory" : "file") 
    //         << std::setw(5) << entry.info.size << std::endl;
    // }

    // gui

    QApplication app(argc, argv);

    file_sync_app::gui::MainWindow window;
    window.show();

    return app.exec();





    return 0;
}