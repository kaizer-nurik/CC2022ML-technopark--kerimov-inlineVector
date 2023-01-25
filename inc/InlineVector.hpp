#pragma once
#include <exception>
#include <iterator>
#include <memory>

#define _INLINE_VECTOR_RESIZE_POLICY 0.5

template <typename T, size_t N> class InlineVector
{
  static_assert (N > 0, "InlineVector size must be >0!");

public:
  InlineVector ();
  InlineVector (std::initializer_list<T> list);
  InlineVector (InlineVector &_other);
  InlineVector &operator= (InlineVector &other);
  InlineVector (InlineVector &&_other);
  InlineVector &operator= (InlineVector &&other);
  ~InlineVector (){};
  template <typename TT, size_t NN> class _Storage
  {
  public:
    _Storage ()
    {
      const_arr = new TT[NN];
      dym_arr = nullptr;
    };
    _Storage (_Storage &other) = delete;
    _Storage &operator= (_Storage &other) = delete;
    _Storage (_Storage &&other) = delete;
    _Storage &operator= (_Storage &&other) = delete;
    ~_Storage ()
    {
      delete[] const_arr;
      if (dym_arr != nullptr)
        {
          delete[] dym_arr;
        }
    };

    T &
    get (size_t ind) const
    {
      if ((ind >= data_length))
        {
          throw std::out_of_range ("inner storage out of range");
        }
      if (ind < const_size)
        {
          return const_arr[ind];
        }
      return dym_arr[ind - const_size];
    }
    void
    set (size_t ind, TT &&value)
    {
      if ((ind >= data_length))
        {
          throw std::out_of_range ("inner storage out of range");
        }
      if (ind < const_size)
        {
          const_arr[ind] = std::forward<T> (value);
        }
      else
        {
          dym_arr[ind - const_size] = std::forward<T> (value);
        }
    }

    void
    set (size_t ind, TT &value)
    {
      if ((ind >= data_length))
        {
          throw std::out_of_range ("inner storage out of range");
        }
      if (ind < const_size)
        {
          const_arr[ind] = value;
        }
      else
        {
          dym_arr[ind - const_size] = value;
        }
    }
    void
    reset ()
    {
      delete[] const_arr;
      if (dym_arr != nullptr)
        {
          delete[] dym_arr;
        }
      const_arr = new TT[NN];
      dym_arr = nullptr;
      dym_size = 0;
      data_length = 0;
    }
    void
    insert (size_t ind, TT &&value)
    {
      // resize если надо
      if (data_length == const_size + dym_size)
        {
          reserve (dym_size * resize_policy);
        }

      // случай добавления в конец (ind == data_length)
      if (ind == data_length)
        {
          data_length++;
          set (data_length - 1, std::forward<T> (value));
        }
      else
        {
          // перестановка в другом случае
          data_length++;
          for (size_t i = (data_length - 2); i >= ind; i--)
            {
              set (i + 1, get (i));
            }
          set (ind, std::forward<T> (value));
        }
    }

    void
    insert (size_t ind, TT &value)
    {
      // resize если надо
      if (data_length == const_size + dym_size)
        {
          reserve (dym_size * resize_policy);
        }

      // случай добавления в конец (ind == data_length)
      if (ind == data_length)
        {
          data_length++;
          set (data_length - 1, value);
        }
      else
        {
          // перестановка в другом случае
          data_length++;
          for (size_t i = (data_length - 1); i >= ind; i--)
            {
              set (i + 1, get (i));
            }
          set (ind, value);
        }
    }

    void
    del (size_t ind)
    { // TODO: очень плохо плохо
      if (ind == (data_length - 1))
        {
          data_length--;
        }
      else
        {
          // перестановка в другом случае
          for (size_t i = ind; i < data_length - 2; i++)
            {
              set (i, get (i + 1));
            }
          data_length--;
        }
    }

    void
    reserve (size_t size)
    {
      if (dym_arr != nullptr)
        {
          TT *new_arr = new TT[dym_size + size];
          for (size_t i = 0; i < (data_length - const_size); i++)
            {
              new_arr[i] = dym_arr[i]; // TODO: страшно и возможно не правильно
            }

          delete[] dym_arr; // TODO: страшно и возможно не правильно
          dym_arr = new_arr;
          dym_size += size;
        }
      else
        {
          dym_arr = new TT[size];
          dym_size = size;
        }
    }
    void
    shrink ()
    {
      if ((const_size + dym_size) > data_length)
        {
          // укоротить динамический массив
          if (data_length > const_size)
            {
              T *new_arr = new TT[data_length - const_size];
              for (size_t i = 0; i < (data_length - const_size); i++)
                {
                  new_arr[i]
                      = dym_arr[i]; // TODO: страшно и возможно не правильно
                }

              delete[] dym_arr; // TODO: страшно и возможно не правильно
              dym_arr = new_arr;
              dym_size = data_length - const_size;
            }
          // удалить динамический.
          else
            {
              delete[] dym_arr;
              dym_size = 0;
            }
        }
    };

    inline size_t
    len () const
    {
      return data_length;
    };
    inline size_t
    len_container () const
    {
      return const_size + dym_size;
    }
    inline size_t
    len_container_const () const
    {
      return const_size;
    }
    inline size_t
    len_container_dym () const
    {
      return dym_size;
    }

  private:
    TT *const_arr;
    TT *dym_arr;
    float resize_policy = _INLINE_VECTOR_RESIZE_POLICY;
    size_t const_size = NN;
    size_t dym_size = 0;
    size_t data_length = 0;
  };

  class Iterator
  {
  public:
    Iterator () : _ptr (-1), _st (nullptr){};
    Iterator (size_t other_ptr, _Storage<T, N> *other_st)
        : _ptr (other_ptr), _st (other_st){};
    Iterator (Iterator &other) : _ptr (other._ptr), _st (other._st) {}
    Iterator (const Iterator &&other) : _ptr (other._ptr), _st (other._st)
    {
      other._ptr = -1;
      other._st = nullptr;
    }
    ~Iterator (){};

    inline Iterator &
    operator= (size_t other_ptr)
    {
      _ptr = other_ptr;
      return *this;
    }
    inline size_t
    pos ()
    {
      return _ptr;
    }
    inline Iterator &
    operator= (const Iterator &other)
    {
      _ptr = other._ptr;
      return *this;
    }
    inline Iterator &
    operator+= (size_t other)
    {
      _ptr += other;
      return *this;
    }
    inline Iterator &
    operator-= (size_t other)
    {
      _ptr -= other;
      return *this;
    }
    inline T &
    operator* () const
    {
      return _st->get (_ptr);
    }
    inline Iterator &
    operator++ ()
    {
      ++_ptr;
      return *this;
    }
    inline Iterator &
    operator-- ()
    {
      --_ptr;
      return *this;
    }
    inline Iterator
    operator++ (int)
    {
      Iterator tmp (*this, _st);
      ++_ptr;
      return tmp;
    }
    inline Iterator
    operator-- (int)
    {
      Iterator tmp (*this, _st);
      --_ptr;
      return tmp;
    }
    inline int
    operator- (const Iterator &other) const
    {
      return _ptr - other.ptr;
    }
    inline Iterator
    operator+ (int other) const
    {
      return Iterator (_ptr + other, _st);
    }
    inline Iterator
    operator- (int other) const
    {
      return Iterator (_ptr - other, _st);
    }
    friend inline Iterator
    operator+ (int lhs, const Iterator &other)
    {
      return Iterator (lhs + other._ptr, other._st);
    }
    friend inline Iterator
    operator- (int lhs, const Iterator &other)
    {
      return Iterator (lhs - other._ptr, other._st);
    }

    inline bool
    operator== (const Iterator &other) const
    {
      return _ptr == other._ptr;
    }
    inline bool
    operator!= (const Iterator &other) const
    {
      return _ptr != other._ptr;
    }
    inline bool
    operator> (const Iterator &other) const
    {
      return _ptr > other._ptr;
    }
    inline bool
    operator<(const Iterator &other) const
    {
      return _ptr < other._ptr;
    }
    inline bool
    operator>= (const Iterator &other) const
    {
      return _ptr >= other._ptr;
    }
    inline bool
    operator<= (const Iterator &other) const
    {
      return _ptr <= other._ptr;
    }

  private:
    size_t _ptr;
    _Storage<T, N> *_st;
  };

  void clear ();

  void reserve (size_t new_size);
  void shrink_to_fit ();

  void erase (Iterator ind);

  void erase (Iterator first, Iterator last);
  void erase (int ind);
  void push_back (T &&_data);
  void push_back (T &_data);

  size_t
  len ()
  {
    return _st.len ();
  }
  void insert (Iterator ind, T &&_data);
  void insert (Iterator ind, T &_data);
  void pop_back ();

  Iterator
  begin ()
  {
    return Iterator (0, &_st);
  }

  Iterator
  end ()
  {
    return Iterator (_st.len (), &_st);
  }

  T &operator[] (int ind);
  T &front ();
  T &back ();

private:
  _Storage<T, N> _st;
};

