add_library(Vendor INTERFACE)

add_subdirectory(spdlog)
add_subdirectory(json)

target_link_libraries(Vendor INTERFACE
spdlog::spdlog_header_only
nlohmann_json::nlohmann_json
)