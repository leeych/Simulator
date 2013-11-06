#include "filereaderwriter.h"
#include <memory.h>
#include <QDebug>

FileReaderWriter::FileReaderWriter()
{
    db_ = MDatabase::GetInstance();
}

FileReaderWriter::~FileReaderWriter()
{
}

void FileReaderWriter::InitDatabase(MDatabase *db_ptr)
{
    db_ = db_ptr;
}

MDatabase* FileReaderWriter::defaultDatabase()
{
    db_ = MDatabase::GetInstance();
    return db_;
}

bool FileReaderWriter::ReadFile(MDatabase *db, const char* file_path)
{
	open_file_path_ = std::string(file_path);
	FILE *fp = fopen(file_path, "rb");
	if (fp == NULL)
	{
		return false;
	}
    db_ = db;
	ResetParam();
	fseek(fp, 0, SEEK_SET);
	fread(&tsc_param_.tsc_header_, sizeof(tsc_param_.tsc_header_), 1, fp);
	fread(&tsc_param_.unit_param_, sizeof(tsc_param_.unit_param_), 1, fp);
	fread(&tsc_param_.sched_table_, sizeof(tsc_param_.sched_table_), 1, fp);
	fread(&tsc_param_.time_section_table_, sizeof(tsc_param_.time_section_table_), 1, fp);
	fread(&tsc_param_.timing_plan_table_, sizeof(tsc_param_.timing_plan_table_), 1, fp);
	fread(&tsc_param_.stage_timing_table_, sizeof(tsc_param_.stage_timing_table_), 1, fp);
	fread(&tsc_param_.phase_table_, sizeof(tsc_param_.phase_table_), 1, fp);
	fread(&tsc_param_.phase_conflict_table_, sizeof(tsc_param_.phase_conflict_table_), 1, fp);
	fread(&tsc_param_.channel_table_, sizeof(tsc_param_.channel_table_), 1, fp);
	fread(&tsc_param_.channel_hint_table_, sizeof(tsc_param_.channel_hint_table_), 1, fp);
	fread(&tsc_param_.detector_table_, sizeof(tsc_param_.detector_table_), 1, fp);
	db_->set_tsc_header(tsc_param_.tsc_header_);
	db_->set_unit_table(tsc_param_.unit_param_);
	db_->set_schedule_table(tsc_param_.sched_table_);
	db_->set_timesection_table(tsc_param_.time_section_table_);
	db_->set_timing_table(tsc_param_.timing_plan_table_);
	db_->set_phasetiming_table(tsc_param_.stage_timing_table_);
	db_->set_phase_table(tsc_param_.phase_table_);
	db_->set_phase_conflict_table(tsc_param_.phase_conflict_table_);
	db_->set_channel_table(tsc_param_.channel_table_);
	db_->set_channel_hint_table(tsc_param_.channel_hint_table_);
	db_->set_detector_table(tsc_param_.detector_table_);

	fclose(fp);
    return true;
}

bool FileReaderWriter::ReadFile(const char *file_path, TSCParam &param)
{
    open_file_path_ = std::string(file_path);
    FILE *fp = fopen(file_path, "rb");
    if (fp == NULL)
    {
        qDebug() << file_path << " file pointer is null";
        return false;
    }
    ResetParam();
    fseek(fp, 0, SEEK_SET);
    fread(&param.tsc_header_, sizeof(tsc_param_.tsc_header_), 1, fp);
    fread(&param.unit_param_, sizeof(tsc_param_.unit_param_), 1, fp);
    fread(&param.sched_table_, sizeof(tsc_param_.sched_table_), 1, fp);
    fread(&param.time_section_table_, sizeof(tsc_param_.time_section_table_), 1, fp);
    fread(&param.timing_plan_table_, sizeof(tsc_param_.timing_plan_table_), 1, fp);
    fread(&param.stage_timing_table_, sizeof(tsc_param_.stage_timing_table_), 1, fp);
    fread(&param.phase_table_, sizeof(tsc_param_.phase_table_), 1, fp);
    fread(&param.phase_conflict_table_, sizeof(tsc_param_.phase_conflict_table_), 1, fp);
    fread(&param.channel_table_, sizeof(tsc_param_.channel_table_), 1, fp);
    fread(&param.channel_hint_table_, sizeof(tsc_param_.channel_hint_table_), 1, fp);
    fread(&param.detector_table_, sizeof(tsc_param_.detector_table_), 1, fp);

    fclose(fp);
    return true;
}

