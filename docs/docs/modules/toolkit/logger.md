---
sidebar_position: 1
---

# Logger

```cpp
#include <toolkit/logger.hpp>
```

## Creation

A logger is created using a `tk::Logger::Builder`, which can be accessed via `tk::Logger::builder(std::string_view name)`.
After enablind the desiered output methods, you can call `build()` to finalize and creaate the logger.

### Options

#### `toStdOut()`{.cpp}

Will output colored messages directly to the terminal standard output using the name specified when building the logger.

:::caution
The usage of `toStdOut()` is not protected. It is possible to add multiple standard output loggers, resulting in duplicated messages being logged.
:::

#### `toFile(const std::filesystem::path& path)`

Will send output to the file at the given path, also using the name previously specified.

### Example

```cpp
tk::Logger logger = tk::Logger::builder("toolkit")
    .toStdOut() // Print messages to the console
    .toFile("toolkit.log") // In addition, log messages to the file "toolkit.log"
    .build();
```

## Usage

### Log Levels

Messages can be logged at various levels.

- Trace
- Info
- Warn
- Error

:::info
Trace is only enabled when compiled without the `NDEBUG` preprocessor definition.
:::

### Methods

#### `log(tk::LogLevel level, fmt::format_string fmt, ...)`

When provided with a log level, this function will output the provided message through the configured loggers in accordance with [fmt format strings](https://fmt.dev/latest/syntax.html).

#### Explicit Logging Methods

No different from calling `log` with the appropriate log level; however, they are simpler to write.

- `trace(fmt::format_string, ...)`
- `info(fmt::format_string, ...)`
- `warn(fmt::format_string, ...)`
- `error(fmt::format_string, ...)`

### Examples

#### Basic

```cpp
logger.trace("Creating window title \"{}\" with size {}x{}", title, width, height);
```

#### Type Formatting

```cpp
logger.error("Failed to create object with flags: {:b}", flags);
```

## Remarks

The logger element of the toolkit is powered under the hood by [spdlog](https://github.com/gabime/spdlog).