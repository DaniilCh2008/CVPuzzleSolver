#pragma once

#include <string>

#include <libimages/image.h>

namespace debug_io {

// Creates parent directories for a filepath (if needed). No-op if already exists.
void ensure_dir_exists_for_file(const std::string &filepath);

// Maps float image to 8-bit grayscale using max value (typical for magnitudes, pixels with void_values ignored and colored green).
image8u normalize(const image32f &img, float void_value=std::numeric_limits<float>::max());

// Maps each value to random color (except pixels with void_value - they will be colored black)
image8u colorize_labels(const image32i &labels, int void_value=std::numeric_limits<int>::max(), std::uint32_t seed = 0);

// Save helpers that creates parent directory (if it still doesn't exist)
void dump_image(const std::string &path, const image8u &img);
void dump_image(const std::string &path, const image32f &img, float void_value=std::numeric_limits<float>::max());

} // namespace debug_io