
#include "mess2_algorithm_demos/demo_low_level_static.hpp"

DemoLowLevelStatic::DemoLowLevelStatic() : Node("demo1")
{
    int64_t resolution;
    this->declare_parameter("resolution", 301);
    this->get_parameter("resolution", resolution);

    auto [x_graph, y_graph] = mess2_algorithms::get_mesh(-3.0, 3.0, -3.0, 3.0, resolution);
    auto [x_threat, y_threat] = mess2_algorithms::get_mesh(-15.0, 15.0, -15.0, 15.0, resolution);

    auto graph = mess2_algorithms::generate_graph(x_graph, y_graph);
    auto actor = mess2_algorithms::generate_and_define_turtlebot3("burger", 0.7, 1.1);
    auto threat = mess2_algorithms::generate_threat_static(x_threat, y_threat);

    (void) low_level_.fill_low_level_search(graph, actor, threat, 0, 1);

    (void) run_node();
};

void DemoLowLevelStatic::run_node()
{
    (void) low_level_.execute_low_level_search();
    std::cout << "done" << std::endl;
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DemoLowLevelStatic>();
    rclcpp::shutdown();
    return 0;
}