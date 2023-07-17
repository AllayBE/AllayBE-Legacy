#pragma once

#include "MinecraftPacket.h"
#include <nbt/Nbt.h>
#include <network/minecraft/structs/BlockCoordinates.h>
#include <network/minecraft/structs/BlockProperty.h>
#include <network/minecraft/structs/EducationSharedResourceUri.h>
#include <network/minecraft/structs/Experiment.h>
#include <network/minecraft/structs/GameRule.h>
#include <network/minecraft/structs/ItemState.h>
#include <network/minecraft/structs/Vec2f.h>
#include <network/minecraft/structs/Vec3f.h>
#include <string>
#include <vector>

typedef std::vector<GameRule> GameRuleList_t;
typedef std::vector<Experiment> ExperimentList_t;
typedef std::vector<BlockProperty> BlockPropertyList_t;
typedef std::vector<ItemState> ItemStateList_t;

class StartGamePacket : public MinecraftPacket
{
protected:
	int64_t entityID;
	uint64_t runtimeEntityID;
	int32_t playerGameMode;
	Vec3f playerPosition;
	Vec2f rotation;
	uint64_t seed;
	int16_t biomeType;
	std::string biomeName;
	int32_t dimension;
	int32_t generator;
	int32_t worldGamemode;
	int32_t difficulty;
	BlockCoordinates spawnPosition;
	bool achivementsDisabled;
	bool editorWorld;
	bool createdInEditor;
	bool exportedFromEditor;
	int32_t dayCycleStopTime;
	int32_t eduOffer;
	bool eduFeaturesEnabled;
	std::string eduProductUuid;
	float rainLevel;
	float lightningLevel;
	bool hasConfirmedPlatformLockedContent;
	bool isMultiplayer;
	bool broadcastToLan;
	uint32_t xboxLiveBroadcastMode;
	uint32_t platformBroadcastMode;
	bool enableCommands;
	bool isTexturePacksRequired;
	GameRuleList_t gameRules;
	ExperimentList_t experiments;
	bool experimentsPreviouslyUsed;
	bool bonusChest;
	bool mapEnabled;
	uint8_t permissionLevel;
	int32_t serverChunkTickRange;
	bool hasLockedBehaviorPack;
	bool hasLockedResourcePack;
	bool isFromLockedWorldTemplate;
	bool msaGamertagsOnly;
	bool isFromWorldTemplate;
	bool isWorldTemplateOptionLocked;
	bool onlySpawnV1Villagers;
	bool personaDisabled;
	bool customSkinsDisabled;
	bool emoteChatMuted;
	std::string gameVersion;
	int32_t limitedWorldWidth;
	int32_t limitedWorldLength;
	bool isNewNether;
	EducationSharedResourceUri eduResourceUri;
	bool experimentalGameplayOverride;
	uint8_t chatRestrictionLevel;
	bool disablePlayerInteractions;
	std::string levelID;
	std::string worldName;
	std::string premiumWorldTemplateID;
	bool isTrail;
	int32_t movementAuthority;
	int32_t rewindHistorySize;
	bool serverAuthoritativeBlockBreaking;
	int64_t currentTick;
	int32_t enchantmentSeed;
	BlockPropertyList_t blockProperties;
	ItemStateList_t itemStates;
	std::string multiplayerCorrelationID;
	bool serverAuthoritativeInventory;
	std::string engine;
	Compound *propertyData;
	uint64_t blockPalletteChecksum;
	std::string worldTemplateID;
	bool clientSideGeneration;
	bool blockNetworkIDsAreHashes;
	bool serverControlledSound;

public:
	virtual uint32_t GetID() const override;

	virtual void DeserializeHeader(BitStream *stream) override { MinecraftPacket::DeserializeHeader(stream); }
	virtual void SerializeHeader(BitStream *stream) override { MinecraftPacket::SerializeHeader(stream); }

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;

