
#include "mess2_algorithm_demos/simulate_actors_2x.hpp"

SimulateActors2X::SimulateActors2X() : Node("simulate_actors_2x")
{
    int64_t resolution;
    this->declare_parameter("resolution", 201);
    this->get_parameter("resolution", resolution);

    bool use_diagonals;
    this->declare_parameter("use_diagonals", false);
    this->get_parameter("use_diagonals", use_diagonals);

    std::string path_edges;
    std::string path_vertices;
    std::string path_actors;
    std::string path_goals;
    this->declare_parameter("path_edges", "~/Projets/mess2/matlab/algorithms/config/edges.csv");
    this->declare_parameter("path_vertices", "~/Projets/mess2/matlab/algorithms/config/vertices.csv");
    this->declare_parameter("path_actors", "~/Projets/mess2/matlab/algorithms/config/actors/");
    this->declare_parameter("path_goals", "~/Projets/mess2/matlab/algorithms/config/goals/");
    this->get_parameter("path_edges", path_edges);
    this->get_parameter("path_vertices", path_vertices);
    this->get_parameter("path_actors", path_actors);
    this->get_parameter("path_goals", path_goals);

    RCLCPP_INFO(this->get_logger(), "generating meshes");
    const auto [x_graph, y_graph] = mess2_algorithms::generate_mesh(-5.0, 5.0, -5.0, 5.0, resolution);
    const auto [x_threat, y_threat] = mess2_algorithms::generate_mesh(-15.0, 15.0, -15.0, 15.0, resolution);

    RCLCPP_INFO(this->get_logger(), "generating graph");
    auto graph = mess2_algorithms::Graph(x_graph, y_graph, resolution, use_diagonals);

    RCLCPP_INFO(this->get_logger(), "writing graph to csv");
    (void) graph.save_edges(path_edges);
    (void) graph.save_vertices(path_vertices);

    RCLCPP_INFO(this->get_logger(), "generating threat");
    const auto threat_static = mess2_algorithms::generate_threat_static(x_threat, y_threat);

    RCLCPP_INFO(this->get_logger(), "generating burger1");
    auto burger1 = mess2_algorithms::generate_actor_turtlebot3("burger", 0.7, 1.1);
    (void) burger1.set_source(graph.lookup_index_vertex(-5.0, -5.0, 90.0));
    (void) burger1.set_target(graph.lookup_index_vertex(5.0, 5.0, 90.0));
    (void) burger1.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) burger1.generate_transition_costs_by_edge(graph, threat_static);
    (void) burger1.generate_transition_times_by_edge(graph);
    (void) burger1.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "generating burger2");
    auto burger2 = mess2_algorithms::generate_actor_turtlebot3("burger", 0.7, 1.1);
    (void) burger2.set_source(graph.lookup_index_vertex(5.0, -5.0, 90.0));
    (void) burger2.set_target(graph.lookup_index_vertex(-5.0, 5.0, 90.0));
    (void) burger2.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) burger2.generate_transition_costs_by_edge(graph, threat_static);
    (void) burger2.generate_transition_times_by_edge(graph);
    (void) burger2.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "writing actors to csv");
    (void) burger1.save_actor(path_actors + "actor1.csv");
    (void) burger2.save_actor(path_actors + "actor2.csv");

    RCLCPP_INFO(this->get_logger(), "executing high level search");
    std::vector<mess2_algorithms::Actor> actors;
    actors.push_back(burger1);
    actors.push_back(burger2);

    mess2_algorithms::HighLevelSearch search;
    mess2_algorithms::high_level_search_output output = search.execute_high_level_search(graph, actors);
    (void) mess2_algorithms::save_high_level_search_output(path_goals, output, graph, true);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimulateActors2X>();
    rclcpp::shutdown();
    return 0;
}
