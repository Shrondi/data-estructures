/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <sstream>
#include <stdexcept>
#include <cassert>

#include "list.hpp"

template <class T>
bool DNode<T>::is_dummy() const
{
    bool ret_v = false;
    // TODO
    if (_item == nullptr){
        ret_v = true;
    }
    //
    return ret_v;
}

template <class T>
DNode<T>::DNode()
{
    // TODO
    _item = nullptr;
    _next = nullptr;
    _prev = nullptr;
    //
    assert(is_dummy());
}

template <class T>
DNode<T>::DNode(T const &it)
{
    // TODO
    _item = std::make_shared<T>(it);
    _prev = nullptr;
    _next = nullptr;
    //
    assert(!is_dummy());
    assert(next() == nullptr);
    assert(prev() == nullptr);
}

template <class T>
typename DNode<T>::Ref DNode<T>::create()
{
    return std::make_shared<DNode<T>>();
}

template <class T>
typename DNode<T>::Ref DNode<T>::create(T const &it)
{
    return std::make_shared<DNode<T>>(it);
}

template <class T>
DNode<T>::~DNode()
{
    // TODO
    // Hint: if std::shared_ptr is used for the references,
    //   there is nothing todo.

    //
}

template <class T>
T DNode<T>::item() const
{
    assert(!is_dummy());
    T it;
    // TODO
    it = *_item.get();
    //
    return it;
}

template <class T>
typename DNode<T>::Ref DNode<T>::prev() const
{
    DNode<T>::Ref n;
    // TODO
    n = _prev;
    //
    return n;
}

template <class T>
typename DNode<T>::Ref DNode<T>::next() const
{
    DNode<T>::Ref n;
    // TODO
    n = _next;
    //
    return n;
}

template <class T>
void DNode<T>::set_item(const T &new_it)
{
    // TODO
    _item = std::make_shared<T>(new_it);
    //
    assert(item() == new_it);
}

template <class T>
void DNode<T>::set_prev(DNode<T>::Ref n)
{
    // TODO
    _prev = n;
    //
    assert(n == prev());
}

template <class T>
void DNode<T>::set_next(DNode<T>::Ref n)
{
    // TODO
    _next = n;
    //
    assert(n == next());
}

template <class T>
List<T>::List()
{
    // TODO
    // Remember: in an empty list, the dummy node is linked with itself.
    _dummy = DNode<T>::create();
    _size = 0;

    _dummy->set_next(_dummy);
    _dummy->set_prev(_dummy);
    //
    assert(is_empty());
}

template <class T>
List<T>::~List()
{
    // Think. We are using smart pointers (shared_ptr) so the nodes will
    // released automatically when the references going off.
}

template <class T>
typename DNode<T>::Ref List<T>::dummy() const
{
    typename DNode<T>::Ref d;
    // TODO
    d = _dummy;
    //
    return d;
}

template <class T>
typename List<T>::Ref List<T>::create()
{
    auto l = List<T>::Ref(new List<T>);
    l->this_ = l;
    return l;
}

template <class T>
typename List<T>::Ref List<T>::create(std::istream &in) noexcept(false)
{
    List<T>::Ref list;
    std::string token;
    in >> token;

    // TODO
    // Hint: use std::istringstream to convert from "string" to template
    //  parameter T type.
    // Remember: throw std::runtime_error("Wrong input format.") exception when an input
    //  format error was found.
    
    T item; // Item to save in the list

    list = List<T>::create();

    // If the list is not empty ...
    if (token != "[]"){
    
        // Check the input format
        if (token != "["){
            throw std::runtime_error("Wrong input format.");
        }

        // Process each element of the input stream as a string until find "]"
        while (in >> token && token != "]"){

            // Convert string to template parameter T type
            std::istringstream convert(token);

            convert >> item;

            // Fail if a element is not a T type
            if (convert.fail()){
                throw std::runtime_error("Wrong input format.");
            }

            // Save the item in the list
            list->push_back(item);
        }

        // Check the format
        if (token != "]"){
            throw std::runtime_error("Wrong input format.");
        }
    }
    //
    return list;
}

template <class T>
bool List<T>::is_empty() const
{
    bool ret_val = true;
    // TODO
    if (_size > 0){
        ret_val = false;
    }
    //
    return ret_val;
}

template <class T>
size_t List<T>::size() const
{
    size_t ret_val = 0;
    // TODO
    ret_val = _size;
    //
    return ret_val;
}

