#pragma once
#include <stdexcept>
#include <string>

class RenderException : public std::exception {
protected:
    std::string message;
public:
    explicit RenderException(const std::string &msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class CameraConfigurationException : public RenderException {
public:
    explicit CameraConfigurationException(const std::string &msg)
        : RenderException("Camera config error: " + msg) {}
};

class RayMarchingException : public RenderException {
public:
    explicit RayMarchingException(const std::string &msg)
        : RenderException("Raymarching error: " + msg) {}
};

class ShapeConstructionException : public RenderException {
public:
    explicit ShapeConstructionException(const std::string &msg)
        : RenderException("Shape error: " + msg) {}
};

class FileIOException : public RenderException {
public:
    explicit FileIOException(const std::string &msg)
        : RenderException("File I/O error: " + msg) {}
};