template <typename T, size_t N> InlineVector<T, N>::InlineVector () {}

template <typename T, size_t N>
InlineVector<T, N>::InlineVector (std::initializer_list<T> list)
{
  for (auto x : list)
    {
      _st.set (_st.len (), x);
    }
}

template <typename T, size_t N>
InlineVector<T, N>::InlineVector (InlineVector &_other)
{
  for (auto x : _other)
    {
      this->push_back (x);
    }
}

template <typename T, size_t N>
InlineVector<T, N> &
InlineVector<T, N>::operator= (InlineVector &other)
{
  for (auto x : other)
    {
      this->push_back (x);
    }
}
template <typename T, size_t N>
InlineVector<T, N> &
InlineVector<T, N>::operator= (InlineVector &&other)
{
  for (auto x : other)
    {
      this->push_back (x);
    }
  other.clear ();
}

template <typename T, size_t N>
void
InlineVector<T, N>::clear ()
{
  _st.reset ();
}

template <typename T, size_t N>
void
InlineVector<T, N>::reserve (size_t new_size)
{
  _st.reserve (new_size);
}

template <typename T, size_t N>
void
InlineVector<T, N>::shrink_to_fit ()
{
  _st.shrink ();
}

template <typename T, size_t N>
void
InlineVector<T, N>::erase (InlineVector<T, N>::Iterator ind)
{
  _st.del (ind.pos ());
}

