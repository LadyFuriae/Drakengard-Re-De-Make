#include "generic_tools.hpp"
std::atomic<bool> should_stop(false);
int generic_tools::random_number(int limit) {
	srand(time(0));
	int num = 0 + rand() % limit;
	return num;
}

int generic_tools::random_number(int limit_start, int limit_end) {
	srand(time(0));
	int num = limit_start + rand() % (limit_end - limit_start + 1);
	return num;
}

void generic_tools::song(const std::string& text) {
	std::wstring wide_text(text.begin(), text.end());
	if (!PlaySound(wide_text.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
		std::cerr << "Error al reproducir:" << text << "\n";
	}
}

void generic_tools::song_loop(const std::string& text = "NULL") {
	
	std::wstring wide_text(text.begin(), text.end());
	if (!should_stop) {
		if (!PlaySound(wide_text.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP)) {
			std::cerr << "Error al reproducir:" << text << "\n";
		}
	}
	if (should_stop) {
		PlaySound(NULL, NULL, 0);
	}
}

void generic_tools::start_song(const std::string& text) {
	should_stop = false;
	std::thread(song_loop, text).detach();
}

void generic_tools::stop_song() {
	should_stop = true;
	song_loop();
	
}

void generic_tools::clear_console() {
	system("cls");
}

void generic_tools::sleep(int time) {
	std::this_thread::sleep_for(std::chrono::seconds(time));
}

void generic_tools::wait_for_enter() {
	std::cout << "\nPresiona enter para salir";
	std::cin.ignore();
	while (std::cin.get() != '\n');
}