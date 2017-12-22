#pragma once

#include <utility>
#include "MCTS/selection/Selection.h"
#include "MCTS/simulation/Simulation.h"
#include "MCTS/Statistic.h"
#include "MCTS/Types.h"
#include "MCTS/builder/TreeUpdater.h"
#include "MCTS/board/Board.h"
#include "MCTS/board/ActionParameterGetter.h"
#include "MCTS/board/RandomGenerator.h"
#include "MCTS/builder/ActionReplayer.h"

namespace mcts
{
	namespace builder
	{
		// Traverse and build a game tree in a monte-carlo fashion
		class TreeBuilder
		{
		public:
			typedef selection::TreeNode TreeNode;

			TreeBuilder(state::PlayerSide side, SOMCTS & caller, Statistic<> & statistic,
				std::mt19937 & selection_rand, std::mt19937 & simulation_rand)
				:
				statistic_(statistic),
				action_parameter_getter_(caller), random_generator_(caller),
				board_(nullptr),
				selection_stage_(side, selection_rand), simulation_stage_(side, simulation_rand)
			{
			}

			TreeBuilder(TreeBuilder const&) = delete;
			TreeBuilder & operator=(TreeBuilder const&) = delete;

			struct SelectResult
			{
				FlowControl::Result result; // Never returns kResultInvalid
				bool change_to_simulation;
				TreeNode * node;

				SelectResult(FlowControl::Result new_result) :
					result(new_result),
					change_to_simulation(false),
					node(nullptr)
				{}
			};
			
			// Note: can only be called when current player is the viewer of 'board'
			SelectResult PerformSelect(TreeNode * node, board::Board const& board,
				detail::BoardNodeMap & last_node_map, TreeUpdater * updater);

			// Note: can only be called when current player is the viewer of 'board'
			FlowControl::Result PerformSimulate(board::Board const& board);

		private:
			template <typename StageHandler>
			FlowControl::Result ApplyAction(StageHandler&& stage_handler);

		public: // for callbacks: action-parameter-getter and random-generator
			int ChooseSelectAction(FlowControl::ActionType action_type, FlowControl::ActionChoices const& choices);
			int ChooseSimulateAction(FlowControl::ActionType action_type, FlowControl::ActionChoices const& choices);

		private:
			Statistic<> & statistic_;

			board::ActionParameterGetter action_parameter_getter_;
			board::RandomGenerator random_generator_;
			board::Board const* board_;

			selection::Selection selection_stage_;
			simulation::Simulation simulation_stage_;
		};
	}
}