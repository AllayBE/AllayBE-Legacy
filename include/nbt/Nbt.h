#pragma once

#include <nbt/list/Compound.h>
#include <nbt/list/Double.h>
#include <nbt/list/Float.h>
#include <nbt/list/Int16.h>
#include <nbt/list/Int32.h>
#include <nbt/list/Int32Array.h>
#include <nbt/list/Int64.h>
#include <nbt/list/Int64Array.h>
#include <nbt/list/Int8.h>
#include <nbt/list/Int8Array.h>
#include <nbt/list/List.h>
#include <nbt/list/String.h>
#include <nbt/list/Tag.h>

class Nbt
{
public:
	static Tag *GetTag(int8_t tagID);

	static void WriteRootBE(Tag *tag, BitStream *stream);
	static void WriteRootLE(Tag *tag, BitStream *stream);
	static void WriteRootNET(Tag *tag, BitStream *stream);

	static Tag *ReadRootBE(BitStream *stream);
	static Tag *ReadRootLE(BitStream *stream);
	static Tag *ReadRootNET(BitStream *stream);
};