template <class T>
void List<T>::set_size(size_t new_size)
{
    // TODO
    _size = new_size;
    //
    assert(size() == new_size);
}

template <class T>
typename List<T>::iterator List<T>::begin() const
{
    iterator iter;
    // TODO
    // Hint: use iterators.
    iter = typename ListIterator<T>::ListIterator(_dummy->next());
    //
    return iter;
}

template <class T>
typename List<T>::iterator List<T>::end() const
{
    iterator iter;
    // TODO
    // Hint: use iterators.
    iter = typename ListIterator<T>::ListIterator(_dummy);
    //
    return iter;
}

template <class T>
T List<T>::front() const
{
    assert(!is_empty());
    T f;
    // TODO
    // Hint: use iterators.
    f = _dummy->next()->item();
    //
    return f;
}

template <class T>
T List<T>::back() const
{
    assert(!is_empty());
    T f;

    // TODO
    // Hint: use iterators.
    f = _dummy->prev()->item();
    //

    return f;
}

template <class T>
void List<T>::fold(std::ostream &out) const
{
    // TODO

    // Empty list -> "[ ]"
    if (is_empty()){

        out << "[ ]";

    // Another list -> [ 0 1 2 ]
    }else{

        out << "[ ";
        
        // Iterate trough the list sending each element to the output stream
        for (auto it = begin(); it != end(); it.goto_next()){
            out << it.item() << " ";
        }
        
        out << "]";

    }
    //
}

template <class T>
void List<T>::hook(typename DNode<T>::Ref n, typename DNode<T>::Ref pos)
{
#ifndef NDEBUG
    auto old_size = size();
#endif
    // TODO
    // Remember updating the size.
    _size += 1;

    n->set_prev(pos->prev());
    pos->prev()->set_next(n);

    n->set_next(pos);
    pos->set_prev(n);

    /*
        if (_size == 1){ // Si dummy no esta linkeado consigo mismo, hay que poner la condicion de cuando es 1 ya que 
                        // los el otro codigo no funcionaria al obtener un nullptr
            n->set_prev(_dummy);
            _dummy->set_next(n);
        }else{
            n->set_prev(pos->prev());
            pos->prev()->set_next(n);
        }

        n->set_next(pos);
        pos->set_prev(n);
    */

    //
    assert(size() == old_size + 1);
}

template <class T>
void List<T>::unhook(typename DNode<T>::Ref pos)
{
#ifndef NDEBUG
    auto old_size = size();
#endif
    // TODO
    // Remember updating the size.
    _size -= 1;

    pos->prev()->set_next(pos->next());
    pos->next()->set_prev(pos->prev());

    //
    assert(size() == old_size - 1);
}

template <class T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator const &pos,
                                           T const &it)
{
#ifndef NDEBUG
    auto old_is_empty = is_empty();
    auto old_size = size();
    auto old_pos_prev = pos.prev();
#endif
    iterator ret_v;
    // TODO
    // Hint: delegate in hook.
    auto node = DNode<T>::create(it);

    hook(node, pos.node());

    ret_v = typename ListIterator<T>::ListIterator(node);
    //
    assert(!old_is_empty || (front() == it && back() == it));
    assert(old_is_empty || ret_v.next() == pos);
    assert(old_is_empty || old_pos_prev == ret_v.prev());
    assert(size() == (old_size + 1));
    return ret_v;
}

template <class T>
typename List<T>::iterator List<T>::remove(List<T>::iterator const &pos)
{
    assert(!is_empty());
#ifndef NDEBUG
    auto old_size = size();
    auto old_pos_next = pos.next();
    auto old_pos_prev = pos.prev();
#endif
    iterator ret_v;
    // TODO
    // Hint: delegate in unkook

    unhook(pos.node());

    ret_v = pos.next();
    //
    assert(ret_v == old_pos_next);
    assert(ret_v.prev() == old_pos_prev);
    assert(size() == (old_size - 1));
    return ret_v;
}

template <class T>
void List<T>::push_front(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    //  Hint: delegate in insert();

    insert(begin(), new_it);

    /*
        if (_size == 0){ // Si dummy no esta linkeado consigo mismo hay que poner la condicion para cuando la lista esta vacia
                        // ya que begin() obtendria nullptr
            insert(_dummy, new_it);
        }else{
            insert(begin(), new_it);
        }
    */

    /*
        _size += 1;

        auto n = DNode<T>::create(new_it);

        if (_size == 1){
            n->set_next(_dummy);
            n->set_prev(_dummy);

            _dummy->set_prev(n);
            _dummy->set_next(n);

        }else{

            _dummy->next()->set_prev(n);

            n->set_next(_dummy->next());
            _dummy->set_next(n);

            n->set_prev(_dummy);
        } 
    */

    //
    assert(front() == new_it);
    assert(size() == (old_size + 1));
}

