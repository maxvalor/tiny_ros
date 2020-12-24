# tiny_ros
The tiny_ros is a tiny ros-like frameworks that supports publish/subscribe communication between multi-thread.

The only thing you should do is to include the tiny_ros.h into in your project.

You can build the sample with three tools: cmake, bazel and cazel, with the following commands:

## cmake

    mkdir build
    cd build
    cmake .. && make -j
  
## bazel

    bazel build ...
 
## cazel

    cazel build tiny_ros
