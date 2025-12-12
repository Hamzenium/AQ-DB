#include <iostream>
#include "storage/KVStore.h"
#include <boost/asio.hpp>
#include "server.h"
int main() {
    KVStore store(8);

    store.set("foo", "bar");
    store.set("name", "Hamza");
    store.set("course", "C++ Systems");

    std::cout << "foo = " << store.get("foo") << std::endl;
    std::cout << "name = " << store.get("name") << std::endl;
    std::cout << "course = " << store.get("course") << std::endl;

    std::string missing = store.get("missing");
    if (missing == "") {
        std::cout << "missing = <not found>" << std::endl;
    }

    bool deleted = store.del("foo");
    std::cout << "delete foo: " << (deleted ? "success" : "failed") << std::endl;
    std::cout << "foo after delete = " << store.get("foo") << std::endl;
    try {
        boost::asio::io_context io;
        server s(io, 6379);

        std::cout << "Async TCP server running on port 6379\n";
        io.run();
    }
    catch (std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
    }
    return 0;
}
