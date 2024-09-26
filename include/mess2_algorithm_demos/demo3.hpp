#ifndef MESS2_ALGORITHM_DEMOS_DEMO2_HPP
#define MESS2_ALGORITHM_DEMOS_DEMO2_HPP

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

class DemoHighLevelStatic : public rclcpp::Node
{
public:
    DemoHighLevelStatic();

private:
    std::vector<mess2_algorithms::Actor> actors_;
    mess2_algorithms::HighLevelSearch search_;
};

#endif // MESS2_ALGORITHM_DEMOS_DEMO2_HPP
