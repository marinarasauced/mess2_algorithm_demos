
#include "mess2_algorithm_demos/simulate_actors_10x.hpp"

SimulateActors10X::SimulateActors10X() : Node("simulate_actors_10x")
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
    (void) burger2.set_source(graph.lookup_index_vertex(-4.0, -5.0, 90.0));
    (void) burger2.set_target(graph.lookup_index_vertex(4.0, 5.0, 90.0));
    (void) burger2.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) burger2.generate_transition_costs_by_edge(graph, threat_static);
    (void) burger2.generate_transition_times_by_edge(graph);
    (void) burger2.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "generating burger3");
    auto burger3 = mess2_algorithms::generate_actor_turtlebot3("burger", 0.7, 1.1);
    (void) burger3.set_source(graph.lookup_index_vertex(-3.0, -5.0, 90.0));
    (void) burger3.set_target(graph.lookup_index_vertex(3.0, 5.0, 90.0));
    (void) burger3.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) burger3.generate_transition_costs_by_edge(graph, threat_static);
    (void) burger3.generate_transition_times_by_edge(graph);
    (void) burger3.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "generating burger4");
    auto burger4 = mess2_algorithms::generate_actor_turtlebot3("burger", 0.7, 1.1);
    (void) burger4.set_source(graph.lookup_index_vertex(-2.0, -5.0, 90.0));
    (void) burger4.set_target(graph.lookup_index_vertex(2.0, 5.0, 90.0));
    (void) burger4.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) burger4.generate_transition_costs_by_edge(graph, threat_static);
    (void) burger4.generate_transition_times_by_edge(graph);
    (void) burger4.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "generating waffle1");
    auto waffle1 = mess2_algorithms::generate_actor_turtlebot3("burger", 0.7, 1.1);
    (void) waffle1.set_source(graph.lookup_index_vertex(-1.0, -5.0, 90.0));
    (void) waffle1.set_target(graph.lookup_index_vertex(1.0, 5.0, 90.0));
    (void) waffle1.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) waffle1.generate_transition_costs_by_edge(graph, threat_static);
    (void) waffle1.generate_transition_times_by_edge(graph);
    (void) waffle1.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "generating waffle2");
    auto waffle2 = mess2_algorithms::generate_actor_turtlebot3("burger", 0.7, 1.1);
    (void) waffle2.set_source(graph.lookup_index_vertex(-0.0, -5.0, 90.0));
    (void) waffle2.set_target(graph.lookup_index_vertex(0.0, 5.0, 90.0));
    (void) waffle2.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) waffle2.generate_transition_costs_by_edge(graph, threat_static);
    (void) waffle2.generate_transition_times_by_edge(graph);
    (void) waffle2.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "generating waffle3");
    auto waffle3 = mess2_algorithms::generate_actor_turtlebot3("burger", 0.7, 1.1);
    (void) waffle3.set_source(graph.lookup_index_vertex(1.0, -5.0, 90.0));
    (void) waffle3.set_target(graph.lookup_index_vertex(5.0, -4.0, 270.0));
    (void) waffle3.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) waffle3.generate_transition_costs_by_edge(graph, threat_static);
    (void) waffle3.generate_transition_times_by_edge(graph);
    (void) waffle3.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "generating waffle4");
    auto waffle4 = mess2_algorithms::generate_actor_turtlebot3("burger", 0.7, 1.1);
    (void) waffle4.set_source(graph.lookup_index_vertex(2.0, -5.0, 90.0));
    (void) waffle4.set_target(graph.lookup_index_vertex(-2.0, 5.0, 90.0));
    (void) waffle4.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) waffle4.generate_transition_costs_by_edge(graph, threat_static);
    (void) waffle4.generate_transition_times_by_edge(graph);
    (void) waffle4.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "generating burger5");
    auto burger5 = mess2_algorithms::generate_actor_turtlebot3("burger", 0.7, 1.1);
    (void) burger5.set_source(graph.lookup_index_vertex(3.0, -5.0, 90.0));
    (void) burger5.set_target(graph.lookup_index_vertex(-3.0, 5.0, 90.0));
    (void) burger5.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) burger5.generate_transition_costs_by_edge(graph, threat_static);
    (void) burger5.generate_transition_times_by_edge(graph);
    (void) burger5.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "generating burger6");
    auto burger6 = mess2_algorithms::generate_actor_turtlebot3("burger", 0.7, 1.1);
    (void) burger6.set_source(graph.lookup_index_vertex(5.0, 5.0, 180.0));
    (void) burger6.set_target(graph.lookup_index_vertex(-5.0, -5.0, 0.0));
    (void) burger6.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) burger6.generate_transition_costs_by_edge(graph, threat_static);
    (void) burger6.generate_transition_times_by_edge(graph);
    (void) burger6.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "generating burger7");
    auto burger7 = mess2_algorithms::generate_actor_turtlebot3("burger", 0.7, 1.1);
    (void) burger7.set_source(graph.lookup_index_vertex(4.0, 5.0, 180.0));
    (void) burger7.set_target(graph.lookup_index_vertex(-4.0, -5.0, 0.0));
    (void) burger7.generate_occupancies_using_graph_map(graph, x_graph, y_graph);
    (void) burger7.generate_transition_costs_by_edge(graph, threat_static);
    (void) burger7.generate_transition_times_by_edge(graph);
    (void) burger7.generate_transition_heuristic_by_edge(graph);

    RCLCPP_INFO(this->get_logger(), "writing actors to csv");
    (void) burger1.save_actor(path_actors + "actor1.csv");
    (void) burger2.save_actor(path_actors + "actor2.csv");
    (void) burger3.save_actor(path_actors + "actor3.csv");
    (void) burger4.save_actor(path_actors + "actor4.csv");
    (void) waffle1.save_actor(path_actors + "actor5.csv");
    (void) waffle2.save_actor(path_actors + "actor6.csv");
    (void) waffle3.save_actor(path_actors + "actor7.csv");
    (void) waffle4.save_actor(path_actors + "actor8.csv");
    (void) burger5.save_actor(path_actors + "actor9.csv");
    (void) burger6.save_actor(path_actors + "actor10.csv");
    (void) burger7.save_actor(path_actors + "actor11.csv");

    RCLCPP_INFO(this->get_logger(), "executing high level search");
    std::vector<mess2_algorithms::Actor> actors;
    actors.push_back(burger1);
    actors.push_back(burger2);
    actors.push_back(burger3);
    actors.push_back(burger4);
    actors.push_back(waffle1);
    actors.push_back(waffle2);
    actors.push_back(waffle3);
    actors.push_back(waffle4);
    actors.push_back(burger5);
    actors.push_back(burger6);
    actors.push_back(burger7);

    mess2_algorithms::HighLevelSearch search;
    mess2_algorithms::high_level_search_output output = search.execute_high_level_search(graph, actors);
    (void) mess2_algorithms::save_high_level_search_output(path_goals, output, graph, true);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimulateActors10X>();
    rclcpp::shutdown();
    return 0;
}
