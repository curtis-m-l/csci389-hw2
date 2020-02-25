
#include <iostream>

#include "cache.hh"

/*

*/

class Impl {
public:
  void set(key_type key, val_type val, size_type size);
  val_type get(key_type key, size_type& val_size) const;
  bool del(key_type key);
  size_type space_used() const;
  void reset();
}

void Impl::set (key_type key, val_type val, size_type size) {
 return;
}

val_type Impl::get(key_type key, size_type& val_size) const {
  return;
}

bool Impl::del(key_type key) {
  return;
}

size_type Impl::space_used() const{
  return;
}

void reset(){
  return;
}

Cache::Cache() : pImpl_(new Impl){}

Cache::~Cache() = default;
