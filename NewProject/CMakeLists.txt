cmake_minimum_required(VERSION 3.22)

project(Delay VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------
# JUCE location
#
# Option 1 (default): point to your local JUCE install.
#   Override from the command line: cmake -DJUCE_PATH=/path/to/JUCE ..
#
# Option 2: comment out the add_subdirectory block and uncomment the
#   FetchContent block below to download JUCE automatically.
# -----------------------------------------------------------------------
set(JUCE_PATH "$ENV{HOME}/Documents/JUCE" CACHE PATH "Path to JUCE root directory")

if(NOT EXISTS "${JUCE_PATH}/CMakeLists.txt")
    message(FATAL_ERROR
        "JUCE not found at '${JUCE_PATH}'.\n"
        "Either install JUCE there, or pass -DJUCE_PATH=/your/path/to/JUCE to cmake.\n"
        "You can download JUCE from https://juce.com/get-juce/")
endif()

add_subdirectory(${JUCE_PATH} JUCE EXCLUDE_FROM_ALL)

# -- FetchContent alternative (uncomment to use instead of add_subdirectory) --
# include(FetchContent)
# FetchContent_Declare(
#     JUCE
#     GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
#     GIT_TAG        8.0.6   # pin to a release tag
# )
# FetchContent_MakeAvailable(JUCE)
# -----------------------------------------------------------------------------

juce_add_plugin(Delay
    COMPANY_NAME                "yourcompany"
    PLUGIN_MANUFACTURER_CODE    "Yocm"
    PLUGIN_CODE                 "Dlay"
    FORMATS                     VST3 AU AUv3 Standalone
    PRODUCT_NAME                "Delay"

    IS_SYNTH                    FALSE
    NEEDS_MIDI_INPUT            FALSE
    NEEDS_MIDI_OUTPUT           FALSE
    IS_MIDI_EFFECT              FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD     TRUE
)

juce_generate_juce_header(Delay)

target_sources(Delay PRIVATE
    Source/PluginProcessor.h
    Source/PluginProcessor.cpp
    Source/PluginEditor.h
    Source/PluginEditor.cpp
)

# Group your source files under "Source" in the Xcode navigator
source_group("Source" FILES
    Source/PluginProcessor.h
    Source/PluginProcessor.cpp
    Source/PluginEditor.h
    Source/PluginEditor.cpp
)

target_compile_definitions(Delay PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_STRICT_REFCOUNTEDPOINTER=1
)

target_link_libraries(Delay
    PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_data_structures
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
