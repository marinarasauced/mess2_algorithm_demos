
#include "mess2_algorithm_demos/demo_low_level_static.hpp"

DemoLowLevelStatic::DemoLowLevelStatic() : Node("demo2")
{
    int64_t resolution;
    this->declare_parameter("resolution", 301);
    this->get_parameter("resolution", resolution);

    RCLCPP_INFO(this->get_logger(), "generating meshes");
    auto [x_graph, y_graph] = mess2_algorithms::generate_mesh(-3.0, 3.0, -3.0, 3.0, resolution);
    auto [x_threat, y_threat] = mess2_algorithms::generate_mesh(-15.0, 15.0, -15.0, 15.0, resolution);

    RCLCPP_INFO(this->get_logger(), "generating graph");
    const auto graph = mess2_algorithms::generate_graph(x_graph, y_graph);

    RCLCPP_INFO(this->get_logger(), "generating threat");
    const auto threat_static = mess2_algorithms::generate_threat_static(x_threat, y_threat);

    RCLCPP_INFO(this->get_logger(), "generating actor");
    auto burger1 = mess2_algorithms::generate_actor_turtlebot3("burger", 0.7, 1.1);

    RCLCPP_INFO(this->get_logger(), "filling actor occupancies by x and y");
    burger1.fill_occupancies_by_x_and_y(x_graph, y_graph, graph);

    RCLCPP_INFO(this->get_logger(), "filling actor scores by edges");
    burger1.fill_scores_by_edges(graph, threat_static);

    RCLCPP_INFO(this->get_logger(), "filling actor times by edges");
    burger1.fill_times_by_edges(graph);

    RCLCPP_INFO(this->get_logger(), "filling low level search");
    low_level_.fill_low_level_search(graph, burger1, 0, std::pow(resolution, 2) - 1);
};

void DemoLowLevelStatic::run_node()
{
    RCLCPP_INFO(this->get_logger(), "executing low level search");
    const auto path = low_level_.execute_low_level_search();
    (void) mess2_algorithms::print_path(path, low_level_.get_graph().get_vertices());
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DemoLowLevelStatic>();
    (void) node->run_node();
    rclcpp::shutdown();
    return 0;
}