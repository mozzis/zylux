#include <string.h>
#pragma warning(disable: 4666 4786)
#include <hash_set>
#pragma warning(default: 4666)

struct eqstr
{
  bool operator()(const char * s1, const char * s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};

int main()
{
  std::hash_set<const char *, const char *, eqstr> Set;
  Set.insert("kiwi");
  Set.insert("plum");
  Set.insert("apple");
  Set.insert("mango");
  Set.insert("apricot");
  Set.insert("banana");

  return Set.end() == Set.find("banana");
}

