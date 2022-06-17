
#include "string.hpp"

int _string::len()
{
	return this->len_string;
}

int _string::_stringlen(const char *str) const
{
	int i = 0;

	while (str[i])
	{
		i++;
	}
	return i;
}

 _string::_string()
 {
	this->str_obj = new (std::nothrow) char[15];
	if (!this->str_obj)
	{
		std::cout << "bad allocate" << std::endl;
	}
	else
	{
		this->memo = 15;
		str_obj[0] = '\0';
		this->len_string = 0;
	}
 }

 _string::_string(const char *str_in)
{
	std::size_t i = 0;
	std::size_t len_const =  _stringlen(str_in);
	std::size_t tmp_memo = len_const + 1;

	if (len_const + 1 <= 15)
	{
		this->str_obj = new (std::nothrow) char[15];
		tmp_memo = 15;
	}
	else if (len_const + 1 <= 30)
	{
		this->str_obj = new (std::nothrow) char[30];
		tmp_memo = 30;
	}
	 else
	{
		this->str_obj = new  (std::nothrow) char[len_const + 1];
	}
	if (!this->str_obj)
	{
		this->memo = 0;
	}
	else
	{
		while (str_in[i])
		{
			this->str_obj[i] = str_in[i];
			i++;
		}
		this->str_obj[i] = '\0';
		this->len_string = len_const;
		this->memo = tmp_memo;
	}
}

std::size_t _string::capacity() const
 {
	 return this->memo;
 }

 _string::_string(const _string &str_copy)
{
	int i = 0;

	this->str_obj = new (std::nothrow) char[this->memo];
	if (!this->str_obj)
	{
		std::cout << "bad allocate";
	}
	else
	{
		this->len_string = str_copy.len_string;
		this->memo = str_copy.capacity();
		while (str_copy.str_obj != nullptr &&  str_copy[i])
		{
			this->str_obj[i] = str_copy[i];
			i++;
		}
		this->str_obj[i] = '\0';
	}
}

 _string::_string(_string &&str_move)
{
	this->str_obj = str_move.str_obj;
	this->len_string = str_move.len_string;
	this->memo = str_move.memo;
	str_move.len_string = 0;
	str_move.str_obj = nullptr;
}

_string::~_string()
{
	delete []this->str_obj;
	this->str_obj = nullptr;
}

 _string& _string::operator=(const _string &str_eq)
{
	int i = 0;

	if (&str_eq == this && str_eq.str_obj == nullptr)
		return *this;
	if (this->str_obj)
	{
		delete []this->str_obj;
	}
	this->len_string = str_eq.len_string;
	this->memo = std::max(str_eq.memo, this->memo);
	this->str_obj = new (std::nothrow) char[this->memo]; //(std::nothrow)
	if (!this->str_obj)
	{
		std::cout << " Bad allocate " << std::endl;
		return *this;
	}
	while (str_eq.str_obj[i])
	{
		this->str_obj[i] = str_eq.str_obj[i];
		i++;
	}
	this->str_obj[i] = '\0';
	return *this;
}

_string& _string::operator=(_string &&str_eq)
{
	this->str_obj = str_eq.str_obj;
	this->len_string = str_eq.len_string;
	this->memo = str_eq.memo;
	str_eq.str_obj = nullptr;
	str_eq.len_string = 0;
	return *this;
}

std::ostream& operator<<(std::ostream &out, const _string &out_string)
{
	int i = 0;

	while (out_string.str_obj != nullptr && out_string.str_obj[i])
	{
		out << out_string.str_obj[i];
		i++;
	}
	return out;
}

const char& _string::operator[](const int i) const
{
	if (this->len_string < i + 1) return this->str_obj[this->len_string];
	return this->str_obj[i];
}

char& _string::operator[](const int i)
{
	if (this->len_string < i + 1) return this->str_obj[this->len_string];
	return this->str_obj[i];
}

int _string::compare (const _string& str) const
{
	return compare(0, this->len_string, str, 0, str.len_string);
}

int _string::compare (size_t pos, size_t len, const _string& str) const
{
	return compare(pos, len, str, 0, str.len_string);
}

int _string::compare (size_t pos, size_t len, const _string& str, size_t subpos) const
{
	return compare(pos, len, str, subpos, str.len_string);
}

int _string::compare (size_t pos, size_t len, const _string& str, size_t subpos, size_t sublen) const
{
	int index = 0;

	while (this->str_obj[index + pos] && str.str_obj[index + subpos])
	{
		if (this->str_obj[index + pos] != str.str_obj[index + subpos])
			return (unsigned char)this->str_obj[index + pos] - (unsigned char)str.str_obj[index + subpos];
		if (len == index + 1 || sublen == index + 1)
			break;
		index++;
	}
	if (sublen != len && (len == index + 1 || sublen == index + 1))
	{
		if (sublen > len && index < str.len_string)
			return -1;
		if  (len > sublen && index < this->len_string)
			return 1;
	}
	return (0);
}

