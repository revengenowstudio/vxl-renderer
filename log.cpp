#include "log.h"

#include <Ole2.h>

std::ofstream logger::_logfile;
logger logger::instance;

bool logger::initialize()
{
	if (_logfile.is_open())
	{
		return true;
	}

	static const std::string log_path = ".\\debug_logs\\";
	auto current = std::chrono::system_clock::now();
	auto current_t = std::chrono::system_clock::to_time_t(current);

	if (!std::filesystem::exists(log_path))
	{
		std::filesystem::create_directories(log_path);
		if (!std::filesystem::exists(log_path))
		{
			return false;
		}
	}

	std::stringstream time_string;
	time_string << std::put_time(std::localtime(&current_t), "%F-%H-%M-%S");
	std::string filename = log_path + "debug-log " + time_string.str() + ".log";

	_logfile.open(filename.c_str());
	return _logfile.is_open();
}

void logger::uninitialize()
{
	if (_logfile)
	{
		_logfile.close();
	}
}
