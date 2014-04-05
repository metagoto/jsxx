#pragma once

#include <jsxx/core/prologue.hpp>


namespace jsxx
{
  namespace internal
  {
    template<typename T>
    constexpr int digits_count10(T n) {
      return n == 0 ? 0 : 1 + digits_count10(n/10);
    }
    template<typename T> // 12345[6]
    constexpr T right_digit10(T n) {
      return n % 10;
    }
    template<typename T> // [12345]6
    constexpr T left_digits10(T n) {
      return n / 10;
    }

    inline double pow10(std::size_t i) noexcept {
      static constexpr double const t[309] = { 0.0,
        1.0E+001, 1.0E+002, 1.0E+003, 1.0E+004, 1.0E+005, 1.0E+006, 1.0E+007, 1.0E+008, 1.0E+009, 1.0E+010,
        1.0E+011, 1.0E+012, 1.0E+013, 1.0E+014, 1.0E+015, 1.0E+016, 1.0E+017, 1.0E+018, 1.0E+019, 1.0E+020,
        1.0E+021, 1.0E+022, 1.0E+023, 1.0E+024, 1.0E+025, 1.0E+026, 1.0E+027, 1.0E+028, 1.0E+029, 1.0E+030,
        1.0E+031, 1.0E+032, 1.0E+033, 1.0E+034, 1.0E+035, 1.0E+036, 1.0E+037, 1.0E+038, 1.0E+039, 1.0E+040,
        1.0E+041, 1.0E+042, 1.0E+043, 1.0E+044, 1.0E+045, 1.0E+046, 1.0E+047, 1.0E+048, 1.0E+049, 1.0E+050,
        1.0E+051, 1.0E+052, 1.0E+053, 1.0E+054, 1.0E+055, 1.0E+056, 1.0E+057, 1.0E+058, 1.0E+059, 1.0E+060,
        1.0E+061, 1.0E+062, 1.0E+063, 1.0E+064, 1.0E+065, 1.0E+066, 1.0E+067, 1.0E+068, 1.0E+069, 1.0E+070,
        1.0E+071, 1.0E+072, 1.0E+073, 1.0E+074, 1.0E+075, 1.0E+076, 1.0E+077, 1.0E+078, 1.0E+079, 1.0E+080,
        1.0E+081, 1.0E+082, 1.0E+083, 1.0E+084, 1.0E+085, 1.0E+086, 1.0E+087, 1.0E+088, 1.0E+089, 1.0E+090,
        1.0E+091, 1.0E+092, 1.0E+093, 1.0E+094, 1.0E+095, 1.0E+096, 1.0E+097, 1.0E+098, 1.0E+099, 1.0E+100,
        1.0E+101, 1.0E+102, 1.0E+103, 1.0E+104, 1.0E+105, 1.0E+106, 1.0E+107, 1.0E+108, 1.0E+109, 1.0E+110,
        1.0E+111, 1.0E+112, 1.0E+113, 1.0E+114, 1.0E+115, 1.0E+116, 1.0E+117, 1.0E+118, 1.0E+119, 1.0E+120,
        1.0E+121, 1.0E+122, 1.0E+123, 1.0E+124, 1.0E+125, 1.0E+126, 1.0E+127, 1.0E+128, 1.0E+129, 1.0E+130,
        1.0E+131, 1.0E+132, 1.0E+133, 1.0E+134, 1.0E+135, 1.0E+136, 1.0E+137, 1.0E+138, 1.0E+139, 1.0E+140,
        1.0E+141, 1.0E+142, 1.0E+143, 1.0E+144, 1.0E+145, 1.0E+146, 1.0E+147, 1.0E+148, 1.0E+149, 1.0E+150,
        1.0E+151, 1.0E+152, 1.0E+153, 1.0E+154, 1.0E+155, 1.0E+156, 1.0E+157, 1.0E+158, 1.0E+159, 1.0E+160,
        1.0E+161, 1.0E+162, 1.0E+163, 1.0E+164, 1.0E+165, 1.0E+166, 1.0E+167, 1.0E+168, 1.0E+169, 1.0E+170,
        1.0E+171, 1.0E+172, 1.0E+173, 1.0E+174, 1.0E+175, 1.0E+176, 1.0E+177, 1.0E+178, 1.0E+179, 1.0E+180,
        1.0E+181, 1.0E+182, 1.0E+183, 1.0E+184, 1.0E+185, 1.0E+186, 1.0E+187, 1.0E+188, 1.0E+189, 1.0E+190,
        1.0E+191, 1.0E+192, 1.0E+193, 1.0E+194, 1.0E+195, 1.0E+196, 1.0E+197, 1.0E+198, 1.0E+199, 1.0E+200,
        1.0E+201, 1.0E+202, 1.0E+203, 1.0E+204, 1.0E+205, 1.0E+206, 1.0E+207, 1.0E+208, 1.0E+209, 1.0E+210,
        1.0E+211, 1.0E+212, 1.0E+213, 1.0E+214, 1.0E+215, 1.0E+216, 1.0E+217, 1.0E+218, 1.0E+219, 1.0E+220,
        1.0E+221, 1.0E+222, 1.0E+223, 1.0E+224, 1.0E+225, 1.0E+226, 1.0E+227, 1.0E+228, 1.0E+229, 1.0E+230,
        1.0E+231, 1.0E+232, 1.0E+233, 1.0E+234, 1.0E+235, 1.0E+236, 1.0E+237, 1.0E+238, 1.0E+239, 1.0E+240,
        1.0E+241, 1.0E+242, 1.0E+243, 1.0E+244, 1.0E+245, 1.0E+246, 1.0E+247, 1.0E+248, 1.0E+249, 1.0E+250,
        1.0E+251, 1.0E+252, 1.0E+253, 1.0E+254, 1.0E+255, 1.0E+256, 1.0E+257, 1.0E+258, 1.0E+259, 1.0E+260,
        1.0E+261, 1.0E+262, 1.0E+263, 1.0E+264, 1.0E+265, 1.0E+266, 1.0E+267, 1.0E+268, 1.0E+269, 1.0E+270,
        1.0E+271, 1.0E+272, 1.0E+273, 1.0E+274, 1.0E+275, 1.0E+276, 1.0E+277, 1.0E+278, 1.0E+279, 1.0E+280,
        1.0E+281, 1.0E+282, 1.0E+283, 1.0E+284, 1.0E+285, 1.0E+286, 1.0E+287, 1.0E+288, 1.0E+289, 1.0E+290,
        1.0E+291, 1.0E+292, 1.0E+293, 1.0E+294, 1.0E+295, 1.0E+296, 1.0E+297, 1.0E+298, 1.0E+299, 1.0E+300,
        1.0E+301, 1.0E+302, 1.0E+303, 1.0E+304, 1.0E+305, 1.0E+306, 1.0E+307, 1.0E+308
      };
      if (i && i < (sizeof(t)/sizeof(double)))
        return t[i];
      return 0.0;
    }

