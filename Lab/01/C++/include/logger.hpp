#pragma once

// Appends a line to `server.log`. It automatically adds '\n' character to the end.
void log_append_line(std::string line);

// Overwrites `server.log` with a line. It automatically adds '\n' character to the end.
void log_overwrite_line(std::string line);