bool FileReaderWriter::WriteFile(const char* file_path)
{
    FILE *fp = fopen(file_path, "wb+");
    fseek(fp, 0, SEEK_SET);
    memcpy(&tsc_param_.tsc_header_, &db_->get_tsc_header(), sizeof(tsc_param_.tsc_header_));
    memcpy(&tsc_param_.unit_param_, &db_->get_unit_table(), sizeof(tsc_param_.unit_param_));
    memcpy(&tsc_param_.sched_table_, &db_->get_schedule(), sizeof(tsc_param_.sched_table_));
    memcpy(&tsc_param_.time_section_table_, &db_->get_timesection(), sizeof(tsc_param_.time_section_table_));
    memcpy(&tsc_param_.timing_plan_table_, &db_->get_timingplan(), sizeof(tsc_param_.timing_plan_table_));
    memcpy(&tsc_param_.stage_timing_table_, &db_->get_timeconfig(), sizeof(tsc_param_.stage_timing_table_));
    memcpy(&tsc_param_.phase_table_, &db_->get_phase(), sizeof(tsc_param_.phase_table_));
    memcpy(&tsc_param_.phase_conflict_table_, &db_->get_phase_err(), sizeof(tsc_param_.phase_conflict_table_));
    memcpy(&tsc_param_.channel_table_, &db_->get_channel(), sizeof(tsc_param_.channel_table_));
    memcpy(&tsc_param_.channel_hint_table_, &db_->get_channel_hint(), sizeof(tsc_param_.channel_hint_table_));
    memcpy(&tsc_param_.detector_table_, &db_->get_detector(), sizeof(tsc_param_.detector_table_));

    size_t header = fwrite(&tsc_param_.tsc_header_, sizeof(tsc_param_.tsc_header_), 1, fp);
    size_t unit = fwrite(&tsc_param_.unit_param_, sizeof(tsc_param_.unit_param_), 1, fp);
    size_t sched = fwrite(&tsc_param_.sched_table_, sizeof(tsc_param_.sched_table_), 1, fp);
    size_t time_section = fwrite(&tsc_param_.time_section_table_, sizeof(tsc_param_.time_section_table_), 1, fp);
    size_t timing = fwrite(&tsc_param_.timing_plan_table_, sizeof(tsc_param_.timing_plan_table_), 1, fp);
    size_t stage_timing = fwrite(&tsc_param_.stage_timing_table_, sizeof(tsc_param_.stage_timing_table_), 1, fp);
    size_t phase_table = fwrite(&tsc_param_.phase_table_, sizeof(tsc_param_.phase_table_), 1, fp);
    size_t phase_conflict = fwrite(&tsc_param_.phase_conflict_table_, sizeof(tsc_param_.phase_conflict_table_), 1, fp);
    size_t channel_table = fwrite(&tsc_param_.channel_table_, sizeof(tsc_param_.channel_table_), 1, fp);
    size_t channel_hint = fwrite(&tsc_param_.channel_hint_table_, sizeof(tsc_param_.channel_hint_table_), 1, fp);
    size_t detector = fwrite(&tsc_param_.detector_table_, sizeof(tsc_param_.detector_table_), 1, fp);
	//fflush(fp);
	fclose(fp);

	if (header == 0 || unit == 0 || sched == 0 || time_section == 0 || timing == 0 || stage_timing == 0
		|| phase_table == 0 || phase_conflict == 0 || channel_table == 0 || channel_hint == 0 || detector == 0)
	{
		return false;
	}
    return true;
}