    template<typename T>
    inline int hex(T c) noexcept {
      #define JSXX_Z16 -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
      static constexpr int const t[256] = {
        JSXX_Z16,JSXX_Z16,JSXX_Z16,
        0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,-1,-1,-1,-1,-1,-1,
        -1,0xa,0xb,0xc,0xd,0xe,0xf,-1,-1,-1,-1,-1,-1,-1,-1,-1,JSXX_Z16,
        -1,0xa,0xb,0xc,0xd,0xe,0xf,-1,-1,-1,-1,-1,-1,-1,-1,-1,JSXX_Z16,
        JSXX_Z16,JSXX_Z16,JSXX_Z16,JSXX_Z16,JSXX_Z16,JSXX_Z16,JSXX_Z16,JSXX_Z16
      };
      #undef JSXX_Z16
      if ((unsigned)c < (sizeof(t)/sizeof(int)))
        return t[(unsigned)c];
      return -1;
    }

    template<typename T>
    inline unsigned int esc(T c) noexcept {
      #define JSXX_Z16 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
      static constexpr char const t[256] = {
        JSXX_Z16,JSXX_Z16,0,0,'\"',0,0,0,0,0,0,0,0,0,0,0,0,'/',
        JSXX_Z16,JSXX_Z16,0,0,0,0,0,0,0,0,0,0,0,0,'\\',0,0,0,
        0,0,'\b',0,0,0,'\f',0,0,0,0,0,0,0,'\n',0,
        0,0,'\r',0,'\t',0,0,0,0,0,0,0,0,0,0,0,
        JSXX_Z16,JSXX_Z16,JSXX_Z16,JSXX_Z16,JSXX_Z16,JSXX_Z16,JSXX_Z16,JSXX_Z16
      };
      #undef JSXX_Z16
      if ((unsigned)c < (sizeof(t)/sizeof(char)))
        return t[(unsigned)c];
      return 0;
    }
  }

  // this routine assumes a valid JSON integer encoded in str[it,end)
  template <typename T, typename It>
  inline int string_to_integer(It it, It const end, T& result) noexcept
  {
    T t = 0;
    bool negative = false;
    if (*it == '-') {
      ++it;
      negative = true;
      if (std::is_unsigned<T>::value)
        return -1;
    }
    if (*it == '0') {
      result = t;
      return 0;
    }
    constexpr auto const d10 = std::numeric_limits<T>::digits10;
    if (std::distance(it, end) > (d10+1))
      return -1;
    int i = 0;
    while (i < d10) {
      t = t * 10 + (*it - '0'); // we have at least one non-zero digit
      if (++it == end)
        break;
      ++i;
    }
    if (it != end) { // last digit
      i = *it - '0';
      if (negative) {
        constexpr auto const n10 = -internal::left_digits10(std::numeric_limits<T>::min());
        constexpr auto const l10 = -internal::right_digit10(std::numeric_limits<T>::min());
        if (t >= n10)
          if (t != n10 || i > l10)
            return -1;
      }
      else {
        constexpr auto const n10 = internal::left_digits10(std::numeric_limits<T>::max());
        constexpr auto const l10 = internal::right_digit10(std::numeric_limits<T>::max());
        if (t >= n10)
          if (t != n10 || i > l10)
            return -1;
      }
      t = t * 10 + i;
    }
    result = negative ? -t : t;
    return 0;
  }


