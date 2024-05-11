using namespace std;
using namespace easel;

int main(int argc, char** argv) {
	vector<string> args(argv + 1, argv + argc);

	auto debug_pos = find(args.begin(), args.end(), "--dbg");
	bool debug = debug_pos != args.end();
	if (debug) args.erase(debug_pos);

	if (args.size() > 0) {
		string& location = args[0];
		auto program = util::SlurpPath(location);
		cout << program;
	}
	else {
		// REPL time!
	}

	return 0;
}