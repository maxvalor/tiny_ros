package(
    default_visibility = ["//visibility:public"],
)

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
  name = "libtiny_ros",
  includes = ["include"],
  srcs = [
    "include/tiny_ros/tiny_ros.h",
  ],
  linkopts = ["-lpthread"],
  linkstatic = False,
  copts = ["-std=c++11"]
)

cc_binary(
  name = "test_pub_sub",
  srcs = glob([
    "sample/pub_sub/*.cpp",
    "sample/pub_sub/*.h",
  ]),
  deps = [":libtiny_ros"],
  copts = ["-std=c++11"],
)

cc_binary(
  name = "test_srv_call",
  srcs = glob([
    "sample/srv_call/*.cpp",
    "sample/srv_call/*.h",
  ]),
  deps = [":libtiny_ros"],
  copts = ["-std=c++11"],
)
