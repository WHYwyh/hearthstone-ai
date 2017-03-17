#pragma once

namespace Cards
{
	struct Card_EX1_089 : public MinionCardBase<Card_EX1_089> {
		static void Battlecry(Contexts::Battlecry context) {
			AnotherPlayer(context).GainEmptyCrystal();
		}
	};

	struct Card_NEW1_038_Enchant : public EnchantmentCardBase {
		static constexpr EnchantmentTiers tier = EnchantmentTiers::kEnchantmentTier1;

		Card_NEW1_038_Enchant() {
			apply_functor = [](auto& stats) {
				++stats.attack;
				++stats.max_hp;
			};
		}
	};

	struct Card_NEW1_038 : public MinionCardBase<Card_NEW1_038> {
		template <typename Context>
		static bool HandleEvent(state::CardRef self, Context&& context) {
			Manipulate(context).Card(self).Enchant().Add(Card_NEW1_038_Enchant());
			return true;
		};

		Card_NEW1_038() {
			RegisterEvent<InPlayZone, NonCategorized_SelfInLambdaCapture,
				state::Events::EventTypes::OnTurnEnd>();
		}
	};

	struct Card_EX1_020 : public MinionCardBase<Card_EX1_020, Shield> {};
	struct Card_CS1_069 : public MinionCardBase<Card_CS1_069, Taunt> {};

	struct Card_CS2_203 : public MinionCardBase<Card_CS2_203> {
		static auto GetBattlecryTargets(Contexts::BattlecryTargetGetter context) {
			return Targets().Minion().Targetable();
		}
		static void Battlecry(Contexts::Battlecry context) {
			return Manipulate(context).Minion(context.GetTarget()).Silence();
		}
	};
}

REGISTER_MINION_CARD(CS2_203)

REGISTER_MINION_CARD(EX1_089)
REGISTER_MINION_CARD(NEW1_038)
REGISTER_MINION_CARD(EX1_020)
REGISTER_MINION_CARD(CS1_069)
