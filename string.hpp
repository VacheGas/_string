#ifndef _STRING_H
#define _STRING_H
#include <iostream>
#include <string>
class _string
 {
	 private :
		char *str_obj;
		int _stringlen(const char *str) const;
		int memo;
		int len_string;
		int _stringcpy(char *str1, char *str2, int index);
	 public :
		int len();
		_string(const char *str_in);
		_string(const _string &str_copy);
		_string(_string &&str_move);
		~_string();
		_string& operator=(const _string &str_eq);
		_string& operator=(_string &&str_eq);
		friend std::ostream & operator<<(std::ostream &out, const _string &out_string);
		char& operator[](const int i);
		const char& operator[](const int i) const;
		int compare (const _string& str) const;
		int compare (size_t pos, size_t len, const _string& str) const;
		int compare (size_t pos, size_t len, const _string& str,
		size_t subpos, size_t sublen) const;
		int compare (size_t pos, size_t len, const _string& str,
		size_t subpos) const;
		int compare (const char* s) const;
		int compare (size_t pos, size_t len, const char* s, size_t n) const;
		friend bool operator== (const _string &str1, const _string &str2);
		friend bool operator!= (const _string &str1, const _string &str2);
		friend bool operator>(const _string &str1, const _string &str2);
		friend bool operator<(const _string &str1, const _string &str2);
		friend bool operator>=(const _string &str1, const _string &str2);
		friend bool operator<=(const _string &str1, const _string &str2);
		bool empty() const;
		void reserve(std::size_t new_cap);
		std::size_t capacity() const;
		void clear();
		_string& insert(std::size_t index, std::size_t count, char ch);
		_string& insert(std::size_t index, const char* s);
		_string& insert(std::size_t index, _string const& str);
		_string& erase( std::size_t index, std::size_t count);
		void pop_back();
		void push_back( char ch );
		_string& append( std::size_t count, char ch );
		_string& append( const _string& str );
		bool contains( const char* s ) const;
		bool contains( const char c ) const;
		bool contains( const _string s ) const;
		void resize( std::size_t count );
		void resize( std::size_t count, char ch );
		_string();
		_string operator + (_string const &obj);
		_string& operator+=(const _string& str);
};
#endif