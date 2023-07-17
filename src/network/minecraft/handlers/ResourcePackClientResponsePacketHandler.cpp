#include <network/minecraft/handlers/ResourcePackClientResponsePacketHandler.h>

bool ResourcePackClientResponsePacketHandler::ProcessPacket(MinecraftPacket *normalPacket, Player *player)
{
	ResourcePackClientResponsePacket *packet = (ResourcePackClientResponsePacket *)normalPacket;
	uint8_t responseStatus = packet->GetResponseStatus();
	if (responseStatus == ResourcePackClientResponses::Refused())
	{
		printf("ResourcePackClient Refused\n");
	}
	else if (responseStatus == ResourcePackClientResponses::SendPacks())
	{
		printf("ResourcePackClient SendPacks\n");
	}
	else if (responseStatus == ResourcePackClientResponses::None() || responseStatus == ResourcePackClientResponses::HaveAllPacks())
	{
		ResourcePackStackPacket *resourcePackStack = new ResourcePackStackPacket();
		resourcePackStack->SetMustAccept(false);
		resourcePackStack->SetBehaviorPacks({});
		resourcePackStack->SetResourcePacks({});
		resourcePackStack->SetGameVersion(MINECRAFT_VERSION);
		resourcePackStack->SetExperiments({});
		resourcePackStack->SetExperimentPreviouslyUsed(false);
		player->SendPacket(resourcePackStack);
		printf("Sending resource pack stack\n");
	}
	else if (responseStatus == ResourcePackClientResponses::Completed())
	{
		printf("Sending start game packet\n");
		StartGamePacket *startGame = new StartGamePacket();
		startGame->SetEntityID(1);
		startGame->SetRuntimeEntityID(1);
		startGame->SetPlayerGameMode(GameModes::Creative());
		startGame->SetPlayerPosition(Vec3f::make(0.0f, 6.0f, 0.0f));
		startGame->SetRotation(Vec2f::make(0.0f, 0.0f));
		startGame->SetSeed(0);
		startGame->SetBiomeType(0);
		startGame->SetBiomeName("Plains");
		startGame->SetDimension(Dimensions::Overworld());
		startGame->SetGenerator(Generators::Infinite());
		startGame->SetWorldGamemode(GameModes::Survival());
		startGame->SetDifficulty(Difficulties::Peaceful());
		startGame->SetSpawnPosition(BlockCoordinates::make(0, 6, 0));
		startGame->SetAchivementsDisabled(true);
		startGame->SetEditorWorld(false);
		startGame->SetCreatedInEditor(false);
		startGame->SetExportedFromEditor(false);
		startGame->SetDayCycleStopTime(0);
		startGame->SetEduOffer(0);
		startGame->SetEduFeaturesEnabled(false);
		startGame->SetEduProductUuid("9bc3f8b9-1541-4e64-88e9-ae11e01a9d83");
		startGame->SetRainLevel(0.0f);
		startGame->SetLightningLevel(0.0f);
		startGame->SetHasConfirmedPlatformLockedContent(false);
		startGame->SetIsMultiplayer(true);
		startGame->SetBroadcastToLan(true);
		startGame->SetXboxLiveBroadcastMode(XboxLiveBroadcastModes::Public());
		startGame->SetPlatformBroadcastMode(XboxLiveBroadcastModes::Public());
		startGame->SetEnableCommands(false);
		startGame->SetIsTexturePacksRequired(false);
		startGame->SetGameRules({});
		startGame->SetExperiments({});
		startGame->SetExperimentsPreviouslyUsed(false);
		startGame->SetBonusChest(false);
		startGame->SetMapEnabled(false);
		startGame->SetPermissionLevel(PermissionLevels::Member());
		startGame->SetServerChunkTickRange(0);
		startGame->SetHasLockedBehaviorPack(false);
		startGame->SetHasLockedResourcePack(false);
		startGame->SetIsFromLockedWorldTemplate(false);
		startGame->SetMsaGamertagsOnly(false);
		startGame->SetIsFromWorldTemplate(false);
		startGame->SetIsWorldTemplateOptionLocked(false);
		startGame->SetOnlySpawnV1Villagers(true);
		startGame->SetPersonaDisabled(false);
		startGame->SetCustomSkinsDisabled(false);
		startGame->SetEmoteChatMuted(true);
		startGame->SetGameVersion(MINECRAFT_VERSION);
		startGame->SetLimitedWorldWidth(0);
		startGame->SetLimitedWorldLength(0);
		startGame->SetIsNewNether(false);
		startGame->SetEduResourceUri(EducationSharedResourceUri::make("", ""));
		startGame->SetExperimentalGameplayOverride(false);
		startGame->SetChatRestrictionLevel(ChatRestrictionLevels::None());
		startGame->SetDisablePlayerInteractions(false);
		startGame->SetLevelID("7046fb74-08aa-4f6a-92c3-69ad0216ec4e");
		startGame->SetWorldName(ALLAYBE_NAME);
		startGame->SetPremiumWorldTemplateID("09d97971-7a41-40a1-a99f-ae2e4cad1dcf");
		startGame->SetIsTrail(false);
		startGame->SetMovementAuthority(MovementAuthorities::Client());
		startGame->SetRewindHistorySize(0);
		startGame->SetServerAuthoritativeBlockBreaking(false);
		startGame->SetCurrentTick(0);
		startGame->SetEnchantmentSeed(0);
		startGame->SetBlockProperties({});
		startGame->SetItemStates({});
		startGame->SetMultiplayerCorrelationID("");
		startGame->SetServerAuthoritativeInventory(false);
		startGame->SetEngine(ALLAYBE_ENGINE);
		startGame->SetPropertyData(new Compound("", {}));
		startGame->SetBlockPalletteChecksum(0);
		startGame->SetWorldTemplateID("b9c9710f-47a7-4cc6-9b82-b45fc15435a4");
		startGame->SetClientSideGeneration(false);
		startGame->SetBlockNetworkIDsAreHashes(false);
		startGame->SetServerControlledSound(false);
		player->SendPacket(startGame);

		BiomeDefinitionListPacket *biomeDefinitionList = new BiomeDefinitionListPacket();
		player->SendPacket(biomeDefinitionList);
		CreativeContentPacket *creativeContent = new CreativeContentPacket();
		player->SendPacket(creativeContent);

		player->SendPlayStatus(PlayStatusTypes::PlayerSpawn());
	}
	return true;
}