  // this routine assumes a valid JSON real number encoded in str[it,end)
  template <typename T, typename It>
  inline int string_to_real(It it, It const end, T& result) noexcept
  {
    T t = 0;
    bool negative = false;
    if (*it == '-') {
      ++it;
      negative = true;
    }
    if (*it == '0')
      ++it;
    if (it == end) {
      result = t;
      return 0;
    }
    if (*it != '.') {
      constexpr auto const e10 = std::numeric_limits<T>::max_exponent10;
      int i = 0, k = 0;
      while (i <= e10) {
        k = *it - '0';
        if (0 <= k && k <= 9)
          t = t * 10 + k;
        else
          break;
        ++i;
        if (++it == end)
          break;
      }
      if (i > e10)
        return -1;
    }
    int exp = 0, expo = 0;
    if (it != end) {
      if (*it == '.') {
        constexpr auto const d10 = -std::numeric_limits<T>::max_digits10; // minus
        int k = 0;
        while (++it != end) {
          k = *it - '0';
          if (0 <= k && k <= 9) {
            if (exp > d10) {
              t = t * 10 + k;
              --exp;
            }
          }
          else
            break;
        }
      }
      if (it != end) {
        if (*it == 'e' || *it == 'E') {
          ++it;
          bool neg = false;
          if (*it == '-') {
            ++it;
            neg = true;
          }
          else if (*it == '+')
            ++it;
          while (it != end && *it == '0') ++it;
          if (it != end) {
            auto const x10 = neg ? -std::numeric_limits<T>::min_exponent10
                                 :  std::numeric_limits<T>::max_exponent10;
            while (expo <= x10) {
              expo = expo * 10 + (*it - '0'); // grammar ensures at least one digit
              if (++it == end)
                break;
            }
            if (expo > x10)
              return -1;
            if (neg)
              expo = -expo;
          }
        }
      }
    }
    expo += exp;
    if (expo != 0) {
      std::size_t const e = std::abs(expo);
      auto const x = internal::pow10(e);
      if (x != 0.0) {
        if (expo > 0) t *= x;
        else t /= x;
      }
      else
        t *= std::pow(T(10), expo);
    }
    result = negative ? -t : t;
    return 0;
  }


  template<typename T, typename It>
  inline int decode_string(It i, It const end, T& result)
  {
    result.reserve(end - i);
    std::back_insert_iterator<T> o = std::back_inserter(result);
    while (i != end)
    {
      auto c = *i++;
      if (c == '\\') {
        c = *i++;
        auto const e = internal::esc(c);
        if (e)
          *o++ = e;
        else if (c == 'u') {

          #define JSXX_P4(CP) e = internal::hex(*i++); if (e < 0) return -1; CP <<= 4; CP += e;

          if (std::distance(i, end) < 4)
            return -1;
          std::uint16_t cp = 0;
          decltype(internal::hex(*i)) e = 0;
          JSXX_P4(cp); JSXX_P4(cp); JSXX_P4(cp); JSXX_P4(cp);

          if (cp < 0x80)
            *o++ = cp;
          else if (cp < 0x800) {
            *o++ = 0xc0 | ((cp >> 6) & 0x1f);
            *o++ = 0x80 | (cp & 0x3f);
          }
          else if (cp < 0xd800 || cp >= 0xe000) {
            *o++ = 0xe0 | ((cp >> 12) & 0x0f);
            *o++ = 0x80 | ((cp >> 6) & 0x3f);
            *o++ = 0x80 | (cp & 0x3f);
          }
          else if (cp < 0xdc00) {
            if (i == end || *i != '\\' || ++i == end || *i != 'u')
              return -1;
            if (std::distance(++i, end) < 4)
              return -1;
            std::uint16_t cp2 = 0;
            JSXX_P4(cp2); JSXX_P4(cp2); JSXX_P4(cp2); JSXX_P4(cp2);

          #undef JSXX_P4

            if (cp2 < 0xdc00 || cp2 >= 0xe000)
              return -1;
            std::uint32_t r = (((cp & 0x3ff) << 10) | (cp2 & 0x3ff)) + 0x10000;
            *o++ = 0xf0 | ((r >> 18) & 0x07);
            *o++ = 0x80 | ((r >> 12) & 0x3f);
            *o++ = 0x80 | ((r >> 6) & 0x3f);
            *o++ = 0x80 | (r & 0x3f);
          }
          else
            return -1;
        }
        else
          return -1;
      }
      else if ((unsigned)c < 0x20)
        return -1;
      else
        *o++ = c;
    }
    return 0;
  }

}
