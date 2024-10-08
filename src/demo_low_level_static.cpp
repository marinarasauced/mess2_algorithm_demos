
#include "mess2_algorithm_demos/demo_low_level_static.hpp"

DemoLowLevelStatic::DemoLowLevelStatic() : Node("demo2")
{
    int64_t resolution;
    this->declare_parameter("resolution", 201);
    this->get_parameter("resolution", resolution);

    bool use_diagonals;
    this->declare_parameter("use_diagonals", false);
    this->get_parameter("use_diagonals", use_diagonals);

    RCLCPP_INFO(this->get_logger(), "generating mesh");
    const auto [x_graph, y_graph] = mess2_algorithms::generate_mesh(-5.0, 5.0, -5.0, 5.0, resolution);

    RCLCPP_INFO(this->get_logger(), "generating graph");
    auto graph = mess2_algorithms::Graph(x_graph, y_graph, resolution, use_diagonals);

    RCLCPP_INFO(this->get_logger(), "generating threat");
    const auto [x_threat, y_threat] = mess2_algorithms::generate_mesh(-15.0, 15.0, -15.0, 15.0, resolution);
    const auto threat_static = mess2_algorithms::generate_threat_static(x_threat, y_threat);

    RCLCPP_INFO(this->get_logger(), "generating burger1");
    auto burger1 = mess2_algorithms::Actor(1.0, 1.0, 0.01, 0.01, 1.0, 1.0, 0.1);
    (void) burger1.set_source(0);
    (void) burger1.set_target(std::pow(resolution, 2) - 1);
    (void) burger1.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) burger1.generate_transition_costs_by_edge(graph, threat_static);
    (void) burger1.generate_transition_times_by_edge(graph);
    (void) burger1.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "generating empty constraints");
    auto constraints = mess2_algorithms::ConstraintsVertices(graph.n_vertices);

    RCLCPP_INFO(this->get_logger(), "executing low level search");
    auto low_level = mess2_algorithms::LowLevelSearch();
    auto output = low_level.execute_low_level_search(graph, burger1, constraints);

    RCLCPP_INFO(this->get_logger(), "printing low level search output");
    (void) mess2_algorithms::info_low_level_search_output(output, graph, burger1);
};

void DemoLowLevelStatic::run_node()
{
    // RCLCPP_INFO(this->get_logger(), "executing low level search");
    // const auto path = low_level_.execute_low_level_search(constraints_);
    // (void) mess2_algorithms::print_path(path, low_level_.get_graph().get_vertices());
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DemoLowLevelStatic>();
    // (void) node->run_node();
    rclcpp::shutdown();
    return 0;
}
