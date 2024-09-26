
#include "mess2_algorithm_demos/demo1.hpp"

DemoGraph::DemoGraph() : Node("demo1")
{
    int64_t resolution;
    this->declare_parameter("resolution", 2001);
    this->get_parameter("resolution", resolution);

    bool use_diagonals;
    this->declare_parameter("use_diagonals", false);
    this->get_parameter("use_diagonals", use_diagonals);

    std::string path_edges;
    std::string path_vertices;
    std::string path_threat;
    this->declare_parameter("path_edges", "~/Projets/mess2/matlab/algorithms/config/edges.csv");
    this->declare_parameter("path_vertices", "~/Projets/mess2/matlab/algorithms/config/vertices.csv");
    this->declare_parameter("path_threat", "~/Projets/mess2/matlab/algorithms/config/threat.csv");
    this->get_parameter("path_edges", path_edges);
    this->get_parameter("path_vertices", path_vertices);
    this->get_parameter("path_threat", path_threat);

    RCLCPP_INFO(this->get_logger(), "generating mesh");
    const auto [x_graph, y_graph] = mess2_algorithms::generate_mesh(-5.0, 5.0, -5.0, 5.0, resolution);

    RCLCPP_INFO(this->get_logger(), "generating graph");
    auto graph = mess2_algorithms::Graph(x_graph, y_graph, resolution, use_diagonals);

    RCLCPP_INFO(this->get_logger(), "writing graph to csv");
    (void) mess2_algorithms::save_vertices(graph, path_vertices);

    RCLCPP_INFO(this->get_logger(), "generating threat");
    const auto [x_threat, y_threat] = mess2_algorithms::generate_mesh(-15.0, 15.0, -15.0, 15.0, resolution);
    const auto threat_static = mess2_algorithms::generate_threat_static(x_threat, y_threat);

    RCLCPP_INFO(this->get_logger(), "writing threat to csv");
    (void) mess2_algorithms::save_threat_static(threat_static, x_graph, y_graph, path_threat);

    // RCLCPP_INFO(this->get_logger(), "generating mesh");
    // auto [x_graph, y_graph] = mess2_algorithms::generate_mesh(-3.0, 3.0, -3.0, 3.0, resolution);

    // RCLCPP_INFO(this->get_logger(), "generating graph");
    // const auto graph = mess2_algorithms::generate_graph(x_graph, y_graph);
    // graph_ = graph;
};

void DemoGraph::run_node()
{
    // RCLCPP_INFO(this->get_logger(), "printing vertices");
    // (void) graph_.print_vertices();

    // RCLCPP_INFO(this->get_logger(), "printing edges");
    // (void) graph_.print_edges();
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DemoGraph>();
    // (void) node->run_node();
    rclcpp::shutdown();
    return 0;
}