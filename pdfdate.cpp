
// c++ -pipe -Os -Wall pdfdate.cpp -o pdfdate -lpoppler-cpp

#include <climits>
#include <cstdlib>
#include <ctime>
#include <poppler/cpp/poppler-document.h>

int main(int argc, char** argv)
{
	using namespace std;
	using namespace poppler;

	if (argc != 2)
	{
		printf("Usage: %s <file>\n", argv[0]);
		exit(EXIT_SUCCESS);
	}

	document* doc = document::load_from_file(argv[1]);
	if (!doc)
	{
		exit(EXIT_FAILURE);
	}

	// try ModificationDate first
	time_t date = doc->get_modification_date();

	if (date == UINT_MAX)
	{
		// no ModificationDate, try CreationDate
		date = doc->get_creation_date();
		if (date == UINT_MAX)
		{
			// no CreationDate either: bail out
			exit(EXIT_FAILURE);
		}
	}

	tm *tmdate = gmtime(&date);
	printf("%s", asctime(tmdate));
	exit(EXIT_SUCCESS);
}

