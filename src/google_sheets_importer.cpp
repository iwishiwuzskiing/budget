
#include <boost/p
#include <google_sheets_importer.h>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

std::vector<std::string> read_transactions(std::string & file)
{
    bp::ipstream is; //reading pipe-stream
    bp::child c(bp::search_path("get_transactions.py"), file, bp::std_out > is);

    std::vector<std::string> data;
    std::string line;

    while (c.running() && std::getline(is, line) && !line.empty())
        data.push_back(line);

    c.wait();

    return data;
}