template <typename T, size_t N>
void
InlineVector<T, N>::erase (
    InlineVector<T, N>::Iterator first,
    InlineVector<T, N>::Iterator last) //!!проверить *iterator != -1
{
  for (Iterator ind = first; ind < last; ind++)
    {
      this->erase (ind);
    }
}

template <typename T, size_t N>
void
InlineVector<T, N>::erase (int ind)
{
  this->erase (Iterator (ind, _st));
}

template <typename T, size_t N>
void
InlineVector<T, N>::push_back (T &&_data)
{
  _st.insert (_st.len (), std::forward<T> (_data));
}
template <typename T, size_t N>
void
InlineVector<T, N>::push_back (T &_data)
{
  _st.insert (_st.len (), _data);
}
template <typename T, size_t N>
void
InlineVector<T, N>::insert (InlineVector<T, N>::Iterator ind, T &&_data)
{
  _st.insert (ind.pos (), std::forward<T> (_data));
}
template <typename T, size_t N>
void
InlineVector<T, N>::insert (InlineVector<T, N>::Iterator ind, T &_data)
{
  _st.insert (ind.pos (), _data);
}
template <typename T, size_t N>
void
InlineVector<T, N>::pop_back ()
{
  _st.del (_st.len () - 1);
}

template <typename T, size_t N>
T &
InlineVector<T, N>::operator[] (int ind)
{
  return _st.get (ind);
}

template <typename T, size_t N>
T &
InlineVector<T, N>::front ()
{
  return _st.get (0); //!!!!!!!
}
template <typename T, size_t N>
T &
InlineVector<T, N>::back ()
{
  return _st.get (_st.len () - 1); // 1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
}
