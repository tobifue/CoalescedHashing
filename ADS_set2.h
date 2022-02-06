#ifndef ADS_SET_H
#define ADS_SET_H

#include <functional>
#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename Key, size_t N = 7>
class ADS_set {
public:
  class Iterator;
  using value_type = Key;
  using key_type = Key;
  using reference = key_type &;
  using const_reference = const key_type &;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;
  using iterator = Iterator;
  using const_iterator = Iterator;
  using key_compare = std::less<key_type>;   // B+-Tree
  using key_equal = std::equal_to<key_type>; // Hashing
  using hasher = std::hash<key_type>;        // Hashing
private:
    struct element {
        key_type key;
        bool free {true};
        struct element *nxt_ptr{nullptr};
    };

    struct rein_nodes {
        key_type val;

    };

    element *table {nullptr};
    size_type table_size{0}, curr_size {0}, temp{table_size}, cellar_size{0}, total_size={0};
    float max_lf {0.7};
    float cellar_fac{0.22};
    size_type h(const key_type &key) const { return hasher{}(key) % table_size;}
    size_type g(const key_type &, size_type pos) const { return (pos + 1) % table_size;}
    void reserve(size_type n);
    void rehash(size_type n);
    element *insert_(const key_type &key);
    element *findo(const key_type &key) const;
    
    

public:
  element *find_(const key_type &key) const;
  ADS_set(){rehash(N);}; // Phase 1
  ADS_set(std::initializer_list<key_type> ilist): ADS_set{} {insert(ilist);}; //Phase 1
  template<typename InputIt> ADS_set(InputIt first, InputIt last): ADS_set{} {insert(first, last);} //Phase 1

  ADS_set(const ADS_set &other): ADS_set{} {
      reserve(other.curr_size);
      for (const auto &k: other){
          insert(k);
      }
  };

  ~ADS_set() {};
  
  ADS_set &operator=(const ADS_set &other){
      if (this == &other) return *this;
      clear();
      reserve(other.curr_size);
      for (const auto &k: other){
          insert(k);
      }
    return *this;
    };

  ADS_set &operator=(std::initializer_list<key_type> ilist){
      
      ADS_set tmp{ilist};
      swap(tmp);
      return *this;
  };

  value_type operator[](size_t pos) const
{
    return table[pos].key;
};
  value_type& operator[](size_t pos)
{
    return table[pos].key;
};


  size_type size() const { return curr_size;} // Phase 1
  bool empty() const { return curr_size == 0;} // Phase 1

  size_type count(const key_type &key) const {if(find_(key)!=nullptr){
      //std::cout<<"schonDRIN"<<std::endl;
      return 1;
  }
  else{
      return 0;
  }
  }
   // TODO
  iterator find(const key_type &key) const {
      if (auto p {find_(key)}) return iterator {p};
      return end();
  };

void clear(){
    for (size_type idx{0}; idx < total_size; ++idx){
        if (table[idx].free == false){
            //table[idx].key = NULL;
            table[idx].free = true;
            table[idx].nxt_ptr = nullptr;
        }
    }
};  

void swap(ADS_set &other){
    using std::swap;
    swap(table,other.table);
    swap(curr_size,other.curr_size);
    swap(cellar_size,other.cellar_size);
    swap(table_size,other.table_size);
    swap(total_size,other.total_size);
};

  void insert(std::initializer_list<key_type> ilist) { 
    for (auto val : ilist) {
      if (!count(val)) {
            reserve(curr_size+1);
            insert_(val);        
        }
    }
}; // Phase 1

  std::pair<iterator,bool> insert(const key_type &key){
      if (auto p {find_(key)}){
          return {iterator{p}, false};
      }
        //reserve(curr_size+1);
        return {iterator{insert_(key)}, true};
  };

  template<typename InputIt> void insert(InputIt first, InputIt last); // Phase 1

