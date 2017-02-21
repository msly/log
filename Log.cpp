#include "Log.h"
#include <iostream>

namespace spdlog
{
	namespace sinks
	{

		template <class Mutex>
		class stdout_sink_no_debug : public base_sink<Mutex>
		{
			using MyType = stdout_sink_no_debug<Mutex>;
		public:
			stdout_sink_no_debug() {}
			static std::shared_ptr<MyType> instance()
			{
				static std::shared_ptr<MyType> instance = std::make_shared<MyType>();
				return instance;
			}

			void _sink_it(const details::log_msg& msg) override
			{
				if (msg.level >= level::info) {
					fwrite(msg.formatted.data(), sizeof(char), msg.formatted.size(), stdout);
					flush();
				}
			}

			void flush() override
			{
				fflush(stdout);
			}
		};

		typedef stdout_sink_no_debug<details::null_mutex> stdout_sink_no_debug_st; 
		typedef stdout_sink_no_debug<std::mutex> stdout_sink_no_debug_mt; // 多线程安全
	}
}

CLog::CLog() {

    try {
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
        sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>("logfile", "txt", 0, 0));
        auto combined_logger = std::make_shared<spdlog::logger>("log", begin(sinks), end(sinks));
        //combined_logger->flush_on(spdlog::level::err); // trigger flush if the log severity is error or higher
        spdlog::register_logger(combined_logger);

        //[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v
        spd::set_pattern("[%H:%M:%S %e] [%L] [%t] %v");
		spd::set_level(spd::level::debug);
    } catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log failed: " << ex.what() << std::endl;
    }

}


CLog::~CLog() {
    // Under VisualStudio, this must be called before main finishes to workaround a known VS issue
    spdlog::drop_all();
}

CLog nono;
