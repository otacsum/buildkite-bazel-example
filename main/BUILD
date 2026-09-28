load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "greet",
    srcs = ["greet.cc"],
    hdrs = ["greet.h"],
)

cc_binary(
    name = "hello-world",
    srcs = ["hello-world.cc"],
    deps = [":greet"],
)

cc_binary(
    name = "hello-world-2",
    srcs = ["hello-world.cc"],
    deps = [":greet"],
)

cc_test(
    name = "greet_test",
    srcs = ["greet_test.cc"],
    deps = [":greet"],
)
