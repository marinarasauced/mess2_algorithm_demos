#ifndef MESS2_ALGORITHM_DEMOS_DEMO1_HPP
#define MESS2_ALGORITHM_DEMOS_DEMO1_HPP

// #include "mess2_algorithm_threat_static/threat.hpp"
// #include "mess2_algorithm_plugins/graph/graph.hpp"
// #include "mess2_algorithm_plugins/utils.hpp"

#include "rclcpp/rclcpp.hpp"

class DemoGraph : public rclcpp::Node
{
public:
    DemoGraph();

    void run_node();

private:
    // mess2_algorithms::Graph graph_;
};

#endif // MESS2_ALGORITHM_DEMOS_DEMO1_HPP
