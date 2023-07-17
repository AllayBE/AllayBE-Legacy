#pragma once

#include "MinecraftPacket.h"
#include <network/minecraft/structs/ResourcePackIDVersion.h>
#include <network/minecraft/structs/Experiment.h>
#include <string>
#include <vector>

typedef std::vector<ResourcePackIDVersion> SBehaviorPackList_t;
typedef std::vector<ResourcePackIDVersion> SResourcePackList_t;
typedef std::vector<Experiment> ExperimentList_t;

class ResourcePackStackPacket : public MinecraftPacket
{
protected:
	bool mustAccept;
	SBehaviorPackList_t behaviorPacks;
	SResourcePackList_t resourcePacks;
	std::string gameVersion;
	ExperimentList_t experiments;
	bool experimentPreviouslyUsed;

public:
	virtual uint32_t GetID() const override;

	virtual void DeserializeHeader(BitStream *stream) override { MinecraftPacket::DeserializeHeader(stream); }
	virtual void SerializeHeader(BitStream *stream) override { MinecraftPacket::SerializeHeader(stream); }

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;

	void SetMustAccept(bool value);
	void SetBehaviorPacks(SBehaviorPackList_t value);
	void SetResourcePacks(SResourcePackList_t value);
	void SetGameVersion(std::string value);
	void SetExperiments(ExperimentList_t value);
	void SetExperimentPreviouslyUsed(bool value);

	bool GetMustAccept();
	SBehaviorPackList_t GetBehaviorPacks();
	SResourcePackList_t GetResourcePacks();
	std::string GetGameVersion();
	ExperimentList_t GetExperiments();
	bool GetExperimentPreviouslyUsed();
};