cmake_minimum_required(VERSION 3.12)

project(deusmagi-toolkit C)
set(DEUSMAGI_TOOLKIT deusmagi-toolkit)

set(CMAKE_SKIP_INSTALL_RULES true)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
set(HAVE_CURL true)

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIR})
set(HAVE_ZLIB true)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
set(HAVE_X11 true)
    
find_library(X11_XMU_LIBRARY Xmu /usr/openwin/lib REQUIRED)
set(HAVE_X11_XMU true)

find_library(MATH_LIBRARY m)

find_library(CRYPT_LIBRARY crypt)
set(HAVE_CRYPT true)

find_library(READLINE_LIBRARY readline)
set(HAVE_READLINE true)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

find_package(Threads REQUIRED)

include(CheckIncludeFiles)
include(CheckFunctionExists)

set(CMAKE_REQUIRED_INCLUDES "math.h")

check_include_files(fcntl.h HAVE_FCNTL_H)
check_include_files(unistd.h HAVE_UNISTD_H)
check_include_files(sys/time.h HAVE_SYS_TIME_H)
check_include_files(time.h HAVE_TIME_H)
check_include_files(stddef.h HAVE_STDDEF_H)
check_include_files(dirent.h HAVE_DIRENT_H)
check_include_files(sys/ndir.h HAVE_SYS_NDIR_H)
check_include_files(sys/dir.h HAVE_SYS_DIR_H)
check_include_files(sys/socket.h HAVE_SYS_SOCKET_H)
check_include_files(ndir.h HAVE_NDIR_H)
check_include_files(crypt.h HAVE_CRYPT_H)
check_include_files(arpa/inet.h HAVE_ARPA_INET_H)
check_include_files(valgrind/valgrind.h HAVE_VALGRIND_H)

check_function_exists(strerror HAVE_STRERROR)
check_function_exists(strcasecmp HAVE_STRCASECMP)
check_function_exists(strncasecmp HAVE_STRNCASECMP)
check_function_exists(stricmp HAVE_STRICMP)
check_function_exists(strnicmp HAVE_STRNICMP)
check_function_exists(srandom HAVE_SRANDOM)
check_function_exists(srand48 HAVE_SRAND48)
check_function_exists(srand HAVE_SRAND)
check_function_exists(getdtablesize HAVE_GETDTABLESIZE)
check_function_exists(sysconf HAVE_SYSCONF)
check_function_exists(gettimeofday HAVE_GETTIMEOFDAY)
check_function_exists(tempnam HAVE_TEMPNAM)
check_function_exists(strcasestr HAVE_STRCASESTR)
check_function_exists(strdup HAVE_STRDUP)
check_function_exists(strndup HAVE_STRNDUP)
check_function_exists(strtok_r HAVE_STRTOK_R)
check_function_exists(sigaction HAVE_SIGACTION)
check_function_exists(getline HAVE_GETLINE)
check_function_exists(usleep HAVE_USLEEP)
check_function_exists(strnlen HAVE_STRNLEN)
check_function_exists(mkstemp HAVE_MKSTEMP)
check_function_exists(sincos HAVE_SINCOS)
check_function_exists(pselect HAVE_PSELECT)
check_function_exists(getaddrinfo HAVE_GETADDRINFO)

configure_file(cmake.h.def cmake.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(TOOLKIT_SOURCES
    binreloc.c
    clioptions.c
    colorspace.c
    console.c
    curl.c
    datetime.c
    logger.c
    math.c
    memory.c
    mempool.c
    packet.c
    path.c
    pbkdf2.c
    porting.c
    process.c
    sha1.c
    shstr.c
    signals.c
    socket.c
    socket_crypto.c
    stringbuffer.c
    string.c
    toolkit.c
    x11.c
)

add_library(${DEUSMAGI_TOOLKIT} ${TOOLKIT_SOURCES})

target_link_libraries(${DEUSMAGI_TOOLKIT} ${CURL_LIBRARIES})
target_link_libraries(${DEUSMAGI_TOOLKIT} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${DEUSMAGI_TOOLKIT} ${ZLIB_LIBRARIES})
target_link_libraries(${DEUSMAGI_TOOLKIT} ${MATH_LIBRARY})
target_link_libraries(${DEUSMAGI_TOOLKIT} ${X11_LIBRARIES})
target_link_libraries(${DEUSMAGI_TOOLKIT} ${X11_XMU_LIBRARY})
target_link_libraries(${DEUSMAGI_TOOLKIT} ${CRYPT_LIBRARY})
target_link_libraries(${DEUSMAGI_TOOLKIT} ${READLINE_LIBRARY})
target_link_libraries(${DEUSMAGI_TOOLKIT} ${OPENSSL_LIBRARIES})
