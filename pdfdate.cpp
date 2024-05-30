
// c++ -pipe -Os -Wall pdfdate.cpp -o pdfdate -lpoppler-cpp

#include <climits>
#include <cstdlib>
#include <ctime>
#include <poppler/cpp/poppler-document.h>

// sanitize a given time_t from UINT_MAX to 0
static inline time_t sanitize(time_t input)
{
	return (input == UINT_MAX ? 0 : input);
}

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

	// Timestamps in many PDF files are frequently broken, with ModificationDate
	// *before* the CreationDate, one of the two values missing or whatever.
	// So all we can do is try our best and use the larger (later) value of the two,
	// after taking into account their possible absence.
	time_t cdate = sanitize(doc->get_creation_date_t());
	time_t mdate = sanitize(doc->get_modification_date_t());
	time_t date = max(cdate, mdate);

	if (date == 0)
	{
		// neither CreationDate nor ModificationDate
		exit(EXIT_FAILURE);
	}

	tm *tmdate = gmtime(&date);
	printf("%s", asctime(tmdate));
	exit(EXIT_SUCCESS);
}

