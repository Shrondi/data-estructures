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

#include "vector2d.hpp"

// TODO: implement the interface for the proposed ADT.
template<class T>
Vector2D<T>::Vector2D(T x, T y){
    _x = x;
    _y = y;
}

template<class T> 
typename Vector2D<T>::Ref Vector2D<T>::create()
{
  return std::make_shared<Vector2D<T>> (0, 0);
}

template<class T> 
typename Vector2D<T>::Ref Vector2D<T>::create(T x, T y)
{
  return std::make_shared<Vector2D<T>> (x, y);
}

template<class T>
T Vector2D<T>::x(){
    return _x;
}

template<class T>
T Vector2D<T>::y(){
    return _y;
}

template<class T>
void Vector2D<T>::set_x(T x){
    _x = x;
    assert(_x == x);
}

template<class T>
void Vector2D<T>::set_y(T y){
    _y = y;
}

template <class T>
void Vector2D<T>::add(Ref other){
    _x += other->x();
    _y += other->y();
}
//