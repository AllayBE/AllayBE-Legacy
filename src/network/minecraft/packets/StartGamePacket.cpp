#include <network/minecraft/packets/StartGamePacket.h>

uint32_t StartGamePacket::GetID() const
{
	return ID_START_GAME;
}

bool StartGamePacket::DeserializeBody(BitStream *stream)
{
	this->entityID = BitStreamHelper::ReadZigZag64(stream);
	this->runtimeEntityID = BitStreamHelper::ReadUnsignedVarLong(stream);
	this->playerGameMode = BitStreamHelper::ReadZigZag32(stream);
	this->playerPosition.deserialize(stream);
	this->rotation.deserialize(stream);
	if (!BitStreamHelper::ReadLittleEndian<uint64_t>(this->seed, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadLittleEndian<int16_t>(this->biomeType, stream))
	{
		return false;
	}
	this->biomeName = BitStreamHelper::ReadStringVarInt(stream);
	this->dimension = BitStreamHelper::ReadZigZag32(stream);
	this->generator = BitStreamHelper::ReadZigZag32(stream);
	this->worldGamemode = BitStreamHelper::ReadZigZag32(stream);
	this->difficulty = BitStreamHelper::ReadZigZag32(stream);
	this->spawnPosition.deserialize(stream);
	if (!BitStreamHelper::ReadBool(this->achivementsDisabled, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->editorWorld, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->createdInEditor, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->exportedFromEditor, stream))
	{
		return false;
	}
	this->dayCycleStopTime = BitStreamHelper::ReadZigZag32(stream);
	this->eduOffer = BitStreamHelper::ReadZigZag32(stream);
	if (!BitStreamHelper::ReadBool(this->eduFeaturesEnabled, stream))
	{
		return false;
	}
	this->eduProductUuid = BitStreamHelper::ReadStringVarInt(stream);
	if (!BitStreamHelper::ReadLittleEndian<float>(this->rainLevel, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadLittleEndian<float>(this->lightningLevel, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->hasConfirmedPlatformLockedContent, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->isMultiplayer, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->broadcastToLan, stream))
	{
		return false;
	}
	this->xboxLiveBroadcastMode = BitStreamHelper::ReadUnsignedVarInt(stream);
	this->platformBroadcastMode = BitStreamHelper::ReadUnsignedVarInt(stream);
	if (!BitStreamHelper::ReadBool(this->enableCommands, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->isTexturePacksRequired, stream))
	{
		return false;
	}
	uint32_t gameRuleListSize = BitStreamHelper::ReadUnsignedVarInt(stream);
	for (uint32_t i = 0; i < gameRuleListSize; ++i)
	{
		this->gameRules[i].serialize(stream);
	}
	int32_t experimentListSize;
	if (!BitStreamHelper::ReadLittleEndian<int32_t>(experimentListSize, stream))
	{
		return false;
	}
	for (int32_t i = 0; i < experimentListSize; ++i)
	{
		this->experiments[i].serialize(stream);
	}
	if (!BitStreamHelper::ReadBool(this->experimentsPreviouslyUsed, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->bonusChest, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->mapEnabled, stream))
	{
		return false;
	}
	if (!stream->Read<uint8_t>(this->permissionLevel))
	{
		return false;
	}
	if (!BitStreamHelper::ReadLittleEndian<int32_t>(this->serverChunkTickRange, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->hasLockedBehaviorPack, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->hasLockedResourcePack, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->isFromLockedWorldTemplate, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->msaGamertagsOnly, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->isFromWorldTemplate, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->isWorldTemplateOptionLocked, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->onlySpawnV1Villagers, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->personaDisabled, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->customSkinsDisabled, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->emoteChatMuted, stream))
	{
		return false;
	}
	this->gameVersion = BitStreamHelper::ReadStringVarInt(stream);
	if (!BitStreamHelper::ReadLittleEndian<int32_t>(this->limitedWorldWidth, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadLittleEndian<int32_t>(this->limitedWorldLength, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->isNewNether, stream))
	{
		return false;
	}
	this->eduResourceUri.deserialize(stream);
	if (!BitStreamHelper::ReadBool(this->experimentalGameplayOverride, stream))
	{
		return false;
	}
	if (!stream->Read<uint8_t>(this->chatRestrictionLevel))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->disablePlayerInteractions, stream))
	{
		return false;
	}
	this->levelID = BitStreamHelper::ReadStringVarInt(stream);
	this->worldName = BitStreamHelper::ReadStringVarInt(stream);
	this->premiumWorldTemplateID = BitStreamHelper::ReadStringVarInt(stream);
	if (!BitStreamHelper::ReadBool(this->isTrail, stream))
	{
		return false;
	}
	this->movementAuthority = BitStreamHelper::ReadZigZag32(stream);
	this->rewindHistorySize = BitStreamHelper::ReadZigZag32(stream);
	if (!BitStreamHelper::ReadBool(this->serverAuthoritativeBlockBreaking, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadLittleEndian<int64_t>(this->currentTick, stream))
	{
		return false;
	}
	this->enchantmentSeed = BitStreamHelper::ReadZigZag32(stream);
	uint32_t blockPropertyListSize = BitStreamHelper::ReadUnsignedVarInt(stream);
	for (uint32_t i = 0; i < blockPropertyListSize; ++i)
	{
		this->blockProperties[i].serialize(stream);
	}
	uint32_t itemStateListSize = BitStreamHelper::ReadUnsignedVarInt(stream);
	for (uint32_t i = 0; i < itemStateListSize; ++i)
	{
		this->itemStates[i].serialize(stream);
	}
	this->multiplayerCorrelationID = BitStreamHelper::ReadStringVarInt(stream);
	if (!BitStreamHelper::ReadBool(this->serverAuthoritativeInventory, stream))
	{
		return false;
	}
	this->engine = BitStreamHelper::ReadStringVarInt(stream);
	this->propertyData = (Compound *)BitStreamHelper::ReadNbtRootNET(stream);
	if (!BitStreamHelper::ReadLittleEndian<uint64_t>(this->blockPalletteChecksum, stream))
	{
		return false;
	}
	this->worldTemplateID = BitStreamHelper::ReadUuid(stream);
	if (!BitStreamHelper::ReadBool(this->clientSideGeneration, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->blockNetworkIDsAreHashes, stream))
	{
		return false;
	}
	if (!BitStreamHelper::ReadBool(this->serverControlledSound, stream))
	{
		return false;
	}
	return true;
}

void StartGamePacket::SerializeBody(BitStream *stream)
{
	BitStreamHelper::WriteZigZag64(this->entityID, stream);
	BitStreamHelper::WriteUnsignedVarLong(this->runtimeEntityID, stream);
	BitStreamHelper::WriteZigZag32(this->playerGameMode, stream);
	this->playerPosition.serialize(stream);
	this->rotation.serialize(stream);
	BitStreamHelper::WriteLittleEndian<uint64_t>(this->seed, stream);
	BitStreamHelper::WriteLittleEndian<int16_t>(this->biomeType, stream);
	BitStreamHelper::WriteStringVarInt(this->biomeName, stream);
	BitStreamHelper::WriteZigZag32(this->dimension, stream);
	BitStreamHelper::WriteZigZag32(this->generator, stream);
	BitStreamHelper::WriteZigZag32(this->worldGamemode, stream);
	BitStreamHelper::WriteZigZag32(this->difficulty, stream);
	this->spawnPosition.serialize(stream);
	BitStreamHelper::WriteBool(this->achivementsDisabled, stream);
	BitStreamHelper::WriteBool(this->editorWorld, stream);
	BitStreamHelper::WriteBool(this->createdInEditor, stream);
	BitStreamHelper::WriteBool(this->exportedFromEditor, stream);
	BitStreamHelper::WriteZigZag32(this->dayCycleStopTime, stream);
	BitStreamHelper::WriteZigZag32(this->eduOffer, stream);
	BitStreamHelper::WriteBool(this->eduFeaturesEnabled, stream);
	BitStreamHelper::WriteStringVarInt(this->eduProductUuid, stream);
	BitStreamHelper::WriteLittleEndian<float>(this->rainLevel, stream);
	BitStreamHelper::WriteLittleEndian<float>(this->lightningLevel, stream);
	BitStreamHelper::WriteBool(this->hasConfirmedPlatformLockedContent, stream);
	BitStreamHelper::WriteBool(this->isMultiplayer, stream);
	BitStreamHelper::WriteBool(this->broadcastToLan, stream);
	BitStreamHelper::WriteUnsignedVarInt(this->xboxLiveBroadcastMode, stream);
	BitStreamHelper::WriteUnsignedVarInt(this->platformBroadcastMode, stream);
	BitStreamHelper::WriteBool(this->enableCommands, stream);
	BitStreamHelper::WriteBool(this->isTexturePacksRequired, stream);
	uint32_t gameRuleListSize = static_cast<uint32_t>(this->gameRules.size());
	BitStreamHelper::WriteUnsignedVarInt(gameRuleListSize, stream);
	for (uint32_t i = 0; i < gameRuleListSize; ++i)
	{
		this->gameRules[i].serialize(stream);
	}
	int32_t experimentListSize = static_cast<int32_t>(this->experiments.size());
	BitStreamHelper::WriteLittleEndian<int32_t>(experimentListSize, stream);
	for (int32_t i = 0; i < experimentListSize; ++i)
	{
		this->experiments[i].serialize(stream);
	}
	BitStreamHelper::WriteBool(this->experimentsPreviouslyUsed, stream);
	BitStreamHelper::WriteBool(this->bonusChest, stream);
	BitStreamHelper::WriteBool(this->mapEnabled, stream);
	stream->Write<uint8_t>(this->permissionLevel);
	BitStreamHelper::WriteLittleEndian<int32_t>(this->serverChunkTickRange, stream);
	BitStreamHelper::WriteBool(this->hasLockedBehaviorPack, stream);
	BitStreamHelper::WriteBool(this->hasLockedResourcePack, stream);
	BitStreamHelper::WriteBool(this->isFromLockedWorldTemplate, stream);
	BitStreamHelper::WriteBool(this->msaGamertagsOnly, stream);
	BitStreamHelper::WriteBool(this->isFromWorldTemplate, stream);
	BitStreamHelper::WriteBool(this->isWorldTemplateOptionLocked, stream);
	BitStreamHelper::WriteBool(this->onlySpawnV1Villagers, stream);
	BitStreamHelper::WriteBool(this->personaDisabled, stream);
	BitStreamHelper::WriteBool(this->customSkinsDisabled, stream);
	BitStreamHelper::WriteBool(this->emoteChatMuted, stream);
	BitStreamHelper::WriteStringVarInt(this->gameVersion, stream);
	BitStreamHelper::WriteLittleEndian<int32_t>(this->limitedWorldWidth, stream);
	BitStreamHelper::WriteLittleEndian<int32_t>(this->limitedWorldLength, stream);
	BitStreamHelper::WriteBool(this->isNewNether, stream);
	this->eduResourceUri.serialize(stream);
	BitStreamHelper::WriteBool(this->experimentalGameplayOverride, stream);
	stream->Write<uint8_t>(this->chatRestrictionLevel);
	BitStreamHelper::WriteBool(this->disablePlayerInteractions, stream);
	BitStreamHelper::WriteStringVarInt(this->levelID, stream);
	BitStreamHelper::WriteStringVarInt(this->worldName, stream);
	BitStreamHelper::WriteStringVarInt(this->premiumWorldTemplateID, stream);
	BitStreamHelper::WriteBool(this->isTrail, stream);
	BitStreamHelper::WriteZigZag32(this->movementAuthority, stream);
	BitStreamHelper::WriteZigZag32(this->rewindHistorySize, stream);
	BitStreamHelper::WriteBool(this->serverAuthoritativeBlockBreaking, stream);
	BitStreamHelper::WriteLittleEndian<int64_t>(this->currentTick, stream);
	BitStreamHelper::WriteZigZag32(this->enchantmentSeed, stream);
	uint32_t blockPropertyListSize = static_cast<uint32_t>(this->blockProperties.size());
	BitStreamHelper::WriteUnsignedVarInt(blockPropertyListSize, stream);
	for (uint32_t i = 0; i < blockPropertyListSize; ++i)
	{
		this->blockProperties[i].serialize(stream);
	}
	uint32_t itemStateListSize = static_cast<uint32_t>(this->itemStates.size());
	BitStreamHelper::WriteUnsignedVarInt(itemStateListSize, stream);
	for (uint32_t i = 0; i < itemStateListSize; ++i)
	{
		this->itemStates[i].serialize(stream);
	}
	BitStreamHelper::WriteStringVarInt(this->multiplayerCorrelationID, stream);
	BitStreamHelper::WriteBool(this->serverAuthoritativeInventory, stream);
	BitStreamHelper::WriteStringVarInt(this->engine, stream);
	BitStreamHelper::WriteNbtRootNET(this->propertyData, stream);
	BitStreamHelper::WriteLittleEndian<uint64_t>(this->blockPalletteChecksum, stream);
	BitStreamHelper::WriteUuid(this->worldTemplateID, 4, stream);
	BitStreamHelper::WriteBool(this->clientSideGeneration, stream);
	BitStreamHelper::WriteBool(this->blockNetworkIDsAreHashes, stream);
	BitStreamHelper::WriteBool(this->serverControlledSound, stream);
}

void StartGamePacket::SetEntityID(int64_t entityID)
{
	this->entityID = entityID;
}

void StartGamePacket::SetRuntimeEntityID(uint64_t runtimeEntityID)
{
	this->runtimeEntityID = runtimeEntityID;
}

void StartGamePacket::SetPlayerGameMode(int32_t playerGameMode)
{
	this->playerGameMode = playerGameMode;
}

void StartGamePacket::SetPlayerPosition(Vec3f playerPosition)
{
	this->playerPosition = playerPosition;
}

void StartGamePacket::SetRotation(Vec2f rotation)
{
	this->rotation = rotation;
}

void StartGamePacket::SetSeed(uint64_t seed)
{
	this->seed = seed;
}

void StartGamePacket::SetBiomeType(int16_t biomeType)
{
	this->biomeType = biomeType;
}

void StartGamePacket::SetBiomeName(std::string biomeName)
{
	this->biomeName = biomeName;
}

void StartGamePacket::SetDimension(int32_t dimension)
{
	this->dimension = dimension;
}

void StartGamePacket::SetGenerator(int32_t generator)
{
	this->generator = generator;
}

void StartGamePacket::SetWorldGamemode(int32_t worldGamemode)
{
	this->worldGamemode = worldGamemode;
}

void StartGamePacket::SetDifficulty(int32_t difficulty)
{
	this->difficulty = difficulty;
}

void StartGamePacket::SetSpawnPosition(BlockCoordinates spawnPosition)
{
	this->spawnPosition = spawnPosition;
}

void StartGamePacket::SetAchivementsDisabled(bool achivementsDisabled)
{
	this->achivementsDisabled = achivementsDisabled;
}

void StartGamePacket::SetEditorWorld(bool editorWorld)
{
	this->editorWorld = editorWorld;
}

void StartGamePacket::SetCreatedInEditor(bool createdInEditor)
{
	this->createdInEditor = createdInEditor;
}

void StartGamePacket::SetExportedFromEditor(bool exportedFromEditor)
{
	this->exportedFromEditor = exportedFromEditor;
}

void StartGamePacket::SetDayCycleStopTime(int32_t dayCycleStopTime)
{
	this->dayCycleStopTime = dayCycleStopTime;
}

void StartGamePacket::SetEduOffer(int32_t eduOffer)
{
	this->eduOffer = eduOffer;
}

void StartGamePacket::SetEduFeaturesEnabled(bool eduFeaturesEnabled)
{
	this->eduFeaturesEnabled = eduFeaturesEnabled;
}

void StartGamePacket::SetEduProductUuid(std::string eduProductUuid)
{
	this->eduProductUuid = eduProductUuid;
}

void StartGamePacket::SetRainLevel(float rainLevel)
{
	this->rainLevel = rainLevel;
}

void StartGamePacket::SetLightningLevel(float lightningLevel)
{
	this->lightningLevel = lightningLevel;
}

void StartGamePacket::SetHasConfirmedPlatformLockedContent(bool hasConfirmedPlatformLockedContent)
{
	this->hasConfirmedPlatformLockedContent = hasConfirmedPlatformLockedContent;
}

void StartGamePacket::SetIsMultiplayer(bool isMultiplayer)
{
	this->isMultiplayer = isMultiplayer;
}

void StartGamePacket::SetBroadcastToLan(bool broadcastToLan)
{
	this->broadcastToLan = broadcastToLan;
}

void StartGamePacket::SetXboxLiveBroadcastMode(uint32_t xboxLiveBroadcastMode)
{
	this->xboxLiveBroadcastMode = xboxLiveBroadcastMode;
}

void StartGamePacket::SetPlatformBroadcastMode(uint32_t platformBroadcastMode)
{
	this->platformBroadcastMode = platformBroadcastMode;
}

void StartGamePacket::SetEnableCommands(bool enableCommands)
{
	this->enableCommands = enableCommands;
}

void StartGamePacket::SetIsTexturePacksRequired(bool isTexturePacksRequired)
{
	this->isTexturePacksRequired = isTexturePacksRequired;
}

void StartGamePacket::SetGameRules(GameRuleList_t gameRules)
{
	this->gameRules = gameRules;
}

void StartGamePacket::SetExperiments(ExperimentList_t experiments)
{
	this->experiments = experiments;
}

void StartGamePacket::SetExperimentsPreviouslyUsed(bool experimentsPreviouslyUsed)
{
	this->experimentsPreviouslyUsed = experimentsPreviouslyUsed;
}

void StartGamePacket::SetBonusChest(bool bonusChest)
{
	this->bonusChest = bonusChest;
}

void StartGamePacket::SetMapEnabled(bool mapEnabled)
{
	this->mapEnabled = mapEnabled;
}

void StartGamePacket::SetPermissionLevel(uint8_t permissionLevel)
{
	this->permissionLevel = permissionLevel;
}

void StartGamePacket::SetServerChunkTickRange(int32_t serverChunkTickRange)
{
	this->serverChunkTickRange = serverChunkTickRange;
}

void StartGamePacket::SetHasLockedBehaviorPack(bool hasLockedBehaviorPack)
{
	this->hasLockedBehaviorPack = hasLockedBehaviorPack;
}

void StartGamePacket::SetHasLockedResourcePack(bool hasLockedResourcePack)
{
	this->hasLockedResourcePack = hasLockedResourcePack;
}

void StartGamePacket::SetIsFromLockedWorldTemplate(bool isFromLockedWorldTemplate)
{
	this->isFromLockedWorldTemplate = isFromLockedWorldTemplate;
}

void StartGamePacket::SetMsaGamertagsOnly(bool msaGamertagsOnly)
{
	this->msaGamertagsOnly = msaGamertagsOnly;
}

void StartGamePacket::SetIsFromWorldTemplate(bool isFromWorldTemplate)
{
	this->isFromWorldTemplate = isFromWorldTemplate;
}

void StartGamePacket::SetIsWorldTemplateOptionLocked(bool isWorldTemplateOptionLocked)
{
	this->isWorldTemplateOptionLocked = isWorldTemplateOptionLocked;
}

void StartGamePacket::SetOnlySpawnV1Villagers(bool onlySpawnV1Villagers)
{
	this->onlySpawnV1Villagers = onlySpawnV1Villagers;
}

void StartGamePacket::SetPersonaDisabled(bool personaDisabled)
{
	this->personaDisabled = personaDisabled;
}

void StartGamePacket::SetCustomSkinsDisabled(bool customSkinsDisabled)
{
	this->customSkinsDisabled = customSkinsDisabled;
}

void StartGamePacket::SetEmoteChatMuted(bool emoteChatMuted)
{
	this->emoteChatMuted = emoteChatMuted;
}

void StartGamePacket::SetGameVersion(std::string gameVersion)
{
	this->gameVersion = gameVersion;
}

void StartGamePacket::SetLimitedWorldWidth(int32_t limitedWorldWidth)
{
	this->limitedWorldWidth = limitedWorldWidth;
}

void StartGamePacket::SetLimitedWorldLength(int32_t limitedWorldLength)
{
	this->limitedWorldLength = limitedWorldLength;
}

void StartGamePacket::SetIsNewNether(bool isNewNether)
{
	this->isNewNether = isNewNether;
}

void StartGamePacket::SetEduResourceUri(EducationSharedResourceUri eduResourceUri)
{
	this->eduResourceUri = eduResourceUri;
}

void StartGamePacket::SetExperimentalGameplayOverride(bool experimentalGameplayOverride)
{
	this->experimentalGameplayOverride = experimentalGameplayOverride;
}

void StartGamePacket::SetChatRestrictionLevel(uint8_t chatRestrictionLevel)
{
	this->chatRestrictionLevel = chatRestrictionLevel;
}

void StartGamePacket::SetDisablePlayerInteractions(bool disablePlayerInteractions)
{
	this->disablePlayerInteractions = disablePlayerInteractions;
}

void StartGamePacket::SetLevelID(std::string levelID)
{
	this->levelID = levelID;
}

void StartGamePacket::SetWorldName(std::string worldName)
{
	this->worldName = worldName;
}

void StartGamePacket::SetPremiumWorldTemplateID(std::string premiumWorldTemplateID)
{
	this->premiumWorldTemplateID = premiumWorldTemplateID;
}

void StartGamePacket::SetIsTrail(bool isTrail)
{
	this->isTrail = isTrail;
}

void StartGamePacket::SetMovementAuthority(int32_t movementAuthority)
{
	this->movementAuthority = movementAuthority;
}

void StartGamePacket::SetRewindHistorySize(int32_t rewindHistorySize)
{
	this->rewindHistorySize = rewindHistorySize;
}

void StartGamePacket::SetServerAuthoritativeBlockBreaking(bool serverAuthoritativeBlockBreaking)
{
	this->serverAuthoritativeBlockBreaking = serverAuthoritativeBlockBreaking;
}

void StartGamePacket::SetCurrentTick(int64_t currentTick)
{
	this->currentTick = currentTick;
}

void StartGamePacket::SetEnchantmentSeed(int32_t enchantmentSeed)
{
	this->enchantmentSeed = enchantmentSeed;
}

void StartGamePacket::SetBlockProperties(BlockPropertyList_t blockProperties)
{
	this->blockProperties = blockProperties;
}

void StartGamePacket::SetItemStates(ItemStateList_t itemStates)
{
	this->itemStates = itemStates;
}

void StartGamePacket::SetMultiplayerCorrelationID(std::string multiplayerCorrelationID)
{
	this->multiplayerCorrelationID = multiplayerCorrelationID;
}

void StartGamePacket::SetServerAuthoritativeInventory(bool serverAuthoritativeInventory)
{
	this->serverAuthoritativeInventory = serverAuthoritativeInventory;
}

void StartGamePacket::SetEngine(std::string engine)
{
	this->engine = engine;
}

void StartGamePacket::SetPropertyData(Compound *propertyData)
{
	this->propertyData = propertyData;
}

void StartGamePacket::SetBlockPalletteChecksum(uint64_t blockPalletteChecksum)
{
	this->blockPalletteChecksum = blockPalletteChecksum;
}

void StartGamePacket::SetWorldTemplateID(std::string worldTemplateID)
{
	this->worldTemplateID = worldTemplateID;
}

void StartGamePacket::SetClientSideGeneration(bool clientSideGeneration)
{
	this->clientSideGeneration = clientSideGeneration;
}

void StartGamePacket::SetBlockNetworkIDsAreHashes(bool blockNetworkIDsAreHashes)
{
	this->blockNetworkIDsAreHashes = blockNetworkIDsAreHashes;
}

void StartGamePacket::SetServerControlledSound(bool serverControlledSound)
{
	this->serverControlledSound = serverControlledSound;
}

int64_t StartGamePacket::GetEntityID()
{
	return this->entityID;
}

uint64_t StartGamePacket::GetRuntimeEntityID()
{
	return this->runtimeEntityID;
}

int32_t StartGamePacket::GetPlayerGameMode()
{
	return this->playerGameMode;
}

Vec3f StartGamePacket::GetPlayerPosition()
{
	return this->playerPosition;
}

Vec2f StartGamePacket::GetRotation()
{
	return this->rotation;
}

uint64_t StartGamePacket::GetSeed()
{
	return this->seed;
}

int16_t StartGamePacket::GetBiomeType()
{
	return this->biomeType;
}

std::string StartGamePacket::GetBiomeName()
{
	return this->biomeName;
}

int32_t StartGamePacket::GetDimension()
{
	return this->dimension;
}

int32_t StartGamePacket::GetGenerator()
{
	return this->generator;
}

int32_t StartGamePacket::GetWorldGamemode()
{
	return this->worldGamemode;
}

int32_t StartGamePacket::GetDifficulty()
{
	return this->difficulty;
}

BlockCoordinates StartGamePacket::GetSpawnPosition()
{
	return this->spawnPosition;
}

bool StartGamePacket::GetAchivementsDisabled()
{
	return this->achivementsDisabled;
}

bool StartGamePacket::GetEditorWorld()
{
	return this->editorWorld;
}

bool StartGamePacket::GetCreatedInEditor()
{
	return this->createdInEditor;
}

bool StartGamePacket::GetExportedFromEditor()
{
	return this->exportedFromEditor;
}

int32_t StartGamePacket::GetDayCycleStopTime()
{
	return this->dayCycleStopTime;
}

int32_t StartGamePacket::GetEduOffer()
{
	return this->eduOffer;
}

bool StartGamePacket::GetEduFeaturesEnabled()
{
	return this->eduFeaturesEnabled;
}

std::string StartGamePacket::GetEduProductUuid()
{
	return this->eduProductUuid;
}

float StartGamePacket::GetRainLevel()
{
	return this->rainLevel;
}

float StartGamePacket::GetLightningLevel()
{
	return this->lightningLevel;
}

bool StartGamePacket::GetHasConfirmedPlatformLockedContent()
{
	return this->hasConfirmedPlatformLockedContent;
}

bool StartGamePacket::GetIsMultiplayer()
{
	return this->isMultiplayer;
}

bool StartGamePacket::GetBroadcastToLan()
{
	return this->broadcastToLan;
}

uint32_t StartGamePacket::GetXboxLiveBroadcastMode()
{
	return this->xboxLiveBroadcastMode;
}

uint32_t StartGamePacket::GetPlatformBroadcastMode()
{
	return this->platformBroadcastMode;
}

bool StartGamePacket::GetEnableCommands()
{
	return this->enableCommands;
}

bool StartGamePacket::GetIsTexturePacksRequired()
{
	return this->isTexturePacksRequired;
}

GameRuleList_t StartGamePacket::GetGameRules()
{
	return this->gameRules;
}

ExperimentList_t StartGamePacket::GetExperiments()
{
	return this->experiments;
}

bool StartGamePacket::GetExperimentsPreviouslyUsed()
{
	return this->experimentsPreviouslyUsed;
}

bool StartGamePacket::GetBonusChest()
{
	return this->bonusChest;
}

bool StartGamePacket::GetMapEnabled()
{
	return this->mapEnabled;
}

uint8_t StartGamePacket::GetPermissionLevel()
{
	return this->permissionLevel;
}

int32_t StartGamePacket::GetServerChunkTickRange()
{
	return this->serverChunkTickRange;
}

bool StartGamePacket::GetHasLockedBehaviorPack()
{
	return this->hasLockedBehaviorPack;
}

bool StartGamePacket::GetHasLockedResourcePack()
{
	return this->hasLockedResourcePack;
}

bool StartGamePacket::GetIsFromLockedWorldTemplate()
{
	return this->isFromLockedWorldTemplate;
}

bool StartGamePacket::GetMsaGamertagsOnly()
{
	return this->msaGamertagsOnly;
}

bool StartGamePacket::GetIsFromWorldTemplate()
{
	return this->isFromWorldTemplate;
}

bool StartGamePacket::GetIsWorldTemplateOptionLocked()
{
	return this->isWorldTemplateOptionLocked;
}

bool StartGamePacket::GetOnlySpawnV1Villagers()
{
	return this->onlySpawnV1Villagers;
}

bool StartGamePacket::GetPersonaDisabled()
{
	return this->personaDisabled;
}

bool StartGamePacket::GetCustomSkinsDisabled()
{
	return this->customSkinsDisabled;
}

bool StartGamePacket::GetEmoteChatMuted()
{
	return this->emoteChatMuted;
}

std::string StartGamePacket::GetGameVersion()
{
	return this->gameVersion;
}

int32_t StartGamePacket::GetLimitedWorldWidth()
{
	return this->limitedWorldWidth;
}

int32_t StartGamePacket::GetLimitedWorldLength()
{
	return this->limitedWorldLength;
}

bool StartGamePacket::GetIsNewNether()
{
	return this->isNewNether;
}

EducationSharedResourceUri StartGamePacket::GetEduResourceUri()
{
	return this->eduResourceUri;
}

bool StartGamePacket::GetExperimentalGameplayOverride()
{
	return this->experimentalGameplayOverride;
}

uint8_t StartGamePacket::GetChatRestrictionLevel()
{
	return this->chatRestrictionLevel;
}

bool StartGamePacket::GetDisablePlayerInteractions()
{
	return this->disablePlayerInteractions;
}

std::string StartGamePacket::GetLevelID()
{
	return this->levelID;
}

std::string StartGamePacket::GetWorldName()
{
	return this->worldName;
}

std::string StartGamePacket::GetPremiumWorldTemplateID()
{
	return this->premiumWorldTemplateID;
}

bool StartGamePacket::GetIsTrail()
{
	return this->isTrail;
}

int32_t StartGamePacket::GetMovementAuthority()
{
	return this->movementAuthority;
}

int32_t StartGamePacket::GetRewindHistorySize()
{
	return this->rewindHistorySize;
}

bool StartGamePacket::GetServerAuthoritativeBlockBreaking()
{
	return this->serverAuthoritativeBlockBreaking;
}

int64_t StartGamePacket::GetCurrentTick()
{
	return this->currentTick;
}

int32_t StartGamePacket::GetEnchantmentSeed()
{
	return this->enchantmentSeed;
}

BlockPropertyList_t StartGamePacket::GetBlockProperties()
{
	return this->blockProperties;
}

ItemStateList_t StartGamePacket::GetItemStates()
{
	return this->itemStates;
}

std::string StartGamePacket::GetMultiplayerCorrelationID()
{
	return this->multiplayerCorrelationID;
}

bool StartGamePacket::GetServerAuthoritativeInventory()
{
	return this->serverAuthoritativeInventory;
}

std::string StartGamePacket::GetEngine()
{
	return this->engine;
}

Compound *StartGamePacket::GetPropertyData()
{
	return this->propertyData;
}

uint64_t StartGamePacket::GetBlockPalletteChecksum()
{
	return this->blockPalletteChecksum;
}

std::string StartGamePacket::GetWorldTemplateID()
{
	return this->worldTemplateID;
}

bool StartGamePacket::GetClientSideGeneration()
{
	return this->clientSideGeneration;
}

bool StartGamePacket::GetBlockNetworkIDsAreHashes()
{
	return this->blockNetworkIDsAreHashes;
}

bool StartGamePacket::GetServerControlledSound()
{
	return this->serverControlledSound;
}
