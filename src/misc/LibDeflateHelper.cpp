#include <misc/LibDeflateHelper.h>

libdeflate_result LibDeflateHelper::InflateRaw(char *inBuffer, size_t inByteSize, char *outBuffer, size_t outByteSize)
{
	libdeflate_decompressor *decompressor = libdeflate_alloc_decompressor();
	libdeflate_result result = libdeflate_deflate_decompress(decompressor, inBuffer, inByteSize, outBuffer, outByteSize, NULL);

	libdeflate_free_decompressor(decompressor);
	return result;
}

size_t LibDeflateHelper::DeflateRaw(char *inBuffer, size_t inByteSize, char *outBuffer)
{
	libdeflate_compressor *compressor = libdeflate_alloc_compressor(7);
	size_t len = strlen((const char *)inBuffer);
	size_t maxCompressedSize = libdeflate_deflate_compress_bound(compressor, len);
	unsigned char *compressedBuffer = (unsigned char *)rakMalloc_Ex(len, _FILE_AND_LINE_);

	size_t actualDecompressedSize = libdeflate_deflate_compress(compressor, inBuffer, len, compressedBuffer, maxCompressedSize);

	libdeflate_free_compressor(compressor);
	return actualDecompressedSize;
}