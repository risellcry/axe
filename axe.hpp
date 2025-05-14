#include <iostream>
#include <string>
#include <vector>

using namespace std;

class axe
{
	public:
		vector<pair<string, pair<bool, pair<int, int>>>> pixels;
		vector<pair<string, pair<char, pair<int, int>>>> chars;
		vector<pair<string, string>> events;
		vector<vector<vector<string>>> pixel_properties;
		vector<vector<vector<string>>> char_properties;
		vector<pair<string, string>> variables;
		int current_event = -1;
		int current_pixel = -1;
		int current_char = -1;
		int current_variable = -1;
		int count = 0;
		int count_chr = 0;
		string object;
		string pxl_name;
		string pxl_visible;
		string pxl_x;
		string pxl_y;
		string chr_name;
		char chr_key;
		string chr_x;
		string chr_y;
		string evt_expression;
		bool in_pxls_header = false;
		bool in_chrs_header = false;
		bool in_vrls_header = false;
		bool in_evts_header = false;
		bool in_sub_header = false;
		void create(string type, string name)
		{
			if (type != "pixel" and type != "char" and type != "variable")
			{
				puts("ERROR: Invalid type.");
				return;
			}
			if (type == "pixel")
			{
				bool founded = false;
				for (auto pixel : pixels)
				{
					if (name == pixel.first)
					{
						founded = true;
						break;
					}
				}
				for (auto _char : chars)
				{
					if (name == _char.first)
					{
						founded = true;
						break;
					}
				}
				for (auto variable : variables)
				{
					if (name == variable.first)
					{
						founded = true;
						break;
					}
				}
				if (founded == true or name == "")
				{
					puts("ERROR: Cannot use the same Name as other Pixel/Character/Variable or cannot use the null Name.");
					return;
				}
				pixels.push_back(make_pair(name, make_pair(true, make_pair(0, 0))));
				current_pixel++;
			}
			else if (type == "char")
			{
				bool founded = false;
				for (auto pixel : pixels)
				{
					if (name == pixel.first)
					{
						founded = true;
						break;
					}
				}
				for (auto _char : chars)
				{
					if (name == _char.first)
					{
						founded = true;
						break;
					}
				}
				for (auto variable : variables)
				{
					if (name == variable.first)
					{
						founded = true;
						break;
					}
				}
				if (founded == true or name == "")
				{
					puts("ERROR: Cannot use the same Name as other Pixel/Character/Variable or Cannot use the null Name.");
					return;
				}
				chars.push_back(make_pair(name, make_pair('a', make_pair(0, 0))));
				current_char++;
			}
			else if (type == "variable")
			{
				bool founded = false;
				for (auto pixel : pixels)
				{
					if (name == pixel.first)
					{
						founded = true;
						break;
					}
				}
				for (auto _char : chars)
				{
					if (name == _char.first)
					{
						founded = true;
						break;
					}
				}
				for (auto variable : variables)
				{
					if (name == variable.first)
					{
						founded = true;
						break;
					}
				}
				if (founded == true or name == "")
				{
					puts("ERROR: Cannot use the same Name as other Pixel/Character/Variable or cannot use the null Name.");
					return;
				}
				variables.push_back(make_pair(name, ""));
				current_variable++;
			}
			return;
		}
		void read(string command)
		{
			if (command.compare(0, string("-").length(), "-") == 0)
			{
				command.replace(0, 1, "");
				if (command != "pxls" and command != "chrs" and command != "vrls" and command != "evts")
				{
					puts("ERROR: Invalid Header.");
					return;
				}
				if (command == "pxls")
				{
					in_pxls_header = true;
				}
				else if (command == "chrs")
				{
					in_chrs_header = true;
				}
				else if (command == "vrls")
				{
					in_vrls_header = true;
				}
				else if (command == "evts")
				{
					in_evts_header = true;
				}
				return;
			}
			else if (command.compare(0, string("=").length(), "=") == 0)
			{
				if (in_pxls_header == false and in_chrs_header == false and in_evts_header == false)
				{
					puts("ERROR: Invalid use for \"=\".");
					return;
				}
				in_sub_header = true;
				command.replace(0, 1, "");
				if (in_pxls_header == true)
				{
					pxl_name = command;
				}
				else if (in_chrs_header == true)
				{
					chr_name = command;
				}
				else if (in_evts_header == true)
				{
					evt_expression = command;
				}
				return;
			}
			else if (command.compare(0, string(":").length(), ":") == 0)
			{
				if (in_pxls_header == false and in_chrs_header == false and in_vrls_header == false and in_evts_header == false)
				{
					puts("ERROR: Use of \":\" before \"-\".");
					return;
				}
				if (in_sub_header == true)
				{
					puts("ERROR: Use of \":\" while in \"=\".");
					return;
				}
				in_pxls_header = false;
				in_chrs_header = false;
				in_vrls_header = false;
				in_evts_header = false;
				return;
			}
			else if (command.compare(0, string(";").length(), ";") == 0)
			{
				if (in_sub_header == false)
				{
					puts("ERROR: Use of \";\" before \"=\".");
					return;
				}
				in_sub_header = false;
				return;
			}
			if (in_sub_header == false and in_vrls_header == false and in_pxls_header == false and in_chrs_header == false and in_evts_header == false)
			{
				return;
			}
			if (in_sub_header == true and in_pxls_header == true)
			{
				count++;
				if (count == 1)
				{
					if (command != "false" and command != "true")
					{
						puts("ERROR: Invalid Boolean.");
						return;
					}
					pxl_visible = command;
				}
				else if (count == 2)
				{
					pxl_x = command;
				}
				else if (count == 3)
				{
					if (command.find(".") != string::npos)
					{
						puts("ERROR: Invalid Integer.");
						return;
					}
					try
					{
						int check = stoi(command);
					}
					catch (exception error)
					{
						puts("ERROR: Invalid Integer.");
						return;
					}
					pxl_y = command;
					count = 0;
					bool is_visible = false;
					if (pxl_visible == "true")
					{
						is_visible = true;
					}
					pixels.push_back(make_pair(pxl_name, make_pair(is_visible, make_pair(stoi(pxl_x), stoi(pxl_y)))));
					return;
				}
			}
			else if (in_sub_header == true and in_chrs_header == true)
			{
				count_chr++;
				if (count_chr == 1)
				{
					if (command.length() > 1)
					{
						puts("ERROR: Invalid Character.");
						return;
					}
					chr_key = command[0];
				}
				else if (count_chr == 2)
				{
					chr_x = command;
				}
				else if (count_chr == 3)
				{
					if (command.find(".") != string::npos)
					{
						puts("ERROR: Invalid Integer.");
						return;
					}
					try
					{
						int check = stoi(command);
					}
					catch (exception error)
					{
						puts("ERROR: Invalid Integer.");
						return;
					}
					chr_y = command;
					count_chr = 0;
					chars.push_back(make_pair(chr_name, make_pair(chr_key, make_pair(stoi(chr_x), stoi(chr_y)))));
					return;
				}
			}
			else if (in_sub_header == true and in_evts_header == true)
			{
				events.push_back(make_pair(evt_expression, command));
				return;
			}
			else if (in_vrls_header == true)
			{
				string name = command;
				name.replace(name.find_first_of(">"), name.length() - name.find_first_of(">"), "");
				command.replace(0, name.length() + 1, "");
				string value = command;
				variables.push_back(make_pair(name, value));
				current_variable++;
			}
			return;
		}
		bool run(string query)
		{
			if (query.compare(0, string("set ").length(), "set ") == 0)
			{
				try
				{
					query.replace(0, 4, "");
					string variable = query;
					variable.replace(variable.find_first_of(" "), variable.length() - variable.find_first_of(" "), "");
					query.replace(0, variable.length() + 1, "");
					string value = query;
					int i;
					bool founded = false;
					for (auto _variable : variables)
					{
						if (variable == _variable.first)
						{
							founded = true;
							break;
						}
						i++;
					}
					if (founded == false)
					{
						puts("ERROR: Invalid Variable.");
						return false;
					}
					variables[i].second = value;
				}
				catch (exception error)
				{
					puts("ERROR: Syntax Error for \"set\".");
					return false;
				}
				return true;
			}
			if (query.compare(0, string("select ").length(), "select ") == 0)
			{
				query.replace(0, 7, "");
				bool founded = false;
				for (auto pixel : pixels)
				{
					if (query == pixel.first)
					{
						founded = true;
						break;
					}
				}
				for (auto _char : chars)
				{
					if (query == _char.first)
					{
						founded = true;
						break;
					}
				}
				if (founded == false)
				{
					puts("ERROR: Invalid Object.");
					return false;
				}
				object = query;
				return true;
			}
			if (query.compare(0, string("change ").length(), "change ") == 0)
			{
				query.replace(0, 7, "");
				if (object == "")
				{
					puts("ERROR: Use of \"change\" before \"select\".");
					return false;
				}
				string property = query;
				try
				{
					property.replace(property.find_first_of(" "), property.length() - property.find_first_of(" "), "");
					query.replace(0, property.length() + 1, "");
				}
				catch (exception error)
				{
					puts("ERROR: Syntax Error for \"change\".");
					return false;
				}
				string value = query;
				bool is_pixel = false;
				int i = 0;
				for (auto pixel : pixels)
				{
					if (object == pixel.first)
					{
						is_pixel = true;
						break;
					}
					i++;
				}
				if (is_pixel == false)
				{
					i = 0;
					for (auto _char : chars)
					{
						break;
					}
					i++;
				}
				if (is_pixel == false)
				{
					if (property == "key")
					{
						if (value.length() > 1)
						{
							puts("ERROR: Invalid Character.");
							return false;
						}
						chars[i].second.first = value[0];
					}
					else if (property == "x")
					{
						if (value.find(".") != string::npos)
						{
							puts("ERROR: Invalid Integer.");
							return false;
						}
						try
						{
							int pos = stoi(value);
							chars[i].second.second.first = pos;
						}
						catch (exception error)
						{
							puts("ERROR: Invalid Integer.");
							return false;
						}
					}
					else if (property == "y")
					{
						if (value.find(".") != string::npos)
						{
							puts("ERROR: Invalid Integer.");
							return false;
						}
						try
						{
							int pos = stoi(value);
							chars[i].second.second.second = pos;
						}
						catch (exception error)
						{
							puts("ERROR: Invalid Integer.");
							return false;
						}
					}
					else
					{
						puts("ERROR: Invalid Property.");
						return false;
					}
				}
				if (is_pixel == true)
				{
					if (property == "visible")
					{
						if (value != "true" and value != "false")
						{
							puts("ERROR: Invalid Boolean.");
							return false;
						}
						bool visible = false;
						if (value == "true")
						{
							visible = true;
						}
						pixels[i].second.first = visible;
					}
					else if (property == "x")
					{
						if (value.find(".") != string::npos)
						{
							puts("ERROR: Invalid Integer.");
							return false;
						}
						try
						{
							int pos = stoi(value);
							pixels[i].second.second.first = pos;
						}
						catch (exception error)
						{
							puts("ERROR: Invalid Integer.");
							return false;
						}
					}
					else if (property == "y")
					{
						if (value.find(".") != string::npos)
						{
							puts("ERROR: Invalid Integer.");
							return false;
						}
						try
						{
							int pos = stoi(value);
							pixels[i].second.second.second = pos;
						}
						catch (exception error)
						{
							puts("ERROR: Invalid Integer.");
							return false;
						}
					}
					else
					{
						puts("ERROR: Invalid Property.");
						return false;
					}
				}
				return true;
			}
			puts("ERROR: Invalid Query.");
			return false;
		}
		bool act(int index)
		{
			string expression = events[index].first;
			string action = events[index].second;
			vector<string> tokens;
			while (expression.find(" ") != string::npos)
			{
				string token = expression;
				token.replace(token.find(" "), token.length() + token.find(" "), "");
				expression.replace(0, token.length() + 1, "");
				tokens.push_back(token);
				continue;
			}
			if (tokens.size() != 3)
			{
				puts("ERROR: Invalid Expression.");
				return false;
			}
			int first_i;
			int second_i;
			int first_type = 0;
			for (auto pixel : pixels)
			{
				if (tokens[0] == pixel.first)
				{
					first_type = 1;
					break;
				}
				first_i++;
			}
			if (first_type == 0)
			{
				for (auto _char : chars)
				{
					if (tokens[0] == _char.first)
					{
						first_type = 2;
						break;
					}
					first_i++;
				}
				if (first_type == 0)
				{
					for (auto variable : variables)
					{
						if (tokens[0] == variable.first)
						{
							first_type = 3;
						}
						first_i++;
					}
				}
			}
			if (first_type == 0)
			{
				puts("ERROR: Invalid Pixel/Character/Variable.");
				return false;
			}
			int second_type = 0;
			for (auto pixel : pixels)
			{
				if (tokens[2] == pixel.first)
				{
					if (first_type != 1)
					{
						puts("ERROR: Cannot Compare any other types with Pixel.");
						return false;
					}
					second_type = 1;
					break;
				}
				second_i++;
			}
			if (second_type == 0)
			{
				for (auto _char : chars)
				{
					if (tokens[2] == _char.first)
					{
						if (first_type != 2)
						{
							puts("ERROR: Cannot Compare any other types with Character.");
							return false;
						}
						second_type = 2;
						break;
					}
					second_i++;
				}
				if (second_type == 0)
				{
					for (auto variable : variables)
					{
						if (tokens[2] == variable.first)
						{
							if (first_type != 3)
							{
								puts("ERROR: Cannot Compare any other types with Variable.");
								return false;
							}
							second_type = 3;
							break;
						}
						second_i++;
					}
				}
			}
			if (second_type == 0)
			{
				puts("ERROR: Invalid Pixel/Character/Variable.");
				return false;
			}
			if (tokens[1] != "==" and tokens[1] != "!=" and tokens[1] != ">" and tokens[1] != ">=" and tokens[1] != "<" and tokens[1] != "<=")
			{
				puts("ERROR: Invalid Operator.");
				return false;
			}
			if (first_type == 1)
			{
				if (tokens[1] == "==")
				{
					if (pixels[first_i].second.first == pixels[second_i].second.first)
					{
						run(action);
					}
				}
				if (tokens[1] == "!=")
				{
					if (pixels[first_i].second.first != pixels[second_i].second.first)
					{
						run(action);
					}
				}
				if (tokens[1] == ">")
				{
					if (pixels[first_i].second.first > pixels[second_i].second.first)
					{
						run(action);
					}
				}
				if (tokens[1] == ">=")
				{
					if (pixels[first_i].second.first >= pixels[second_i].second.first)
					{
						run(action);
					}
				}
				if (tokens[1] == "<")
				{
					if (pixels[first_i].second.first < pixels[second_i].second.first)
					{
						run(action);
					}
				}
				if (tokens[1] == "<=")
				{
					if (pixels[first_i].second.first <= pixels[second_i].second.first)
					{
						run(action);
					}
				}
			}
			if (first_type == 2)
			{
				if (tokens[1] == "==")
				{
					if (chars[first_i].second.first == chars[second_i].second.first)
					{
						run(action);
					}
				}
				if (tokens[1] == "!=")
				{
					if (chars[first_i].second.first != chars[second_i].second.first)
					{
						run(action);
					}
				}
				if (tokens[1] == ">" or tokens[1] == ">=" or tokens[1] == "<" or tokens[1] == "<=")
				{
					puts("ERROR: Cannot use operator >, >=, < or <= to compare Characters.");
					return false;
				}
			}
			if (first_type == 3)
			{
				if (tokens[1] == "==")
				{
					if (variables[first_i].second == variables[second_i].second)
					{
						run(action);
					}
				}
				if (tokens[1] == "!=")
				{
					if (variables[first_i].second != variables[second_i].second)
					{
						run(action);
					}
				}
				if (tokens[1] == ">" or tokens[1] == ">=" or tokens[1] == "<" or tokens[1] == "<=")
				{
					puts("ERROR: Cannot use operator >, >=, < or <= to compare Variables.");
					return false;
				}
			}
			return true;
		}
};