template <class T>
void List<T>::push_back(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    //  Hint: delegate in insert();
    insert(end(), new_it);
    //
    assert(back() == new_it);
    assert(size() == (old_size + 1));
}

template <class T>
void List<T>::pop_front()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    auto old_begin_next = begin().next();
#endif
    // TODO
    // Hint: delegate in remove.

    remove(begin());
    //
    assert(is_empty() || begin() == old_begin_next);
    assert(size() == (old_size - 1));
}

template <class T>
void List<T>::pop_back()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    auto old_end_prev_prev = end().prev().prev();
#endif
    // TODO
    // Hint: delegate in remove.

    remove(end().prev());
    //
    assert(is_empty() || end().prev() == old_end_prev_prev);
    assert(size() == (old_size - 1));
}

template <class T>
typename List<T>::iterator List<T>::find(T const &it, List<T>::iterator const &from) const
{
    iterator ret_v;
    // TODO

    // Iterate through the list searching the item
    // If the item is not found the iterator end() is returned
    for (ret_v = from; ret_v != end(); ret_v.goto_next()){

        // If the item is the searched -> BREAK
        if (ret_v.item() == it){
            break;
        }
    }
    //
    assert(ret_v == end() || ret_v.item() == it);
    return ret_v;
}

template <class T>
void List<T>::splice(iterator const &pos, Ref list2,
                     iterator const &first, iterator const &last)
{
#ifndef NDEBUG
    size_t old_size = size();
    size_t old_l2_size = list2->size();
    auto old_range_size = first.distance(last);
#endif
    // TODO
    // Hint: if the range [first, last) is empty, nothing must be done.

    // Example:
    //
    // pos = b; first = e; last = h
    //      before splice
    //          this:            ⇄ a ⇄ b ⇄ c ⇄
    //          list2:           ⇄ d ⇄ e ⇄ f ⇄ g ⇄ h ⇄
    //      after splice:
    //          this:            ⇄ a ⇄ e ⇄ f ⇄ g ⇄ b ⇄ c ⇄
    //          list2:           ⇄ d ⇄ h ⇄


    auto range_size = first.distance(last);

    if (range_size > 0){
        
        // Update lists sizes
        _size += range_size;
        list2->_size -= range_size;


        auto posNode = pos.node();
        auto prevPosNode = posNode->prev();
        auto firstNode = first.node();
        auto prevFirstNode = firstNode->prev();
        auto lastNode = last.node();
        auto prevLastNode = lastNode->prev();

        // Connect list2 range into this

        prevPosNode->set_next(firstNode); // a --> e : a next to e
        firstNode->set_prev(prevPosNode); // a <-- e : e prev to a

        posNode->set_prev(prevLastNode); // g <-- b : b prev to g
        prevLastNode->set_next(posNode); // g --> b : g next to b

        // Remove range from lis2

        prevFirstNode->set_next(lastNode);
        lastNode->set_prev(prevFirstNode);
    }

    
    //
    assert(size() == (old_size + old_range_size));
    assert(list2->size() == (old_l2_size - old_range_size));
}

template <class T>
void List<T>::splice(iterator const &pos, Ref list2)
{
#ifndef NDEBUG
    size_t old_size = size();
    auto old_list2_size = list2->size();
#endif
    // TODO
    // Hint: Delegate in splice the list2 range [begin, end).
    splice(pos, list2, list2->begin(), list2->end());
    //
    assert(size() == (old_size + old_list2_size));
    assert(list2->size() == 0);
    assert(list2->is_empty());
}

template <class T>
void List<T>::splice(iterator const &pos, Ref list2, iterator const &i)
{
#ifndef NDEBUG
    size_t old_size = size();
    auto old_list2_size = list2->size();
#endif
    // TODO
    // Hint: Delegate in splice the list2 range [i, i.next()).
    splice(pos, list2, i, i.next());
    //
    assert(size() == (old_size + 1));
    assert(list2->size() == (old_list2_size - 1));
}

