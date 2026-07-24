
#include "structs/ComparisonEntry.hpp"
#include "DirectoryComparer.hpp"
#include <algorithm>
#include <vector>

namespace file_sync_app {
    std::vector<structs::ComparisonEntry> DirectoryComparer::compare(const std::vector<structs::FileInfo>& source, const std::vector<structs::FileInfo>& target){
        std::vector<structs::ComparisonEntry> entries;

        for(const auto& sourceElement : source){
            bool isFound = false;

            for(const auto& targetElement : target){
                if(sourceElement.path == targetElement.path){
                    isFound = true;
                    break;
                }
            }

            if(isFound){
                entries.push_back(structs::ComparisonEntry {sourceElement, structs::ComparisonStatus::Unchanged});
            }else{
                entries.push_back(structs::ComparisonEntry {sourceElement, structs::ComparisonStatus::Added});
            }
        }

        for(const auto& targetElement : target){
            bool isFound = false;

            for(const auto& sourceElement : source){
                if(sourceElement.name == targetElement.name){
                    isFound = true;
                    break;
                }
            }

            if(!isFound){
                entries.push_back(structs::ComparisonEntry {targetElement, structs::ComparisonStatus::Removed});
            }
        }

        return entries;
    }
}