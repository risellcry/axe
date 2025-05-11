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
		string pxl_name;
		string pxl_visible;
		string pxl_x;
		string pxl_y;
		bool in_pxls_header = false;
		bool in_chrs_header = false;
		bool in_vrls_header = false;
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
				pixels.push_back(make_pair(name, make_pair(true, make_pair(0, 0))));
				current_pixel++;
			}
			else if (type == "char")
			{
				chars.push_back(make_pair(name, make_pair('a', make_pair(0, 0))));
				current_char++;
			}
			else if (type == "variable")
			{
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
				if (command != "pxls" and command != "chrs" and command != "vrls")
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
				return;
			}
			else if (command.compare(0, string("=").length(), "=") == 0)
			{
				if (in_pxls_header == false and in_chrs_header == false)
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
				return;
			}
			else if (command.compare(0, string(":").length(), ":") == 0)
			{
				if (in_sub_header == true)
				{
					puts("ERROR: Use of \":\" while in \"=\".");
					return;
				}
				in_pxls_header = false;
				in_chrs_header = false;
				in_vrls_header = false;
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
			if (in_sub_header == false and in_vrls_header == false and in_pxls_header == false and in_chrs_header == false)
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
			int first_type = 0;
			for (auto pixel : pixels)
			{
				if (tokens[0] == pixel.first)
				{
					first_type = 1;
					break;
				}
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
				}
				if (first_type == 0)
				{
					for (auto variable : variables)
					{
						if (tokens[0] == variable.first)
						{
							first_type = 3;
						}
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
					}
				}
			}
			if (second_type == 0)
			{
				puts("ERROR: Invalid Pixel/Character/Variable.");
				return false;
			}
			return true;
		}
};
