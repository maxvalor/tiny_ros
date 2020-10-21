# sample.cmake

include_directories(
  include
  sample/pub_sub
)

add_executable(sample_ps sample/pub_sub/main.cpp)
add_executable(sample_sc sample/srv_call/main.cpp)
target_link_libraries(sample_ps
  pthread
)
target_link_libraries(sample_sc
  pthread
)
