#ifndef GDWG_H
#define GDWG_H

#include <map>
#include <set>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <algorithm>

namespace gdwg {
    using std::shared_ptr;
    using std::weak_ptr;
    template <typename N, typename E> class Graph {
        public:
            // default default constructor
            Graph() = default;

            // default move constructor
            Graph(Graph &&original) = default;

            // copy constructor
            Graph(const Graph& original);

            // default move assignment
            Graph& operator=(Graph &&original) = default;

            // copy assignment
            Graph& operator=(Graph &original);

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
            struct Edge;
            struct Node {
                Node(const N& val_): val{val_} {}

                N val;

                // edges which have this node as their destination
                std::set<shared_ptr<Edge>> inEdges;

                // edges which have this node as their source
                std::set<shared_ptr<Edge>> outEdges;

                shared_ptr<Edge> getEdgeTo(const N& dst, const E& w) const {
                    for (auto edge : outEdges) {
                        shared_ptr<Node> dst_ = edge->dst.lock();
                        if ((edge->w == w) && (dst_->val == dst)) {
                            return edge;
                        }
                    }
                    return nullptr;
                }

                bool isConnected(const N& dst) const {
                    for (auto edge : outEdges) {
                        shared_ptr<Node> dst_ = edge->dst.lock();
                        if (dst_->val == dst) {
                            return true;
                        }
                    }
                    return false;
                }

                unsigned int outdegree() const {
                    return outEdges.size();
                }
            };

            struct Edge {
                Edge(shared_ptr<Node> src_, shared_ptr<Node> dst_, const E& w_): src{src_}, dst{dst_}, w{w_} {}
                weak_ptr<Node> src;
                weak_ptr<Node> dst;
                E w;
            };

            std::map<N, shared_ptr<Node>> nodes;

            mutable decltype(nodes.cbegin()) it;

            template <typename N_, typename E_>
            friend void swap(Graph<N_, E_>& a, Graph<N_, E_>& b);
    };

    #include "Graph.tem"
}

#endif
