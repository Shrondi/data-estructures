/**
 * @file graph_utils_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <string>

#include "graph.hpp"

////////////////////////////////////////////////////////////////////////////////
// Vertex implementation
////////////////////////////////////////////////////////////////////////////////

template <class T>
Vertex<T>::Vertex(size_t l, T const &data)
{
    // TODO
    label_ = l;
    item_ = data;
    is_visited_ = false;
    //
    assert(label() == l);
    assert(item() == data);
    assert(!is_visited());
}

template <class T>
const T &Vertex<T>::item() const
{
    // TODO
    // Change the code to return a const reference to the proper attribute.
    //T aux;
    //return aux;
    return item_;
    //
}

template <class T>
typename Vertex<T>::key_t Vertex<T>::key() const
{
    key_t ret_v;
    // TODO
    // Remember: it is assumed that T type defines a type T::key_t and
    // a method 'T::key_t T::key() const'
    ret_v = item_.key();
    //
    return ret_v;
}

template <class T>
size_t Vertex<T>::label() const
{
    size_t ret_v = 0;
    // TODO
    ret_v = label_;
    //
    return ret_v;
}

template <class T>
bool Vertex<T>::is_visited() const
{
    bool ret_v = false;
    // TODO
    ret_v = is_visited_ == true;
    //
    return ret_v;
}

template <class T>
void Vertex<T>::set_item(T const &v)
{
    // TODO
    item_ = v;
    //
    assert(item() == v);
}

template <class T>
void Vertex<T>::set_visited(bool new_st)
{
    // TODO
    is_visited_ = new_st;
    //
    assert(new_st || !is_visited());
    assert(!new_st || is_visited());
}

////////////////////////////////////////////////////////////////////////////////
// Edge implementation
////////////////////////////////////////////////////////////////////////////////

template <class T, class E>
Edge<T, E>::Edge(VertexRef u, VertexRef v, E const &data)
{
    // TODO
    u_ = u;
    v_ = v;
    item_ = data;
    is_visited_ = false;
    //
    assert(has(u));
    assert(has(v));
    assert(other(u) == v);
    assert(other(v) == u);
    assert(first() == u);
    assert(second() == v);
    assert(item() == data);
    assert(!is_visited());
}

template <class T, class E>
bool Edge<T, E>::is_visited() const
{
    bool ret_v = false;
    // TODO
    ret_v = is_visited_ == true;
    //
    return ret_v;
}

template <class T, class E>
E const &Edge<T, E>::item() const
{
    // TODO
    // Change the code to return a const reference to the proper attribute.
    //E aux;
    //return aux;
    return item_;
    //
}

template <class T, class E>
bool Edge<T, E>::has(VertexRef const &n) const
{
    bool ret_val = false;
    // TODO
    ret_val = n == u_ || n == v_;
    //
    return ret_val;
}

template <class T, class E>
typename Edge<T, E>::VertexRef Edge<T, E>::other(VertexRef const &n) const
{
    assert(has(n));
    VertexRef ret_val;
    // TODO
    ret_val = (n == u_ ? v_ : u_); 
    //
    return ret_val;
}

template <class T, class E>
typename Edge<T, E>::VertexRef const &Edge<T, E>::first() const
{
    // TODO
    // Change the code to return a const reference to the proper attribute.
    //VertexRef aux;
    //return aux;
    return u_;
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef const &Edge<T, E>::second() const
{
    // TODO
    // Change the code to return a const reference to the proper attribute.
    //VertexRef aux;
    //return aux;
    return v_;
    //
}

template <class T, class E>
void Edge<T, E>::set_visited(bool new_st)
{
    // TODO
    is_visited_ = new_st;
    //
    assert(new_st || !is_visited());
    assert(!new_st || is_visited());
}

template <class T, class E>
void Edge<T, E>::set_item(E const &v)
{
    // TODO
    item_ = v;
    //
    assert(item() == v);
}

////////////////////////////////////////////////////////////////////////////////
// Graph implementation
////////////////////////////////////////////////////////////////////////////////

template <class T, class E>
Graph<T, E>::Graph(bool directed)
{
    // TODO
    // Remember: set next label attribute to 0.
    next_label_ = 0;
    is_directed_ = directed;
    //

    assert(is_empty());
    assert(!directed || is_directed());
    assert(directed || !is_directed());
}

template <class T, class E>
bool Graph<T, E>::is_empty() const
{
    bool ret_v = true;
    // TODO
    // Hint: check if the vertices list is empty.
    ret_v = vertices_.empty();
    //
    return ret_v;
}

template <class T, class E>
bool Graph<T, E>::is_directed() const
{
    bool ret_v = true;
    // TODO
    ret_v = is_directed_ == true;
    //
    return ret_v;
}

template <class T, class E>
size_t Graph<T, E>::num_vertices() const
{
    size_t ret_v = 0;
    // TODO
    ret_v = vertices_.size();
    //
    return ret_v;
}

template <class T, class E>
size_t Graph<T, E>::num_edges() const
{
    size_t ret_v = 0;
    // TODO
    // Remember: is the graph is undirected the edge (u:v) was duplicated in
    // the incident list of u an v.
    for (auto const &pair : vertices_){
        for (auto const &edges : pair.second){
            if (edges->first() == pair.first){
                ++ret_v;
            }
        }
    }
    //
    return ret_v;
}

template <class T, class E>
std::vector<typename Graph<T, E>::VertexRef>
Graph<T, E>::vertices() const
{
    std::vector<typename Graph<T, E>::VertexRef> vs;
    // TODO
    for (auto pair : vertices_){
        vs.push_back(pair.first);
    }
    //
    assert(vs.size() == num_vertices());
    return vs;
}

template <class T, class E>
std::vector<typename Graph<T, E>::EdgeRef>
Graph<T, E>::edges() const
{
    std::vector<typename Graph<T, E>::EdgeRef> es;
    // TODO
    // Remember: if the graph is undirected, the edge (u,v) was inserted into
    // the incident list of u and v, but we only want one in the returned vector.
    for (auto const& pair : vertices_){
        for (auto const &edge : pair.second){
            if (edge->first() == pair.first){
                es.push_back(edge);
            }
        }
    }
    //
    assert(es.size() == num_edges());
    return es;
}

template <class T, class E>
bool Graph<T, E>::has(VertexRef const &u) const
{
    assert(u != nullptr);
    bool ret_v = false;
    // TODO
    // Hint: scan the vertices pair list and check if someone has the first element
    // equal to u.
    for (auto pair : vertices_){
        if (pair.first == u){
            ret_v = true;
            break;
        }
    }
    //
    return ret_v;
}

template <class T, class E>
bool Graph<T, E>::is_adjacent(VertexRef const &u, VertexRef const &v) const
{
    assert(has(u));
    assert(has(v));
    bool ret_v = false;

    // TODO
    // Remember: a vertex u is adjacent to v if there is a edge (u,v) or
    // if the graph is undirected, there is a edge (v,u).
    // Hint: use the method edge(x, y).
    ret_v = edge(u, v) != nullptr;
    //
    return ret_v;
}

template <class T, class E>
typename Graph<T, E>::VertexRef
Graph<T, E>::vertex(size_t label) const
{
    VertexRef ret_v = nullptr;

    // TODO
    auto iter = std::begin(vertices_);
    while (iter != std::end(vertices_) && !ret_v)
    {
        if (iter->first->label() == label)
            ret_v = iter->first;
        else
            ++iter;
    }
    //

    return ret_v;
}

template <class T, class E>
bool Graph<T, E>::has_current_vertex() const
{
    bool ret_v = false;
    // TODO
    // Hint: check if the vertex cursor is at the end of the vertices list.
    ret_v = curr_vertex_ != vertices_.end();
    //
    return ret_v;
}

template <class T, class E>
typename Graph<T, E>::VertexRef Graph<T, E>::current_vertex() const
{
    assert(has_current_vertex());
    VertexRef ret_v;
    // TODO
    ret_v = curr_vertex_->first;
    //
    return ret_v;
}

template <class T, class E>
bool Graph<T, E>::has_current_edge() const
{
    bool ret_v = false;
    // TODO
    // Hint: check if the edge cursor is at the end of the adjacent list of the
    // current vertex.
    ret_v = curr_edge_ != curr_vertex_->second.end();
    //
    assert(!ret_v || has_current_vertex());
    return ret_v;
}

template <class T, class E>
typename Graph<T, E>::EdgeRef Graph<T, E>::current_edge() const
{
    assert(has_current_edge());
    EdgeRef ret_v;
    // TODO
    ret_v = *curr_edge_;
    //
    assert(!is_directed() || ret_v->first() == current_vertex());
    assert(is_directed() || ret_v->has(current_vertex()));
    return ret_v;
}

template <class T, class E>
typename Graph<T, E>::EdgeRef Graph<T, E>::edge(VertexRef const &u,
                                                VertexRef const &v) const
{
    assert(has(u));
    assert(has(v));
    EdgeRef ret_v = nullptr;

    // TODO
    // Hint: Use 'goto_vertex()' and 'goto_edge()' to find the edge, but
    // remember to restore the cursors to their initial values ​​at the end.
    auto curr_vertex = curr_vertex_;
    auto curr_edge = curr_edge_;

    const_cast<Graph*>(this)->goto_edge(u,v);
    ret_v = has_current_edge() ? *curr_edge_ : nullptr;

    const_cast<Graph*>(this)->curr_vertex_ = curr_vertex;
    const_cast<Graph*>(this)->curr_edge_ = curr_edge;
    //

    assert(!ret_v || (!is_directed() || ret_v->first() == u));
    assert(!ret_v || (!is_directed() || ret_v->second() == v));
    assert(!ret_v || (is_directed() || ret_v->has(u)));
    assert(!ret_v || (is_directed() || ret_v->has(v)));
    return ret_v;
}

template <class T, class E>
void Graph<T, E>::reset(bool state)
{
    // TODO
    // Remember: Both vertices and edges has a visited flag to be reset.
    for (auto &n : vertices_)
    {
        n.first->set_visited(state);
        for (auto &e : n.second)
            e->set_visited(state);
    }
    //
}

template <class T, class E>
void Graph<T, E>::goto_first_vertex()
{
    assert(!is_empty());
    // TODO
    // Remember: the edge cursor must be initialized too.
    curr_vertex_ = vertices_.begin();
    goto_first_edge();
    //
    assert(!has_current_edge() ||
           (!is_directed() || current_edge()->first() == current_vertex()));
    assert(!has_current_edge() ||
           (is_directed() || current_edge()->has(current_vertex())));
}

template <class T, class E>
void Graph<T, E>::goto_first_edge()
{
    assert(has_current_vertex());
    // TODO
    curr_edge_ = curr_vertex_->second.begin();
    //
    assert(!has_current_edge() ||
           (!is_directed() || current_edge()->first() == current_vertex()));
    assert(!has_current_edge() ||
           (is_directed() || current_edge()->has(current_vertex())));
}

template <class T, class E>
void Graph<T, E>::goto_next_vertex()
{
    assert(has_current_vertex());
    // TODO
    //  Remember: you must update the edge cursor too.
    ++curr_vertex_;
    if (has_current_vertex()){
        goto_first_edge();
    }else{
        curr_edge_ = curr_vertex_->second.end();
    }
    //
    assert(!has_current_edge() ||
           (!is_directed() || current_edge()->first() == current_vertex()));
    assert(!has_current_edge() ||
           (is_directed() || current_edge()->has(current_vertex())));
}

template <class T, class E>
void Graph<T, E>::goto_next_edge()
{
    assert(has_current_edge());
    // TODO
    ++curr_edge_;
    //
    assert(!has_current_edge() ||
           (!is_directed() || current_edge()->first() == current_vertex()));
    assert(!has_current_edge() ||
           (is_directed() || current_edge()->has(current_vertex())));
}

template <class T, class E>
void Graph<T, E>::goto_vertex(VertexRef const &u)
{
    assert(has(u));
    // TODO
    //  Remember: update edge cursor too.
    for (auto it = vertices_.begin(); it != vertices_.end(); ++it){
        if (it->first == u){
            curr_vertex_ = it;
            goto_first_edge();
            break;
        }
    }
    //
    assert(!has_current_edge() ||
           (!is_directed() || current_edge()->first() == current_vertex()));
    assert(!has_current_edge() ||
           (is_directed() || current_edge()->has(current_vertex())));
}

template <class T, class E>
void Graph<T, E>::goto_edge(VertexRef const &v)
{
    assert(has_current_vertex());
    assert(has(v));
    // TODO
    // Remember: we are finding out the edge (current_vertex(),v)
    while (has_current_edge() && current_edge()->other(current_vertex()) != v){
        goto_next_edge();
    }

    //
    assert(!has_current_edge() || (!is_directed() || current_edge()->first() == current_vertex()));
    assert(!has_current_edge() || (!is_directed() || current_edge()->second() == v));
    assert(!has_current_edge() || (is_directed() || current_edge()->has(current_vertex())));
    assert(!has_current_edge() || (is_directed() || current_edge()->has(v)));
}

template <class T, class E>
void Graph<T, E>::goto_edge(VertexRef const &u, VertexRef const &v)
{
    assert(has(u));
    assert(has(v));
    // TODO
    // Hint: use goto_vertex() and goto_edge() methods.
    goto_vertex(u);
    goto_edge(v);
    //
    assert(current_vertex() == u);
    assert(!has_current_edge() || (!is_directed() || current_edge()->first() == u));
    assert(!has_current_edge() || (!is_directed() || current_edge()->second() == v));
    assert(!has_current_edge() || (is_directed() || current_edge()->has(u)));
    assert(!has_current_edge() || (is_directed() || current_edge()->has(v)));
}

template <class T, class E>
void Graph<T, E>::goto_edge(EdgeRef const &e)
{
    assert(has(e->first()));
    assert(has(e->second()));
    // TODO
    // Hint: delegate to goto_edge(u,v)
    goto_edge(e->first(), e->second());
    //
    assert(current_vertex() == e->first());
    assert(!has_current_edge() || current_edge()->first() == e->first());
    assert(!has_current_edge() || current_edge()->second() == e->second());
}

template <class T, class E>
typename Graph<T, E>::VertexRef Graph<T, E>::find_vertex(typename T::key_t const &key)
{
    assert(!is_empty());
    VertexRef ret_v = nullptr;
    // TODO
    // Hint: use find_next_vertex() from the first vertex.
    goto_first_vertex();
    ret_v = find_next_vertex(key);
    //
    assert(!ret_v || (has_current_vertex() && (current_vertex() == ret_v) && (ret_v->key() == key)));
    return ret_v;
}

template <class T, class E>
typename Graph<T, E>::VertexRef Graph<T, E>::find_next_vertex(typename T::key_t const &key)
{
    assert(!is_empty());
    VertexRef ret_v = nullptr;
    // TODO
    // Remember: find from current vertex to the last.
    // Hint: use vertex cursor movement methods.
    while(has_current_vertex() && current_vertex()->key() != key){
        goto_next_vertex();
    }

    ret_v = has_current_vertex() ? current_vertex() : nullptr;
    //
    assert(!ret_v || (has_current_vertex() && (current_vertex() == ret_v) && (ret_v->key() == key)));
    return ret_v;
}

template <class T, class E>
typename Graph<T, E>::VertexRef Graph<T, E>::add_vertex(T const &v)
{
    VertexRef ret_v = nullptr;
    // TODO
    // Remember: update vertex and edge cursors.
    // Remember: use push_back to add the vertex to the list of vertices.
    // Remember: updated the next label attribute to next integer.
    ret_v = std::make_shared<Vertex<T>>(next_label_, v);

    vertices_.push_back({ret_v, edges_list_t()});

    curr_vertex_ = std::prev(vertices_.end());
    goto_first_edge();

    ++next_label_;
    //
    assert(has_current_vertex());
    assert(ret_v == current_vertex());
    assert(ret_v->item() == v);
    return ret_v;
}

template <class T, class E>
void Graph<T, E>::remove_vertex()
{
    assert(has_current_vertex());
#ifndef NDEBUG
    auto old_num_vertices = num_vertices();
    VertexRef old_vertex = current_vertex();
#endif
    // TODO
    // Remember: you must also remove all edges incident in this vertex.

    for (auto &pair : vertices_){

        auto &edges = pair.second;
        for (auto edge_it = edges.begin(); edge_it != edges.end(); ++edge_it){
            if ((*edge_it)->second() == current_vertex()){
                edge_it = edges.erase(edge_it);
            }
                    
        }
    }

    vertices_.erase(curr_vertex_);
    curr_vertex_ = vertices_.end();
    
    //
    assert(!has(old_vertex));
    assert(!has_current_vertex());
    assert(num_vertices() == (old_num_vertices - 1));
}

template <class T, class E>
typename Graph<T, E>::EdgeRef Graph<T, E>::add_edge(VertexRef const &u, VertexRef const &v, E const &item)
{
    assert(has(u));
    assert(has(v));

    EdgeRef ret_v = nullptr;

    // TODO
    // Remember: update vertex and edge cursors.
    // Remember: if the graph is directed, the edge only is incident on
    // the u end but if it is not directed, the edge is incident both u and v ends.
    ret_v = std::make_shared<Edge<T,E>>(u, v, item);
    
    if (!is_directed()){
        goto_vertex(v);
        curr_vertex_->second.push_back(ret_v);
    }

    goto_vertex(u);
    curr_vertex_->second.push_back(ret_v);
    curr_edge_ = std::prev(curr_vertex_->second.end());

    //
    assert(current_vertex() == u);
    assert(current_edge()->second() == v);
    assert(current_edge()->item() == item);
    return ret_v;
}

template <class T, class E>
void Graph<T, E>::remove_edge()
{
    assert(has_current_edge());
#ifndef NDEBUG
    auto old_num_edges = num_edges();
    auto old_first = current_edge()->first();
    auto old_second = current_edge()->second();
#endif
    // TODO
    // Remember: if the graph is undirected, the edge u-v was duplicated as
    // incident in the u and v lists.

    auto curr_vertex = curr_vertex_;

    curr_vertex_->second.erase(curr_edge_);

    if (!is_directed()){
        goto_vertex(current_edge()->second());
        curr_vertex_->second.erase(curr_edge_);
    }

    curr_vertex_ = curr_vertex;
    curr_edge_ = curr_vertex_->second.end();

    //
    assert(!has_current_edge());
    assert(!is_adjacent(old_first, old_second));
    assert(is_directed() || !is_adjacent(old_second, old_first));
    assert(num_edges() == (old_num_edges - 1));
}

template <class T, class E>
std::ostream &
Graph<T, E>::fold(std::ostream &out) const
{
    // TODO
    // Hint: you can use cursor movement.
    // Remember: restore cursors to initial values.
    out << (is_directed() ? "DIRECTED" : "UNDIRECTED") << "\n";

    out << num_vertices() << "\n";
    for (auto vertex : vertices()){
        out << vertex->item() << "\n";
    }

    out << num_edges() << "\n";
    for (auto edge : edges()){
        out << edge->first()->key() << " " << edge->second()->key() << " " << edge->item() << "\n";
    }
    //
    return out;
}

template <class T, class E>
Graph<T, E>::Graph(std::istream &in) noexcept(false)
{
    // TODO
    // Remember: Throw std::runtime_error("Wrong graph") when detecting a wrong
    //           input format.
    // Remember: key_t type is used to give the edge's ends.

    // TODO
    std::string token;

    // Reset the next label attribute to 0.
    next_label_ = 0;
    //

    // TODO
    // First: is it directed or undirected?
    in >> token;
    if (token == "DIRECTED"){
        is_directed_ = true;

    }else if (token == "UNDIRECTED"){
        is_directed_ = false;

    }else{
        std::runtime_error("Wrong graph");
    }
    //

    size_t size = 0;
    // TODO
    // Second: get the number of vertices and create a Graph with this capacity.
    in >> size;
    //

    // TODO
    // Third: load the N vertices data item and create the regarding vertices.
    // Hint: use add_vertex() to add the unfold vertices to the graph.
    for (size_t i = 0; i < size; i++){
        T item;
        in >> item;
        add_vertex(item);
    }
    //

    size_t n_edges = 0;

    // TODO
    // Fourth: load the number of edges.
    in >> n_edges;
    //

    // TODO
    // Fifth: load the N edges.
    // Remember: Use T::key_t type to load the edge's end keys.
    // Hint: use find_vertex() to get ends.
    // Hint: use add_edge() to add the unfold edge to the graph.

    for (size_t i = 0; i < n_edges; i++){
        typename T::key_t u_key, v_key;
        E item;

        in >> u_key >> v_key >> item;

        VertexRef u = find_vertex(u_key);
        VertexRef v = find_vertex(v_key);

        if (u == nullptr || v == nullptr){
            throw std::runtime_error("Wrong graph");
        }
        
        add_edge(u, v, item);
    }
    //
}
