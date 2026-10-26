include_directories("${CMAKE_CURRENT_LIST_DIR}")

set(LOVYANGFX_DIR "/mnt/nvme-990/dietpi_userdata/esphome/lib/LovyanGFX")

if(EXISTS "${LOVYANGFX_DIR}/src")

    # set(COMPONENT_ADD_INCLUDEDIRS
    #    include_directories("${LOVYANGFX_DIR}/src")
    # )

    include_directories("${LOVYANGFX_DIR}/src")
    include_directories("${LOVYANGFX_DIR}/src/lgfx/v1")
    include_directories("${LOVYANGFX_DIR}/src/lgfx/v1/panel")
    include_directories("${LOVYANGFX_DIR}/src/lgfx/v1/bus")
    include_directories("${LOVYANGFX_DIR}/src/lgfx/v1/platforms")
    include_directories("${LOVYANGFX_DIR}/src/lgfx/v1/platforms/esp32")

    file(GLOB_RECURSE LOVYANGFX_SOURCES
        "${LOVYANGFX_DIR}/src/*.cpp"
        "${LOVYANGFX_DIR}/src/*.c"
    )

    idf_component_register(SRCS ${srcs}
                           PRIV_REQUIRES esp_lcd unity esp_driver_i2s
                           WHOLE_ARCHIVE)

    list(APPEND COMPONENT_SRCS ${LOVYANGFX_SOURCES})
    register_component()

    # --- MAIN.CPP ---
    target_include_directories(${COMPONENT_TARGET} PUBLIC "${LOVYANGFX_DIR}/src")
    target_include_directories(${COMPONENT_TARGET} PUBLIC "${LOVYANGFX_DIR}/src/lgfx/v1")
endif()
