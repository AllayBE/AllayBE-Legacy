#include <misc/ZlibHelper.h>

bool ZlibHelper::InflateRaw(const void *inputBuffer, uLongf inputSize, void *outputBuffer, uLongf &outputSize)
{
	z_stream zStream;
	memset(&zStream, 0, sizeof(z_stream));
	zStream.next_in = (Bytef *)inputBuffer;
	zStream.avail_in = inputSize;
	zStream.next_out = (Bytef *)outputBuffer;
	zStream.avail_out = outputSize;

	if (inflateInit2(&zStream, -MAX_WBITS) != Z_OK)
	{
		return false;
	}

	int inflateResult = inflate(&zStream, Z_FINISH);

	if (inflateResult != Z_STREAM_END && inflateResult != Z_OK)
	{
		inflateEnd(&zStream);
		return false;
	}

	outputSize = zStream.total_out;

	inflateEnd(&zStream);
	return true;
}

bool ZlibHelper::DeflateRaw(int compressionLevel, const void *inputBuffer, uLongf inputSize, void *outputBuffer, uLongf &outputSize)
{
	z_stream zStream;
	memset(&zStream, 0, sizeof(z_stream));
	zStream.next_in = (Bytef *)inputBuffer;
	zStream.avail_in = inputSize;
	zStream.next_out = (Bytef *)outputBuffer;
	zStream.avail_out = outputSize;
	zStream.zalloc = Z_NULL;
	zStream.zfree = Z_NULL;

	int status = deflateInit2(&zStream, compressionLevel, Z_DEFLATED, -MAX_WBITS, 8, Z_DEFAULT_STRATEGY);

	if (status != Z_OK)
	{
		printf("unable to init deflate\n");
		return false;
	}


	status = deflate(&zStream, Z_FINISH);

	printf("deflate\n");

	if (status != Z_STREAM_END && status != Z_OK)
	{
		printf("stream not end\n");
		deflateEnd(&zStream);
		return false;
	}

	printf("done\n");
	outputSize = zStream.total_out;

	deflateEnd(&zStream);
	printf("end\n");
	return true;
}