template <class T>
template <class Compare>
void List<T>::merge(List<T>::Ref other, Compare comp)
{
    // TODO
    // Remember: The nodes of the other list are spliced into this list.

    auto it1 = begin(), it2 = other->begin();
    while (it1 != end() && it2 != other->end()){
        if (comp(it1.item(), it2.item())){
            it1.goto_next();

        }else{
            auto tmp = it2;

            it2.goto_next();

            splice(it1, other, tmp);
        }
    }

    if (it2 != other->end()){
        splice(it1, other);
    }
    //
}

template <class T>
template <class Compare>
void List<T>::sort(Compare comp)
{
    // TODO
    // Remember: we want a complexity in to N Log(N) so mergeSort algorithm is
    // a good candidate to sort the list.
    // Hint: Do a recursive implementation, splitting the list into two halves,
    // sorting recursively each part and merging the sorted lists to obtain
    // the full sorted list.

    // The empty list and a list with only one element are sorted by default.

    //
}

template <class T>
ListIterator<T>::~ListIterator() {}

template <class T>
bool ListIterator<T>::is_valid() const
{
    bool ret_v = false;
    // TODO
    // Remember: To Invoke node() here will provoque an infinite recursion!!.
    if (node_ != nullptr){
        ret_v = true;
    }
    //
    return ret_v;
}
template <class T>
ListIterator<T>::ListIterator()
{
    // TODO
    node_ = nullptr;
    //
    assert(!is_valid());
};

template <class T>
ListIterator<T>::ListIterator(typename DNode<T>::Ref const &n)
{
    // TODO
    node_ = n;
    //
    assert(n != nullptr || !is_valid());
};

template <class T>
T ListIterator<T>::item() const
{
    assert(is_valid());
    T ret_v;
    // TODO
    ret_v = node_->item();
    //
    return ret_v;
}

template <class T>
ListIterator<T> ListIterator<T>::next(size_t dist) const
{
    assert(is_valid());
    ListIterator<T> ret_v;
    // TODO
    auto n = DNode<T>::create();
    n = node_->next();

    if (dist > 1){
        for (int i = 1; i < dist; i++){
            n = n->next();
        }
    }

/*     std::cout << "VALOR NEXT: " << n << std::endl; */
    ret_v = ListIterator(n);
    //
    return ret_v;
}

template <class T>
ListIterator<T> ListIterator<T>::prev(size_t dist) const
{
    assert(is_valid());
    ListIterator<T> ret_v;
    // TODO
    auto n = DNode<T>::create();
    n = node_->prev();

    if (dist > 1){
        for (int i = 1; i < dist; i++){
            n = n->prev();
        }
    }
  /*   std::cout << "VALOR PREV: " << n << std::endl; */
    ret_v = ListIterator(n);
    //
    return ret_v;
}

template <class T>
size_t ListIterator<T>::distance(ListIterator<T> const &other) const
{
    assert(is_valid());
    assert(other.is_valid());
    size_t ret_v = 0;
    // TODO
    auto it = *this;
    while(it != other){
        ++ret_v;
        it.goto_next();
    } 
    //
    return ret_v;
}

template <class T>
bool ListIterator<T>::operator==(ListIterator<T> const &o) const
{
    bool ret_v = false;

    // TODO
    // Remember: two iterators are equal if both point to the same node.
    if (this->node() == o.node()){
        ret_v = true;
    }
    //
    return ret_v;
}

template <class T>
bool ListIterator<T>::operator!=(ListIterator<T> const &o) const
{
    bool ret_v = false;

    // TODO
    // Remember: two iterators are equal if both point to the same node.
    if (this->node() != o.node()){
        ret_v = true;
    }
    //
    return ret_v;
}

template <class T>
void ListIterator<T>::set_item(T const &it)
{
    assert(is_valid());
    // TODO
    node_->set_item(it);
    //
    assert(it == item());
}

template <class T>
void ListIterator<T>::goto_next(size_t dist)
{
    assert(is_valid());
    // TODO
    node_ = next(dist).node();
    //
}

template <class T>
void ListIterator<T>::goto_prev(size_t dist)
{
    assert(is_valid());
    // TODO
    node_ = prev(dist).node();
    //
}

template <class T>
typename DNode<T>::Ref ListIterator<T>::node() const
{
    typename DNode<T>::Ref ret_v;
    // TODO
    ret_v = node_;
    //
    return ret_v;
}

template <class T>
void ListIterator<T>::set_node(typename DNode<T>::Ref const &n)
{
    // TODO
    node_ = n;
    //
    assert(node() == n);
}