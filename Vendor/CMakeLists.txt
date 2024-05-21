add_library(Vendor INTERFACE)

add_subdirectory(spdlog)
add_subdirectory(json)
#add_subdirectory(matplotlib-cpp)

target_link_libraries(Vendor INTERFACE
spdlog::spdlog_header_only
nlohmann_json::nlohmann_json
#matplotlib_cpp
)