  size_type erase(const key_type &key);

/*
  size_type x() const{
        //std::cout<<h(key)<<std::endl;
      element *curr_elem = &table[0];
      element *curr_min;
      element *help1;
      element *small1;
      difference_type out;

      element *smallest1;
      value_type smallest;
      element* idx1;
      value_type small;
      element* idx2;

      for (size_type idx{0}; idx < total_size; ++idx){
        if (table[idx].free == false){

        curr_elem = &table[idx];
        std::cout<<"curr elem"<<(*curr_elem).key<<std::endl;


        if(!curr_min){
            curr_min = &table[idx];
            std::cout<<"test"<<std::endl;
        };

        if (key_compare{}((*curr_elem).key, (*curr_min).key)){
            small1 = smallest1;

            std::cout<<"small: "<<(*curr_elem).key<<std::endl;

            smallest1 = curr_elem;
            curr_min = curr_elem;

            
        }
    }
          help1 = curr_min;

      }

      if ((*small1).key<0){
          std::cout<<"testli"<<std::endl;
        for (size_type idx1{0}; idx1 < total_size; ++idx1){

        if (table[idx1].free == false && table[idx1].key != (*help1).key){
        curr_elem = &table[idx1];

          //std::cout<<"curr_min: "<<(*curr_min).key<<" smallest_key: "<<(*smallest1).key<< std::endl;

        if((*curr_min).key == (*help1).key){
            curr_min = &table[idx1];
            std::cout<<"yeaf"<<table[idx1].key<<std::endl;
        };

        if (key_compare{}((*curr_elem).key, (*curr_min).key)){
                    std::cout<<"small"<<std::endl;

            small1 = curr_min;
            curr_min = curr_elem;
        }

    }
    }
    }
     if (small1){
    out = curr_min-smallest1; 
     }
     else{      
    out = curr_min-help1; 
     }

    std::cout<<"small: "<<(*curr_min).key<<"  smallest: "<< (*smallest1).key<< "diff"<< out<<std::endl;
    return out;
  };
*/


  const_iterator begin() const { return const_iterator{table};} ;
  const_iterator end() const { return const_iterator{table+total_size};} ;

  void dump(std::ostream &o = std::cerr) const; // Phase 1

  friend bool operator==(const ADS_set &lhs, const ADS_set &rhs){
      if (lhs.curr_size != rhs.curr_size){
        return false;
    }

    for (const auto &k: rhs){
        if(!lhs.count(k)){
            return false;
        }
    }

    return true;
  };


  friend bool operator!=(const ADS_set &lhs, const ADS_set &rhs){
          /*if (lhs.curr_size != rhs.curr_size){
        return true;
    }

    for (int i = 0; i < lhs.total_size; ++i){
        if (lhs.table[i].key != rhs.table[i].key){
            return true;
        }
    }

    return false;
  };*/
  if (lhs.curr_size != rhs.curr_size){
        return true;
    }

    for (const auto &k: rhs){
        if(!lhs.count(k)){
            return true;
        }
    }

    return false;
  };
};


template <typename Key, size_t N>
typename ADS_set<Key,N>::element *ADS_set<Key,N>::insert_(const key_type &key){
        size_type idx {h(key)};
        //std::cout<<h(key)<<std::endl;
        element *curr_elem;
        //std::cout<<key<<std::endl;
        //std::cout<<table_size<<"--ts"<<std::endl;
        //std::cout<<idx<<"--idx"<<std::endl;
        element *help;
        help = &table[idx];
        curr_elem = help;


        if (table[idx].free ==false){
            //dont do while if place is free
            //else do as long nxt_ptr exists
            help = &table[idx];
            do {
                if ((*curr_elem).nxt_ptr == nullptr){
                    // Set next_ptr
                    //std::cout<<"hey"<<std::endl;
                    //std::cout<<table(*curr_elem).nxt_ptr;
                    break;
                }
                else{
                    // Move to next_ptr
                    element *help = (*curr_elem).nxt_ptr;
                    //std::cout<<"move on"<<std::endl;
                    curr_elem = help;
                    //std::cout<<"hello"<<std::endl;
                    //std::cout<<help<<std::endl;
                    //std::cout<<curr_elem<<std::endl;
                    //std::cout<<(curr_elem);

                }
            }
            while ((*curr_elem).nxt_ptr != nullptr);

            size_t gh = 1;
            while(table[total_size-gh].free != true){
                gh++;
            }
            //std::cout<<"hi"<<std::endl;
            //std::cout<<(*curr_elem).key<<std::endl;
            table[total_size-gh].key = key;
            //std::cout<<total_size-gh<<"----"<<std::endl;
            table[total_size-gh].free = false;
            (*curr_elem).nxt_ptr = &table[total_size-gh];
            //(*help_var).nxt_ptr = &table[idx];                   
        }

        else {
            table[idx].key = key;
            table[idx].free = false;
            //std::cout<<"moin"<<std::endl;
        }
        
        
    ++curr_size;
    return table+idx; // table ist pointer und index auch
}

template <typename Key, size_t N>
typename ADS_set<Key,N>::element *ADS_set<Key,N>::find_(const key_type &key) const{
    size_type idx {h(key)};
        element *curr_elem = &table[idx];

        if (table[idx].free == true){
            return nullptr;
        }

        else if(key_equal{}(table[idx].key, key)){
            return &table[idx];
        }

        else{
            //dont do while if place is free
            //else do as long nxt_ptr exists
            do {
                //std::cout<<"wasNOTfree "<<key<<"   " <<(*curr_elem).key<< std::endl;
                // DO if nxtptr is free
                if (key_equal{}((*curr_elem).key, key)){
                    //std::cout<<"equal"<<std::endl;
                    return curr_elem;
                }
                else{
                    if((*curr_elem).nxt_ptr != nullptr){
                    element *help = (*curr_elem).nxt_ptr;   
                    //std::cout<<"ifNotFreeGoNext"<<std::endl;     
                    curr_elem = help;
                    }
                }
            }
            while ((*curr_elem).nxt_ptr != nullptr);

            //std::cout<<"hi";
            //std::cout<<"iAMHere"<<std::endl;
            if(key_equal{}((*curr_elem).key, key)){
            return curr_elem;
            }
            else{
                return nullptr;
            }
        }
}


