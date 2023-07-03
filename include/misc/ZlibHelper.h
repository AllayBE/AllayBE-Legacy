#pragma once

#include <zlib.h>
#include <string>

class ZlibHelper
{
public:
	static bool InflateRaw(const void *inputBuffer, uLongf inputSize, void *outputBuffer, uLongf &outputSize);
	static bool DeflateRaw(int compressionLevel, const void *inputBuffer, uLongf inputSize, void *outputBuffer, uLongf &outputSize);
};