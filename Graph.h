#ifndef GDWG_H
#define GDWG_H

#include <map>
#include <set>

namespace gdwg {
    template <typename N, typename E> class Graph {
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

            // the following four operations provide a fake iterator for
            // enumerating all the node values in a graph. You can abstract a
            // graph in any sequence, as long as the sequence consists of all
            // and only the nodes in the graph. 
            // should be short. use mutable. reference solution uses 1 line per function
            void begin() const;
            bool end() const;
            void next() const;
            const N& value() const;
        private:
            struct Edge {
                Edge(const N& d, const E& w): dst{d}, weight{w} {}
                N dst;
                E weight;
            }

            std::map<N, std::set<Edge>> nodes;

            // mutable iterator?
    }

    #include "Graph.tem"
}

#endif
