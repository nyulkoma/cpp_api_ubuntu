#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <time.h>

/**
 * Convert the input to a string using its name.
 * @param name Name of the variable.
 * @returns The created string.
 */
#ifndef stringify
#define stringify(name) std::string(#name)
#endif

class Logger {
 private:
  // An array which contains the appropriate function
  // definitions to convert an enum to string.
  static std::string appTypeToString[2];

  /**
   * Create a sink which will handle the logging to the console.
   *
   * @param log_level Level of logging. Options:
   * trace, debug, info, warn, err, critical and off.
   * @returns Shared pointer to the created console sink.
   */
  static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> createConsoleSink(
      const spdlog::level::level_enum log_level);

  /**
   * Create a sink which will handle the logging to the file.
   *
   * @param log_level Level of logging. Options:
   * trace, debug, info, warn, err, critical and off.
   * @param file_path Path of the logging file.
   * @param app_name Name of your application which will be built to the file
   * name.
   * @returns Shared pointer to the created file sink.
   */
  static std::shared_ptr<spdlog::sinks::basic_file_sink_mt> createFileSink(
      const spdlog::level::level_enum log_level, const std::string file_path,
      const std::string app_name);

  /**
   * Register the given logger to the global registy of spdlog only if a logger
   * with the same name does not exist already.
   *
   * @param logger Shared pointer to the created logger.
   */
  static void registerLogger(std::shared_ptr<spdlog::logger> logger);

 public:
  // Possible types of your application.
  enum appType {
    grpc_sender,
    grpc_receiver
  };

  /**
   * Get the globally registered logger.
   *
   * @param app_type Type of your application. Check appType enum for possible
   * values.
   * @returns Shared pointer to the registered logger or null pointer if it does
   * not exist.
   */
  static std::shared_ptr<spdlog::logger> getRegisteredLogger(
      const appType app_type);

  /**
   * Set logging only to the console.
   *
   * @param log_level Level of logging. Options:
   * trace, debug, info, warn, err, critical and off.
   * @param app_type Type of your application. Check appType enum for possible
   * values.
   * @returns Shared pointer to the created logger.
   */
  static std::shared_ptr<spdlog::logger> setLoggingToConsole(
      const spdlog::level::level_enum log_level, const appType app_type);

  /**
   * Set logging only to a file.
   *
   * @param log_level Level of logging. Options:
   * trace, debug, info, warn, err, critical and off.
   * @param file_path Path of the logging file.
   * @param app_type Type of your application. Check appType enum for possible
   * values.
   * @returns Shared pointer to the created logger.
   */
  static std::shared_ptr<spdlog::logger> setLoggingToFile(
      const spdlog::level::level_enum log_level, const std::string file_path,
      const appType app_type);

  /**
   * Set logging to the console and to a file also with the same logging level.
   *
   * @param log_level Level of logging. Options:
   * trace, debug, info, warn, err, critical and off.
   * @param file_path Path of the logging file.
   * @param app_type Type of your application. Check appType enum for possible
   * values.
   * @returns Shared pointer to the created logger.
   */
  static std::shared_ptr<spdlog::logger> setLoggingToConsoleAndFile(
      const spdlog::level::level_enum log_level, const std::string file_path,
      const appType app_type);

  /**
   * Set logging to the console and to a file also with different logging
   * levels.
   *
   * @param console_log_level, file_log_level Level of logging to the console
   * and to the file. Options: trace, debug, info, warn, err, critical and off.
   * @param file_path Path of the logging file.
   * @param app_type Type of your application. Check appType enum for possible
   * values.
   * @returns Shared pointer to the created logger.
   */
  static std::shared_ptr<spdlog::logger> setLoggingToConsoleAndFile(
      const spdlog::level::level_enum console_log_level,
      const spdlog::level::level_enum file_log_level,
      const std::string file_path, const appType app_type);
};

#endif  // LOGGER_HPP
