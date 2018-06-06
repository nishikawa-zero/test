#include "CsvParser.h"

CsvParser::CsvParser(void): m_file_name(NULL),
                            m_delimiter(NULL),
                            m_max_line(0),
                            m_current_line(0) {
}

CsvParser::~CsvParser(void) {
}

int
CsvParser::initialize(const char *file_name, const char delimiter) {
  int result = 0;

  if (file_name == NULL) {
    result = -1;
  }
  if ((delimiter != ',') && (delimiter != '\t')) {
    result = -1;
  }

  if (result == 0) {
    if (m_ifs) {
      m_ifs.close();
      m_ifs.clear();
    }
    m_ifs.open(file_name);

    if (!m_ifs) {
      std::cout << "[ERROR] cannot open " << file_name << std::endl;
      result = -1;
    } else {
      m_file_name = file_name;
      m_delimiter = delimiter;
      m_max_line = 0;
      m_current_line = 0;
      
      m_line_data.clear();
      m_cells.clear();
      
      while (std::getline(m_ifs, m_line_data)) {
        ++m_max_line;
      }
      m_ifs.clear();
      m_ifs.seekg(0);
    }
  }
  return result;
}

int
CsvParser::getInt32(unsigned int row, unsigned int column) {
  return convertString<int>(getString(row, column));
}

unsigned int
CsvParser::getUint32(unsigned int row, unsigned int column) {
  return convertString<unsigned int>(getString(row, column));
}

long long
CsvParser::getInt64(unsigned int row, unsigned int column) {
  return convertString<long long>(getString(row, column));
}

unsigned long long
CsvParser::getUint64(unsigned int row, unsigned int column) {
  return convertString<unsigned long long>(getString(row, column));
}

double
CsvParser::getDouble(unsigned int row, unsigned int column) {
  return convertString<double>(getString(row, column));
}

template<class Type>
Type
CsvParser::convertString(const std::string &s) {
  Type result;
  std::stringstream ss;
  unsigned int space_count = 0;

  for (unsigned int i = 0; i < s.size(); ++i) {
    if (s.at(i) == ' ') {
      ++space_count;
    } else {
      break;
    }
  }

  if (!s.empty()) {
    if (s.substr(space_count, 2) == "0x") {
      ss << s.substr(space_count + 2);
      ss >> std::hex >> result;      
    } else {
      ss << s;
      ss >> result;
    }
  } else {
    result = 0;
  }

  return result;
}

std::string
CsvParser::getString(unsigned int row, unsigned int column) {
  parseLine(row + 1);
  assert(column < m_cells.size());
  return m_cells.at(column);
}

unsigned int
CsvParser::getRowSize(void) {
  return m_max_line;
}

unsigned int
CsvParser::getColumnSize(unsigned int row) {
  parseLine(row + 1);
  return m_cells.size();
}

void
CsvParser::seekLine(unsigned int line) {
  assert(line <= m_max_line);

  if (line != m_current_line) {
    m_cells.clear();
    if (line < m_current_line) {
      m_ifs.clear();
      m_ifs.seekg(0);
      m_current_line = 0;
    }
    while (m_current_line != line) {
      std::getline(m_ifs, m_line_data);
      ++m_current_line;
    }
  }
}

void
CsvParser::parseLine(unsigned int line) {
  seekLine(line);
  
  if (m_cells.empty()) {
    while (m_line_data.find('\r') != std::string::npos) {
      m_line_data.erase(m_line_data.find('\r'), 1);
    }
    while (m_line_data.find('\n') != std::string::npos) {
      m_line_data.erase(m_line_data.find('\n'), 1);
    }

    boost::escaped_list_separator<char> els('\\', m_delimiter, '\"');
    boost::tokenizer<boost::escaped_list_separator<char> > tokens(m_line_data, els);

    m_cells.assign(tokens.begin(), tokens.end());
  }
}
