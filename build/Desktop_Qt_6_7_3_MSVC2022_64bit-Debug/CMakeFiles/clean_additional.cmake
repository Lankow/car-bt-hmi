# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appcar-bt-hmi_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appcar-bt-hmi_autogen.dir\\ParseCache.txt"
  "appcar-bt-hmi_autogen"
  )
endif()
