#include <iostream>
#include <string>
#include <tuple>

#include "types.h"
#include "algorithms/Identity.h"

using namespace transfer::types;
using namespace transfer::size;


template <typename Type>
class clear_value final
{
public:
	clear_value() = delete;

	clear_value(Type& value):
		value_(value)
	{
	}

	~clear_value()
	{
		memset(&value_, 0, sizeof(Type));
	}

private:
	Type& value_;
};

struct transfer_payload
{
	key_type source_public{};
	key_type destination_public{};
	amount_type amount{};
	tick_type tick{};
	description_size_type description_size{};
	signature_type signature{};

	std::string to_json()
	{
		auto identity_to_id = [](const identity_type& identity, id_type& id)
		{
			for (int32_t i = 0; i < id_len + 1; ++i)
			{
				id[i] = static_cast<uint8_t>(identity[i]);
			}
		};

		identity_type source_identity{};
		identity_type destination_identity{};
		id_type source_id{};
		id_type dest_id{};
		getIdentity(source_public, source_identity);
		getIdentity(destination_public, destination_identity);
		identity_to_id(source_identity, source_id);
		identity_to_id(destination_identity, dest_id);

		std::string json;
		json += "{\n";
		json += R"("source":")";
		json += std::string(std::begin(source_id), std::end(source_id) - 1);
		json += "\",\n";
		json += R"("destination":")";
		json += std::string(std::begin(dest_id), std::end(dest_id) - 1);
		json += "\",\n";
		json += R"("amount":)";
		json += std::to_string(amount);
		json += ",\n";
		json += R"("tick":)";
		json += std::to_string(tick);
		json += ",\n";
		json += R"("description_size":)";
		json += std::to_string(description_size);
		json += ",\n";
		json += R"("description":)";
		json += "\"\"";
		json += ",\n";
		json += R"("signature":")";
		std::string signature_str;
		for (const auto& symbol : signature)
		{
			signature_str += std::to_string(symbol);
			signature_str += ".";
		}
		signature_str.erase(signature_str.length() - 1);
		// json += std::string(std::begin(signature), std::end(signature));
		json += signature_str;
		json += "\"\n}";

		return json;
	}

	void from_json(const std::string& json)
	{
		auto get_str = [&](const char* name, std::string& str, const size_t& len) -> bool
		{
			const auto pos{json.find(name)};
			if (pos == std::string::npos)
			{
				return false;
			}

			str = json.substr(pos + std::strlen(name), len);

			return true;
		};

		auto get_number = [&]<typename T>(const char* name, T& number) -> bool
		{
			const auto name_len{std::strlen(name)};
			const auto found_pos{json.find(name)};
			if (found_pos == std::string::npos)
			{
				return false;
			}
			constexpr auto comma_str{","};
			const auto comma_pos{json.find(comma_str, found_pos)};
			if (comma_pos == std::string::npos)
			{
				return false;
			}

			const auto substr_start{found_pos + name_len};
			const auto substr_end{comma_pos - substr_start};
			number = std::stoi(json.substr(substr_start, substr_end));
			return true;
		};

		/** Source*/
		constexpr auto source_str{R"("source":")"};
		std::string source_id{};
		get_str(source_str, source_id, id_len);
		getPublicKeyFromIdentity(reinterpret_cast<uint8_t*>(source_id.data()), this->source_public);

		/** Destination*/
		constexpr auto destination_str{R"("destination":")"};
		std::string destination_id{};
		get_str(destination_str, destination_id, id_len);
		getPublicKeyFromIdentity(reinterpret_cast<uint8_t*>(destination_id.data()), this->destination_public);

		/** Amount*/
		if (!get_number(R"("amount":)", this->amount))
		{
			clear();
			return;
		}

		/** Tick*/
		if (!get_number(R"("tick":)", this->tick))
		{
			clear();
			return;
		}

		/** Description size*/
		if (!get_number(R"("description_size":)", this->description_size))
		{
			clear();
			return;
		}

		/** Signature*/
		std::string signature_str{};
		constexpr auto signature_name{R"("signature":")"};
		const auto signature_start{json.find(signature_name) + std::strlen(signature_name)};
		const auto signature_end{json.find('"', signature_start)};
		if (!get_str(R"("signature":")", signature_str, signature_end - signature_start))
		{
			clear();
			return;
		}

		std::string value_concat;
		uint8_t signature_idx{0};
		for (const auto& value : signature_str)
		{
			if (value == '.')
			{
				this->signature[signature_idx++] = std::stoi(value_concat);
				value_concat.clear();
			}
			else
			{
				value_concat += value;
			}
		}
	}

	void clear()
	{
		memset(this, 0, sizeof(transfer_payload));
	}
};

