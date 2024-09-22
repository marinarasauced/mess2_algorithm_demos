
#include "mess2_algorithm_demos/demo_low_level_static.hpp"

DemoLowLevelStatic::DemoLowLevelStatic() : Node("demo1")
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

    RCLCPP_INFO(this->get_logger(), "filling actor occupancies by vertices");
    burger1.fill_occupancies_by_vertex(x_graph, y_graph, graph.get_vertices());

    RCLCPP_INFO(this->get_logger(), "filling actor scores by edges");
    burger1.fill_scores_by_edges(graph.get_edges(), threat_static);

    RCLCPP_INFO(this->get_logger(), "filling actor times by edges");
    burger1.fill_times_by_edges(graph.get_edges(), graph.get_vertices());

    RCLCPP_INFO(this->get_logger(), "filling low level search");
    low_level_.fill_low_level_search(graph, threat_static, burger1, 0, 300);

    // auto graph = mess2_algorithms::generate_graph(x_graph, y_graph);
    // auto actor = mess2_algorithms::generate_and_define_turtlebot3("burger", 0.7, 1.1);
    // auto threat = mess2_algorithms::generate_threat_static(x_threat, y_threat);

    // (void) low_level_.fill_low_level_search(graph, actor, threat, 0, 1);

    (void) run_node();
};

void DemoLowLevelStatic::run_node()
{
    RCLCPP_INFO(this->get_logger(), "executing low level search");
    (void) low_level_.execute_low_level_search();
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DemoLowLevelStatic>();
    rclcpp::shutdown();
    return 0;
}