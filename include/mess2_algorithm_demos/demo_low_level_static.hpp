#ifndef MESS2_ALGORITHM_DEMOS_DEMO1_HPP
#define MESS2_ALGORITHM_DEMOS_DEMO1_HPP

#include "mess2_algorithm_threat_static/threat.hpp"

#include "mess2_algorithm_plugins/low_level/_low_level.hpp"
#include "mess2_algorithm_plugins/other/turtlebot3.hpp"
#include "mess2_algorithm_plugins/actor.hpp"
#include "mess2_algorithm_plugins/utils.hpp"

#include "rclcpp/rclcpp.hpp"

class DemoLowLevelStatic : public rclcpp::Node
{
public:
    DemoLowLevelStatic();

    void run_node();

private:
    mess2_algorithms::LowLevelSearch low_level_;
};

#endif // MESS2_ALGORITHM_DEMOS_DEMO1_HPP
