/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once
#include <cassert>
#include "stack.hpp"

template <class T>
Stack<T>::Stack()
{
    // TODO
    l_ = List<T>::create();
    //
    assert(is_empty());
}

template <class T>
typename Stack<T>::Ref Stack<T>::create()
{
    return std::make_shared<Stack<T>>();
}

template <class T>
typename Stack<T>::Ref Stack<T>::create(std::istream &in) noexcept(false)
{
    auto stack = Stack<T>::create();
    // TODO
    // Hint: unfold the list used as implementation.

    std::string token;
    in >> token;

    T item; // Item to save in the stack

    // If the stack is not empty ...
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

            // Save the item in the stack
            stack->push(item);
        }

        // Check the format
        if (token != "]"){
            throw std::runtime_error("Wrong input format.");
        }
    }
    //
    return stack;
}

template <class T>
bool Stack<T>::is_empty() const
{
    bool ret_val = true;
    // TODO
    ret_val = l_.get()->is_empty();
    //
    return ret_val;
}

template <class T>
size_t Stack<T>::size() const
{
    size_t ret_val = 0;
    // TODO
    ret_val = l_.get()->size();
    //
    return ret_val;
}

template <class T>
T Stack<T>::top() const
{
    assert(!is_empty());
    T it;
    // TODO
    it = l_.get()->front();
    //
    return it;
}

template <class T>
void Stack<T>::fold(std::ostream &out) const
{
    // TODO
    // Hint: fold the list used as implementation.
    l_.get()->fold(out);
    //
}
template <class T>
void Stack<T>::push(const T &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    l_.get()->push_front(new_it);
    //
    assert(top() == new_it);
    assert(size() == (old_size + 1));
}

template <class T>
void Stack<T>::pop()
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    assert(!is_empty());
    // TODO
    l_.get()->pop_front();
    //
    assert(size() == (old_size - 1));
}
