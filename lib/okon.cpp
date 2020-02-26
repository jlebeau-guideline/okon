#include <okon/okon.h>

#include "btree.hpp"
#include "fstream_wrapper.hpp"
#include "preparer.hpp"

int okon_prepare(const char* input_db_file_path, const char* output_file_directory)
{
  std::ofstream{ output_file_directory + std::string{ "/okon.btree" } };
  okon::preparer generator{ input_db_file_path, output_file_directory };
  generator.prepare();

  return 0;
}

int okon_exists_text(const char* sha1, const char* processed_file_path)
{
  const auto sha1_bin = okon::to_sha1(sha1);
  return okon_exists_binary(sha1_bin.data(), processed_file_path);
}

int okon_exists_binary(const void* sha1, const char* processed_file_path)
{
  okon::fstream_wrapper file{ processed_file_path };
  okon::btree tree{ file };

  okon::sha1_t sha1_bin;
  std::memcpy(&sha1_bin[0], sha1, 20u);

  return tree.contains(sha1_bin) ? 1 : 0;
}