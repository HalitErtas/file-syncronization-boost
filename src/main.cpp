#include "DirectoryComparer.hpp"
#include "FileScanner.hpp"
#include "structs/ComparisonEntry.hpp"
#include "structs/FileType.hpp"
#include <filesystem>
#include <iostream>
#include <vector>


int main()
{
    file_sync_app::FileScanner scanner;
    auto source = std::filesystem::current_path() / "test-files/source";
    auto target = std::filesystem::current_path() / "test-files/target";

    auto type = file_sync_app::structs::FileType::ALL;
    
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

    file_sync_app::DirectoryComparer comparer;
    auto result = comparer.compare(sourceFiles, targetFiles);
    // auto type = file_sync_app::structs::FileType::ALL;
    
    // std::vector<file_sync_app::structs::FileInfo> files = scanner.scan(path, type);

    for(const auto& entry : result){
        std::cout <<
            (entry.status == file_sync_app::structs::ComparisonStatus::Added ? "[ADDED]" : 
            entry.status == file_sync_app::structs::ComparisonStatus::Unchanged ? "[UNCHANGED]" :
             entry.status == file_sync_app::structs::ComparisonStatus::Removed ? "[REMOVED]" : "")
            << std::setw(20) <<  entry.info.path <<  std::setw(20)  << (entry.info.isDirectory ? "Directory" : "file") 
            << std::setw(5) << entry.info.size << std::endl;
    }

    return 0;
}