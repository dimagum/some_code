#pragma once

#include <map>
#include <limits>
#include <algorithm>


using namespace std;


struct Point { double x, y, z; };
std::ostream& operator << (std::ostream& out, Point p) {
    std::cout << '(' << p.x << ',' << p.y << ',' << p.z << ')';
    return out;
}


/*!
 * \brief Это граф!
 * @tparam key_type
 * @tparam value_type
 * @tparam weight_type
 */
template<typename key_type, typename value_type, typename weight_type>
class Graph {

    /*!
     * \brief Узел (внутренний класс)
     */
    class Node {
    public:
        value_type val;

        map<key_type, weight_type> edges;

        Node() = default;

        Node(const Node& other) = default;

        Node(Node&& other) noexcept = default;

        explicit Node(const Point& point) {
            val = point;
        }

        Node& operator=(const Node& rhs) = default;

        Node& operator=(Node&& rhs) noexcept = default;

        Node& operator=(const Point& point) {
            val = point;
            return *this;
        }

        bool empty() const {
            return edges.empty();
        }

        size_t size() const {
            return edges.size();
        }

        value_type& value() {
            return val;
        }

        const value_type& value() const {
            return val;
        }

        void clear() {
            edges.clear();
        }

        typedef typename std::map<key_type, weight_type>::iterator iterator;
        typedef typename std::map<key_type, weight_type>::const_iterator const_iterator;

        iterator begin() {
            return edges.begin();
        }

        iterator end() {
            return edges.end();
        }

        const_iterator begin() const {
            return edges.begin();
        }

        const_iterator end() const {
            return edges.end();
        }

        const_iterator cbegin() const {
            return edges.cbegin();
        }

        const_iterator cend() const {
            return edges.cend();
        }

        pair<iterator, bool> insert_edge(key_type key, weight_type weight) {
            return edges.insert(pair<key_type, weight_type>(key, weight));
        }

        pair<iterator, bool> insert_or_assign_edge(key_type key, weight_type weight) {
            return edges.insert_or_assign(key, weight);
        }


        bool erase_edge(key_type key) {
            if (edges.find(key) == edges.end()) {
                return false;
            }

            edges.erase(key);
            return true;
        }

    };

    map<key_type, Node> graph;

public:

    Graph() = default;

    Graph(const Graph& other) = default;

    Graph(Graph&& other) noexcept = default;

    Graph& operator=(const Graph& rhs) = default;

    Graph& operator=(Graph&& rhs) noexcept = default;

    /*!
     * \brief Итератор begin()
     * @return bool
     */
    bool empty() const {
        return graph.empty();
    }

    size_t size() const {
        return graph.size();
    }

    void clear() {
        graph.clear();
    }

    void swap(Graph<key_type, value_type, weight_type>& other) {
        Graph<key_type, value_type, weight_type> tmp = other;
        other = *this;
        *this = tmp;
    }

    friend void swap(Graph<key_type, value_type, weight_type>& first, Graph& second) {
        Graph<key_type, value_type, weight_type> tmp;
        tmp = first;
        first = second;
        second = tmp;
    }

    typedef typename map<key_type, Node>::iterator iterator;
    typedef typename map<key_type, Node>::const_iterator const_iterator;

    iterator begin() {
        return graph.begin();
    }

    iterator end() {
        return graph.end();
    }

    const_iterator begin() const {
        return graph.begin();
    }

    const_iterator end() const {
        return graph.end();
    }

    const_iterator cbegin() const {
        return graph.cbegin();
    }

    const_iterator cend() const {
        return graph.cend();
    }

    size_t degree_in(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw std::logic_error("no node with this key in the graph.");
        }

        size_t result = 0;

        for (auto& [node_key, node] : graph) {
            if (node.edges.find(key) != node.edges.end()) {
                result++;
            }
        }

