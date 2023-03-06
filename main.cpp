#include <iostream>
#include <Matrix_file.h>
#include <Graph.h>


template<typename Graph>
void print(const Graph& graph) {
    if (graph.empty()) {
        std::cout << "> This graph is empty!" << std::endl;
        return;
    }
    std::cout << "> Size of graph: " << graph.size() << std::endl;
    for (const auto& [key, node] : graph) {
        std::cout << '[' << key << "] stores: " << node.value()
                  << " and matches with:" << std::endl;
        for (const auto& [key1, weight] : node)
            std::cout << "\t[" << key << "]\t with weight: "
                      << weight << std::endl;
    }
}


int main() {/*
    Graph<int, int, int> graph;
    auto [it1, flag1] = graph.insert_node(1, 1);
    auto [it2, flag2] = graph.insert_node(2, 2);
    auto [it3, flag3] = graph.insert_node(2, 5);

    cout << it2->second.value() << " " << it3->second.value() << "\n";

    auto [it4, flag4] = graph.insert_or_assign_node(2, 5);

    cout << boolalpha << flag1 << " " << flag2 << " " << flag3 << " " << flag4 << "\n";
    cout << it4->second.value() << "\n";

    cout << boolalpha << graph[1].empty() << "\n";

    graph.insert_edge({1, 1}, 2);

    cout << boolalpha << graph[1].empty() << "\n";

    graph.insert_edge({2, 1}, 5);
    graph.insert_edge({1, 2}, 7);

    cout << boolalpha << graph[1].size() << " " << graph[2].size() << "\n";

    graph.erase_edges_go_from(1);

    cout << boolalpha << graph[1].size() << " " << graph[2].size() << "\n";

    graph.clear_edges();

    cout << boolalpha << graph[1].size() << " " << graph[2].size() << "\n";

    cout << graph.size() << "\n";

    graph.erase_node(2);

    cout << graph.size() << "\n";
    */

    Graph<std::string, Point, double> graph;
    graph["zero"]; // Заполнится точкой, которая заполнится нулями
    auto [it1, flag1] = graph.insert_node("first", {1, 1, 1});
    std::cout << std::boolalpha << flag1 << std::endl; // => true
    graph["second"]; // Заполнится точкой, которая заполнится нулями
    auto [it2, flag2] = graph.insert_or_assign_node("second", {2, 2, 2}); //перезаполнит
    std::cout << std::boolalpha << flag2 << std::endl; // => false
    graph["third"] = Point{ 3, 3, 3 };
    auto [it3, flag3] = graph.insert_node("third", {1, 1, 1}); // бездействует
    std::cout << std::boolalpha << flag3 << std::endl; // => false
    graph["fourth"]; // Заполнится точкой, которая заполнится нулями
    graph.at("fourth") = Point{ 4, 4, 4 };
    try { graph.at("fifth"); }
    catch (std::exception& ex) { std::cout << ex.what() << std::endl; }
    auto [it4, flag4] = graph.insert_edge({ "first", "second" }, 44.44);
    std::cout << std::boolalpha << flag4 << std::endl; // => true
    auto [it5, flag5] = graph.insert_edge({ "first", "second" }, 55.55);
    std::cout << std::boolalpha << flag5 << std::endl; // => false
    auto [it6, flag6] = graph.insert_or_assign_edge({ "first", "second" }, 66.66);
    std::cout << std::boolalpha << flag6 << std::endl; // => false
    auto [it7, flag7] = graph.insert_or_assign_edge({ "second", "first" }, 77.77);
    std::cout << std::boolalpha << flag7 << std::endl; // => true
    print(graph);
    auto graph_other = graph; // Конструктор копирования
    auto graph_new = std::move(graph); // Конструктор перемещения
    graph = std::move(graph_new); // Перемещающее присваивание
    graph_new = graph; // Копирующее присваивание
    graph.swap(graph_new); // Поменять местами содержимое графов
    swap(graph, graph_new); // Поменять местами содержимое графов
    print(graph);
    for (auto& [key, node] : graph) {
        std::cout << "Is here no edges?" << std::boolalpha << node.empty() <<
                  std::endl;
        std::cout << "How many edges are going from here?" << node.size() <<
                  std::endl;
        node.value() = Point{ 1,2,3 }; // могу поменять вес
        for (auto& [key1, weight] : node) {
                            // key = "new key"; // ОШИБКА: нельзя менять ключ
            weight = 11.11; // могу задать новый вес у этого ребра
        }
        bool flag = node.erase_edge("first"); // => true, если удалил
// => false, если такого ребра нет
    }
    print(graph);
    bool flag8 = graph.erase_node("new name");
    std::cout << std::boolalpha << flag8 << std::endl;
    bool flag9 = graph.erase_node("first");
    std::cout << std::boolalpha << flag9 << std::endl;
    print(graph);
    graph.insert_edge({ "second", "zero" }, 4.4);
    graph.insert_edge({ "third", "second" }, 6.6);
    print(graph);
    bool flag10 = graph.erase_edges_go_from("new name");
    std::cout << std::boolalpha << flag10 << std::endl;
    bool flag11 = graph.erase_edges_go_from("second");
    std::cout << std::boolalpha << flag11 << std::endl;
    print(graph);
    graph.erase_edges_go_to("second");
    print(graph);
    graph.insert_edge({ "second", "zero" }, 4.4);
    graph.insert_edge({ "third", "second" }, 6.6);
    graph.insert_edge({ "third", "third" }, 6.6);
    graph.insert_edge({ "third", "zero" }, 6.6);
    print(graph);
    std::cout << graph.degree_in("second") << std::endl;
    std::cout << graph.degree_in("third") << std::endl;
    std::cout << graph.degree_out("second") << std::endl;
    std::cout << graph.degree_out("third") << std::endl;
    std::cout << std::boolalpha << graph.loop("second") << std::endl;
    std::cout << std::boolalpha << graph.loop("third") << std::endl;
    bool flag12 = graph.erase_node("new name");
    std::cout << std::boolalpha << flag12 << std::endl;
    bool flag13 = graph.erase_node("second");
    std::cout << std::boolalpha << flag13 << std::endl;
    print(graph);
    graph.clear_edges(); // Очистить все рёбра
    print(graph);
    graph.clear(); // Очистить все вершины (очевидно, вместе с рёбрами)
    print(graph);

    Graph<int, int, double> g;
    g.insert_node(0, 0);
    g.insert_node(1, 0);
    g.insert_node(2, 0);
    g.insert_node(3, 0);
    g.insert_node(4, 0);

    g.insert_edge({0, 0}, 5);
    g.insert_edge({1, 3}, 2);
    g.insert_edge({2, 0}, 1.2);
    g.insert_edge({2, 3}, 15);
    g.insert_edge({2, 4}, 10.5);
    g.insert_edge({3, 1}, 3);
    g.insert_edge({4, 1}, 8);
    g.insert_edge({4, 3}, 1);

    auto [distance, route] = dijkstra<double, vector<int>, Graph<int, int, double>, int>(g, 2, 1);

    cout << distance << "\n";

    for (auto item : route) {
        cout << item << " ";
    }
    cout << "\n";

    try {
        auto [weight1, route1] = dijkstra<double, vector<int>, Graph<int, int, double>, int>(g, 2, 5);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    g.insert_edge({4, 0}, -1.4);

    try {
        auto [weight2, route2] = dijkstra<double, vector<int>, Graph<int, int, double>, int>(g, 2, 1);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    g.erase_edges_go_from(4);
    g.insert_edge({4, 3}, 1);
    g.insert_edge({4, 1}, 8);

    g.insert_node(5, 7);

    try {
        auto [weight3, route3] = dijkstra<double, vector<int>, Graph<int, int, double>, int>(g, 2, 5);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}
