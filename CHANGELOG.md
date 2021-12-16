# Anticarium_Desktop

- ADD: Video reading from UDP port
- ADD: Video display capability
- MODIFY: Create log file path from `QApplication::applicationDirPath()`

# 1.3.0
- REMOVE: `VersionConfig.h.in` file and cmake script, because it is unused
- ADD: `settings.ini.h` gets copied to build directory as `settings.ini` to become real application settings 
- ADD: `Sensor_Data_fetch_timeout` setting for sensor data fetching timeout from server
- ADD: `Anticarium_Server_URL` setting that stores URL to which to make requests
- ADD: Application settings class `ApplicationSettings` along with its tests
- ADD: Save `RegimeValue` from incoming `Regime` in `MainWindowManager.cpp`
- MODIFY: Changed http response header to "Anticarium_content_description"
- MODIFY: Formatted code using new .clang-format config from Anticarium_Doc 2283a5e594f9b46cb9fd90737b32b8f952dcc5b8
- MODIFY: .gitignore .clang-format file
- REMOVE: .clang-format file, it is located in Anticarium_Doc
- ADD: DisplayRegimes widget that displays all saved regimes
- ADD: DisplayRegimes delete element button that allows to delete Regime in SavedRegimes
- ADD: DisplayRegimes edit element button that allows to edit Regime in SavedRegimes
- MODIFY: RegimeDialog now can be used in edit mode
- ADD: DisplayRegimes widget can be opened from Home->Edit regimes
- MODIFY: shared_types v1.3.0
- MODIFY: Request regimes by its id and not by string name

# 1.2.0
- MODIFY: Synchronous replies from server
- ADD: Regime dialog to create new regimes from main screen
- ADD: spdlog logger
- MODIFY: shared_types v1.2.0
- ADD: Save button with ui functionality
- MODIFY: Sliders for all MainWindow main inputs
- ADD: QComboBox for regimes display and choosing
- ADD: Text to display slider values
- ADD: Send regime data to server
- REMOVE: Auto checkbox

# 1.1.0
- MODIFY: shared_types v1.1.3
- ADD: Use shared_types serializers in JTTP http requests
- MODIFY: Downgrade to Qt5
- ADD: Send input data to server
- ADD: Code structure for sending and requesting data
- MODIFY: Naming refactor, file names to PascalCase and variables to camelCase

## 1.0.1
- MODIFY: Use layouts and standard qt components for gui
- ADD: MainWindowManager for use of MainWindow

## 1.0.0
- MODIFY: Moved to CMake
- ADD: Shared_Types repo
- REMOVE: OpenGL widget