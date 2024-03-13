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
#include <cassert>
#include "cdarray.hpp"

template <class T>
CDArray<T>::CDArray(size_t cap)
{
    assert(cap > 0);
    // TODO

    cap_ = cap;
    tam_ = 0;
    front_ = 0;
    back_ = 0;
    data_ = std::shared_ptr<T>(new T[cap]);

    //
    assert(capacity() == cap);
    assert(is_empty());
    assert(size() == 0);
}

template <class T>
CDArray<T>::~CDArray()
{
    // TODO
    // Remember: depending on your representation, it is possible that nothing
    // must be done.

    //
}

template <class T>
typename CDArray<T>::Ref
CDArray<T>::create(size_t cap)
{
    return std::make_shared<CDArray<T>>(cap);
}

template <class T>
typename CDArray<T>::Ref
CDArray<T>::create(std::istream &in) noexcept(false)
{
    auto ret_v = std::make_shared<CDArray<T>>(1);
    // TODO
    // Hint: use std::istringstream to convert from "string" to template
    //  parameter T type.
    // Remember: throw std::runtime_error("Wrong input format.") exception when an input
    //  format error was found.

    std::string token;
    in >> token;

    T item; // Item to save in the array

    // If the array is not empty ...
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

            // Save the item in the array
            ret_v->push_back(item);
        }

        // Check the format
        if (token != "]"){
            throw std::runtime_error("Wrong input format.");
        }
    }

    //
    return ret_v;
}

template <class T>
bool CDArray<T>::is_empty() const
{
    bool ret_v = false;
    // TODO

    ret_v = tam_ == 0;

    //
    return ret_v;
}

template <class T>
bool CDArray<T>::is_full() const
{
    bool ret_v = false;
    // TODO

    ret_v = tam_ == cap_;

    //
    assert(!ret_v || size() == capacity());
    return ret_v;
}

template <class T>
size_t
CDArray<T>::capacity() const
{
    size_t ret_v = 0;
    // TODO

    ret_v = cap_;

    //
    return ret_v;
}

template <class T>
size_t
CDArray<T>::size() const
{
    size_t ret_v = 0;
    // TODO

    ret_v = tam_;

    //
    return ret_v;
}

template <class T>
std::ostream &
CDArray<T>::fold(std::ostream &out) const
{
    // TODO
    // Empty array -> "[ ]"
    if (is_empty()){

        out << "[ ]";

    // Another array -> [ 0 1 2 ] where 0 is the front and 2 is the back
    }else{

        out << "[ ";
        
        // Loop trough the array sending each element to the output stream
        for (int i = 0; i < tam_; ++i){
            out << get(i) << " ";
        }
        
        out << "]";

    }
    //
    return out;
}

template <class T>
T CDArray<T>::get(size_t pos) const
{
    T ret_v;
    // TODO

    ret_v = data_.get()[(front_ + (int)pos) % cap_];

    //
    return ret_v;
}

template <class T>
void CDArray<T>::set(size_t pos, T const &new_v)
{
    // TODO

    data_.get()[(front_ + (int)pos)%cap_] = new_v;

    //
    assert(new_v == get(pos));
}

size_t cInc(size_t v, size_t size)
{
    size_t ret_v;
    // TODO

    ret_v = ((int)v + 1) % size;

    //
    return ret_v;
}

size_t cDec(size_t v, size_t size)
{
#ifndef NDEBUG
    size_t old_v = v;
#endif
    size_t ret_v;
    // TODO
    // Remember: v is a unsigned value, so you must cast to signed before decrementing

    ret_v = (static_cast<int>(v) - 1 + size) % size;

    //
    assert(old_v == cInc(ret_v, size));
    return ret_v;
}

template <class T>
void CDArray<T>::push_front(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
    bool old_is_empty = is_empty();
    T old_front = is_empty() ? T() : get(0);
#endif
    // TODO

    if (is_empty()){
        front_ = 0;
        back_ = 0;

    }else{
        if (is_full()){
            grow();
        }

        front_ = cDec(front_, cap_);  
    }

    data_.get()[front_] = new_it;

    ++tam_;

    //
    assert(size() == old_size + 1);
    assert(get(0) == new_it);
    assert(old_is_empty || (get(1) == old_front));
}

template <class T>
void CDArray<T>::push_back(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
    bool old_is_empty = is_empty();
    T old_back = is_empty() ? T() : get(size() - 1);
#endif
    // TODO

    if (is_empty()){
        front_ = 0;
        back_ = 0;
    }else{
        if (is_full()){
            grow();
        }

        back_ = cInc(back_, cap_);
    }

    data_.get()[back_] = new_it;

    ++tam_;

    //
    assert(size() == old_size + 1);
    assert(get(size() - 1) == new_it);
    assert(old_is_empty || (get(size() - 2) == old_back));
}

template <class T>
void CDArray<T>::pop_front()
{
#ifndef NDEBUG
    size_t old_size = size();
    T old_next_front = size() > 1 ? get(1) : T();
#endif
    // TODO

    front_ = cInc(front_, cap_);
    --tam_;

    //
    assert(size() == old_size - 1);
    assert(is_empty() || get(0) == old_next_front);
}

template <class T>
void CDArray<T>::pop_back()
{
#ifndef NDEBUG
    size_t old_size = size();
    T old_prev_back = size() > 1 ? get(size() - 2) : T();
#endif
    // TODO

    back_ = cDec(back_, cap_);
    --tam_;

    //
    assert(size() == old_size - 1);
    assert(is_empty() || get(size() - 1) == old_prev_back);
}

template <class T>
void CDArray<T>::insert(size_t pos, T const &v)
{
    assert(pos >= 0 && pos < size());
#ifndef NDEBUG
    size_t old_size = size();
    T old_back = get(size() - 1);
    T old_pos_v = get(pos);
#endif
    // TODO
    // Hint: if pos==0, delegate in push_front.
    // Remember: back_ needs to be updated too.

    if (pos == 0){
        push_front(v);

    }else{
        if (is_full()){
            grow();
        }

        ++tam_;

        for (int i = tam_ - 2; i >= pos; --i){
            set(i + 1, get(i));
        }

        set(pos, v);

        back_ = cInc(back_, cap_);
    }

    //
    assert(size() == old_size + 1);
    assert(get(pos) == v);
    assert(get(pos + 1) == old_pos_v);
    assert(get(size() - 1) == old_back);
}

template <class T>
void CDArray<T>::remove(size_t pos)
{
    assert(pos >= 0 && pos < size());
#ifndef NDEBUG
    size_t old_size = size();
    T old_next_pos_v = (pos <= (size() - 2)) ? get(pos + 1) : T();
#endif
    // TODO
    // Remember: back_ needs to be updated.

    for (int i=pos; i < tam_; ++i){
        set(i, get(i + 1));
    }

    back_ = cDec(back_, tam_);
    --tam_;

    //
    assert(size() == old_size - 1);
    assert(pos == size() || get(pos) == old_next_pos_v);
}

template <class T>
void CDArray<T>::grow()
{
#ifndef NDEBUG
    size_t old_capacity = capacity();
#endif
    // TODO

    auto tmp = std::shared_ptr<T>(new T[(cap_ * 2)]);
    for (int i = 0; i < tam_; ++i){
        tmp.get()[i] = get(i);
    }
    
    front_ = 0;
    back_ = tam_ - 1;
    data_ = tmp;
    cap_ *= 2;
    
    //
    assert(capacity() == 2 * old_capacity);
}