bool seed_to_public_key(const seed_type& seed, key_type& public_key)
{
	subseed_type subseed;
	if (!getSubseed(seed, subseed))
	{
		return false;
	}

	key_type private_key{};
	clear_value<key_type> clear_private{private_key};
	getPrivateKey(subseed, private_key);
	getPublicKey(private_key, public_key);
	return true;
}

class transformation final
{
public:
	transformation() = delete;

	transformation(seed_type& seed, id_type& id, amount_type& amount, tick_type& tick):
		seed_(seed), id_(id), amount_(amount), tick_(tick)
	{
	}

	[[nodiscard]] std::tuple<bool, transfer_payload> get_transfer_payload() const
	{
		transfer_payload payload;
		if (!seed_to_public_key(seed_, payload.source_public))
		{
			return std::make_tuple(false, transfer_payload());
		}

		/** Destination*/
		getPublicKeyFromIdentity(id_, payload.destination_public);

		payload.amount = amount_;
		payload.tick = tick_;
		payload.description_size = 0;

		/** Kangaroo Twelve*/
		payload.source_public[0] ^= 6;
		constexpr auto payload_size{sizeof(transfer_payload) - signature_size};
		digest_type digest;
		KangarooTwelve(reinterpret_cast<uint8_t*>(&payload), payload_size, digest, digest_size);
		payload.source_public[0] ^= 6;

		/** FourQ*/
		subseed_type subseed;
		if (!getSubseed(seed_, subseed))
		{
			return std::make_tuple(false, transfer_payload());
		}
		sign(subseed, payload.source_public, digest, payload.signature);

		return std::make_tuple(true, payload);
	}

private:
	seed_type& seed_;
	id_type& id_;
	amount_type& amount_;
	tick_type& tick_;
};

int main(int argc, char* argv[])
{
	std::wcout << L"Hello friend!" << std::endl;

	/** Seed*/
	std::wcout << L"Seed: ";
	seed_type seed{};
	clear_value<seed_type> mutex_value(seed);
	std::cin >> seed;
	if (std::strlen(reinterpret_cast<const char*>(seed)) != seed_len)
	{
		std::wcerr << L"Invalid Seed" << std::endl;
		return EXIT_FAILURE;
	}

	/** Source ID*/
	std::wcout << L"Your ID: ";
	key_type public_key{};
	seed_to_public_key(seed, public_key);
	uint16_t source_id[id_len + 1]{};
	getIdentity(public_key, source_id);
	/** Cout ID*/
	for (const auto& symbol : source_id)
	{
		std::cout << static_cast<uint8_t>(symbol);
	}
	std::cout << std::endl;

	/** Destination */
	std::wcout << L"Destination ID: ";
	id_type destination_id{};
	std::cin >> destination_id;
	if (std::strlen(reinterpret_cast<const char*>(destination_id)) != id_len)
	{
		std::wcerr << L"Invalid ID" << std::endl;
		return EXIT_FAILURE;
	}

	/** Amount*/
	std::wcout << L"Amount: ";
	const amount_type amount_min{static_cast<uint32_t>(std::pow(10, 6))};
	const amount_type amount_max{static_cast<uint32_t>(std::pow(10, 15))};
	amount_type amount{};
	std::cin >> amount;
	if (amount < amount_min || amount > amount_max)
	{
		std::wcerr << L"Invalid Amount" << std::endl;
		return EXIT_FAILURE;
	}

	/** Tick*/
	std::wcout << L"Tick when the transfer can be processed: " << std::endl;
	tick_type tick{};
	std::cin >> tick;
	if (tick == 0)
	{
		std::wcerr << L"Invalid Tick" << std::endl;
		return EXIT_FAILURE;
	}

	const auto transformation_payload{transformation(seed, destination_id, amount, tick)};
	auto result{transformation_payload.get_transfer_payload()};
	if (!std::get<0>(result))
	{
		std::wcerr << L"Failed to prepare data" << std::endl;
		return EXIT_FAILURE;
	}

	/** Result*/
	auto& payload{std::get<1>(result)};
	std::wcout << L"Result:" << std::endl;
	const std::string json{payload.to_json()};
	std::cout << json << std::endl;

	return EXIT_SUCCESS;
	
	/** Checker*/
	transfer_payload payload_from_json;
	payload_from_json.from_json(json);

	std::wcout << L"Checker:\n";
	std::cout << (memcmp(&payload, &payload_from_json, sizeof(transfer_payload)) == 0) << std::endl;

	return EXIT_SUCCESS;
}
