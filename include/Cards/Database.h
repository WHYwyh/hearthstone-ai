#pragma once

#include <assert.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include "json/json.h"

#include "Cards/CardData.h"
#include "State/Types.h"
#include "State/Cards/CardData.h"

namespace Cards
{
	class Database
	{
	public:
		static Database & GetInstance()
		{
			static Database instance;
			return instance;
		}

	public:
		bool LoadJsonFile(std::string const& path)
		{
			Json::Reader reader;
			Json::Value cards_json;

			std::ifstream cards_file(path);

			if (reader.parse(cards_file, cards_json, false) == false) return false;

			return this->ReadFromJson(cards_json);
		}

		std::unordered_map<std::string, int> GetIdMap() const { return origin_id_map_; }

		CardData const& Get(int id)
		{
			assert(id >= 0);
			assert(id < final_cards_size_);
			return final_cards_[id];
		}

	private:
		Database() { }

		bool ReadFromJson(Json::Value const & cards_json)
		{
			if (cards_json.isArray() == false) return false;

			std::vector<CardData> cards;

			// Reserve id = 0
			cards.push_back(CardData());

			origin_id_map_.clear();
			for (auto const& card_json : cards_json) {
				this->AddCard(card_json, cards);
			}

			if (final_cards_) { delete[] final_cards_; }

			final_cards_size_ = (int)cards.size();
			final_cards_ = new CardData[final_cards_size_];

			// Copy to raw array to support lock-free access
			for (int i = 0; i < cards.size(); ++i) {
				final_cards_[i] = cards[i];
			}

			return true;
		}

		void AddCard(Json::Value const& json, std::vector<CardData> & cards)
		{
			const std::string origin_id = json["id"].asString();
			const std::string type = json["type"].asString();

			if (origin_id_map_.find(origin_id) != origin_id_map_.end()) {
				throw std::exception("Card ID string collision.");
			}

			CardData new_card;
			new_card.card_id = (int)cards.size();

			if (type == "MINION") {
				new_card.card_type = state::kCardTypeMinion;
			}
			else if (type == "SPELL") {
				new_card.card_type = state::kCardTypeSpell;
			}
			else if (type == "WEAPON") {
				new_card.card_type = state::kCardTypeWeapon;
			}
			else if (type == "HERO_POWER") {
				new_card.card_type = state::kCardTypeHeroPower;
			}
			else {
				return; // ignored
			}

			new_card.cost = json["cost"].asInt();
			new_card.attack = json["attack"].asInt();
			new_card.max_hp = json["health"].asInt();

			origin_id_map_[origin_id] = new_card.card_id;
			cards.push_back(new_card);
		}

	private:
		CardData * final_cards_; // Raw array to support lock-free access
		int final_cards_size_;

		std::unordered_map<std::string, int> origin_id_map_;
	};
}