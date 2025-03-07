#ifndef GENERIC_TOOLS_HPP
#define GENERIC_TOOLS_HPP
#pragma once

#include <random>
#include <ctime>
#include <windows.h>
#include <MMsystem.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <atomic>


extern std::atomic<bool> should_stop;

namespace generic_tools {
	int random_number(int limit);
	int random_number(int limit_start, int limit_end);
	void song(const std::string& text);
	void song_loop(const std::string& text);
	void start_song(const std::string& text);
	void stop_song();
	void clear_console();
	void sleep(int time);
	void wait_for_enter();
}
#endif //GENERIC_TOOLS_HPP