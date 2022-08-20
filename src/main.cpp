#include "../lib/computorv1.h"

void handleParserError(ParsableString ps)
{
    for (auto i = ps.errors.rbegin(); i != ps.errors.rend(); ++i)
        std::cerr << *i;
}

std::string readFromFile(std::string file)
{
	std::string line;
	std::ifstream in(file);
	if (in.is_open())
		getline(in, line);
	else
	{
		std::cout << "Unable to read file" << std::endl;
		exit(0);
	}
	in.close();

	return line;
}

int     main(int argc, char **argv)
{
    std::string line;

	if (argc < 2)
		return -1;
	else if (strcmp(argv[1], "-f") == 0)
	{
		if (argc < 3)
			return -1;
		line = readFromFile(argv[2]);
	}
	else
		line = argv[1];

    ParsableString parsableString = ParsableString((char*)line.c_str());

    parsableString.parse();
	if (parsableString.errors.size() > 0)
	{
		handleParserError(parsableString);
		return -1;
	}

	PolyPrinter polyPrinter = PolyPrinter(parsableString.polynomial);
	polyPrinter.print();

	return 0;
}
