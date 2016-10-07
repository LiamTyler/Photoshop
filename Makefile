all: brushwork

brushwork: main.o base_gfx_app.o brushwork_app.o color_data.o pixel_buffer.o
	g++ main.o base_gfx_app.o brushwork_app.o color_data.o pixel_buffer.o -o brushwork -std=c++11 -lglut -lGL -lGLU -lglui -L./ext/glui/lib

main.o: src/main.cc
	g++ -c -I. -I./ext/glui/include src/main.cc -std=c++11

brushwork_app.o: src/brushwork_app.cc
	g++ -c -I. -I./ext/glui/include src/brushwork_app.cc -std=c++11

base_gfx_app.o: src/base_gfx_app.cc
	g++ -c -I. -I./ext/glui/include src/base_gfx_app.cc -std=c++11

color_data.o: src/color_data.cc
	g++ -c -I. -I./ext/glui/include src/color_data.cc -std=c++11

pixel_buffer.o: src/pixel_buffer.cc
	g++ -c -I. -I./ext/glui/include src/pixel_buffer.cc -std=c++11

clean:
	rm *o brushwork
