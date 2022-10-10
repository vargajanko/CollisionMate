module;

#include <concepts>
#include <vector>

export module gjk;
export import vector;
import <iostream>;
export namespace colliders {



} // namespace colliders

export namespace gjk {

  class box {
  public:
    static math::vector3<> support(const math::vector3<>& direction) {

      math::vector3<> result;
      result.x = (direction.x > 0) ? 2.5f : -2.5f;
      result.y = (direction.y > 0) ? 2.5f : -2.5f;
      result.z = (direction.z > 0) ? 2.5f : -2.5f;
      return result;
    }
  };

  class collider {
  public:
    math::vector3<> world_position{};
  };

  bool doCollide(const collider& lhs, const collider& rhs) {

    math::vector3<> new_simplex_vertex{};
    math::vector3<> search_direction{ 1.0f, -1.0f,
                                     0.1f }; // random start search direction
    std::vector<math::vector3<float, float>> simplex;
    simplex.reserve(4);

    math::vector3<> first_simplex{
        (box::support(search_direction) + rhs.world_position) +
        (-(box::support(-search_direction) + lhs.world_position)) };
    simplex.push_back(first_simplex);
    std::cout << "First simplex: " << first_simplex << "\n";
    // search for next simplex on minkoskis "diffrents" in the oppisite direction
    search_direction = -first_simplex;
    while (true) {
      math::vector3<> newst_simplex{
          (box::support(search_direction) + rhs.world_position) +
          (-(box::support(-search_direction) + lhs.world_position)) };
          auto dot{ newst_simplex.dot(search_direction) };
      std::cout << simplex.size() + 1 << ". simplex: " << newst_simplex << "\n";
      if (dot < 0.0F) {
        // found simplex is not on the otherside of the origin.
        return false;
      }
      simplex.push_back(newst_simplex);
      if (simplex.size() == 4) {
        // tip of the tetrahedral
        const math::vector3<>& tip{ simplex[3] };
        // base of the tetrahedral
        const math::vector3<>& a = simplex[2], b = simplex[1], c = simplex[0];
        // normal of the 3 new created faces.
        math::vector3<> tipab{ (a-tip).cross(b-tip) };
        math::vector3<> tipbc{ (b-tip).cross(c-tip) };
        math::vector3<> tipca{ (c-tip).cross(a-tip) };

        math::vector3<> tip0{ -tip };

        if (tipab.dot(tip0) > 0.0f) {
          // origin is in front of tipab
          search_direction = tipab;
          simplex[0] = simplex[3];
          simplex.pop_back();
          continue;
        }
        if (tipbc.dot(tip0) > 0.0f) {
          // origin is in front of tipbc
          search_direction = tipbc;
          simplex[2] = simplex[3];
          simplex.pop_back();
          continue;
        }
        if (tipca.dot(tip0) > 0.0f) {
          // origin is in front of tipca
          search_direction = tipca;
          simplex[1] = simplex[3];
          simplex.pop_back();
          continue;
        }
        // enclosed the origin.
        return true;

      }
      else if (simplex.size() == 2) {
        const math::vector3<>& a{ simplex[1] };
        const math::vector3<>& b{ simplex[0] };
        math::vector3<> ab{ b - a };
        math::vector3<> a0{ -a };

        math::vector3 abxa{ ab.cross(a0) };
        search_direction = math::vector3<>{ abxa.cross(ab) };
        std::cout << "search for face at: " << search_direction << "\n";
      }
      else {
        const math::vector3<>& a = simplex[2], b = simplex[1], c = simplex[0];
        math::vector3<> ac{ c - a };
        math::vector3<> ab{ b - a };
        // triangle normal
        math::vector3<> normal{ ac.cross(ab) };
        // a0. a to the origin
        math::vector3<> a0{ -a };

        math::vector3<float, float> acxnormal{ ac.cross(normal) };
        if (acxnormal.dot(a0) > 0.0F) {
          // close to edge ac
          math::vector3 acxa0{ ac.cross(a0) };
          search_direction = acxa0.cross(ac);
          // delete simplex b cause its not helpful to enclose the origin
          simplex[1] = simplex[2];
          simplex.pop_back();
          continue;
        }

        math::vector3<> normalxab{ normal.cross(ab) };
        if (normalxab.dot(a0) > 0.0F) {
          // close to edge ab
          math::vector3 abxa0{ ab.cross(a0) };
          search_direction = abxa0.cross(ab);
          // delete simplex c cause its not helpful to enclose the origin
          simplex[0] = simplex[1];
          simplex[1] = simplex[2];
          simplex.pop_back();
          continue;
        }

        if (normal.dot(a0) > 0.0F) {
          // above triangle
          math::vector3 tmp = simplex[2];
          simplex[2] = simplex[1];
          simplex[1] = tmp;
          search_direction = normal;
          continue;
        }

        search_direction = -normal;
      }
    }

    return true;
  }

} // namespace gjk
