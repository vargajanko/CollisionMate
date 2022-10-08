module;

#include <array>
#include <concepts>
#include <iostream>

export module vector;

export namespace math {

  template <typename T>
  concept arithmetic = std::is_arithmetic_v<T>;

  /**
   * Vector represents 3 arithmetic values. Default float type.
   * Data is stored as 3 component array, with x, y ,z as easy access members
   * T: type of the data members. by default float.
   * PRECISION: type of scalar return type of member functions(e.g magnitude())
   */
  template <arithmetic T = float, typename PRECISION = float> class vector3 {

  public:
    vector3() = default;

    vector3(T x_value, T y_value, T z_value) : vec({ x_value, y_value, z_value }) {}
    explicit vector3(const std::array<T, 3>& arr) : vec(arr) {}

    vector3(const vector3&) = default;
    vector3& operator=(const vector3&) = default;

    vector3(vector3&&) noexcept = default;
    vector3& operator=(vector3&&) noexcept = default;
    ~vector3() = default;

    friend constexpr vector3 operator+(const vector3& lhs,
      const vector3& rhs) noexcept {
      return vector3{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
    }

    friend constexpr vector3 operator-(const vector3& lhs,
      const vector3& rhs) noexcept {
      return vector3{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
    }

    friend constexpr vector3 operator/(const vector3& lhs,
      const vector3& rhs) noexcept {
      return vector3{ lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z };
    }

    friend constexpr vector3 operator*(const vector3& lhs,
      const vector3& rhs) noexcept {
      return vector3{ lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
    }

    friend constexpr bool operator==(const vector3& lhs,
      const vector3& rhs) noexcept {
      return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
    }

    friend std::ostream& operator<<(std::ostream& out_stream,
      const vector3& value) {
      out_stream << "[" << value.x << ", " << value.y << ", " << value.z << "]";
      return out_stream;
    }

    [[nodiscard]] constexpr PRECISION magnitude() const noexcept {
      return static_cast<PRECISION>(std::sqrt(x * x + y * y + z * z));
    }

    /**
     * Cross product: this x rhs
     */
    [[nodiscard]] constexpr vector3 cross(const vector3& rhs) const noexcept {
      T tmp_x{ y * rhs.z - rhs.y * z };
      T tmp_y{ z * rhs.x - rhs.z * x };
      T tmp_z{ x * rhs.y - rhs.x * y };
      return vector3{ tmp_x, tmp_y, tmp_z };
    }

    /**
     * Dot prdouct.
     */
    [[nodiscard]] constexpr PRECISION dot(const vector3& rhs) const noexcept {
      T tmp_x{ x * rhs.x };
      T tmp_y{ y * rhs.y };
      T tmp_z{ z * rhs.z };
      return static_cast<PRECISION>(tmp_x + tmp_y + tmp_z);
    }

    std::array<T, 3> vec{};
    T& x{ vec[0] };
    T& y{ vec[1] };
    T& z{ vec[2] };
  };
} // namespace math
