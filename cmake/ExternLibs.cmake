function(ADDJSON TARGET_NAME)
	find_package(nlohmann_json CONFIG REQUIRED)
	target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
endfunction()

function(ADDGTEST TARGET_NAME)
	include(FetchContent)
	FetchContent_Declare(
	  googletest
	  URL https://github.com/google/googletest/archive/2f80c2ba71c0e8922a03b9b855e5b019ad1f7064.zip
	)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)
	enable_testing()
	target_link_libraries(${TARGET_NAME} PRIVATE gtest_main)
	include(GoogleTest)
	gtest_discover_tests(${TARGET_NAME})
endfunction()

function(ADDQT6CORE TARGET_NAME)
	find_package(Qt6 COMPONENTS Core REQUIRED)
	target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Core)
endfunction()

function(ADDQT6WIDGETS TARGET_NAME)
	find_package(Qt6 COMPONENTS Widgets REQUIRED)
	target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Widgets)
endfunction()

function(ADDQT6NETWORK TARGET_NAME)
	find_package(Qt6 COMPONENTS Network REQUIRED)
	target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Network)
endfunction()