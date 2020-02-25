
#include <iostream>
#include <unordered_map>

#include "cache.hh"

/*

*/

class Impl {
  public:
    //Our data members:
    size_type m_current_mem;
    std::unordered_map<key_type, val_type> m_cache_vals;
    std::unordered_map<key_type, size_type> m_cache_sizes;

    // Initial data members/functions:
    size_type m_maxmem;
    float m_max_load_factor;
    Evictor* m_evictor = nullptr;

    void Impl::set (key_type key, val_type val, size_type size) {
      existing_value = m_cache_vals.find(key);
      if (existing_value != m_cache_vals.end()) {
        size = size - m_cache_sizes.find(key)->second;
      }
      if (m_current_mem + size <= m_maxmem){
        m_cache_vals.emplace(key, val);
        m_cache_sizes.emplace(key, size);
        m_current_mem += size;
      }
      else {
        std::cout<<"CACHE IS TOO FULL!\n";
      }
    }

    val_type Impl::get(key_type key, size_type& val_size) const {
      auto toRe = m_cache_vals.find(key);
      if (toRe == m_cache_vals.end()) {
        return nullptr;
      }
      val_size = m_cache_sizes.find(key)->second;
      return static_cast<val_type>(toRe->second);
    }

    bool Impl::del(key_type key) {
      auto entry = m_cache_vals.find(key);
      if (entry = m_cache_vals.end()) {
        return false;
      }
      else {
        m_cache_vals.erase(key);
        m_cache_sizes.erase(key);
        return true;
      }
    }

    size_type Impl::space_used() const {
      return m_current_mem;
    }

    void reset(){
      m_cache_vals.clear();
      m_cache_sizes.clear();
    }
};

Cache::Cache(size_type maxmem,
             float max_load_factor = 0.75,
             Evictor* evictor = nullptr,
             auto hasher = std::hash<key_type>()) :
      pImpl_(new Impl),
      pImpl_.m_maxmem = maxmem,
      pImpl_.m_max_load_factor = max_load_factor,
      pImpl_.m_evictor = evictor,
      pImpl_.m_hasher = hasher,
      pImpl_.m_current_mem = 0,
      std::unordered_map <key_type, val_type> m_cache_vals(m_hasher),
      std::unordered_map <key_type, size_type> m_cache_sizes()
{}

Cache::~Cache() = default;
