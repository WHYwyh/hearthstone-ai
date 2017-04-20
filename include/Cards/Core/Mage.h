#pragma once

// http://www.hearthpwn.com/cards?filter-premium=1&filter-set=2&filter-class=16&sort=-cost&display=1
// Finished: Polymorph

namespace Cards
{
	struct Card_CS2_034 : public HeroPowerCardBase<Card_CS2_034> {
		Card_CS2_034() {
			onplay_handler.SetSpecifyTargetCallback([](Contexts::SpecifiedTargetGetter const& context) {
				*context.targets_ = TargetsGenerator(context.player_).SpellTargetable().GetInfo();
				return true;
			});
			onplay_handler.SetOnPlayCallback([](FlowControl::onplay::context::OnPlay const& context) {
				context.manipulate_
					.OnBoardCharacter(context.GetTarget())
					.Damage(context.card_ref_, 1);
			});
		}
	};

	struct Card_EX1_277 : SpellCardBase<Card_EX1_277> {
		Card_EX1_277() {
			onplay_handler.SetOnPlayCallback([](FlowControl::onplay::context::OnPlay const& context) {
				int damage = 0;
				context.manipulate_
					.Board()
					.CalculateFinalDamageAmount(context.card_ref_, 3, &damage);

				Targets targets = TargetsGenerator(context.player_).Enemy(context).Alive().GetInfo();
				for (int i = 0; i < damage; ++i) {
					state::CardRef target = context.manipulate_.GetRandomTarget(targets);
					assert(target.IsValid());
					context.manipulate_
						.OnBoardCharacter(target)
						.ConductFinalDamage(context.card_ref_, 1);
				}
			});
		}
	};

	struct Card_CS2_mirror : MinionCardBase<Card_CS2_mirror, Taunt> {};
	struct Card_CS2_027 : SpellCardBase<Card_CS2_027> {
		Card_CS2_027() {
			onplay_handler.SetSpecifyTargetCallback([](Contexts::SpecifiedTargetGetter const& context) {
				if (context.manipulate_.Board().Player(context.player_).minions_.Full()) return false;
				return true;
			});
			onplay_handler.SetOnPlayCallback([](FlowControl::onplay::context::OnPlay const& context) {
				SummonToRightmost(context.manipulate_, context.player_, Cards::ID_CS2_mirror);
				SummonToRightmost(context.manipulate_, context.player_, Cards::ID_CS2_mirror);
			});
		}
	};

	struct Card_CS2_025 : public SpellCardBase<Card_CS2_025> {
		Card_CS2_025() {
			onplay_handler.SetOnPlayCallback([](FlowControl::onplay::context::OnPlay const& context) {
				int spell_damage = context.manipulate_.Board().GetSpellDamage(context.player_);
				context.manipulate_.Board().Player(context.player_.Opposite()).minions_.ForEach([&](state::CardRef card_ref) {
					context.manipulate_.OnBoardMinion(card_ref).Damage(context.card_ref_, 1 + spell_damage);
				});
			});
		}
	};

	struct Card_CS2_024 : public SpellCardBase<Card_CS2_024> {
		Card_CS2_024() {
			onplay_handler.SetSpecifyTargetCallback([](Contexts::SpecifiedTargetGetter const& context) {
				*context.allow_no_target_ = false;
				*context.targets_ = TargetsGenerator(context.player_).SpellTargetable().GetInfo();
				return true;
			});
			onplay_handler.SetOnPlayCallback([](FlowControl::onplay::context::OnPlay const& context) {
				int spell_damage = context.manipulate_.Board().GetSpellDamage(context.player_);
				state::CardRef target = context.GetTarget();
				context.manipulate_.OnBoardCharacter(target).Damage(context.card_ref_, 3 + spell_damage);
				context.manipulate_.OnBoardCharacter(target).Freeze(true);
			});
		}
	};

	struct Card_CS2_023 : public SpellCardBase<Card_CS2_023> {
		Card_CS2_023() {
			onplay_handler.SetOnPlayCallback([](FlowControl::onplay::context::OnPlay const& context) {
				context.manipulate_.Hero(context.player_).DrawCard();
				context.manipulate_.Hero(context.player_).DrawCard();
			});
		}
	};

	struct Card_CS2_026 : public SpellCardBase<Card_CS2_026> {
		Card_CS2_026() {
			onplay_handler.SetOnPlayCallback([](FlowControl::onplay::context::OnPlay const& context) {
				context.manipulate_.Board().Player(context.player_.Opposite()).minions_.ForEach([&](state::CardRef card_ref) {
					context.manipulate_.OnBoardMinion(card_ref).Freeze(true);
				});
			});
		}
	};

	struct Card_CS2_029 : SpellCardBase<Card_CS2_029> {
		Card_CS2_029() {
			onplay_handler.SetSpecifyTargetCallback([](Contexts::SpecifiedTargetGetter const& context) {
				*context.allow_no_target_ = false;
				*context.targets_ = TargetsGenerator(context.player_).SpellTargetable().GetInfo();
				return true;
			});
			onplay_handler.SetOnPlayCallback([](FlowControl::onplay::context::OnPlay const& context) {
				int spell_damage = context.manipulate_.Board().GetSpellDamage(context.player_);
				state::CardRef target = context.GetTarget();
				assert(target.IsValid());
				context.manipulate_.OnBoardCharacter(target).Damage(context.card_ref_, 6 + spell_damage);
			});
		}
	};

	struct Card_CS2_022 : public SpellCardBase<Card_CS2_022> {
		Card_CS2_022() {
			onplay_handler.SetSpecifyTargetCallback([](FlowControl::onplay::context::GetSpecifiedTarget const& context) {
				*context.allow_no_target_ = false;
				*context.targets_ = TargetsGenerator(context.player_).Minion().SpellTargetable().GetInfo();
				return true;
			});
			onplay_handler.SetOnPlayCallback([](FlowControl::onplay::context::OnPlay const& context) {
				context.manipulate_
					.OnBoardMinion(context.GetTarget())
					.Transform(CardId::ID_CS2_tk1);
			});
		}
	};

	struct Card_CS2_033 : public MinionCardBase<Card_CS2_033, FreezeAttack> {};

	struct Card_CS2_032 : public SpellCardBase<Card_CS2_032> {
		Card_CS2_032() {
			onplay_handler.SetOnPlayCallback([](FlowControl::onplay::context::OnPlay const& context) {
				int damage = 4 + context.manipulate_.Board().GetSpellDamage(context.player_);
				context.manipulate_.Board().Player(context.player_.Opposite()).minions_.ForEach([&](state::CardRef minion) {
					context.manipulate_.OnBoardMinion(minion).Damage(context.card_ref_, damage);
				});
			});
		}
	};
}

REGISTER_CARD(CS2_032)
REGISTER_CARD(CS2_033)
REGISTER_CARD(CS2_022)
REGISTER_CARD(CS2_029)
REGISTER_CARD(CS2_026)
REGISTER_CARD(CS2_023)
REGISTER_CARD(CS2_024)
REGISTER_CARD(CS2_025)
REGISTER_CARD(CS2_027)
REGISTER_CARD(CS2_mirror)
REGISTER_CARD(EX1_277)
REGISTER_CARD(CS2_034)
