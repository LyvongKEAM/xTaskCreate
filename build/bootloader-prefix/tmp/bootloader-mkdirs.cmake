# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/WONG/.espressif/frameworks/esp-idf-v5.3/components/bootloader/subproject"
  "C:/Users/WONG/esp-idf/Assigment/Tasks/build/bootloader"
  "C:/Users/WONG/esp-idf/Assigment/Tasks/build/bootloader-prefix"
  "C:/Users/WONG/esp-idf/Assigment/Tasks/build/bootloader-prefix/tmp"
  "C:/Users/WONG/esp-idf/Assigment/Tasks/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/WONG/esp-idf/Assigment/Tasks/build/bootloader-prefix/src"
  "C:/Users/WONG/esp-idf/Assigment/Tasks/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/WONG/esp-idf/Assigment/Tasks/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/WONG/esp-idf/Assigment/Tasks/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