	void SetEntityID(int64_t entityID);
	void SetRuntimeEntityID(uint64_t runtimeEntityID);
	void SetPlayerGameMode(int32_t playerGameMode);
	void SetPlayerPosition(Vec3f playerPosition);
	void SetRotation(Vec2f rotation);
	void SetSeed(uint64_t seed);
	void SetBiomeType(int16_t biomeType);
	void SetBiomeName(std::string biomeName);
	void SetDimension(int32_t dimension);
	void SetGenerator(int32_t generator);
	void SetWorldGamemode(int32_t worldGamemode);
	void SetDifficulty(int32_t difficulty);
	void SetSpawnPosition(BlockCoordinates spawnPosition);
	void SetAchivementsDisabled(bool achivementsDisabled);
	void SetEditorWorld(bool editorWorld);
	void SetCreatedInEditor(bool createdInEditor);
	void SetExportedFromEditor(bool exportedFromEditor);
	void SetDayCycleStopTime(int32_t dayCycleStopTime);
	void SetEduOffer(int32_t eduOffer);
	void SetEduFeaturesEnabled(bool eduFeaturesEnabled);
	void SetEduProductUuid(std::string eduProductUuid);
	void SetRainLevel(float rainLevel);
	void SetLightningLevel(float lightningLevel);
	void SetHasConfirmedPlatformLockedContent(bool hasConfirmedPlatformLockedContent);
	void SetIsMultiplayer(bool isMultiplayer);
	void SetBroadcastToLan(bool broadcastToLan);
	void SetXboxLiveBroadcastMode(uint32_t xboxLiveBroadcastMode);
	void SetPlatformBroadcastMode(uint32_t platformBroadcastMode);
	void SetEnableCommands(bool enableCommands);
	void SetIsTexturePacksRequired(bool isTexturePacksRequired);
	void SetGameRules(GameRuleList_t gameRules);
	void SetExperiments(ExperimentList_t experiments);
	void SetExperimentsPreviouslyUsed(bool experimentsPreviouslyUsed);
	void SetBonusChest(bool bonusChest);
	void SetMapEnabled(bool mapEnabled);
	void SetPermissionLevel(uint8_t permissionLevel);
	void SetServerChunkTickRange(int32_t serverChunkTickRange);
	void SetHasLockedBehaviorPack(bool hasLockedBehaviorPack);
	void SetHasLockedResourcePack(bool hasLockedResourcePack);
	void SetIsFromLockedWorldTemplate(bool isFromLockedWorldTemplate);
	void SetMsaGamertagsOnly(bool msaGamertagsOnly);
	void SetIsFromWorldTemplate(bool isFromWorldTemplate);
	void SetIsWorldTemplateOptionLocked(bool isWorldTemplateOptionLocked);
	void SetOnlySpawnV1Villagers(bool onlySpawnV1Villagers);
	void SetPersonaDisabled(bool personaDisabled);
	void SetCustomSkinsDisabled(bool customSkinsDisabled);
	void SetEmoteChatMuted(bool emoteChatMuted);
	void SetGameVersion(std::string gameVersion);
	void SetLimitedWorldWidth(int32_t limitedWorldWidth);
	void SetLimitedWorldLength(int32_t limitedWorldLength);
	void SetIsNewNether(bool isNewNether);
	void SetEduResourceUri(EducationSharedResourceUri eduResourceUri);
	void SetExperimentalGameplayOverride(bool experimentalGameplayOverride);
	void SetChatRestrictionLevel(uint8_t chatRestrictionLevel);
	void SetDisablePlayerInteractions(bool disablePlayerInteractions);
	void SetLevelID(std::string levelID);
	void SetWorldName(std::string worldName);
	void SetPremiumWorldTemplateID(std::string premiumWorldTemplateID);
	void SetIsTrail(bool isTrail);
	void SetMovementAuthority(int32_t movementAuthority);
	void SetRewindHistorySize(int32_t rewindHistorySize);
	void SetServerAuthoritativeBlockBreaking(bool serverAuthoritativeBlockBreaking);
	void SetCurrentTick(int64_t currentTick);
	void SetEnchantmentSeed(int32_t enchantmentSeed);
	void SetBlockProperties(BlockPropertyList_t blockProperties);
	void SetItemStates(ItemStateList_t itemStates);
	void SetMultiplayerCorrelationID(std::string multiplayerCorrelationID);
	void SetServerAuthoritativeInventory(bool serverAuthoritativeInventory);
	void SetEngine(std::string engine);
	void SetPropertyData(Compound *propertyData);
	void SetBlockPalletteChecksum(uint64_t blockPalletteChecksum);
	void SetWorldTemplateID(std::string worldTemplateID);
	void SetClientSideGeneration(bool clientSideGeneration);
	void SetBlockNetworkIDsAreHashes(bool blockNetworkIDsAreHashes);
	void SetServerControlledSound(bool serverControlledSound);

