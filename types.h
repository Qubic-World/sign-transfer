#pragma once
#include <cstdint>

namespace transfer
{
	namespace size
	{
		constexpr uint8_t seed_len{55};
		constexpr uint8_t id_len{70};
		constexpr uint8_t signature_size{64};
		constexpr uint8_t digest_size{32};
		constexpr uint8_t key_size{32};
	}

	namespace types
	{
		using seed_type = uint8_t[size::seed_len + 1];
		using id_type = uint8_t[size::id_len + 1];
		using identity_type = uint16_t[size::id_len + 1];
		using amount_type = uint64_t;
		using tick_type = uint32_t;
		using subseed_type = uint8_t[32];

		using key_type = uint8_t[size::key_size];
		using description_size_type = uint32_t;
		using signature_type = uint8_t[64];

		using digest_type = uint8_t[size::digest_size];
	}
}
