#pragma once

#include <map>


using namespace std;

/*!
 * \brief Это граф!
 * @tparam key_type
 * @tparam value_type
 * @tparam weight_type
 */
template<typename key_type, typename value_type, typename weight_type>
class Graph {

    /*!
     *
     */
    class Node {
        value_type val;

        map<key_type, weight_type> edges;

    public:
        Node() = default;

        Node(const Node& other) = default;

        Node(Node&& other) noexcept = default;

        Node& operator=(const Node& rhs) = default;

        Node& operator=(Node&& rhs) noexcept = default;

        bool empty() const {
            return edges.empty();
        }

        size_t size() const {
            return edges.size();
        }

        value_type& value() {
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

        const_iterator cbegin() const {
            return edges.cbegin();
        }

        const_iterator cend() const {
            return edges.cend();
        }

    };

    map<key_type, Node> graph;

public:

    Graph() = default;

    Graph(const Graph& other) = default;

    Graph(Graph&& other) noexcept = default;

    Graph& operator=(const Graph& rhs) = default;

    Graph& operator=(Graph&& rhs) noexcept = default;

    bool empty() const {
        return graph.empty();
    }

    size_t size() const {
        return graph.size();
    }

    void clear() {
        graph.clear();
    }

    typedef typename map<key_type, Node>::iterator iterator;
    typedef typename map<key_type, Node>::const_iterator const_iterator;

    iterator begin() {
        return graph.begin();
    }

    iterator end() {
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
            throw logic_error("no such node.\n");
        }

        size_t result = 0;
        for (auto [key1, node1] : graph) {
            if (node1.edges.find(key) != node1.edges.end()) {
                result++;
            }
        }

        return result;
    }

    size_t degree_out(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw logic_error("no such node.\n");
        }

        return graph[key].edges.size();
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

    Node& at(key_type key) {
        if (graph.find(key) == graph.end()) {
            throw logic_error("no such node.\n");
        }

        return graph.at(key);
    }

};


