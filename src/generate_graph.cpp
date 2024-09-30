
#include "mess2_algorithm_demos/generate_graph.hpp"

GenerateGraph::GenerateGraph() : Node("generate_graph")
{
    int64_t resolution;
    this->declare_parameter("resolution", 201);
    this->get_parameter("resolution", resolution);

    bool use_diagonals;
    this->declare_parameter("use_diagonals", false);
    this->get_parameter("use_diagonals", use_diagonals);

    std::string path_edges;
    std::string path_vertices;
    std::string path_threat;
    this->declare_parameter("path_edges", "~/Projets/mess2/matlab/algorithms/config/edges.csv");
    this->declare_parameter("path_vertices", "~/Projets/mess2/matlab/algorithms/config/vertices.csv");
    this->get_parameter("path_edges", path_edges);
    this->get_parameter("path_vertices", path_vertices);

    RCLCPP_INFO(this->get_logger(), "generating mesh");
    const auto [x_graph, y_graph] = mess2_algorithms::generate_mesh(-5.0, 5.0, -5.0, 5.0, resolution);

    RCLCPP_INFO(this->get_logger(), "generating graph");
    auto graph = mess2_algorithms::Graph(x_graph, y_graph, resolution, use_diagonals);

    RCLCPP_INFO(this->get_logger(), "writing graph to csv");
    (void) graph.save_edges(path_edges);
    (void) graph.save_vertices(path_vertices);
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<GenerateGraph>();
    rclcpp::shutdown();
    return 0;
}
