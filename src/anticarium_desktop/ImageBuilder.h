#pragma once

#include <anticarium_desktop/config/ImageRow.hpp>

// Purely static class
class ImageBuilder {
  public:
    ImageBuilder() = delete;

    // Builds one image row
    static ImageRow build(const QByteArray& inRow);
};
