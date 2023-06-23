#pragma once

#include "MinecraftPacket.h"

class NetworkSettingsPacket : public MinecraftPacket
{
protected:
	uint16_t compressionThreshold;
	uint16_t compressionAlgorithm;
	bool clientThrottle;
	uint8_t clientThrottleThreshold;
	float clientThrottleScalar;

public:
	virtual uint32_t GetID() const override;

	virtual void DeserializeHeader(BitStream *stream) override { MinecraftPacket::DeserializeHeader(stream); }
	virtual void SerializeHeader(BitStream *stream) override { MinecraftPacket::SerializeHeader(stream); }

	virtual bool DeserializeBody(BitStream *stream) override;
	virtual void SerializeBody(BitStream *stream) override;

	void SetCompressionThreshold(uint16_t value);
	void SetCompressionAlgorithm(uint16_t value);
	void SetClientThrottle(bool value);
	void SetClientThrottleThreshold(uint8_t value);
	void SetClientThrottleScalar(float value);

	uint16_t GetCompressionThreshold();
	uint16_t GetCompressionAlgorithm();
	bool GetClientThrottle();
	uint8_t GetClientThrottleThreshold();
	float GetClientThrottleScalar();
};