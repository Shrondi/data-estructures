/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "pattern.hpp"

Pattern::Pattern(const size_t d, const int cl)
{
    // TODO
    _values = std::make_shared<std::valarray<float>>(d);
    _class_label = cl;
    //
    assert(dim() == d);
    assert(class_label() == cl);
}

Pattern::Pattern(const float values[], const size_t size, const int cl)
{
    assert(size>0);
    // TODO
    _values = std::make_shared<std::valarray<float>>(values, size);
    _class_label = cl;
    //
    assert(dim() == size);
    assert(class_label() == cl);
}

Pattern::Pattern(const std::vector<float>& values, const int cl)
{
    assert(values.size()>0);
    // TODO
    _values = std::make_shared<std::valarray<float>>(values.data(), values.size());
    _class_label = cl;
    //
    assert(dim() == values.size());
    assert(class_label() == cl);
}

Pattern::Pattern(const std::valarray<float>& values, const int cl)
{
    assert(values.size()>0);
    // TODO
    _values = std::make_shared<std::valarray<float>>(values);
    _class_label = cl;
    //
    assert(dim() == values.size());
    assert(class_label() == cl);
}

std::valarray<float>
Pattern::values () const
{
    std::valarray<float> vs;
    // TODO
    vs = *_values;
    //
    return vs;
}

Pattern Pattern::copy() const
{
    Pattern ret_v;
    // TODO: return a deep copy of this.
    ret_v._class_label = _class_label;
    ret_v._values = std::make_shared<std::valarray<float>>(*_values);
    //
    return ret_v;    
}

Pattern::~Pattern()
{;}

size_t Pattern::dim() const
{
    size_t d = 0;
    // TODO
    d = _values->size();
    //
    return d;
}

bool Pattern::operator==(const Pattern& o)
{
    assert( dim()==o.dim());
    bool ret_val = false;
    // TODO
    //ret_val = class_label() == o.class_label() && (*this - o).abs().sum() == 0.0;
    ret_val = class_label() == o.class_label() && std::abs(values()-o.values()).sum() == 0.0;

    //
    assert(!ret_val || class_label() == o.class_label());
    assert(!ret_val || (*this-o).abs().sum()==0.0);
    return ret_val;    
}

void Pattern::set_dim(size_t new_dim)
{
    // TODO
    _values->resize(new_dim);
    //
    assert(dim()==new_dim);
}

int Pattern::class_label() const
{
    int cl = -1;
    // TODO
    cl = _class_label;
    //
    return cl;
}

float Pattern::operator [](const size_t idx) const
{
    assert(idx < dim());
    float v = 0.0;
    // TODO
    v = (*_values)[idx];
    //
    return v;
}

float Pattern::sum() const
{
    float s = 0.0;
    // TODO
    s = _values->sum();
    //
    return s;
}

float Pattern::max() const
{
    float m = 0.0;
    // TODO
    m = _values->max();
    //
    return m;
}

float Pattern::min() const
{
    float m = 0.0;
    // TODO
    m = _values->min();
    //
    return m;
}

void Pattern::set_class_label(const int new_label)
{
    // TODO
    _class_label = new_label;
    //
    assert (class_label() == new_label);
}

void Pattern::set_value(const size_t idx, const float new_val)
{
    assert(idx < dim());
    // TODO
    (*_values)[idx] = new_val;
    //
    assert((*this)[idx]==new_val);
}

Pattern& Pattern::operator += (const Pattern& o)
{
    assert(o.dim()==dim());
    // TODO
    *_values += o.values();
    //
    return *this;
}

Pattern& Pattern::operator -= (const Pattern& o)
{
    assert(o.dim()==dim());
    // TODO
    *_values -= o.values();
    //
    return *this;
}

Pattern& Pattern::operator *= (const Pattern& o)
{
    assert(o.dim()==dim());
    // TODO
    *_values *= o.values();
    //
    return *this;
}

Pattern& Pattern::operator /= (const Pattern& o)
{
    assert(o.dim()==dim());
    // TODO
    *_values /= o.values();
    //
    return *this;
}

Pattern& Pattern::operator *= (const float c)
{
    // TODO
    *_values *= c;
    //
    return *this;
}

Pattern& Pattern::operator /= (const float c)
{
    // TODO
    *_values /= c;
    //
    return *this;
} 

Pattern& Pattern::abs()
{
    //TODO
    _values = std::make_shared<std::valarray<float>>(std::abs(values()));
    //
    return *this;
}

std::ostream& Pattern::fold(std::ostream& output) const
{
    // TODO
    // Remember: format "[ class_label [ v0 v1 ... vn-1 ] ]"
    output << "[ " << _class_label << " [ ";

    for (auto i : values()){
        output << i << " ";
    }

    output << "] ]";
    //
    return output;
}

std::ostream& operator << (std::ostream& output, const Pattern& p)
{
    // TODO
    // Hint: use p.fold()
    p.fold(output);
    //
    return output;
}


Pattern::Pattern(std::istream &input) noexcept(false)
{
    // TODO
    // Remember: input format is "[ class_label [ <dim_0> <dim_1> ... <dim_size-1> ] ]"

    std::string token;
    int cl;
    float value;
    std::vector<float> values;

    input >> token;
    if (token != "["){
        throw std::runtime_error("wrong input format");
    }

    input >> cl;

    input >> token;
    if (token != "["){
        throw std::runtime_error("wrong input format");
    }

    while (input >> token && token != "]"){
        std::istringstream convert(token);
        convert >> value;
  
        values.push_back(value);
    }

    token.clear();

    input >> token;
    if (token != "]"){
        throw std::runtime_error("wrong input format");
    }

    _values = std::make_shared<std::valarray<float>>(values.data(), values.size());
    _class_label = cl;

    //
}

std::istream &operator>>(std::istream &input, Pattern &p) noexcept(false)
{
    assert(input);
    p = Pattern(input);
    return input;
}

float
distance_L2(const Pattern& a, const Pattern& b)
{
    float dist = 0.0;
    // TODO
    dist = std::sqrt(std::pow((a - b).values(), 2).sum());
    //
    assert(dist >= 0.0);    
    return dist;
}

float
distance_L1(const Pattern& a, const Pattern& b)
{
    float dist = 0.0;
    // TODO
    dist = (a - b).abs().sum();
    //
    assert(dist >= 0.0);    
    return dist;
}


std::istream&
load_dataset(std::istream& input,
                  std::vector<Pattern>& dts) noexcept(false)
{
    // TODO
    // Remember: input format is
    // "<size_t num_patterns> <size_t pattern_dimensions>
    // <p_0>
    // <p_1>
    // ...
    // <p_num_patterns-1>
    // "

    std::string token;
    Pattern p;
    size_t num_patterns, pattern_dimensions;

    input >> token;

    std::istringstream convert(token);
    convert >> num_patterns;

    input >> token;

    std::istringstream convert2(token);
    convert2 >> pattern_dimensions;

    for (size_t i = 0; i < num_patterns; ++i){
        try{
            input >> p;
        }catch (std::runtime_error &e){
            throw std::runtime_error("wrong input format");
        }

        if (p.dim() != pattern_dimensions){
            throw std::runtime_error("wrong input format");
        }

        dts.push_back(p);
    }

    //
    return input;
}
