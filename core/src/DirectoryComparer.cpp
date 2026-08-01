#include "DirectoryComparer.hpp"
#include "ComparisonEntry.hpp"
#include <iostream>
#include <openssl/evp.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <array>

namespace file_sync_app::core {
    std::vector<common::ComparisonEntry> core::DirectoryComparer::compare(
            const std::vector<common::FileInfo>& source, 
            const std::vector<common::FileInfo>& target, 
            std::function<void(int)> progress)
    {
        std::vector<common::ComparisonEntry> entries;

        int total = source.size() + target.size();
        int current = 0;

        if(total == 0)
        {
            if(progress)
                progress(100);

            return entries;
        }

        for(const auto& sourceElement : source){
            bool isFound = false;
            bool isSame = false;

            for(const auto& targetElement : target){
                if(sourceElement.path == targetElement.path && sourceElement.isDirectory == targetElement.isDirectory){
                    isFound = true;
                    if(sourceElement.size == targetElement.size && sourceElement.sha256 == targetElement.sha256){
                        isSame = true;
                    }
                    break;
                }
            }

            if(!isFound){
                entries.push_back(common::ComparisonEntry {sourceElement, common::ComparisonStatus::Added});
            }
            else if(sourceElement.isDirectory){
                entries.push_back(common::ComparisonEntry {sourceElement, common::ComparisonStatus::Unchanged});
            }
            else if(!isSame){
                entries.push_back(common::ComparisonEntry {sourceElement, common::ComparisonStatus::Modified});
            }
            else{
                entries.push_back(common::ComparisonEntry {sourceElement, common::ComparisonStatus::Unchanged});
            }

            current++;

            if(progress){
                progress((current * 100) / total);
            }
        }

        for(const auto& targetElement : target){
            bool isFound = false;

            for(const auto& sourceElement : source){
                if(sourceElement.path == targetElement.path && sourceElement.isDirectory == targetElement.isDirectory){
                    isFound = true;
                    break;
                }
            }

            if(!isFound){
                entries.push_back(common::ComparisonEntry {targetElement, common::ComparisonStatus::Removed});
            }
            
            current++;

            if(progress){
                progress((current * 100) / total);
            }
        }
        std::sort(entries.begin(), entries.end(), [](const common::ComparisonEntry& entry1, const common::ComparisonEntry& entry2){
            return entry1.info.isDirectory > entry2.info.isDirectory;
        });
        return entries;
    }

    std::string core::DirectoryComparer::computeSHA256(const std::filesystem::path& filePath)
    {
        std::ifstream file(filePath, std::ios::binary);

        if (!file)
        {
            throw std::runtime_error("Cannot open file: " + filePath.string());
        }

        EVP_MD_CTX* context = EVP_MD_CTX_new();

        if (context == nullptr)
        {
            throw std::runtime_error("Failed to create EVP context.");
        }

        if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1)
        {
            EVP_MD_CTX_free(context);
            throw std::runtime_error("DigestInit failed.");
        }

        std::array<char, 4096> buffer;

        while (file.good())
        {
            file.read(buffer.data(), buffer.size());

            std::streamsize bytesRead = file.gcount();

            if (bytesRead > 0)
            {
                if (EVP_DigestUpdate(context, buffer.data(), bytesRead) != 1)
                {
                    EVP_MD_CTX_free(context);
                    throw std::runtime_error("DigestUpdate failed.");
                }
            }
        }

        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int hashLength = 0;

        if (EVP_DigestFinal_ex(context, hash, &hashLength) != 1)
        {
            EVP_MD_CTX_free(context);
            throw std::runtime_error("DigestFinal failed.");
        }

        EVP_MD_CTX_free(context);

        std::ostringstream oss;

        for (unsigned int i = 0; i < hashLength; ++i)
        {
            oss << std::hex
                << std::setw(2)
                << std::setfill('0')
                << static_cast<int>(hash[i]);
        }

        return oss.str();
    }
}