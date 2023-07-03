#pragma once

#include "MinecraftPacket.h"
#include <network/minecraft/structs/BehaviorPackInfo.h>
#include <network/minecraft/structs/TexturePackInfo.h>
#include <vector>

typedef std::vector<BehaviorPackInfo> BehaviorPackList_t;
typedef std::vector<TexturePackInfo> TexturePackList_t;

class ResourcePacksInfoPacket : public MinecraftPacket
{
protected:
	bool mustAccept;
	bool hasScripts;
	bool forceServerPacks;
	BehaviorPackList_t behaviorPacks;
	TexturePackList_t texturePacks;

public:
	virtual uint32_t GetID() const override;

	virtual void DeserializeHeader(BitStream *stream) override { MinecraftPacket::DeserializeHeader(stream); }
	virtual void SerializeHeader(BitStream *stream) override { MinecraftPacket::SerializeHeader(stream); }

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;

	void SetMustAccept(bool value);
	void SetHasScripts(bool value);
	void SetForceServerPacks(bool value);
	void SetBehaviorPacks(BehaviorPackList_t value);
	void SetTexturePacks(TexturePackList_t value);

	bool GetMustAccept();
	bool GetHasScripts();
	bool GetForceServerPacks();
	BehaviorPackList_t GetBehaviorPacks();
	TexturePackList_t GetTexturePacks();
};