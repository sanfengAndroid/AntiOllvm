cmake_minimum_required(VERSION 3.6.0)

project(OpenSSL-Test)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/openssl/include
)


 
if(CMAKE_SYSTEM_PROCESSOR MATCHES "amd64.*|x86_64.*|AMD64.*|x64.*")
  set(LIBRARY_X64, 1)
  set(LIBRARY_64BIT, 1)
  set(FILE_NAME_SUFFIX "64-x64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i386.*|x86.*")
  set(LIBRARY_X32 1)
  set(LIBRARY_32BIT, 1)
  set(FILE_NAME_SUFFIX "32-x86")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^arm64.*")
  set(LIBRARY_A64, 1)
  set(LIBRARY_64BIT, 1)
  set(FILE_NAME_SUFFIX "64-arm64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(aarch64.*|AARCH64.*)")
  set(LIBRARY_A64, 1)
  set(LIBRARY_64BIT, 1)
  set(FILE_NAME_SUFFIX "64-arm64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm.*|ARM.*)")
  set(LIBRARY_A32, 1)
  set(LIBRARY_32BIT, 1)
  set(FILE_NAME_SUFFIX "32-arm")
else()
  message(FATAL_ERROR "Processor ${CMAKE_SYSTEM_PROCESSOR} configuration error")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "^Android")
  set(FILE_NAME_SUFFIX  "${FILE_NAME_SUFFIX}-android")
  set(SYSTEM_ANDROID 1)
elseif(CMAKE_SYSTEM_NAME MATCHES "^Windows")
  set(FILE_NAME_SUFFIX "${FILE_NAME_SUFFIX}-coff")
  set(SYSTEM_WINDOES 1)
elseif(CMAKE_SYSTEM_NAME MATCHES "^Linux")
  set(FILE_NAME_SUFFIX "${FILE_NAME_SUFFIX}-elf")
  set(SYSTEM_LINUX 1)
elseif(CMAKE_SYSTEM_NAME MATCHES "^iOS")
  set(FILE_NAME_SUFFIX "${FILE_NAME_SUFFIX}-macho-i")
  set(SYSTEM_IOS 1)
elseif(CMAKE_SYSTEM_NAME MATCHES "^macOS")
  set(FILE_NAME_SUFFIX "${FILE_NAME_SUFFIX}-macho-m")
  set(SYSTEM_MACOS 1)
else()
  message (FATAL_ERROR "System name ${CMAKE_SYSTEM_NAME} configuration error")
endif()

message(WARNING, "${FILE_NAME_SUFFIX}")

add_library(openssl-crypto-obf STATIC IMPORTED)
set_target_properties(openssl-crypto-obf PROPERTIES 
IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/openssl/lib${FILE_NAME_SUFFIX}/libcrypto-obf.a)

add_library(openssl-ssl-obf STATIC IMPORTED)
set_target_properties(openssl-ssl-obf PROPERTIES IMPORTED_LOCATION 
${CMAKE_CURRENT_SOURCE_DIR}/openssl/lib${FILE_NAME_SUFFIX}/libssl-obf.a)

add_library(openssl-crypto STATIC IMPORTED)
set_target_properties(openssl-crypto PROPERTIES 
IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/openssl/lib${FILE_NAME_SUFFIX}/libcrypto.a)

add_library(openssl-ssl STATIC IMPORTED)
set_target_properties(openssl-ssl PROPERTIES IMPORTED_LOCATION 
${CMAKE_CURRENT_SOURCE_DIR}/openssl/lib${FILE_NAME_SUFFIX}/libssl.a)

if(SYSTEM_ANDROID)
 add_compile_options( -g0 -ffunction-sections -fdata-sections -fvisibility=hidden -O3)
 add_link_options(-Wl,--gc-sections,--icf=safe,-S)
endif()

add_executable(test-md5-obf test.c)
add_executable(test-md5 test.c)

target_link_libraries(test-md5-obf openssl-crypto-obf)
target_link_libraries(test-md5 openssl-crypto)

install(TARGETS test-md5 test-md5-obf
  LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/lib-${FILE_NAME_SUFFIX}
  RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/binary-${FILE_NAME_SUFFIX}
)