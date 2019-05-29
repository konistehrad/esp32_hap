#
# Component Makefile
#

CFLAGS += -DFREERTOS
CFLAGS += -D LOG_LOCAL_LEVEL=ESP_LOG_DEBUG

COMPONENT_ADD_INCLUDEDIRS := include

COMPONENT_SRCDIRS := . tests crypto utils utils/ll