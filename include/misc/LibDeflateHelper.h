#pragma once

#include <libdeflate.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <RakMemoryOverride.h>

using namespace RakNet;

class LibDeflateHelper
{
public:
	static libdeflate_result InflateRaw(char *inBuffer, size_t inByteSize, char *outBuffer, size_t outByteSize);
	static size_t DeflateRaw(char *inBuffer, size_t inByteSize, char *outBuffer);
};