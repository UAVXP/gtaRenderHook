/**
 * @brief This file conatains logging utility for RenderHook rendering engine
 *
 * @file DebugLogger.h
 * @author Peter Georgievsky
 * @date 2018-07-20
 *
 * We use static class DebugLogger to write logs and errors to rhdebug.log
 * file(by default) and IDE console.
 */
#pragma once
#include "Engine/Common/types/string_typedefs.h"
#include <array>
#include <memory>

/// converts from string to RH string
rh::engine::String ToRHString( const std::string &t_str );

/// converts from wide string to RH string
rh::engine::String ToRHString( const std::wstring &t_str );

/// converts from RH string to string
std::string FromRHString( const rh::engine::String &t_str );

/// converts from RH string to string
std::wstring FromRHString_( const rh::engine::String &t_str );

namespace rh::debug
{

/**
 * @brief Logging level enum
 *
 */
enum class LogLevel : uint8_t
{
    ConstrDestrInfo = 0,
    Info,
    Warning,
    Error
};

/**
 * @brief Debug logger class
 *
 * Contains static methods for logging debug info
 */
class DebugLogger
{
  public:
    /**
     * @brief Initializes DebugLogger
     *
     * @param fileName - path to log file
     * @param minLogLevel - minimum logging level
     *
     * *If path is empty log won't be written to file.
     */
    static void Init( const engine::String &fileName, LogLevel minLogLevel );

    /**
     * @brief Prints Log message to console and debug file if min log level is
     * greater than logLevel
     *
     * @param msg - log message
     * @param logLevel - message logging level
     */
    static void Log( const engine::String &msg,
                     LogLevel              logLevel = LogLevel::Info );

    /**
     * @brief Prints formatted Log message to console and debug file
     *
     * @param msg - error message
     */
    template <typename... Args>
    static void LogFmt( const engine::String &msg,
                        LogLevel logLevel = LogLevel::Info, Args... args )
    {
        if ( logLevel < m_MinLogLevel )
            return;
        static std::array<char, 4096> temp_buff{};
        std::unique_ptr<char[]>       dyn_buf;

        size_t size = snprintf( nullptr, 0, msg.c_str(), args... ) + 1;

        char *data_ptr;

        // Use bigger heap buffer for big strings, should be rare
        if ( size > 4096 )
        {
            dyn_buf  = std::make_unique<char[]>( size );
            data_ptr = dyn_buf.get();
        }
        else
            data_ptr = temp_buff.data();

        snprintf( data_ptr, size, msg.c_str(), args... );

        Log( std::string( data_ptr, data_ptr + size - 1 ) );
    }

    /**
     * @brief Prints Error message to console and debug file
     *
     * @param msg - log message
     */
    static void Error( const engine::String &msg );

    static void SyncDebugFile();

    /**
     * @brief Prints formatted Error message to console and debug file
     *
     * @param msg - error message
     */
    template <typename... Args>
    static void ErrorFmt( const engine::String &msg, Args... args )
    {
        static std::array<char, 4096> temp_buff{};
        std::unique_ptr<char[]>       dyn_buf;

        size_t size = snprintf( nullptr, 0, msg.c_str(), args... ) + 1;

        char *data_ptr;

        // Use bigger heap buffer for big strings, should be rare
        if ( size > 4096 )
        {
            dyn_buf  = std::make_unique<char[]>( size );
            data_ptr = dyn_buf.get();
        }
        else
            data_ptr = temp_buff.data();

        snprintf( data_ptr, size, msg.c_str(), args... );

        Error( std::string( data_ptr, data_ptr + size - 1 ) );
    }

  private:
    static std::unique_ptr<engine::OutFileStream> m_pLogStream;

  public:
    static engine::String m_sFileName;
    static LogLevel       m_MinLogLevel;
    static void *         g_hDebugPipeHandle;
    static void *         g_hDebugPipeReadHandle;
    static void *         GetDebugFileHandle();
};
} // namespace rh::debug

#ifdef _DEBUG

#define RH_ASSERT( expr )                                                      \
    if ( !( expr ) )                                                           \
    {                                                                          \
        rh::debug::DebugLogger::Error( TEXT( "Assertion failed: " ) +          \
                                       ToRHString( #expr ) );                  \
    }

#else

#define RH_ASSERT( expr )

#endif // DEBUG
