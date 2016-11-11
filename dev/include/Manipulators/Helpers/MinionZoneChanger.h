#pragma once

#include "Entity/Card.h"
#include "Entity/CardZone.h"
#include "EntitiesManager/CardRef.h"
#include "State/State.h"
#include "State/PlayerIdentifier.h"
#include "State/Player.h"

namespace Manipulators
{
	namespace Helpers
	{
		class MinionZoneChanger
		{
		public:
			MinionZoneChanger(EntitiesManager& mgr, CardRef card_ref, Entity::Card &card) : mgr_(mgr), card_ref_(card_ref), card_(card) {}

			void Change(State::State & state, State::PlayerIdentifier player_identifier, Entity::CardZone zone, int pos)
			{
				Remove(state);

				auto location_setter = card_.GetLocationSetter();
				location_setter.SetPlayerIdentifier(player_identifier);
				location_setter.SetZone(zone);
				location_setter.SetZonePosition(pos);

				Add(state);
			}

			void Add(State::State & state)
			{
				switch (card_.GetZone())
				{
				case Entity::kCardZonePlay:
					return AddToPlayZone(state);
				}
			}

		private:
			void AddToPlayZone(State::State & state)
			{
				State::Player & player = state.players.Get(card_.GetPlayerIdentifier());

				player.minions_.GetLocationManipulator().Insert(mgr_, card_ref_);
			}

			void Remove(State::State & state)
			{
				switch (card_.GetZone())
				{
				case Entity::kCardZonePlay:
					return RemoveFromPlayZone(state);
				}
			}

			void RemoveFromPlayZone(State::State & state)
			{
				State::Player & player = state.players.Get(card_.GetPlayerIdentifier());

				player.minions_.GetLocationManipulator().Remove(mgr_, card_.GetZonePosition());
			}

		private:
			EntitiesManager & mgr_;
			CardRef card_ref_;
			Entity::Card & card_;
		};
	}
}