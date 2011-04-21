SOURCES := $(shell ls *.cpp)

OBJS := $(SOURCES:.cpp=.o)
all: package-kit

package-kit: $(OBJS)
	$(CXX) $(CFLAGS) -o jsd_builder $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -c $<

clean: 
	rm -f $(OBJS) $(SOURCES:.cpp=.d) jsd_builder
