
#include "mess2_algorithm_demos/demo_graph.hpp"

DemoGraph::DemoGraph() : Node("demo1")
{
    int64_t resolution;
    this->declare_parameter("resolution", 2);
    this->get_parameter("resolution", resolution);

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
    (void) node->run_node();
    rclcpp::shutdown();
    return 0;
}