TEMPLATE = subdirs

SUBDIRS += \
    protocol \
    test \
    libs \
    devices \
    tools \

# Path of sub-directories
protocol.subdir = protocol
test.subdir     = protocol/test
tools.subdir    = tools
libs.subdir     = libs
devices.subdir  = devices

# Dependencies between projects
libs.depends    = protocol
test.depends    = protocol
devices.depends = libs
