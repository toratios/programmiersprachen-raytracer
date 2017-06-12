#ifndef SHAPE_HPP
#define SHAPE_HPP

template <typename T>
Class Shape{

  public:
  
  virtual T area const = 0;
  virtual T volume const = 0;
};

#endif