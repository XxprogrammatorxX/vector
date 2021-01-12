#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <memory>

typedef unsigned long long stype;


template<typename T, typename A>
struct Vector_base {
	stype sz;
	stype space;
	A alloc;
	T* elem;
	void base_swap(Vector_base& a);

	Vector_base(Vector_base&& a) : sz { a.sz }, space { a.space }, elem { a.elem }, alloc { std::move(a.alloc) } {
		a.elem = nullptr;
		a.space = 0;
		a.sz = 0;
	}

	Vector_base& operator= (Vector_base&& a) {
		if (this == &a) return *this;

		sz = a.sz;
		space = a.space;
		elem = a.elem;
		alloc = std::move(a.alloc);
		a.elem = nullptr;
		a.space = 0;
		a.sz = 0;
		return *this;
	} 

	Vector_base(A a, stype n) 
		: alloc { a }, sz { n }, elem { a.allocate(n) }, space { n } { }
	~Vector_base() { alloc.deallocate(elem, space);	}	
};

template<typename T, typename A = std::allocator<T>>
class Vector : private Vector_base<T, A> {
public:
	Vector(A allc = A()) : Vector_base<T, A> (allc, 0) { }
	explicit Vector(stype s, T val = T(), A allc = A());
	Vector(std::initializer_list<T> lst, A allc = A());
	Vector(const Vector<T, A>& arg);
	Vector(Vector<T, A>&& a);// = default;

	~Vector() {
		for (stype i = 0; i < this->sz; i++)
			this->alloc.destroy(&this->elem[i]);
	}

	Vector& operator= (const Vector& a);
	Vector& operator= (Vector&& a);// = default;
	
	T& operator[] (stype n) { return this->elem[n]; }
	const T& operator[] (stype n) const { return this->elem[n]; }
	
	T& at(stype n);
	const T& at(stype n) const;

	T* begin() { return &this->elem[0]; }
    const T* begin() const { return &this->elem[0]; }
    T* end() { return &this->elem[this->sz]; }
    const T* end() const { return &this->elem[this->sz]; }


	stype size() const { return this->sz; } 
	stype capacity() const { return this->space; };
	void reserve(stype newalloc);
	void resize(stype newsize, T val = T());
	void push_back(const T& val);
};

struct out_of_range {};


template<typename T, typename A>
Vector<T, A>::Vector(stype s, T val, A allc) 
	: Vector_base<T, A> (allc, s) {
		for (stype i = 0; i < this->sz; i++)
        	this->alloc.construct(&this->elem[i], val);
}

template<typename T, typename A>
Vector<T, A>::Vector(std::initializer_list<T> lst, A allc) 
	: Vector_base<T, A> (allc, lst.size()) {
		for (stype i = 0; i < this->sz; i++)
        	this->alloc.construct(&this->elem[i], *(lst.begin() + i));
}

template<typename T, typename A>
Vector<T, A>::Vector(const Vector<T, A>& arg) 
	: Vector_base<T, A> (arg.alloc, arg.sz) {
		for (stype i = 0; i < this->sz; i++)
			this->alloc.construct(&this->elem[i], arg[i]);
}

template<typename T, typename A>
Vector<T, A>::Vector(Vector<T, A>&& a) 
	: Vector_base<T, A> (a) { }

template<typename T, typename A>
Vector<T, A>& Vector<T, A>::operator= (const Vector<T, A>& a){
	if (this == &a) return *this;
		
	Vector_base<T, A> b (this->alloc, a.sz);
	std::uninitialized_copy(a.begin(), a.end(), b.elem);
	this->base_swap(b);
	for(stype i = 0; i < b.sz; i++)
        b.alloc.destroy(b.elem + i);
	return *this;
}

template<typename T, typename A>
Vector<T, A>& Vector<T, A>::operator= (Vector&& a){
	this->base_swap(a);
	return *this;
}

template<typename T, typename A>
void Vector<T, A>::reserve(stype newalloc){
	if ( newalloc <= this->space ) return; 

	Vector_base<T, A> b (this->alloc, newalloc);
	std::uninitialized_copy(this->begin(), this->end(), b.elem);
	//std::cerr << this->sz << std::endl;

	for (stype i = 0; i < this->sz; i++)
		this->alloc.destroy(&this->elem[i]);

	b.sz = this->sz;
	//this->base_swap(b);
	//std::swap<Vector_base<T, A>> (*this, b); 
}


template<typename T, typename A>
void Vector<T, A>::resize(stype newsize, T val){
	reserve(newsize);
	for (stype i = this->sz ; i < newsize ; i++)
		this->alloc.construct(&(this->elem[i]), val);
	for (stype i = newsize; i < this->sz; i++)
		this->alloc.destroy(&(this->elem[i]));
	this->sz = newsize;
}

template<typename T, typename A>
void Vector<T, A>::push_back(const T& val){
	if (this->space == 0)
		reserve(8);
	else if (this->sz == this->space)
		reserve(2*(this->space));
	this->alloc.construct(&(this->elem[this->sz]), val);
	this->sz++;
}

template<typename T, typename A>
T& Vector<T, A>::at(stype n){
	if (n < 0 || this->sz <= n) throw out_of_range();
	return this->elem[n];
}

template<typename T, typename A>
const T& Vector<T, A>::at(stype n) const{
	if (n < 0 || this->sz <= n) throw out_of_range();
	return this->elem[n];
}
 

template<typename T>
void Ha_ekpaH(T& v, stype start = 0) {
	std::cout << ".....\n";
	std::cout << "size = " << v.size() << '\n';
    for (stype i = start; i < v.size(); i++){
    	std::cout  << v[i] << '\n';
    }
    std::cout << ".....\n";
}

template<typename T, typename A>
void Vector_base<T,A>::base_swap(Vector_base& v) {
    std::swap (this->elem, v.elem);
    std::swap (this->sz, v.sz);
    std::swap (this->space, v.space);
}
#endif // VECTOR_H