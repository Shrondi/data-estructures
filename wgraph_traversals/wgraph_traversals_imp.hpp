/**
 * @file graph_traversals_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <tuple>
#include <stack>
#include <queue>

#include "wgraph_traversals.hpp"

template <class T, class E, class Processor>
void depth_first_scan(Graph<T, E> &g, Processor &p)
{
    // TODO
    // Remember: set the visited flags to false.
    // Remember: to mark the start of the traversal, 'u' arriving
    // from 'u' must be indicated.
    g.reset(false);
    g.goto_first_vertex();

    while(g.has_current_vertex()){
        auto u = g.current_vertex();

        if (!u->is_visited()){
            depth_first_scan(g, u, u, p);
            g.goto_vertex(u);
        }

        g.goto_next_vertex();
    }
    //
}

template <class T, class E, class Processor>
void depth_first_scan(Graph<T, E> &g,
                      typename Graph<T, E>::VertexRef &v,
                      typename Graph<T, E>::VertexRef &u,
                      Processor &p)
{
    assert(!v->is_visited());
    // TODO
    // Remember: move vertex cursor to v to scan all the edges incident on it.

    v->set_visited(true);
    p(v,u);

    g.goto_vertex(v);
    while (g.has_current_edge()) {

        auto u = g.current_edge()->other(v);

        if (!u->is_visited()) {
            depth_first_scan(g, u, v, p);
            g.goto_edge(v,u);
        }

        g.goto_next_edge();
    }

    //
}

template <class T, class E, class Processor>
void breadth_first_scan(Graph<T, E> &g, Processor &p)
{
    // TODO
    // Remember: reset to false the visited flags.
    g.reset(false);
    g.goto_first_vertex();

    while(g.has_current_vertex()){
        auto u = g.current_vertex();

        if (!u->is_visited()){
            depth_first_scan(g, u, u, p);
            g.goto_vertex(u);
        }

        g.goto_next_vertex();
    }
    //
}

template <class T, class E, class Processor>
void breadth_first_scan(Graph<T, E> &g, typename Graph<T, E>::VertexRef &v,
                        typename Graph<T, E>::VertexRef &u,
                        Processor &p)
{
    assert(!v->is_visited());

    // TODO
    // Remember: we want to know from which vertex 'u' arriving from when processing
    // a vertex 'v' so we can enqueue a pair <v,u>.
    // Remember: to mark the first vertex we enqueue the pair <u,u>
    using Pair = std::pair<typename Graph<T, E>::VertexRef, typename Graph<T, E>::VertexRef>;

    std::queue<Pair> q;

    q.push(Pair(g.current_vertex(), g.current_vertex()));
    while (!q.empty()){

        auto pair = q.front(); 
        auto u = pair.first;
        q.pop();

        if (!u->is_visited()){
            p(pair.first, pair.second);
            u->set_visited(true);
            g.goto_vertex(u);

            while (g.has_current_edge()){
                auto v = g.current_edge()->other(u);

                if (!v->is_visited()){
                    q.push(Pair(v,u));
                }
                g.goto_next_edge();
            }
        }

    }


    //
}

/**
 * @brief Helper function to do the topological sorting.
 *
 * @param g is the directed acyclic graph.
 * @param u is the vertex to continue the traversal.
 * @param sorting is the sorted vertices list.
 */
template <class T, class E>
void topological_sorting(Graph<T, E> &g,
                         typename Graph<T, E>::VertexRef &u,
                         std::list<typename Graph<T, E>::VertexRef> &sorting)
{
    assert(!u->is_visited());
    // TODO
    // Remember: move vertex cursor to u to scan all the edges incident on it.

    g.goto_vertex(u);

    while (g.has_current_edge()){
        auto v = g.current_edge()->other(u);

        if (!v->is_visited()){
            topological_sorting(g, v, sorting);
            g.goto_edge(u , v);
        }
        
        g.goto_next_edge();
    }

    u->set_visited(true);
    sorting.push_front(u);

    //
}

template <class T, class E>
void topological_sorting(Graph<T, E> &g,
                         std::list<typename Graph<T, E>::VertexRef> &sorting)
{
    assert(g.is_directed());
    // TODO
    // Remember: set the visited flags to false.

    g.reset(false);
    g.goto_first_vertex();

    while(g.has_current_vertex()){
        auto u = g.current_vertex();

        if (!u->is_visited()){
            topological_sorting(g, u, sorting);
            g.goto_vertex(u);
        }

        g.goto_next_vertex();
    }

    //
}