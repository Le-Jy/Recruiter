/**
 ** \file misc/singleton.hh
 ** \brief Generic singleton
 */

#pragma once

namespace misc
{
  template <typename T> class Singleton
  {
  public:
    Singleton(const Singleton<T>&) = delete;
    Singleton(Singleton<T>& other) = delete;
    Singleton(Singleton<T>&&) = delete;

    Singleton<T>& operator=(const Singleton<T>&) = delete;
    Singleton<T>& operator=(Singleton<T>& other) = delete;
    Singleton<T>& operator=(Singleton<T>&&) = delete;

    static const T& instance()
    {
      static T instance;
      return instance;
    }

  protected:
    Singleton() = default;
  };
} // namespace misc