template <typename Key, size_t N>
template<typename InputIt> void ADS_set<Key,N>::insert(InputIt first, InputIt last){
    for (auto it {first};it != last; ++it) {
        if (!count(*it)) {
            reserve(curr_size+1);
            insert_(*it);        
        }
    }
}


template <typename Key, size_t N>
size_t ADS_set<Key,N>::erase(const key_type &key){
    size_type idx {h(key)};
    element *curr_elem = &table[idx];
    size_type success = 1;
    
        size_type nodes_size = 4;
        rein_nodes *nodes {new rein_nodes[nodes_size]};
        size_type helper{0};
        if (table[idx].free == true){
            return 0;
        }

        else if(key_equal{}(table[idx].key, key) && table[idx].nxt_ptr==nullptr){
            success = 1;
        }

        else{
            //dont do while if place is free
            //else do as long nxt_ptr exists
            do {
                //std::cout<<nodes_size<<"---Helper:"<<helper<<std::endl;
                if(helper>nodes_size-1){
                    size_type new_nodes_size = 2 * nodes_size + 1;
                    rein_nodes *old_nodes = nodes;
                    rein_nodes *nodes {new rein_nodes[new_nodes_size]};
                    //std::cout<<"Heureka"<<std::endl;
                    for (size_type i{0}; i < nodes_size; i++){
                        nodes[i]=old_nodes[i];
                    }
                    nodes_size = new_nodes_size;
                }

                // DO if nxtptr is free
                if (key_equal{}((*curr_elem).key, key)){
                    //std::cout<<"test"<<std::endl; 
 
                    //dont write Value to be deltet in Nodes_array!!!!
                    //nodes[helper].val = (*curr_elem).key;
                    //std::cout<<nodes[helper].val<<std::endl;     
                    //helper++;
                    (*curr_elem).free = true;  
                    element *help = (*curr_elem).nxt_ptr; 
                    (*curr_elem).nxt_ptr = nullptr;  
                    curr_elem = help;  
                    success = 1;
                }
                else{
                    if((*curr_elem).nxt_ptr != nullptr){
                    nodes[helper].val = curr_elem->key;
                    //std::cout<<nodes[helper].val<<std::endl;     
                    helper++;
                    (*curr_elem).free = true;  
                    element *help = (*curr_elem).nxt_ptr; 
                    (*curr_elem).nxt_ptr = nullptr;   
                    curr_elem = help;
                    }
                }
            }
            while ((*curr_elem).nxt_ptr != nullptr);

            nodes[helper].val = (*curr_elem).key;
            //std::cout<<nodes[helper].val<<std::endl;  
            //(*curr_elem).key = NULL;
            (*curr_elem).free = true;     

            //Reinsert values (+1 to get all values)
            for (size_type idx{0}; idx < helper + 1; ++idx){
                insert_(nodes[idx].val);
                curr_size--;
            }
            if(key_equal{}(nodes[helper].val, key)){
                success = 1;
            }
        }
        //std::cout<<success<<std::endl;
        curr_size--;
        return success;
}

/*template <typename Key, size_t N>
size_t ADS_set<Key,N>::erase(const key_type &key){
    size_type idx {h(key)}, start_idx{idx};
    element *curr_elem = &table[idx];
    size_type success = 1;
    
        rein_nodes *nodes {new rein_nodes[10]};
        size_type helper{0};
        if (table[idx].free == free::free){
            return 0;
        }

        else if(key_equal{}(table[idx].key, key) && table[idx].nxt_ptr==nullptr){
            success = 1;
        }

        else{
            //dont do while if place is free
            //else do as long nxt_ptr exists
            do {
                // DO if nxtptr is free
                if (key_equal{}((*curr_elem).key, key)){
                    std::cout<<"test"<<std::endl; 
 
                    //nodes[helper].val = (*curr_elem).key;
                    std::cout<<nodes[helper].val<<std::endl;     
                    //helper++;
                    (*curr_elem).key = NULL;
                    (*curr_elem).free = free::free;  
                    element *help = (*curr_elem).nxt_ptr; 
                    (*curr_elem).nxt_ptr = nullptr;  
                    curr_elem = help;  
                    success = 1;
                }
                else{
                    if((*curr_elem).nxt_ptr != nullptr){
                    nodes[helper].val = (*curr_elem).key;
                    std::cout<<nodes[helper].val<<std::endl;     
                    helper++;
                    (*curr_elem).key = NULL;
                    (*curr_elem).free = free::free;  
                    element *help = (*curr_elem).nxt_ptr; 
                    (*curr_elem).nxt_ptr = nullptr;   
                    curr_elem = help;
                    }
                }
            }
            while ((*curr_elem).nxt_ptr != nullptr);

            nodes[helper].val = (*curr_elem).key;
            std::cout<<nodes[helper].val<<std::endl;  
            (*curr_elem).key = NULL;
            (*curr_elem).free = free::free;     


            for (size_type idx{0}; idx < helper; ++idx){
                insert_(nodes[idx].val);
            }
            if(key_equal{}(nodes[helper].val, key)){
                success = 1;
            }
        }
        std::cout<<success<<std::endl;
        return success;
}
*/


