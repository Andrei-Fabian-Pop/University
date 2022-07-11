# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/a8_9_AndreiFabianPop_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/a8_9_AndreiFabianPop_autogen.dir/ParseCache.txt"
  "a8_9_AndreiFabianPop_autogen"
  )
endif()
