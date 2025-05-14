#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <signal.h>
#include "axe.hpp"

using namespace std;

int prevents = 0;

void project_exit(int signal)
{
	prevents++;
}

int main()
{
	signal(SIGINT, project_exit);
	puts("  aaaa aa xxx   xxx  eeee  ");
	puts(" aa   aaa  xxx xxx  ee  ee ");
	puts("aa    aa     xxx    eeee   ");
	puts("aa    aa   xxx xxx   ee  ee");
	puts(" aaaaa aa xxx   xxx   eeee ");
	puts("");
	puts("Type \"help\" if you want the help manual.");
	puts("");
	string file = "<NULL>";
	string query = "";
	string object = "";
	string raw = "";
	bool in_object = false;
	axe engine;
	while (true)
	{
		printf(">> ");
		getline(cin, query);	
		if (query == "help")
		{
			puts("< HELP MANUAL >");
			puts(" * help << Help");
			puts(" * new [project-name] << New Project (String)");
			puts(" * open [project-name] << Open Project (String)");
			puts(" * run [project-name] << Run Project (String)");
			puts(" * news [1-5] << News (Integer)");
			puts(" * features << Engine Features");
			puts(" * about << About Engine");
			puts(" * donate << Donate Creator");
			puts(" * quit << Quit Axe");
			puts("< PROJECT ENGINE >");
			puts(" * display [events/properties/objects/variable-name] (String)");
			puts(" * select [object-name] << Select Object (String)");
			puts(" * attach [expression]:[event] << Attach Event (Expression/Event/Integer)");
			puts(" * detach [event-number] << Detach Event (Integer)");
			puts(" * save [project-name] << Save Project (String)");
			puts(" * create [pixel/char/variable] [object-name] << Create Object (String/String)");
			puts(" * set [variable-name] [value] (String/String)");
			puts(" * delete [object-name] (String)");
			puts(" * change [property-name] [value] << Change Property (String/Any)");
			puts(" * exit << Exit Application");
			puts("< PIXEL PROPERTIES >");
			puts(" * x << X Position [Integer(0-15)]");
			puts(" * y << Y Position [Integer(0-15)]");
			puts(" * visible << Is Pixel Visble (Boolean)");
			puts("< CHAR PROPERTIES >");
			puts(" * x << X Position [Integer(0-15)]");
			puts(" * y << Y Position [Integer(0-15)]");
			puts(" * key << Character Key (Character)");
			continue;
		}
		if (query.compare(0, string("new ").length(), "new ") == 0)
		{
			query.replace(0, 4, "");
			vector<bool> checks;
			for (int i = 0; i <= 2; i++)
			{
				checks.push_back(false);
			}
			checks[0] = (query.find("\\") != string::npos or query.find("/") != string::npos or query.find("|") != string::npos);
			checks[1] = (query.find(":") != string::npos or query.find("*") != string::npos or query.find("?") != string::npos);
			checks[2] = (query.find("\"") != string::npos or query.find("<") != string::npos or query.find(">") != string::npos);
			if (checks[0] or checks[1] or checks[2] or query.find("|") != string::npos)
			{
				puts("ERROR: Project Name cannot contains character \\, /, :, *, ?, \", <, > or |.");
				continue;
			}
			engine.pixels.clear();
			engine.chars.clear();
			engine.variables.clear();
			engine.events.clear();
			engine.current_event = -1;
			engine.current_pixel = -1;
			engine.current_char = -1;
			engine.current_variable = -1;
			ifstream check(query + ".axe");
			if (check.is_open())
			{
				check.close();
				puts("Overwrite file? [Y/N]: ");
				string option;
				getline(cin, option);	
				if (option == "n" or option == "N")
				{
					continue;
				}
				else if (option == "y" or option == "Y")
				{
					;
				}
				else
				{
					puts("ERROR: Invalid Option.");
					continue;
				}
			}
			ofstream project(query + ".axe");
			file = query + ".axe";
			project.close();
			continue;
		}
		if (query.compare(0, string("open ").length(), "open ") == 0)
		{
			query.replace(0, 5, "");
			vector<bool> checks;
			for (int i = 0; i <= 2; i++)
			{
				checks.push_back(false);
			}
			checks[0] = (query.find("\\") != string::npos or query.find("/") != string::npos or query.find("|") != string::npos);
			checks[1] = (query.find(":") != string::npos or query.find("*") != string::npos or query.find("?") != string::npos);
			checks[2] = (query.find("\"") != string::npos or query.find("<") != string::npos or query.find(">") != string::npos);
			if (checks[0] or checks[1] or checks[2] or query.find("|") != string::npos)
			{
				puts("ERROR: Project Name cannot contains character \\, /, :, *, ?, \", <, > or |.");
				continue;
			}
			engine.pixels.clear();
			engine.chars.clear();
			engine.variables.clear();
			engine.events.clear();
			engine.current_event = -1;
			engine.current_pixel = -1;
			engine.current_char = -1;
			engine.current_variable = -1;
			ifstream project(query + ".axe");
			if (!project.is_open())
			{
				puts("ERROR: Invalid File.");
				continue;
			}
			vector<string> lines;
			int current_line;
			string line;
			while (project.good())
			{
				getline(project, line);
				lines.push_back(line);
				current_line++;
			}	
			for (auto line : lines)
			{
				engine.read(line);
			}
			project.close();
			file = query + ".axe";
			continue;
		}
		if (query == "donate")
		{
			puts("https://ry2110.itch.io/axe-donate");
			continue;
		}
		if (query.compare(0, string("news ").length(), "news ") == 0)
		{
			query.replace(0, 4, "");
			if (query.find(".") != string::npos)
			{
				puts("ERROR: Invalid Integer.");
				continue;
			}
			try
			{
				int check = stoi(query);
			}
			catch (exception error)
			{
				puts("ERROR: Invalid Integer.");
				continue;
			}
			if (stoi(query) < 1 or stoi(query) > 5)
			{
				puts("ERROR: Integer is Lower than 1 or Higher than 5.");
				continue;
			}
			if (stoi(query) == 1)
			{
				puts("< ALPHA 0.1.0 >");
				puts(" * Created Axe Engine");
				puts(" * Added Pixel, Character, Variable");
				puts(" * Added *.axe Extension");
				puts(" * Added First Type of Application, JIT (Just In Time)");
				puts("NOTES: JIT Applications can run anywhere if you had Axe installed.");
			}
			if (stoi(query) == 2)
			{
				puts("< ALPHA 0.1.1 >");
				puts(" * Fixed some Bugs");
			}
			if (stoi(query) == 3)
			{
				puts("< ALPHA 0.1.2 >");
				puts(" * Fixed some Bugs");
			}
			if (stoi(query) == 4)
			{
				puts("< ALPHA 0.1.3 >");
				puts(" * Fixed some Bugs");
				puts(" * Made Peformace Faster");
			}
			if (stoi(query) == 5)
			{
				puts("< ALPHA 0.1.4 >");
				puts(" * Fixed \"events\" and \"properties\" Option when using \"display\"");
				puts(" * Fixed \"change\"");
			}
			continue;
		}
		if (query.compare(0, string("display ").length(), "display ") == 0)
		{
			if (file == "<NULL>")
			{
				puts("ERROR: Use of \"display\" before \"new\" or \"open\".");
				continue;
			}
			query.replace(0, 8, "");
			if (query == "objects")
			{
				puts("PIXELS:");
				int i = 0;
				for (auto pixel : engine.pixels)
				{
					puts(pixel.first.c_str());
					i++;
				}
				if (i == 0)
				{
					puts("-");
				}
				puts("CHARACTERS:");
				i = 0;
				for (auto _char : engine.chars)
				{
					puts(_char.first.c_str());
					i++;
				}
				if (i == 0)
				{
					puts("-");
				}
				puts("VARIABLES:");
				i = 0;
				for (auto variable : engine.variables)
				{
					puts(variable.first.c_str());
					i++;
				}
				if (i == 0)
				{
					puts("-");
				}
				continue;
			}
			if (query == "events")
			{
				int i = 0;
				for (auto event : engine.events)
				{
					printf("ID: %i\n", i);
					printf("EXPRESSION: %s\n", event.first.c_str());
					printf("ACTION: %s\n", event.second.c_str());
					i++;
				}
				continue;
			}
			if (query == "properties")
			{
				if (object != "")
				{
					string type = "";
					int i = 0;
					for (auto pixel : engine.pixels)
					{
						if (object == pixel.first)
						{
							type = "pixel";
							break;
						}
						i++;
					}
					if (type == "")
					{
						i = 0;
						for (auto _char : engine.chars)
						{
							type = "char";
							break;
						}
						i++;
					}
					if (type == "pixel")
					{
						auto pixel = engine.pixels[i];
						printf("NAME: \"%s\"\n", pixel.first);
						printf("X: %i\n", pixel.second.second.first);
						printf("Y: %i\n", pixel.second.second.second);
						if (pixel.second.first == true)
						{
							printf("VISIBLE: true\n");
						}
						else
						{
							printf("VISIBLE: false\n");
						}
					}
					continue;
				}
				puts("ERROR: Use of \"properties\" before \"select\".");
				continue;
			}
			bool founded = false;
			for (auto variable : engine.variables)
			{
				if (query == variable.first)
				{
					founded = true;
					puts(variable.second.c_str());
					break;
				}
			}
			if (founded == false)
			{
				puts("ERROR: Invalid Pixel/Character/Variable.");
				continue;
			}
			continue;
		}
		if (query.compare(0, string("select ").length(), "select ") == 0)
		{
			if (file == "<NULL>")
			{
				puts("ERROR: Use of \"select\" before \"new\" or \"open\".");
				continue;
			}
			query.replace(0, 7, "");
			bool founded = false;
			for (auto pixel : engine.pixels)
			{
				if (query == pixel.first)
				{
					founded = true;
					break;
				}
			}
			if (founded == false)
			{
				for (auto _char : engine.chars)
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
					continue;
				}
			}
			object = query;
			engine.object = query;
			continue;
		}
		if (query == "deselect")
		{
			if (file == "<NULL>")
			{
				puts("ERROR: Use of \"deselect\" before \"new\" or \"open\".");
				continue;
			}
			if (object == "")
			{
				puts("ERROR: Use of \"deselect\" before \"select\".");
				continue;
			}
			object = "";
			continue;
		}
		if (query.compare(0, string("attach ").length(), "attach ") == 0)
		{
			if (file == "<NULL>")
			{
				puts("ERROR: Use of \"attach\" before \"new\" or \"open\".");
				continue;
			}
			query.replace(0, 7, "");
			string expression = query;
			if (expression.find(":") != string::npos)
			{
				expression.replace(expression.find(":"), expression.length() - expression.find(":"), "");
				string subject;
				string sign;
				string object;
				try
				{
					subject = expression;
					subject.replace(subject.find_first_of(" "), subject.length() - subject.find_first_of(" "), "");
					expression.replace(0, subject.length() + 1, "");
					sign = expression;
					sign.replace(sign.find_first_of(" "), sign.length() - sign.find_first_of(" "), "");
					expression.replace(0, sign.length() + 1, "");
					object = expression;
					query.replace(0, subject.length() + 1 + sign.length() + 1 + object.length() + 1, "");
				}
				catch (exception error)
				{
					puts("ERROR: Syntax Error for \"attach\".");
					continue;
				}
				if (sign != "==" and sign != "!=" and sign != ">" and sign != "<" and sign != ">=" and sign != "<=")
				{
					puts("ERROR: Invalid Sign.");
					continue;
				}	
				string action = query;
				string type;
				string type_2;
				for (auto pixel : engine.pixels)
				{
					if (subject == pixel.first)
					{
						type = "pixel";
						break;
					}
				}
				if (type == "")
				{
					for (auto _char : engine.chars)
					{
						if (subject == _char.first)
						{
							type = "char";
							break;
						}
					}
					if (type == "")
					{
						for (auto variable : engine.variables)
						{
							if (subject == variable.first)
							{
								type = "variable";
								break;
							}
						}
						if (type == "")
						{
							puts("ERROR: Invalid Object/Variable.");
							continue;
						}
					}
				}
				for (auto pixel : engine.pixels)
				{
					if (object == pixel.first)
					{
						type_2 = "pixel";
						break;
					}
				}
				if (type_2 == "")
				{
					for (auto _char : engine.chars)
					{
						if (object == _char.first)
						{
							type_2 = "char";
							break;
						}
					}
					if (type_2 == "")
					{
						for (auto variable : engine.variables)
						{
							if (object == variable.first)
							{
								type_2 = "variable";
								break;
							}
						}
						if (type_2 == "")
						{
							puts("ERROR: Invalid Object/Variable.");
							continue;
						}
					}
				
				}
				if (type == "pixel" and type_2 == "char")
				{
					puts("ERROR: Cannot compare Pixel and Character.");
					continue;
				}
				if (type == "char" and type_2 == "pixel")
				{
					puts("ERROR: Cannot compare Character and Pixel.");
					continue;
				}
				if (type == "pixel" and type_2 == "variable")
				{
					puts("ERROR: Cannot compare Pixel and Variable.");
					continue;
				}
				if (type == "char" and type_2 == "variable")
				{
					puts("ERROR: Cannot compare Character and Variable.");
					continue;
				}
				if (type == "variable" and type_2 == "pixel")
				{
					puts("ERROR: Cannot compare Variable and Pixel.");
					continue;
				}
				if (type == "variable" and type_2 == "char")
				{
					puts("ERROR: Cannot compare Variable and Character.");
					continue;
				}
				engine.current_event++;
				engine.events.push_back(make_pair(subject + " " + sign + " " + object, action));
				printf("EXPRESSION-AND-EVENT-ID: %i\n", engine.current_event);
				continue;
			}
			puts("ERROR: Attach command must had \":\" between Expression and Event.");
			continue;
		}
		if (query.compare(0, string("detach ").length(), "detach ") == 0)
		{
			query.replace(0, 7, "");
			if (file == "<NULL>")
			{
				puts("ERROR: Use of \"detach\" before \"new\" or \"open\".");
				continue;
			}
			try
			{
				int check = stoi(query);
			}
			catch (exception error)
			{
				puts("ERROR: Invalid Integer.");
				continue;
			}
			if (stoi(query) < -1 or stoi(query) > engine.current_event)
			{
				printf("ERROR: Integer is Lower than 0 or Higher than %i.\n", engine.current_event);
				continue;
			}
			engine.events.erase(engine.events.begin() + stoi(query));
			continue;
		}
		if (query.compare(0, string("create ").length(), "create ") == 0)
		{
			query.replace(0,  7, "");
			if (file == "<NULL>")
			{
				puts("ERROR: Use of \"create\" before \"new\" or \"open\".");
				continue;
			}
			string type = query;
			type.replace(type.find_first_of(" "), type.length() - type.find_first_of(" "), "");
			query.replace(0, type.length() + 1, "");
			string name = query;
			if (name.find(" ") != string::npos)
			{
				puts("ERROR: String cannot Contains whitespace(s), Use \"-\" Instead.");
				continue;
			}
			engine.create(type, name);
			continue;
		}
		if (query.compare(0, string("delete ").length(), "delete ") == 0)
		{
			query.replace(0, 7, "");
			if (file == "<NULL>")
			{
				puts("ERROR: Use of \"create\" before \"new\" or \"open\".");
				continue;
			}
			int i = 0;
			bool founded = false;
			for (auto pixel : engine.pixels)
			{
				if (query == pixel.first)
				{
					engine.pixels.erase(engine.pixels.begin() + i);
					founded = true;
					break;
				}
				i++;
			}
			i = 0;
			for (auto _char : engine.chars)
			{
				if (query == _char.first)
				{
					engine.chars.erase(engine.chars.begin() + i);
					founded = true;
					break;
				}
				i++;
			}
			i = 0;
			for (auto variable : engine.variables)
			{
				if (query == variable.first)
				{
					engine.variables.erase(engine.variables.begin() + i);
					founded = true;
					break;
				}
				i++;
			}
			if (founded == false)
			{
				puts("ERROR: Invalid Pixel/Character/Variable.");
			}
			continue;
		}
		if (query.compare(0, string("set ").length(), "set ") == 0)
		{
			query.replace(0, 4, "");
			if (file == "<NULL>")
			{
				puts("ERROR: Use of \"set\" before \"new\" or \"open\".");
				continue;
			}
			int i = 0;
			bool founded = false;
			string name = query;
			name.replace(name.find_first_of(" "), name.length() - name.find_first_of(" "), "");
			query.replace(0, name.length() + 1, "");
			string value = query;
			for (auto variable : engine.variables)
			{
				if (name == variable.first)
				{
					variable = make_pair(variable.first, value);
					engine.variables[i] = variable;
					founded = true;
					break;
				}
				i++;
			}
			if (founded == false)
			{
				puts("ERROR: Invalid Variable.");
			}
			continue;
		}
		if (query.compare(0, string("save").length(), "save") == 0)
		{
			query.replace(0, 5, "");
			ofstream file(query + ".axe");
			string raw;
			raw += "-pxls\n";
			for (auto pixel : engine.pixels)
			{
				string visible = "false";
				if (pixel.second.first == true)
				{
					visible = "true";
				}
				raw += "=" + pixel.first + "\n";
				raw += visible + "\n";
				raw += to_string(pixel.second.second.first) + "\n";
				raw += to_string(pixel.second.second.second) + "\n";
				raw += ";\n";
			}
			raw += ":\n";
			raw += "-chrs\n";
			for (auto _char : engine.chars)
			{
				raw += "=" + _char.first + "\n";
				raw += _char.second.first + "\n";
				raw += to_string(_char.second.second.first) + "\n";
				raw += to_string(_char.second.second.second) + "\n";
				raw += ";\n";
			}
			raw += ":\n";
			raw += "-vrls\n";
			for (auto variable : engine.variables)
			{
				raw += variable.first + ">" + variable.second + "\n";
			}
			raw += ":\n";
			raw += "-evts\n";
			for (auto event : engine.events)
			{
				raw += "=" + event.first + "\n";
				raw += event.second + "\n";
				raw += ";\n";
			}
			raw += ":";
			file << raw;
			file.close();
			continue;
		}
		if (query.compare(0, string("run ").length(), "run ") == 0)
		{
			query.replace(0, 4, "");
			engine.pixels.clear();
			engine.chars.clear();
			engine.variables.clear();
			engine.events.clear();
			engine.current_event = -1;
			engine.current_pixel = -1;
			engine.current_char = -1;
			engine.current_variable = -1;
			ifstream project(query + ".axe");
			if (!project.is_open())
			{
				puts("ERROR: Invalid File.");
				continue;
			}
			vector<string> lines;
			string line;
			while (project.good())
			{
				getline(project, line);
				lines.push_back(line);
			}	
			for (auto line : lines)
			{
				engine.read(line);
			}
			project.close();
			prevents = 0;
			while (true)
			{	
				signal(SIGINT, project_exit);
				int x = 0;
				int y = 0;
				vector<pair<int, int>> pixels_prj;
				vector<pair<char, pair<int, int>>> chars_prj;
				for (auto pixel : engine.pixels)
				{
					if (pixel.second.first == false)
					{
						continue;
					}
					pixels_prj.push_back(make_pair(pixel.second.second.first, pixel.second.second.second));
				}
				for (auto _char : engine.chars)
				{
					chars_prj.push_back(make_pair(_char.second.first, make_pair(_char.second.second.first, _char.second.second.second)));
				}
				if (prevents > 0)
				{
					prevents = 0;
					break;
				}
				for (int h = 0; h <= 5; h++)
				{
					for (int i = 0; i <= 15; i++)
					{
						bool founded = false;
						for (auto pixel : pixels_prj)
						{
							if (pixel.first == x and pixel.second == y)
							{
								founded = true;
								putchar('+');
								break;
							}
						}
						if (founded == true)
						{
							x++;
							continue;
						}
						for (auto _char : chars_prj)
						{
							if (_char.second.first == x and _char.second.second == y)
							{
								founded = true;
								putchar(_char.first);
								break;
							}
						}
						if (founded == false)
						{
							putchar('-');
						}
						x++;
						continue;
					}
					puts("");
					y++;
					continue;
				}
				if (engine.current_event > 0)
				{
					for (int i = 0; i <= 99; i++)
					{
						if (engine.current_event >= i)
						{
							engine.act(i);
							continue;
						}
						break;
					}
				}
				printf("\033[2J\033[1;1H");
			}
			continue;
		}
		if (query.compare(0, string("change ").length(), "change ") == 0)
		{
			engine.run(query);
			continue;
		}
		if (query.compare(0, string("delete ").length(), "delete ") == 0)
		{
			query.replace(0, 7, "");
			bool founded = false;
			int i = 0;
			for (auto pixel : engine.pixels)
			{
				if (query == pixel.first)
				{
					engine.pixels.erase(engine.pixels.begin() + i);
					founded = true;
					break;
				}
				i++;
			}
			if (founded == true)
			{
				continue;
			}
			i = 0;
			for (auto _char : engine.chars)
			{
				if (query == _char.first)
				{
					engine.chars.erase(engine.chars.begin() + i);
					founded = true;
					break;
				}
			}
			if (founded == true)
			{
				continue;
			}
			i = 0;
			for (auto variable : engine.variables)
			{
				if (query == variable.first)
				{
					engine.variables.erase(engine.variables.begin() + i);
				}
				i++;
			}
			if (founded == false)
			{
				puts("ERROR: Invalid Pixel/Character/Variable.");
			}
			continue;
		}
		if (query == "license")
		{
			vector<string> lines;
			string line;
			int i = 0;
			ifstream file("LICENSE.txt");
			if (file.is_open() == false)
			{
				puts("ERROR: Invalid File.");
				continue;
			}
			while (file.good())
			{
				getline(file, line);
				lines.push_back(line);
				i++;
			}
			file.close();
			for (auto line : lines)
			{
				puts(line.c_str());
			}
			continue;
		}
		if (query == "license")
		{
			vector<string> lines;
			string line;
			int i = 0;
			ifstream file("TERMS AND CONDTIONS.txt");
			if (file.is_open() == false)
			{
				puts("ERROR: Invalid File.");
				continue;
			}
			while (file.good())
			{
				getline(file, line);
				lines.push_back(line);
				i++;
			}
			file.close();
			for (auto line : lines)
			{
				puts(line.c_str());
			}
			continue;
		}	
		if (query == "features")
		{
			puts("< FEATURES >");
			puts(" * Easy for Learn Coding");
			puts(" * Color-blind friendly");
			continue;
		}
		if (query == "about")
		{
			puts("< ABOUT >");
			puts(" * Axe 1.0");
			puts(" * Made by Ry");
			continue;
		}
		if (query == "quit")
		{
			break;
		}
		if (query.empty() == true)
		{
			if (prevents > 0)
			{
				break;
			}
			continue;
		}
		puts("ERROR: Invalid Query.");
		continue;
	}
}
