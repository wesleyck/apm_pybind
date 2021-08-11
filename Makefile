CXXFLAGS = -O3 -Wall -shared -std=c++11 -fPIC 
LDFLAGS =  $(shell python3-config -m pybind11 --includes)

CXX_SOURCES = src/test.cc

LIB_SO = hello_test$(shell python3-config --extension-suffix)

$(LIB_SO): $(CXX_SOURCES) $(DEPS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(CXX_SOURCES) -o $(LIB_SO)

clean:
	rm -rf $(LIB_SO)

#g++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) -Iinclude/thire -Llib/webrtc /src/main.cc -o apm$(python3-config --extension-suffix)
#c++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) src/example.cc -o example$(python3-config --extension-suffix)
