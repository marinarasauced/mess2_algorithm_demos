
#include "mess2_algorithm_demos/generate_threat.hpp"

GenerateThreat::GenerateThreat() : Node("generate_threat")
{
    int64_t resolution;
    this->declare_parameter("resolution", 501);
    this->get_parameter("resolution", resolution);

    bool use_diagonals;
    this->declare_parameter("use_diagonals", false);
    this->get_parameter("use_diagonals", use_diagonals);

    std::string path_threat;
    this->declare_parameter("path_threat", "~/Projets/mess2/matlab/algorithms/config/threat.csv");

    this->get_parameter("path_threat", path_threat);

    RCLCPP_INFO(this->get_logger(), "generating meshes");
    const auto [x_threat, y_threat] = mess2_algorithms::generate_mesh(-15.0, 15.0, -15.0, 15.0, resolution);
    const auto [x_graph, y_graph] = mess2_algorithms::generate_mesh(-5.0, 5.0, -5.0, 5.0, resolution);

    RCLCPP_INFO(this->get_logger(), "generating threat");
    const auto threat_static = mess2_algorithms::generate_threat_static(x_threat, y_threat);

    RCLCPP_INFO(this->get_logger(), "writing threat to csv");
    (void) mess2_algorithms::save_threat_static(threat_static, x_graph, y_graph, path_threat);
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<GenerateThreat>();
    rclcpp::shutdown();
    return 0;
}
