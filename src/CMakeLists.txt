# source file
file(GLOB DIR_HEADER "*.h" "*.hpp")
file(GLOB DIR_SOURCE "*.c" "*.cpp")
list(APPEND DIR_HEADER ${INCLUDE_DIR}/interface.h)

source_group(header FILES ${DIR_HEADER})
source_group(source FILES ${DIR_SOURCE})

# target
add_library(samples OBJECT ${DIR_SOURCE} ${DIR_HEADER})