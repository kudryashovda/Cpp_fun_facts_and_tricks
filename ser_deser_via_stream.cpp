#include <sstream>
#include <cassert>

using namespace std;

int main()
{
  // serialize
  const uint32_t data = 0xAABBCCDD;
  stringstream oss(ios::in | ios::out | ios::binary);
  oss.write(reinterpret_cast<const char*>(&data), sizeof(data));

  // modify
  oss.seekp(1);
  uint8_t number = 0x00;
  oss.write(reinterpret_cast<const char*>(&number), 1);

  // deserialize
  uint32_t obj;
  char *accessor = reinterpret_cast<char *>(&obj);
  copy(istreambuf_iterator<char>(oss), istreambuf_iterator<char>(), accessor);

  assert(obj == 0xAABB00DD);

  return 0;
}
