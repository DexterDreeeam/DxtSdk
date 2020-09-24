#include "ext_logs_interface.hpp"

void _int_files_dummy_func()
{
}

using namespace std;

int main()
{
    outf f = output_file_create("D:/1/2/3/abc.txt");
    outf *pf = &f;

    output_file_write(f, "objk");
    output_file_write(f, "1234");
    output_file_destroy(f);

    log("test %p test  %ull test %d test %s", &f, 123456789, -99999, "okjkljkl");
    err("test %p test  %ull test %d test %s", &f, 123456789, -99999, "okjkljkl");

    return 0;
}
