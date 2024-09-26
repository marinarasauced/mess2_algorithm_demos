
#include "mess2_algorithm_demos/demo3.hpp"

DemoHighLevelStatic::DemoHighLevelStatic() : Node("demo3")
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
    (void) burger1.set_source(graph.lookup_index_vertex(-5.0, -5.0, 90.0));
    (void) burger1.set_target(graph.lookup_index_vertex(5.0, 5.0, 90.0));
    (void) burger1.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) burger1.generate_transition_costs_by_edge(graph, threat_static);
    (void) burger1.generate_transition_times_by_edge(graph);
    (void) burger1.generate_transition_heuristic_by_edge(graph);
    actors_.push_back(burger1);

    RCLCPP_INFO(this->get_logger(), "generating burger2");
    auto burger2 = mess2_algorithms::Actor(1.0, 1.0, 0.01, 0.01, 1.0, 1.0, 0.1);
    (void) burger2.set_source(graph.lookup_index_vertex(5.0, -5.0, 90.0));
    (void) burger2.set_target(graph.lookup_index_vertex(-5.0, 5.0, 90.0));
    (void) burger2.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) burger2.generate_transition_costs_by_edge(graph, threat_static);
    (void) burger2.generate_transition_times_by_edge(graph);
    (void) burger2.generate_transition_heuristic_by_edge(graph);
    actors_.push_back(burger2);

    RCLCPP_INFO(this->get_logger(), "executing high level search");
    mess2_algorithms::high_level_search_output output = search_.execute_high_level_search(graph, actors_);
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DemoHighLevelStatic>();
    // (void) node->run_node();
    rclcpp::shutdown();
    return 0;
}
