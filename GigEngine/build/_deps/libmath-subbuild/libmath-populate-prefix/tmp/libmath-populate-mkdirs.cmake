# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/Work/Moteur/GigEngine/build/_deps/libmath-src"
  "E:/Work/Moteur/GigEngine/build/_deps/libmath-build"
  "E:/Work/Moteur/GigEngine/build/_deps/libmath-subbuild/libmath-populate-prefix"
  "E:/Work/Moteur/GigEngine/build/_deps/libmath-subbuild/libmath-populate-prefix/tmp"
  "E:/Work/Moteur/GigEngine/build/_deps/libmath-subbuild/libmath-populate-prefix/src/libmath-populate-stamp"
  "E:/Work/Moteur/GigEngine/build/_deps/libmath-subbuild/libmath-populate-prefix/src"
  "E:/Work/Moteur/GigEngine/build/_deps/libmath-subbuild/libmath-populate-prefix/src/libmath-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/Work/Moteur/GigEngine/build/_deps/libmath-subbuild/libmath-populate-prefix/src/libmath-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/Work/Moteur/GigEngine/build/_deps/libmath-subbuild/libmath-populate-prefix/src/libmath-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
