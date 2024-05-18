/**
 * @file hash_table_entry_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once

#include <cassert>
#include "hash_table_entry.hpp"

template <class K, class V>
HashTableEntry<K, V>::HashTableEntry()
{
    // TODO
    _state = EntryState::EMPTY;
    //
    assert(is_empty());
}

template <class K, class V>
HashTableEntry<K, V>::HashTableEntry(const K &k, const V &v)
{
    // TODO
    _data.first = k;
    _data.second = v;
    _state = EntryState::VALID;
    //
    assert(is_valid());
    assert(key() == k);
    assert(value() == v);
}

template <class K, class V>
bool HashTableEntry<K, V>::is_valid() const
{
    bool ret_val = false;
    // TODO
    ret_val = _state == EntryState::VALID;
    //
    return ret_val;
}

template <class K, class V>
bool HashTableEntry<K, V>::is_empty() const
{
    bool ret_val = false;
    // TODO
    ret_val = _state == EntryState::EMPTY;
    //
    return ret_val;
}

template <class K, class V>
bool HashTableEntry<K, V>::is_deleted() const
{
    bool ret_val = false;
    // TODO
    ret_val = _state == EntryState::DELETED;
    //
    return ret_val;
}

template <class K, class V>
K const &
HashTableEntry<K, V>::key() const
{
    assert(!is_empty());
    // TODO: recode according to your representation.
    //K aux = _data.first; // No se puede hacer hacer asi ya que devuelve de tipo const
    // return aux

    return _data.first;
    //
}

template <class K, class V>
void HashTableEntry<K, V>::set(const K &k, const V &v)
{
    // TODO
    _data.first = k;
    _data.second = v;
    _state = EntryState::VALID;
    //
    assert(is_valid());
    assert(key() == k);
    assert(value() == v);
}

template <class K, class V>
V const &HashTableEntry<K, V>::value() const
{
    // TODO: recode according to your representation.
    //V aux = _data.second; 
    //return aux;

    return _data.second;
    //
}

template <class K, class V>
V &HashTableEntry<K, V>::value()
{
    assert(is_valid());

    // TODO: recode according to your representation.
    //V aux = _data.second;
    // return aux

    return _data.second;
    //
}

template <class K, class V>
void HashTableEntry<K, V>::set_deleted()
{
    assert(is_valid());
    // TODO
    _state = EntryState::DELETED;
    //
    assert(is_deleted());
}
