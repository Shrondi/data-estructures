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

    //
    return ret_v;
}

template <class T>
DNode<T>::DNode()
{
    // TODO

    //
    assert(is_dummy());
}

template <class T>
DNode<T>::DNode(T const &it)
{
    // TODO

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

    //
    return it;
}

template <class T>
typename DNode<T>::Ref DNode<T>::prev() const
{
    DNode<T>::Ref n;
    // TODO

    //
    return n;
}

template <class T>
typename DNode<T>::Ref DNode<T>::next() const
{
    DNode<T>::Ref n;
    // TODO

    //
    return n;
}

template <class T>
void DNode<T>::set_item(const T &new_it)
{
    // TODO

    //
    assert(item() == new_it);
}

template <class T>
void DNode<T>::set_prev(DNode<T>::Ref n)
{
    // TODO

    //
    assert(n == prev());
}

template <class T>
void DNode<T>::set_next(DNode<T>::Ref n)
{
    // TODO

    //
    assert(n == next());
}

template <class T>
List<T>::List()
{
    // TODO
    // Remember: in an empty list, the dummy node is linked with itself.

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

    //
    return list;
}

template <class T>
bool List<T>::is_empty() const
{
    bool ret_val = true;
    // TODO

    //
    return ret_val;
}

template <class T>
size_t List<T>::size() const
{
    size_t ret_val = 0;
    // TODO

    //
    return ret_val;
}

template <class T>
void List<T>::set_size(size_t new_size)
{
    // TODO

    //
    assert(size() == new_size);
}

template <class T>
typename List<T>::iterator List<T>::begin() const
{
    iterator iter;
    // TODO
    // Hint: use iterators.

    //
    return iter;
}

template <class T>
typename List<T>::iterator List<T>::end() const
{
    iterator iter;
    // TODO
    // Hint: use iterators.

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

    //

    return f;
}

template <class T>
void List<T>::fold(std::ostream &out) const
{
    // TODO

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

    //
    assert(is_empty() || end().prev() == old_end_prev_prev);
    assert(size() == (old_size - 1));
}

template <class T>
typename List<T>::iterator List<T>::find(T const &it, List<T>::iterator const &from) const
{
    iterator ret_v;
    // TODO

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

    //
    return ret_v;
}
template <class T>
ListIterator<T>::ListIterator()
{
    // TODO

    //
    assert(!is_valid());
};

template <class T>
ListIterator<T>::ListIterator(typename DNode<T>::Ref const &n)
{
    // TODO

    //
    assert(n != nullptr || !is_valid());
};

template <class T>
T ListIterator<T>::item() const
{
    assert(is_valid());
    T ret_v;
    // TODO

    //
    return ret_v;
}

template <class T>
ListIterator<T> ListIterator<T>::next(size_t dist) const
{
    assert(is_valid());
    ListIterator<T> ret_v;
    // TODO

    //
    return ret_v;
}

template <class T>
ListIterator<T> ListIterator<T>::prev(size_t dist) const
{
    assert(is_valid());
    ListIterator<T> ret_v;
    // TODO

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

    //
    return ret_v;
}

template <class T>
bool ListIterator<T>::operator==(ListIterator<T> const &o) const
{
    bool ret_v = false;

    // TODO
    // Remember: two iterators are equal if both point to the same node.

    //
    return ret_v;
}

template <class T>
bool ListIterator<T>::operator!=(ListIterator<T> const &o) const
{
    bool ret_v = false;

    // TODO
    // Remember: two iterators are equal if both point to the same node.

    //
    return ret_v;
}

template <class T>
void ListIterator<T>::set_item(T const &it)
{
    assert(is_valid());
    // TODO

    //
    assert(it == item());
}

template <class T>
void ListIterator<T>::goto_next(size_t dist)
{
    assert(is_valid());
    // TODO

    //
}

template <class T>
void ListIterator<T>::goto_prev(size_t dist)
{
    assert(is_valid());
    // TODO

    //
}

template <class T>
typename DNode<T>::Ref ListIterator<T>::node() const
{
    typename DNode<T>::Ref ret_v;
    // TODO

    //
    return ret_v;
}

template <class T>
void ListIterator<T>::set_node(typename DNode<T>::Ref const &n)
{
    // TODO

    //
    assert(node() == n);
}