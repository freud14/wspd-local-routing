#ifndef POINT_WSP_H
#define POINT_WSP_H
#include <CGAL/WSPD.h>
#include <CGAL/enum.h>
#include "WSP_iterator.h"

template <typename Traits>
class Point_wsp
{
public:
  typedef CGAL::WSPD<Traits>                                      WSPD;
  typedef typename WSPD::Well_separated_pair                      Well_separated_pair;
  typedef typename WSPD::Node_const_handle                        Node_const_handle;
  typedef WSP_iterator<Traits>                                    WSP_iterator_type;

  typedef typename Traits::K K;
  typedef typename K::FT FT;
  typedef typename K::Point_2 Point_2;
  typedef typename K::Iso_rectangle_2 Iso_rectangle_2;

public:
  Point_wsp() : point_(0,0), number_(0), rep_biggest_box_(Point_2(0, 0), Point_2(0,0)) { }

  Point_wsp(Point_2 p, int n) : point_(p), number_(n), rep_biggest_box_(Point_2(0, 0), Point_2(0,0)) { }

  void point(Point_2 p) {
    point_ = p;
  }

  Point_2 point() const {
    return point_;
  }

  void number(int n) {
    number_ = n;
  }

  int number() const {
    return number_;
  }

  void add_representative_of(Well_separated_pair pair, Node_const_handle from, Node_const_handle to) {
    representative_of_.push_back(pair);

    Iso_rectangle_2 bbox = from->bounding_box();
    if(rep_biggest_box_.area() <= bbox.area()) {
      rep_biggest_box_ = bbox;
    }
  }

  bool is_representative(Node_const_handle node) const {
    return node->bounding_box().has_on_boundary(point_);
  }

  bool is_outside(Iso_rectangle_2 rect) const {
    return rect.has_on_unbounded_side(point_);
  }

  bool is_inside(Iso_rectangle_2 rect) const {
    return !is_outside(rect);
  }

  WSP_iterator_type representative_of_begin() const {
    return WSP_iterator_type(*this, representative_of_.begin());
  }

  WSP_iterator_type representative_of_end() const {
    return WSP_iterator_type(*this, representative_of_.end());
  }

  Iso_rectangle_2 rep_biggest_box() const {
    return rep_biggest_box_;
  }

  bool operator==(const Point_wsp& p) const {
    return p.point_ == point_;
  }

  bool operator!=(const Point_wsp& p) const {
    return !operator==(p);
  }

  operator Point_2() const {
    return point_;
  }

  operator int() const {
    return number_;
  }
private:
  Point_2 point_;
  int number_;
  std::vector<Well_separated_pair> representative_of_;
  Iso_rectangle_2 rep_biggest_box_;
};

#endif // POINT_WSP_H
