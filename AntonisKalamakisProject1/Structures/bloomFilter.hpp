#ifndef _BLOOMFILTER_HPP_
#define _BLOOMFILTER_HPP_

class bloomFilter{
  int len;
  char* array;

  int k=3;
  unsigned long djb2(unsigned char *str);
  unsigned long sdbm(unsigned char *str);
  unsigned long hash_i(unsigned char *str, unsigned int i);
public:
  bloomFilter(int l);
  ~bloomFilter();
  void insert(int s);
  bool is_inside(int s);
};

#endif