bool FileReaderWriter::WriteFile(const TSCParam &param, const char *file_path)
{
    FILE *fp = fopen(file_path, "wb+");
    fseek(fp, 0, SEEK_SET);
    size_t header = fwrite(&param.tsc_header_, sizeof(param.tsc_header_), 1, fp);
    size_t unit = fwrite(&param.unit_param_, sizeof(param.unit_param_), 1, fp);
    size_t sched = fwrite(&param.sched_table_, sizeof(param.sched_table_), 1, fp);
    size_t time_section = fwrite(&param.time_section_table_, sizeof(param.time_section_table_), 1, fp);
    size_t timing = fwrite(&param.timing_plan_table_, sizeof(param.timing_plan_table_), 1, fp);
    size_t stage_timing = fwrite(&param.stage_timing_table_, sizeof(param.stage_timing_table_), 1, fp);
    size_t phase_table = fwrite(&param.phase_table_, sizeof(param.phase_table_), 1, fp);
    size_t phase_conflict = fwrite(&param.phase_conflict_table_, sizeof(param.phase_conflict_table_), 1, fp);
    size_t channel_table = fwrite(&param.channel_table_, sizeof(param.channel_table_), 1, fp);
    size_t channel_hint = fwrite(&param.channel_hint_table_, sizeof(param.channel_hint_table_), 1, fp);
    size_t detector = fwrite(&param.detector_table_, sizeof(param.detector_table_), 1, fp);
    //fflush(fp);
    fclose(fp);

    if (header == 0 || unit == 0 || sched == 0 || time_section == 0 || timing == 0 || stage_timing == 0
        || phase_table == 0 || phase_conflict == 0 || channel_table == 0 || channel_hint == 0 || detector == 0)
    {
        return false;
    }
    return true;
}

void FileReaderWriter::SetTSCParam(const TSCParam &param)
{
    memcpy(&tsc_param_, &param, sizeof(param));
}

void FileReaderWriter::ResetParam()
{
	memset(&tsc_param_.tsc_header_, 0x00, sizeof(tsc_param_.tsc_header_));
	char company_name[9]={'C','H','A','O','Y','U','A','N','\0'};
	char product_name[4]={'T','S','M','\0'}; //Traffic Signal Machine
	char product_version[6]={'1','.','0','.','0','\0'};
	memcpy(&tsc_param_.tsc_header_.CompanyName, &company_name, sizeof(company_name));
	memcpy(&tsc_param_.tsc_header_.ProductName, &product_name, sizeof(product_name));
	memcpy(&tsc_param_.tsc_header_.ProductId, &product_version, sizeof(product_version));

	memset(&tsc_param_.unit_param_, 0x00, sizeof(tsc_param_.unit_param_));
	memset(&tsc_param_.sched_table_, 0x00, sizeof(tsc_param_.sched_table_));
	memset(&tsc_param_.time_section_table_, 0x00, sizeof(tsc_param_.time_section_table_));
	memset(&tsc_param_.timing_plan_table_, 0x00, sizeof(tsc_param_.timing_plan_table_));
	memset(&tsc_param_.stage_timing_table_, 0x00, sizeof(tsc_param_.stage_timing_table_));
	memset(&tsc_param_.phase_table_, 0x00, sizeof(tsc_param_.phase_table_));
	memset(&tsc_param_.phase_conflict_table_, 0x00, sizeof(tsc_param_.phase_conflict_table_));
	memset(&tsc_param_.channel_table_, 0x00, sizeof(tsc_param_.channel_table_));
	memset(&tsc_param_.channel_hint_table_, 0x00, sizeof(tsc_param_.channel_hint_table_));
	memset(&tsc_param_.detector_table_, 0x00, sizeof(tsc_param_.detector_table_));
}