template <typename Key, size_t N>
void ADS_set<Key,N>::reserve(size_type n){
    if (n>table_size*max_lf){
        size_type new_table_size = table_size + table_size * cellar_fac;
        do {
            new_table_size = new_table_size * 2 +1;
        } while (n > new_table_size * max_lf);
        rehash(new_table_size);
    }
}


template <typename Key, size_t N>
void ADS_set<Key,N>::rehash(size_type n){
    size_type new_table_size {std::max(N, std::max(n,size_type(curr_size/max_lf)))};
    size_type new_cellar_size = {(size_type(new_table_size * cellar_fac))};
    size_type new_total_size = {new_table_size + new_cellar_size};
    element *new_table {new element[new_total_size]};
    size_type old_table_size {total_size};
    element *old_table{table};
    curr_size =0;
    table = new_table;
    table_size = new_table_size;
    cellar_size = new_cellar_size;
    total_size = new_total_size;
    for (size_type idx{0}; idx < old_table_size; ++idx){
        if (old_table[idx].free == false) insert_(old_table[idx].key);
    }
    delete[] old_table;
}

template <typename Key, size_t N>
void ADS_set<Key,N>::dump(std::ostream &o) const{
    o << "########################################################################"<< "\n";
    o << "No         address         Value          Nxt_Ptr "<< "\n";
    o << "curr_size = " << curr_size << " table_size = " << table_size << " total_size = " << total_size << " cellar_size: " << cellar_size << "\n";
    for (size_type idx{0}; idx < total_size; ++idx){
        if(idx < table_size){
        o << idx << "   ";
        switch (table[idx].free){
            case true:
                o << " ("<<&table[idx]<<") free"<<" | "<<table[idx].nxt_ptr;
                break;
            case false:
                o << " ("<<&table[idx]<< ") " <<table[idx].key<<" | "<<table[idx].nxt_ptr;
                break;
        }
        o << "\n";
        }
        else{
            o << idx << "c ";
            switch (table[idx].free){
           case true:
                o << " ("<<&table[idx]<<") free"<<" | "<<table[idx].nxt_ptr;
                break;
            case false:
                o << " ("<<&table[idx]<< ") " <<table[idx].key<<" | "<<table[idx].nxt_ptr;
                break;
        }
        o << "\n";
}
    }
    o << "########################################################################"<< "\n";

}

template <typename Key, size_t N>
class ADS_set<Key,N>::Iterator {
public:
  using value_type = Key;
  using difference_type = std::ptrdiff_t;
  using reference = const value_type &;
  using pointer = const value_type *;
  using iterator_category = std::forward_iterator_tag;

  //explicit Iterator( implementation-dependent );
  explicit Iterator(element *pos = nullptr): pos{pos} {/*std::cout<<"iterator";*/ if (pos) skip();}
  reference operator*() const { /*std::cout<<"iterator"<<pos->key<<std::endl;*/ return pos->key;};
  pointer operator->() const { /*std::cout<<"iterator";*/ return &pos->key;};
  
  Iterator &operator++(){ /*std::cout<<"&++";*/ ++pos; skip(); return *this;};

  Iterator operator++(int){ /*std::cout<<"++";*/ auto rc {*this}; ++*this; return rc;};
  friend bool operator==(const Iterator &lhs, const Iterator &rhs){return lhs.pos == rhs.pos;};
  friend bool operator!=(const Iterator &lhs, const Iterator &rhs){return !(lhs == rhs);};
private:
    element *pos;
    void skip() { /*std::cout<<"skipaidap";*/ while (pos->free != false) ++pos;}
};

template <typename Key, size_t N> void swap(ADS_set<Key,N> &lhs, ADS_set<Key,N> &rhs) { lhs.swap(rhs); }

#endif // ADS_SET_H