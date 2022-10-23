#pragma once
#include "Log.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#define format fmt::format

class CodeGenerator {
  using Path = std::filesystem::path;
  std::stringstream FileBuffer;
  const Path Dir;
  const std::string FileName;
  const std::string FileID;

public:
  explicit CodeGenerator(const Path &OriginalPath)
      : FileID(GetFileID(OriginalPath)),
        FileName(OriginalPath.stem().string() + ".generated.h"),
        Dir(OriginalPath.parent_path()) {

    if (is_directory(OriginalPath)) {
      Loge("not the target source file {}", OriginalPath.string());
      exit(-1);
    }

    FileBuffer << "/*=========================================================="
                  "=================\n"
                  "Generated code exported from EngineHeaderTool.\n"
                  "DO NOT modify this manually! Edit the corresponding .h "
                  "files instead!\n"
                  "============================================================"
                  "===============*/\n\n";

    FileBuffer << R"(#include "UObject/Public/ObjectMacros.h")"
               << "\n\n";

    // CURRENT_FILE_ID
    AddRewriteDefine("CURRENT_FILE_ID", FileID);
  }

  static std::string GetFileID(const std::filesystem::path &FilePath) {
    std::string FileID = FilePath.relative_path().string();
    std::replace(FileID.begin(), FileID.end(), '/', '_');
    std::replace(FileID.begin(), FileID.end(), '.', '_');
    return FileID;
  }

  void AddUnDefine(const std::string &Name) {
    FileBuffer << format("#undef {}\n\n", Name);
  }

  void AddDefine(const std::string &Name, const std::string &Body) {
    FileBuffer << format("#define {} {}\n\n", Name, Body);
  }

  void AddRewriteDefine(const std::string &Name, const std::string &Body) {
    FileBuffer << format("#undef {}\n", Name);
    FileBuffer << format("#define {} {}\n\n", Name, Body);
  }

  void AddGeneratedBody(int32_t LineNumber) {
    auto defineName = format("{}_{}_GENERATED_BODY", FileID, LineNumber);
    AddDefine(defineName, "");
  }

  void Write() {
    std::ofstream File;
    File.open(Dir / FileName, std::ios::ate);
    if (errno) {
      LogSystemCallError();
      exit(-1);
    }
    File << FileBuffer.str();
    std::cout << FileBuffer.str() << std::endl;
  }
};