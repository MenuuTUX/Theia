// This script creates log messages with the current date and time.
// Made by: @MenuuTUX with ❤️ on GitHub
// Check out: https://github.com/MenuuTUX

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

/**
 * Logs a message with the current date and time.
 *
 * @param message The message to be logged.
 */

void log(const std::string& message) {
    // Get the current time
    auto now = std::chrono::system_clock::now();

    // Convert the current time to the local time
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&time);

    // Get the milliseconds part of the current time
    std::chrono::milliseconds ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

    // Format the time string as "YYYY-MM-DD HH:MM:SS"
    char buffer[20];
    std::strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", &local_time);

    // Print the log message with the current time in the format "[YYYY-MM-DD HH:MM:SS,sss] message"
    std::cout << "[" << buffer << "," << std::setfill('0') << std::setw(3)
              << ms.count() << "] " << message << std::endl;
}
