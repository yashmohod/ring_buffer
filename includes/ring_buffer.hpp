#include <iostream>
#include <type_traits> 

template <typename T, size_t N>
class RingBuffer{

  public:

    void push(T value){
      data_[(head_ + size_) % N] = value;
      if (size_ < N) size_++;
      else head_ = (head_ +1) % N;
    }

    size_t size() const{
      return size_; 
    }

    bool full() const{
      return N == size_;
    }

    T operator[](size_t i)const{
      return data_[(head_ + i) % N];
    }

    double mean() const{
      static_assert(std::is_arithmetic<T>::value, "mean() requires numeric type");
      double mean = 0;
      for(size_t i=0; i < size_; i++)
        mean+=(*this)[i];
      return (size()>0) ? mean/size() : 0;
    }

  private:
    T data_[N];
    size_t head_ = 0;
    size_t size_ = 0;

};