        return result;
    }

    size_t degree_out(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw logic_error("no such node.\n");
        }

        return graph[key].size();
    }

    bool loop(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw logic_error("no such node.\n");
        }

        if (graph[key].edges.find(key) != graph[key].edges.end()) {
            return true;
        }

        return false;
    }

    Node& operator[](key_type key) {
        if (graph.find(key) == graph.end()) {
            return graph[key] = Node();
        }

        return graph[key];
    }

    const Node& operator[](key_type key) const {
        if (graph.find(key) == graph.end()) {
            throw logic_error("no such node.\n");
        }

        return graph.at(key);
    }

    Node& at(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw logic_error("no such node.\n");
        }

        return graph.at(key);
    }

    pair<iterator, bool> insert_node(key_type key, value_type val) {
        if (graph.find(key) != graph.end()) {
            return pair<iterator, bool>(graph.find(key), false);
        }

        Node tmp;
        tmp.value() = val;

        return graph.insert(pair<key_type, Node>(key, tmp));
    }

    pair<iterator, bool> insert_or_assign_node(key_type key, value_type val) {
        if (graph.find(key) != graph.end()) {
            graph[key].value() = val;
            return pair<iterator, bool>(graph.find(key), false);
        }

        Node tmp;
        tmp.value() = val;

        return graph.insert(pair<key_type, Node>(key, tmp));
    }

    pair<iterator, bool> insert_edge(pair<key_type, key_type> keys, weight_type weight) {
        key_type key_from = keys.first, key_to = keys.second;

        if (graph.find(key_from) == graph.end()) {
            throw logic_error("first node is absent\n");
        }

        if (graph.find(key_to) == graph.end()) {
            throw logic_error("second node is absent\n");
        }

        auto [it, flag] = graph[key_from].insert_edge(key_to, weight);

        return pair<iterator, bool>(graph.find(key_from), flag);
    }

    pair<iterator, bool> insert_or_assign_edge(pair<key_type, key_type> keys, weight_type weight) {
        key_type key_from = keys.first, key_to = keys.second;

        if (graph.find(key_from) == graph.end()) {
            throw logic_error("first node is absent\n");
        }

        if (graph.find(key_to) == graph.end()) {
            throw logic_error("second node is absent\n");
        }

        auto [it, flag] = graph[key_from].insert_or_assign_edge(key_to, weight);

        return pair<iterator, bool>(graph.find(key_from), flag);
    }


    void clear_edges() {
        for (auto [node_key, node] : graph) {
            node.clear();
        }
    }

    bool erase_edges_go_from(key_type key) {
        if (graph.find(key) == graph.end()) {
            return false;
        }

        graph[key].clear();
        return true;
    }

    bool erase_edges_go_to(key_type key) {
        if (graph.find(key) == graph.end()) {
            return false;
        }

        for (auto [node_key, node] : graph) {
            node.erase_edge(key);
        }

        return true;
    }

    bool erase_node(key_type key) {
        if (graph.find(key) == graph.end()) {
            return false;
        }

        for (auto [node_key, node] : graph) {
            node.erase_edge(key);
        }

        graph.erase(key);
        return true;
    }
};

template<typename weight_t, typename route_t, typename graph_t, typename node_type_t>
pair<weight_t, route_t> dijkstra(const graph_t& graph, node_type_t key_from, node_type_t key_to) {
    graph[key_from];
    graph[key_to];

    map<node_type_t, weight_t> d;
    map<node_type_t, bool> u;

    for (auto [key, node] : graph) {
        d[key] = numeric_limits<weight_t>::max();
        u[key] = false;
    }

    d[key_from] = 0;

    map<node_type_t, node_type_t> possible;
    possible[key_from] = numeric_limits<node_type_t>::max();

    for (auto i = 0; i < graph.size(); i++) {
        node_type_t v = -1;

        for (auto [key, node] : graph) {
            if (!u[key] && (v == -1 || d[key] < d[v])) {
                v = key;
            }
        }

        if (d[v] == numeric_limits<weight_t>::max()) {
            break;
        }

        for (auto [to, len] : graph[v]) {
            if (len < 0) {
                throw logic_error("negative weight.\n");
            }
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                possible[to] = v;
            }
        }

        u[v] = true;

    }

    if (d[key_to] == numeric_limits<weight_t>::max()) {
        throw logic_error("no route.\n");
    }

    route_t route;

    for (auto key = key_to; possible[key] < numeric_limits<node_type_t>::max(); ) {
        route.push_back(key);
        key = possible[key];
    }

    route.push_back(key_from);
    reverse(route.begin(), route.end());


    return pair<weight_t, route_t>(d[key_to], route);
}
