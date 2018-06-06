#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <boost/tokenizer.hpp>

#ifndef CSV_PARSER_H
#define CSV_PARSER_H

class CsvParser {
public:
  CsvParser(void);
  ~CsvParser(void);
  
  int initialize(const char *file_name, char delimiter = ',');

  int getInt32(unsigned int row, unsigned int column);
  unsigned int getUint32(unsigned int row, unsigned int column);
  long long getInt64(unsigned int row, unsigned int column);
  unsigned long long getUint64(unsigned int row, unsigned int column);
  double getDouble(unsigned int row, unsigned int column);
  std::string getString(unsigned int row, unsigned int column);

  unsigned int getRowSize(void);
  unsigned int getColumnSize(unsigned int row);

private:
  void seekLine(unsigned int line);
  void parseLine(unsigned int line);
  template<class Type> Type convertString(const std::string &s);

private:
  const char *m_file_name;
  char m_delimiter;

  unsigned int m_max_line;
  unsigned int m_current_line;
  
  std::ifstream m_ifs;
  std::string m_line_data;
  std::vector<std::string> m_cells;
};

#endif /* CSV_PARSER_H */
