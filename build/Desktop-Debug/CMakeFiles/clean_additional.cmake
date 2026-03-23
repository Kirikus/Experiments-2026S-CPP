# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Experiments_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Experiments_autogen.dir/ParseCache.txt"
  "Experiments_autogen"
  )
endif()
