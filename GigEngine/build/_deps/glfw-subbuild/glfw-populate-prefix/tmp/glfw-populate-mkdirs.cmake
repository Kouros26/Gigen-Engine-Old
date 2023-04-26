# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/Work/Moteur/GigEngine/build/_deps/glfw-src"
  "E:/Work/Moteur/GigEngine/build/_deps/glfw-build"
  "E:/Work/Moteur/GigEngine/build/_deps/glfw-subbuild/glfw-populate-prefix"
  "E:/Work/Moteur/GigEngine/build/_deps/glfw-subbuild/glfw-populate-prefix/tmp"
  "E:/Work/Moteur/GigEngine/build/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp"
  "E:/Work/Moteur/GigEngine/build/_deps/glfw-subbuild/glfw-populate-prefix/src"
  "E:/Work/Moteur/GigEngine/build/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/Work/Moteur/GigEngine/build/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/Work/Moteur/GigEngine/build/_deps/glfw-subbuild/glfw-populate-prefix/src/glfw-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()