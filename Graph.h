#ifndef GDWG_H
#define GDWG_H

#include <map>
#include <set>

namespace gdwg {
    template <typename N, typename E> class Graph {
        using std::shared_ptr;
        using std::weak_ptr; // are these needed?
        public:
            // just using default constructor for now
            // Graph();

            bool addNode(const N& val);
            bool addEdge(const N& src, const N& dst, const E& w);
            bool replace(const N& oldData, const N& newData);
            void mergeReplace(const N& oldData, const N& newData);
            void deleteNode(const N&) noexcept;
            void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
            void clear() noexcept;
            bool isNode(const N& val) const;
            bool isConnected(const N& src, const N& dst) const;
            void printNodes() const;
            void printEdges(const N& val) const;

            void begin() const;
            bool end() const;
            void next() const;
            const N& value() const;
        private:
            struct Node {
                Node(const N& val_): val{src_} {}
                N val;

                // edges which have this node as their destination
                std::set<shared_ptr<Edge>> inEdges;

                // edges which have this node as their source
                std::set<shared_ptr<Edge>> outEdges;

                shared_ptr<Edge> getEdgeTo(const N& dst, const E& w) {
                    for (auto edge : outEdges) {
                        if ((edge->w == w) && (edge->dst->val == dst)) {
                            return edge;
                        }
                    }
                    return nullptr;
                }

                bool isConnected(const N& dst) {
                    for (auto edge : outEdges) {
                        if (edge->dst->val == dst) {
                            return true;
                        }
                    }
                    return false;
                }

                unsigned int outdegree() {
                    return outEdges.size();
                }
            }

            struct Edge {
                Edge(shared_ptr<Node> src_, shared_ptr<Node> dst_, const E& w): src{src_}, dst{dst_}, w{w_} {}
                weak_ptr<Node> src;
                weak_ptr<Node> dst;
                E w;
            }

            std::map<N, shared_ptr<Node> nodes;

            mutable decltype(nodes.begin()) it;
    }

    #include "Graph.tem"
}

#endif
