# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/app/build/Desktop-Debug/_deps/qcustomplot-src"
  "/app/build/Desktop-Debug/_deps/qcustomplot-build"
  "/app/build/Desktop-Debug/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix"
  "/app/build/Desktop-Debug/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix/tmp"
  "/app/build/Desktop-Debug/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix/src/qcustomplot-populate-stamp"
  "/app/build/Desktop-Debug/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix/src"
  "/app/build/Desktop-Debug/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix/src/qcustomplot-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/app/build/Desktop-Debug/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix/src/qcustomplot-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/app/build/Desktop-Debug/_deps/qcustomplot-subbuild/qcustomplot-populate-prefix/src/qcustomplot-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
