/**
 * /mnt/z/my_git/sixth-semester/computer_networks/lab/lab4/ByteStuffing.cpp
 * @file ByteStuffing.cpp
 * @author Avinal Kumar
 * @since February 17, 2021
 *
 * Byte Stuffing Implementation in C++
 */

#include <iostream>

std::string byte_stuff(std::string const data, std::string const escape) {
  std::string stuffed = "0x";
  size_t last_pos = 2;
  while (true) {
    size_t esc = data.find(escape, last_pos);
    if (esc != std::string::npos) {
      stuffed += data.substr(last_pos, esc - last_pos);
      stuffed += "5D";
      stuffed += escape;
      last_pos = esc + 2;
    } else {
      break;
    }
  }
  stuffed += data.substr(last_pos);
  return stuffed;
}

std::string byte_unstuff(std::string const data) {
  std::string unstuff = "0x";
  size_t last_pos = 2;
  while (true) {
    size_t esc = data.find("5D", last_pos);
    if (esc != std::string::npos) {
      unstuff += data.substr(last_pos, esc - last_pos);
      unstuff += data.substr(esc + 2, 2);
      last_pos = esc + 4;
    } else {
      break;
    }
  }
  unstuff += data.substr(last_pos);
  return unstuff;
}

int main(int argc, char const *argv[]) {
  std::string data = "";
  std::cout << "Enter hexadecimal data string starting with 0x: " << std::endl;
  std::cin >> data;
  std::cout << "Flag to escape: ";
  std::string escape = "";
  std::cin >> escape;
  std::string stuff = byte_stuff(data, "5D");
  stuff = byte_stuff(stuff, escape);
  std::cout << "Data after Byte stuffing: " << stuff << std::endl;
  std::string unstuff = byte_unstuff(stuff);
  std::cout << "Data after unstuffing: " << unstuff << std::endl;
  std::cout << std::endl;
  return 0;
}
