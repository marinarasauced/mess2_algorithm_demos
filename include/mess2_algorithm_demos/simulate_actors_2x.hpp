#ifndef MESS2_ALGORITHM_DEMOS_SIMUALTE_ACTORS_2X_HPP
#define MESS2_ALGORITHM_DEMOS_SIMUALTE_ACTORS_2X_HPP

#include "mess2_algorithm_threat_static/threat.hpp"
#include "mess2_algorithm_plugins/actor.hpp"
#include "mess2_algorithm_plugins/constraint.hpp"
#include "mess2_algorithm_plugins/graph.hpp"
#include "mess2_algorithm_plugins/high_level_queue.hpp"
#include "mess2_algorithm_plugins/high_level_search.hpp"
#include "mess2_algorithm_plugins/low_level_history.hpp"
#include "mess2_algorithm_plugins/low_level_queue.hpp"
#include "mess2_algorithm_plugins/low_level_search.hpp"

#include "rclcpp/rclcpp.hpp"

class SimulateActors2X : public rclcpp::Node
{
public:
    SimulateActors2X();
private:
};

#endif // MESS2_ALGORITHM_DEMOS_SIMUALTE_ACTORS_2X_HPP
