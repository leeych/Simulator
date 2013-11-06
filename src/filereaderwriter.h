#ifndef FILEREADERWRITER_H
#define FILEREADERWRITER_H

#include "tscparam.h"
#include "mdatabase.h"
#include <stdio.h>
#include <fstream>
#include <string>


class FileReaderWriter
{
    
public:
    FileReaderWriter();
    ~FileReaderWriter();

    void InitDatabase(MDatabase *db_ptr);
    MDatabase *defaultDatabase();

    bool ReadFile(MDatabase *db, const char* file_path);
    bool ReadFile(const char *file_path, TSCParam &param);
    bool WriteFile(const char* file_path);
    bool WriteFile(const TSCParam &param, const char *file_path);
    void SetTSCParam(const TSCParam &param);

private:
	void ResetParam();

private:
    MDatabase *db_;
    TSCParam tsc_param_;

    std::string open_file_path_;
    std::string new_file_path_;
    std::string write_file_path_;
};

#endif // FILEREADERWRITER_H