int _string::compare (size_t pos, size_t len, const char* s, size_t n) const
{
	int i = 0;
	while (s[i] && this->str_obj[i + pos] && s[i] == this->str_obj[i + pos] && len != i && i != n)
	{
		i++;
	}
	return (unsigned char)this->str_obj[i + pos] - (unsigned char)s[i];
}

bool operator== (const _string &c1, const _string &c2)
{
	if (c1.len_string != c2.len_string) return false;
	if (c1.compare(c2) != 0) return false;

	return true;
}

bool operator!= (const _string &c1, const _string &c2)
{
	return !(c1 == c2);
}

bool operator>(const _string &str1, const _string &str2)
{
	if (str1.compare(str2) > 0) return true;
	
	return false;
}

bool operator<(const _string &str1, const _string &str2)
{
   return !(str1 > str2);
}

bool operator>=(const _string &str1, const _string &str2)
{
	if (str1 == str2 || str1 > str2) return true;
	 
	return false;
}

bool operator<=(const _string &str1, const _string &str2)
{
	if (str1 == str2 || str1 < str2) return true;
	
	return false;
}

bool _string::empty() const
{
	return this->len_string == 0;
}

void _string::reserve(std::size_t new_cap)
{
	char 	*tmp;
	int 	i = 0;

	if (this->memo >= new_cap + 1) return;
	tmp = new (std::nothrow) char[new_cap + 1];
	if (!tmp)
	{
		std::cout << "bad allocate" << std::endl;
	}
	while (this->str_obj[i])
	{
		tmp[i] = str_obj[i];
		i++;
	}
	tmp[i] = '\0';
	delete []str_obj;
	str_obj = tmp;
	this->memo = new_cap + 1;
}

void _string::clear()
{
	int i = 0;

	while (this->str_obj[i])
	{
		this->str_obj[i] = '\0';
		i++;
	}
}

 _string& _string::insert(std::size_t index, std::size_t count, char ch)
{
	int		i = 0;
	char	*tmp;
	int		str_i = 0;

	if (count == 0) return *this;
	if (index > this->len_string) return *this;
	tmp = new (std::nothrow) char[this->len_string + count + 1];
	if (!tmp)
	{
		std::cout<<"Bad allocate" << std::endl;
		return *this;
	}
	this->memo += this->len_string + count + 1;

	while (this->str_obj[i] && i < index)
	{
		tmp[i] = this->str_obj[i];
		i++;
	}
	str_i = i;
	while (count != 0)
	{
		tmp[i] = ch;
		count--;
		i++;
	}
	while (this->str_obj[str_i])
	{
		tmp[i] = this->str_obj[str_i];
		i++;
		str_i++;
	}
	tmp[i] = '\0';
	delete []str_obj;
	str_obj = tmp;
	this->len_string = i;

	return *this;
 }

 _string& _string::insert(std::size_t index, const char* s)
 {
	char    *tmp;
	int     len_insert = _stringlen(s);
	int     i = 0;
	int     str_i = 0;
	int     s_i = 0;

	if (len_insert == 0) return *this;
	if (index > this->len_string) return *this;
	tmp = new (std::nothrow)char[len_insert + len_string + 1];
	if (!tmp)
	{
		std::cout << "bad allocate" << std::endl;
		return *this;
	}
	memo =  len_insert + len_string + 1;
	while (this->str_obj[i] && i < index)
	{
		tmp[i] = this->str_obj[i];
		i++;
	}
	str_i = i;
	while (s[s_i])
	{
		tmp[i] = s[s_i];
		i++;
		s_i++;
	}
	while (this->str_obj[str_i])
	{
		tmp[i] = this->str_obj[str_i];
		i++;
		str_i++;
	}
	tmp[i] = '\0';
	delete []str_obj;
	str_obj = tmp;
	len_string = i;

	return *this;
 }

 _string& _string::insert(std::size_t index, _string const& str)
 {
	char    *tmp;
	int     i = 0;
	int     str_i = 0;
	int     s_i = 0;

	
	if (str.len_string == 0) return *this;
	if (index > this->len_string) return *this;
	tmp = new (std::nothrow) char[str.len_string + len_string + 1];
	if (!tmp)
	{
		std::cout << "bad allocate" << std::endl;
		return *this;
	}
	memo = str.len_string + len_string + 1;
	while (this->str_obj[i] && i < index)
	{
		tmp[i] = this->str_obj[i];
		i++;
	}
	str_i = i;
	while (str.str_obj[s_i])
	{
		tmp[i] = str.str_obj[s_i];
		i++;
		s_i++;
	}
	while (this->str_obj[str_i])
	{
		tmp[i] = this->str_obj[str_i];
		i++;
		str_i++;
	}
	tmp[i] = '\0';
	delete []str_obj;
	str_obj = tmp;
	len_string = i;
	return *this;
 }

 _string& _string::erase( std::size_t index, std::size_t count)
 {
	int i = 0;

	if (index + 1 > this->len_string) return *this;

	while (this->str_obj[index + count])
	{
		std::swap(this->str_obj[index], this->str_obj[index + count]);
		index++;
	}
	while (str_obj[i + index] && i + 1 < count )
	{
		this->str_obj[index + i] = '\0';
		i++;
	}
	return *this;
 }