	int64_t GetEntityID();
	uint64_t GetRuntimeEntityID();
	int32_t GetPlayerGameMode();
	Vec3f GetPlayerPosition();
	Vec2f GetRotation();
	uint64_t GetSeed();
	int16_t GetBiomeType();
	std::string GetBiomeName();
	int32_t GetDimension();
	int32_t GetGenerator();
	int32_t GetWorldGamemode();
	int32_t GetDifficulty();
	BlockCoordinates GetSpawnPosition();
	bool GetAchivementsDisabled();
	bool GetEditorWorld();
	bool GetCreatedInEditor();
	bool GetExportedFromEditor();
	int32_t GetDayCycleStopTime();
	int32_t GetEduOffer();
	bool GetEduFeaturesEnabled();
	std::string GetEduProductUuid();
	float GetRainLevel();
	float GetLightningLevel();
	bool GetHasConfirmedPlatformLockedContent();
	bool GetIsMultiplayer();
	bool GetBroadcastToLan();
	uint32_t GetXboxLiveBroadcastMode();
	uint32_t GetPlatformBroadcastMode();
	bool GetEnableCommands();
	bool GetIsTexturePacksRequired();
	GameRuleList_t GetGameRules();
	ExperimentList_t GetExperiments();
	bool GetExperimentsPreviouslyUsed();
	bool GetBonusChest();
	bool GetMapEnabled();
	uint8_t GetPermissionLevel();
	int32_t GetServerChunkTickRange();
	bool GetHasLockedBehaviorPack();
	bool GetHasLockedResourcePack();
	bool GetIsFromLockedWorldTemplate();
	bool GetMsaGamertagsOnly();
	bool GetIsFromWorldTemplate();
	bool GetIsWorldTemplateOptionLocked();
	bool GetOnlySpawnV1Villagers();
	bool GetPersonaDisabled();
	bool GetCustomSkinsDisabled();
	bool GetEmoteChatMuted();
	std::string GetGameVersion();
	int32_t GetLimitedWorldWidth();
	int32_t GetLimitedWorldLength();
	bool GetIsNewNether();
	EducationSharedResourceUri GetEduResourceUri();
	bool GetExperimentalGameplayOverride();
	uint8_t GetChatRestrictionLevel();
	bool GetDisablePlayerInteractions();
	std::string GetLevelID();
	std::string GetWorldName();
	std::string GetPremiumWorldTemplateID();
	bool GetIsTrail();
	int32_t GetMovementAuthority();
	int32_t GetRewindHistorySize();
	bool GetServerAuthoritativeBlockBreaking();
	int64_t GetCurrentTick();
	int32_t GetEnchantmentSeed();
	BlockPropertyList_t GetBlockProperties();
	ItemStateList_t GetItemStates();
	std::string GetMultiplayerCorrelationID();
	bool GetServerAuthoritativeInventory();
	std::string GetEngine();
	Compound *GetPropertyData();
	uint64_t GetBlockPalletteChecksum();
	std::string GetWorldTemplateID();
	bool GetClientSideGeneration();
	bool GetBlockNetworkIDsAreHashes();
	bool GetServerControlledSound();
};