int _string::_stringcpy(char *str1, char *str2, int index)
{
	int i = 0;

	while (str2[i])
	{
		str1[index] = str2[i];
		i++;
		index++;
	}
	str_obj[index] = '\0';
	return index;
}

void _string::pop_back()
{
	if (this->len_string != 0)
	{
		this->len_string--;
		this->str_obj[this->len_string] = '\0';
	}
}

void _string::push_back(char ch)
{
	int		i = 0;

	if (this->memo < this->len_string + 2)
	{
		char	*tmp;
	
		this->str_obj = new (std::nothrow) char[this->len_string + 2];
		if (!this->str_obj)
		{
			std::cout << "bad allocate" << std::endl;
			return;
		}
		while (this->str_obj[i])
		{
			tmp[i] = this->str_obj[i];
			i++;
		}
		tmp[i] = ch;
		tmp[i] = '\0';
		delete []this->str_obj;
		this->str_obj = tmp;
		this->len_string += 1;
		this->memo += 1; 
		return;
	}
	this->str_obj[this->len_string] = ch;
	this->str_obj[len_string + 1] = '\0';
	this->len_string += 1;
}

_string& _string::append( std::size_t count, char ch )
{
	while (count != 0)
	{
		push_back(ch);
		count--;
	}
	return *this;
}

_string& _string::append(const _string& str)
{
	int i = 0;

	if (str.len_string + this->len_string + 1 > this->memo)
	{
		return insert(this->len_string, str);	
	}
	while (str[i])
	{
		this->push_back(str[i]);
		i++;
	}
	return *this;
}

bool _string::contains( const char* s ) const
{
	int i = 0;

	while (this->str_obj[i])
	{
		if (this->str_obj[i] == s[0])
		{
			if(compare(i, this->len_string - i, s) == 0) return true;
		}
		i++;
	}
	return false;
}

bool _string::contains(const char c) const
{
	int i = 0;
	while (this->str_obj[i])
	{
		if (this->str_obj[i] == c)
		{
			return true;
		}
		i++;
	}
	return false;
}

bool _string::contains( const _string s ) const
{
	int i = 0;

	while (this->str_obj[i])
	{
		if (this->str_obj[i] == s[0])
		{
			if(compare(i, this->len_string - i, s) == 0) return true;
		}
		i++;
	}
	return false;
}


void _string::resize(std::size_t count)
{
	char *tmp;
	int i = 0;
	std::size_t tmp_count = 0;

	tmp = new (std::nothrow) char[this->memo + count];
	if (!tmp)
	{
		std::cout << "bad allocate" << std::endl;
		return ;
	}
	i = _stringcpy(tmp, str_obj, 0);
	while (tmp_count != 0)
	{
		tmp[i] = '\0';
		i++;
		tmp_count--;
	}
	this->memo += count;
	delete str_obj;
	str_obj = tmp; 
}

_string _string::operator + (_string const &obj)
{
	_string a;
	int next_index;

	a.reserve(this->len_string + obj.len_string + 1);
	next_index = _stringcpy(a.str_obj, this->str_obj, 0);
	_stringcpy(a.str_obj, obj.str_obj, next_index);
	return a;
}


_string& _string::operator+=(const _string& str)
{
	return (insert(this->len_string - 1, str));
}

void _string::resize( std::size_t count, char ch )
{
	char *tmp;
	int i = 0;
	std::size_t tmp_count = this->memo - this->len_string + count;

	tmp = new (std::nothrow) char[this->memo + count];
	if (!tmp)
	{
		std::cout << "bad allocate" << std::endl;
		return ;
	}
	i = _stringcpy(tmp, str_obj, 0);
	while (tmp_count > 1)
	{
		tmp[i] = ch;
		i++;
		tmp_count--;
	}
	tmp[i] = '\0';
	this->memo += count;
	delete str_obj;
	str_obj = tmp; 
}
